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

Gc::Gc() : allocSize(0), running(false), marker(0), trace(true), gcSupport(nullptr) {
    lastAllocSize = 1024;
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
    gcRoot.push_back(obj);
}

void Gc::mergeNewAlloc() {
    for (auto it = newAllocRef.begin(); it != newAllocRef.end(); ++it) {
        allRef.insert(*it);
    }
    newAllocRef.clear();
}

GcObj* Gc::alloc(void *type, int asize) {
    int size = asize + sizeof(GcObj);
    if (allocSize + size > lastAllocSize * 1.5) {
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
    newAllocRef.push_back(obj);
    lock.unlock();
    
    if (trace) {
        printf("malloc %p %p\n", type, obj);
    }
    return obj;
}

void Gc::collect() {
    {
        std::lock_guard<std::recursive_mutex> lock_guard(lock);
        if (running) {
            return;
        }
        running = true;
        mergeNewAlloc();
        marker = !marker;
    }
    
    getRoot();
    
    mark();
    
    puaseWorld();
    while (remark()) {}
    resumeWorld();
    
    sweep();
    
    {
        std::lock_guard<std::recursive_mutex> lock_guard(lock);
        lastAllocSize = allocSize;
        running = false;
    }
}

void Gc::getRoot() {
    gcRoot.clear();
    
    puaseWorld();
    
    lock.lock();
    for (auto it = pinObjs.begin(); it != pinObjs.end(); ++it) {
        gcRoot.push_back(*it);
    }
    lock.unlock();
    
    gcSupport->walkRoot(this);
    
    if (trace) {
        printf("ROOT:\n");
        for (auto it = gcRoot.begin(); it != gcRoot.end(); ++it) {
            gcSupport->printObj(*it);
            printf(", ");
        }
        printf("\n");
    }
    resumeWorld();
}

void Gc::mark() {
    for (auto it = gcRoot.begin(); it != gcRoot.end(); ++it) {
        markNode(*it);
    }
}

bool Gc::remark() {
    bool has = false;
    for (auto it = allRef.begin(); it != allRef.end(); ++it) {
        GcObj* obj = *it;
        if (gc_isDirty(obj)) {
            has = true;
            markNode(obj);
        }
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

void Gc::markNode(GcObj* obj) {
    if (obj == nullptr) {
        return;
    }
    if (!gc_isDirty(obj) && gc_getMark(obj) == marker) {
        return;
    }
    gc_setMark(obj, marker);
    gc_setDirty(obj, 0);
    gcSupport->walkNodeChildren(this, obj);
}
