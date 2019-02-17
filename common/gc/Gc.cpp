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
    , maxAddress(NULL), minAddress(NULL){
    lastAllocSize = 29;
    collectSize = 10000;
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
    if (obj == nullptr) {
        return;
    }
    if (allRef.find(obj) == allRef.end()) {
        //printf("ERROR:");
        //gcSupport->printObj(obj);
        //printf("\n");
        return;
    }
    tempGcRoot.push_back(obj);
}

void Gc::mergeNewAlloc() {
    for (auto it = newAllocRef.begin(); it != newAllocRef.end(); ++it) {
        allRef.insert(*it);
    }
    newAllocRef.clear();
}

GcObj* Gc::alloc(void *type, int asize) {
    int size = asize + sizeof(GcObj);
    if (allocSize > collectSize && allocSize + size > lastAllocSize * 1.5) {
        collect();
    } else {
        lastAllocSize -= 8;
    }
    
    GcObj* obj = (GcObj*)calloc(1, size);
    if (obj == NULL) {
        collect();
        obj = (GcObj*)calloc(1, size);
    }
    
    assert(obj);
    obj->header = type;
    gc_setMark(obj, marker);
    gc_setDirty(obj, 0);
    
    lock.lock();
    if (maxAddress == NULL || obj > maxAddress) {
        maxAddress = obj;
    }
    if (minAddress == NULL || obj < minAddress) {
        minAddress = obj;
    }
    newAllocRef.push_back(obj);
    lock.unlock();
    
    if (trace) {
        printf("malloc ");
        gcSupport->printObj(obj);
        printf("\n");
    }
    return obj;
}

void Gc::collect() {
    gcSupport->onStartGc();
    {
        std::lock_guard<std::recursive_mutex> lock_guard(lock);
        if (running) {
            return;
        }
        running = true;
        mergeNewAlloc();
        marker = !marker;
    }
    
    //get root
    puaseWorld(true);
    getRoot();
    
    //concurrent mark
    resumeWorld();
    mark(tempGcRoot, &tempArrived);
    
    //remark changed
    puaseWorld(false);
    mark(tempArrived, NULL);
    
    //remark root
    puaseWorld(true);
    getRoot();
    mark(tempArrived, NULL);
    
    //concurrent sweep
    resumeWorld();
    sweep();
    
    {
        std::lock_guard<std::recursive_mutex> lock_guard(lock);
        lastAllocSize = allocSize;
        running = false;
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

bool Gc::mark(std::vector<GcObj*> &root, std::vector<GcObj*> *arrived) {
    bool has = false;
    std::vector<GcObj*> &list = root;
    if (arrived) arrived->clear();
    while (list.size() > 0) {
        GcObj *obj = list.back();
        list.pop_back();
        if (markNode(obj)) {
            has = true;
            gcSupport->getNodeChildren(this, obj, &list);
        }
        if (arrived) arrived->push_back(obj);
    }
    return has;
}

void Gc::sweep() {
    for (auto it = allRef.begin(); it != allRef.end();) {
        GcObj* obj = *it;
        if (gc_getMark(obj) != marker) {
            remove(obj, it);
        } else {
            ++it;
        }
    }
}

void Gc::remove(GcObj* obj, std::set<GcObj*>::iterator &it) {
    
    int size = gcSupport->allocSize(gc_getType(obj));
    allocSize -= size;
    
    it = allRef.erase(it);
    gcSupport->finalizeObj(obj);
    
    if (trace) {
        printf("free ");
        gcSupport->printObj(obj);
        printf("\n");
    }
    
    obj->header = nullptr;
    free(obj);
}

bool Gc::markNode(GcObj* obj) {
    if (obj == nullptr) {
        return false;
    }
    if (allRef.find(obj) == allRef.end()) {
        //printf("ERROR: unknow obj %p", obj);
        return false;
    }
    if (!gc_isDirty(obj) && gc_getMark(obj) == marker) {
        return false;
    }
    gc_setMark(obj, marker);
    gc_setDirty(obj, 0);
//    printf("mark %d:", marker);
//    gcSupport->printObj(obj);
//    if (gc_getMark(obj) != marker) {
//        printf("ERROR");
//    }
    return true;
}
