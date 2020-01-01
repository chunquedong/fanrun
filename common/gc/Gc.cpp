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
//#include "BitmapTest.h"

Gc::Gc() : allocSize(0), running(false), marker(0), trace(true), gcSupport(nullptr)
    {
    lastAllocSize = 29;
    collectLimit = 1000;
#if GC_USE_BITMAP
    //pass
#else
    //allRefs = NULL;
#endif
    //BitmapTest_run();
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
void Gc::onVisit(GcObj* obj) {
    if (obj == NULL) {
        return;
    }
    if (!isRef(obj)) {
        abort();
    }
    markStack.push_back(obj);
}

void Gc::setDirty(GcObj *obj) {
    std::lock_guard<std::recursive_mutex> lock_guard(lock);
    dirtyList.push_back(obj);
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
    //gc_setDirty(obj, 1);
    
    lock.lock();
#if GC_USE_BITMAP
    allRefs.putPtr(obj, true);
#else
    //gc_setNext(obj, this->allRefs);
    //allRefs = obj;
    //allRefs.insert(obj);
    allRefs[obj] = true;
#endif
    //newAllocRef.push_back(obj);
    allocSize += size;
    
    lock.unlock();
    
    if (trace) {
        printf("malloc ");
        gcSupport->printObj(obj);
        printf("\n");
    }
    return obj;
}

void Gc::beginGc() {
    std::lock_guard<std::recursive_mutex> lock_guard(lock);
    if (running) {
        return;
    }
    running = true;
    //mergeNewAlloc();
    marker = !marker;
}
void Gc::endGc() {
    std::lock_guard<std::recursive_mutex> lock_guard(lock);
    lastAllocSize = allocSize;
    running = false;
}

void Gc::collect() {
    if (trace) {
        printf("******* start gc: memory:%ld (limit:%ld, last:%ld)\n", allocSize, collectLimit, lastAllocSize);
    }
    long beginSize = allocSize;
    
    //ready for gc
    gcSupport->onStartGc();
    beginGc();
    
    //get root
    puaseWorld(true);
    getRoot();
    
    resumeWorld();
    //concurrent mark
    mark();
    mark();
    
    //remark root
    puaseWorld(true);
    //gcSupport->walkDirtyList(this);
    
    //remark changed
    mark();
    
    //concurrent sweep
    resumeWorld();
    sweep();
    
    endGc();
    
    if (trace) {
        printf("******* end gc: memory:%ld, free:%ld\n", allocSize, beginSize - allocSize);
    }
}

void Gc::getRoot() {
    markStack.clear();
    lock.lock();
    for (auto it = pinObjs.begin(); it != pinObjs.end(); ++it) {
        markStack.push_back(*it);
    }
    lock.unlock();
    
    gcSupport->walkRoot(this);
    
    if (trace) {
        printf("ROOT:\n");
        for (auto it = markStack.begin(); it != markStack.end(); ++it) {
            gcSupport->printObj(*it);
            printf(", ");
        }
        printf("\n");
    }
}

bool Gc::mark() {
    if (markStack.size() == 0) {
        lock.lock();
        markStack.swap(dirtyList);
        lock.unlock();
    }
    
    while (markStack.size() > 0) {
        GcObj *obj = markStack.back();
        markStack.pop_back();
        if (markNode(obj)) {
            gcSupport->visitChildren(this, obj);
        }
    }
    return true;
}

void Gc::sweep() {
#if GC_USE_BITMAP
    uint64_t pos = 0;
    while (true) {
        GcObj *obj = (GcObj*)allRefs.nextPtr(pos);
        if (!obj) break;
        if (gc_getMark(obj) != marker) {
            remove(obj);
        }
    }
#else
    lock.lock();
    for (auto itr = allRefs.begin(); itr != allRefs.end();) {
        GcObj *obj = (GcObj*)(itr->first);
        if (!obj) break;
        if (gc_getMark(obj) != marker) {
            remove(obj);
            itr = allRefs.erase(itr);
        }
        else {
            ++itr;
        }
    }
    lock.unlock();
//    GcObj *pre = NULL;
//    while (obj) {
//        GcObj *next = (GcObj*)gc_getNext(obj);
//        if (gc_getMark(obj) != marker) {
//            remove(obj);
//            if (pre == NULL) {
//                allRefLink = next;
//            }
//            else {
//                gc_setNext(pre, next);
//            }
//            obj = next;
//        }
//        else {
//            pre = obj;
//            obj = next;
//        }
//    }
#endif
    
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
#if GC_USE_BITMAP
    allRefs.putPtr(obj, false);
#else
    //
#endif
    lock.unlock();
    
    obj->type = NULL;
    //obj->next = NULL;
    free(obj);
}

bool Gc::markNode(GcObj* obj) {
    if (obj == NULL) {
        return false;
    }

    if (gc_getMark(obj) == marker) {
        return false;
    }
    gc_setMark(obj, marker);
    //gc_setDirty(obj, 0);

    return true;
}
