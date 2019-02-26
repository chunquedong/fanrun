//
//  Gc.cpp
//  vm
//
//  Created by yangjiandong on 10/25/15.
//  Copyright © 2015 chunquedong. All rights reserved.
//

#include "Gc.h"
#include <atomic>
#include <stdlib.h>
//#include "FType.h"
#include <assert.h>

Gc::Gc() : allocSize(0), running(false), marker(0), trace(true), gcSupport(nullptr)
    {
    lastAllocSize = 29;
    collectLimit = 1000;
    allRefHead = NULL;
}

Gc::~Gc() {
}

void Gc::pinObj(GcObj* obj) {
    std::lock_guard<std::recursive_mutex> lock_guard(lock);
    pinObjs.push_back(obj);
}
void Gc::unpinObj(GcObj* obj) {
    std::lock_guard<std::recursive_mutex> lock_guard(lock);
    pinObjs.remove(obj);
}
void Gc::onRoot(GcObj* obj) {
    if (obj == NULL) {
        return;
    }
    tempGcRoot.push_back(obj);
}

GcObj* Gc::alloc(void *type, int asize) {
    //int size = asize + sizeof(GcObj);
    int size = asize;
    if (allocSize > collectLimit && allocSize + size > lastAllocSize * 2) {
        collect();
    } else {
        lastAllocSize -= 1;
    }
    
    GcObj* obj = (GcObj*)calloc(1, size);
    if (obj == NULL) {
        collect();
        obj = (GcObj*)calloc(1, size);
    }
    
    assert(obj);
    obj->type = type;
    gc_setMark(obj, marker);
    gc_setDirty(obj, 1);
    
    lock.lock();

    gc_setNext(obj, this->allRefHead);
    allRefHead = obj;
    //newAllocRef.push_back(obj);
    allocSize += size;
#ifdef GC_REF_TABLE
    allRefs.insert(obj);
#endif
    
    lock.unlock();
    
    if (trace) {
        printf("malloc ");
        gcSupport->printObj(obj);
        printf("\n");
    }
    return obj;
}

void Gc::collect() {
    if (trace) {
        printf("******* start gc: %ld (%ld, %ld)\n", allocSize, collectLimit, lastAllocSize);
    }
    
    //ready for gc
    gcSupport->onStartGc();
    {
        std::lock_guard<std::recursive_mutex> lock_guard(lock);
        if (running) {
            return;
        }
        running = true;
        //mergeNewAlloc();
        marker = !marker;
    }
    
    //get root
    puaseWorld(true);
    getRoot();
    
    resumeWorld();
    //concurrent mark
    mark();
    
    //remark root
    puaseWorld(true);
    getRoot();
    
    //remark changed
    mark();
    
    //concurrent sweep
    resumeWorld();
    sweep();
    
    {
        std::lock_guard<std::recursive_mutex> lock_guard(lock);
        lastAllocSize = allocSize;
        running = false;
    }
    
    if (trace) {
        printf("******* end gc: %ld\n", allocSize);
    }
}

void Gc::getRoot() {
    tempGcRoot.clear();
    lock.lock();
    for (auto it = pinObjs.begin(); it != pinObjs.end(); ++it) {
        tempGcRoot.push_back(*it);
    }
    lock.unlock();
    
    gcSupport->walkRoot(this);
    
    if (trace) {
        printf("ROOT:\n");
        for (auto it = tempGcRoot.begin(); it != tempGcRoot.end(); ++it) {
            gcSupport->printObj(*it);
            printf(", ");
        }
        printf("\n");
    }
}

bool Gc::mark() {
    std::list<GcObj*> visitQueue;
    for (int i=0; i<tempGcRoot.size(); ++i) {
        visitQueue.push_back(tempGcRoot[i]);
    }
    
    while (visitQueue.size() > 0) {
        GcObj *obj = visitQueue.front();
        visitQueue.pop_front();
        if (markNode(obj)) {
            gcSupport->getNodeChildren(this, obj, &visitQueue);
        }
    }
    return true;
}

void Gc::sweep() {
    GcObj *obj = allRefHead;
    GcObj *pre = NULL;
    while (obj) {
        GcObj *next = (GcObj*)gc_getNext(obj);
        if (gc_getMark(obj) != marker) {
            remove(obj);
            if (pre == NULL) {
                allRefHead = next;
            }
            else {
                gc_setNext(pre, next);
            }
            obj = next;
        }
        else {
            pre = obj;
            obj = next;
        }
    }
}

void Gc::remove(GcObj* obj) {
    
    int size = gcSupport->allocSize(gc_getType(obj));
    
    gcSupport->finalizeObj(obj);
    
    if (trace) {
        printf("free ");
        gcSupport->printObj(obj);
        printf("\n");
    }
    
    lock.lock();
    allocSize -= size;
#ifdef GC_REF_TABLE
    allRefs.erase(obj);
#endif
    lock.unlock();
    
    obj->type = NULL;
    obj->next = NULL;
    free(obj);
}

bool Gc::markNode(GcObj* obj) {
    if (obj == NULL) {
        return false;
    }

    if (!gc_isDirty(obj) && gc_getMark(obj) == marker) {
        return false;
    }
    gc_setMark(obj, marker);
    gc_setDirty(obj, 0);

    return true;
}
