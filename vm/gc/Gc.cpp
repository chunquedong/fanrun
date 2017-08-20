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
#include "FType.h"
#include <assert.h>

Gc::Gc() : allocSize(0), running(false), marker(0), trace(true), gcSupport(nullptr) {
    mtx_init(&lock, mtx_recursive);
    lastAllocSize = 1024;
}

Gc::~Gc() {
    mtx_destroy(&lock);
}

void Gc::pinObj(FObj* obj) {
    mtx_lock(&lock);
    pinObjs.push_back(obj);
    mtx_unlock(&lock);
}
void Gc::unpinObj(FObj* obj) {
    mtx_lock(&lock);
    pinObjs.remove(obj);
    mtx_unlock(&lock);
}
void Gc::onRoot(FObj* obj) {
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

FObj* Gc::alloc(fr_Env env, FType *type, int size) {
    
    if (allocSize + size > lastAllocSize * 1.5) {
        collect();
    } else {
        lastAllocSize -= 8;
    }
    
    FObj* obj = (FObj*)calloc(1, size);
    if (obj == NULL) {
        collect();
        obj = (FObj*)calloc(1, size);
    }
    
    assert(obj);
    
    obj->dirty = false;
    obj->mark = marker;
    obj->type = type;
    
    mtx_lock(&lock);
    newAllocRef.push_back(obj);
    mtx_unlock(&lock);
    
    if (trace) {
        printf("malloc %s %p\n", type->c_name.c_str(), obj);
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

void printValue(fr_TagValue *val);

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
            fr_TagValue val;
            val.type = fr_vtObj;
            val.any.o = *it;
            printValue(&val);
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
        FObj* obj = *it;
        if (obj->dirty) {
            has = true;
            markNode(obj);
        }
    }
    return has;
}

void Gc::sweep() {
    for (auto it = allRef.begin(); it != allRef.end();) {
        FObj* obj = *it;
        if (obj->mark != marker) {
            remove(obj, it);
        } else {
            ++it;
        }
    }
}

void Gc::remove(FObj* obj, std::set<FObj*>::iterator &it) {
    
    int size = obj->type->c_allocSize;
    allocSize -= size;
    
    it = allRef.erase(it);
    gcSupport->finalizeObj(obj);
    
    if (trace) {
        printf("free %s %p\n", obj->type->c_name.c_str(), obj);
    }
    
    obj->type = nullptr;
    free(obj);
}

void Gc::markNode(FObj* obj) {
    if (obj == nullptr) {
        return;
    }
    if (!obj->dirty && obj->mark == marker) {
        return;
    }
    obj->dirty = false;
    obj->mark = marker;
    gcSupport->walkNodeChildren(this, obj);
}
