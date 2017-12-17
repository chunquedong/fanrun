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
    mtx_init(&lock, mtx_recursive);
    lastAllocSize = 1024;
}

Gc::~Gc() {
    mtx_destroy(&lock);
}

void Gc::pinObj(GcObj* obj) {
    mtx_lock(&lock);
    pinObjs.push_back(obj);
    mtx_unlock(&lock);
}
void Gc::unpinObj(GcObj* obj) {
    mtx_lock(&lock);
    pinObjs.remove(obj);
    mtx_unlock(&lock);
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
    int size = gcSupport->allocSize(type);
    if (size < asize) {
        size = asize;
    }
    
    size = size + sizeof(GcObj);
    
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
    
    mtx_lock(&lock);
    newAllocRef.push_back(obj);
    mtx_unlock(&lock);
    
    if (trace) {
        printf("malloc %p %p\n", type, obj);
    }
    return obj;
}

void Gc::collect() {
    {
        mtx_lock(&lock);
        if (running) {
            mtx_unlock(&lock);
            return;
        }
        running = true;
        mergeNewAlloc();
        marker = !marker;
        mtx_unlock(&lock);
    }
    
    getRoot();
    
    mark();
    
    puaseWorld();
    while (remark()) {}
    resumeWorld();
    
    sweep();
    
    {
        mtx_lock(&lock);
        lastAllocSize = allocSize;
        running = false;
        mtx_unlock(&lock);
    }
}

void Gc::getRoot() {
    gcRoot.clear();
    
    puaseWorld();
    
    mtx_lock(&lock);
    for (auto it = pinObjs.begin(); it != pinObjs.end(); ++it) {
        gcRoot.push_back(*it);
    }
    mtx_unlock(&lock);
    
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
