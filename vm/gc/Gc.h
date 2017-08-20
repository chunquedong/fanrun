//
//  Gc.hpp
//  vm
//
//  Created by yangjiandong on 10/25/15.
//  Copyright © 2015 chunquedong. All rights reserved.
//

#ifndef Gc_hpp
#define Gc_hpp

#include <stdio.h>
#include "vm.h"
#include <list>
#include <vector>
#include <set>
#include "tinycthread.h"

class Gc;

class GcSupport {
public:
    virtual void walkNodeChildren(Gc *gc, FObj* obj) = 0;
    virtual void walkRoot(Gc *gc) = 0;
    
    virtual void finalizeObj(FObj* obj) = 0;
    virtual void puaseWorld() = 0;
    virtual void resumeWorld() = 0;
};

class Gc {
    std::list<FObj*> pinObjs;
    std::vector<FObj*> newAllocRef;
    
    std::vector<FObj*> gcRoot;
    std::set<FObj*> allRef;
    
    mtx_t lock;
    bool isStopWorld;
    int marker;
    bool running;
public:
    GcSupport *gcSupport;
    int lastAllocSize;
    int allocSize;
    bool trace;
    
    Gc();
    ~Gc();
    
    FObj* alloc(fr_Env env, FType *type, int size);
    
    void pinObj(FObj* obj);
    void unpinObj(FObj* obj);
    
    void onRoot(FObj* obj);
    void onChild(FObj* obj) {
        markNode(obj);
    }
 
    void collect();
    
private:
    void puaseWorld() {
        isStopWorld = true;
        gcSupport->puaseWorld();
    }
    
    void resumeWorld() {
        gcSupport->resumeWorld();
        isStopWorld = false;
    }
    
    void mergeNewAlloc();
    void mark();
    void getRoot();
    void sweep();
    bool remark();
    void remove(FObj* obj, std::set<FObj*>::iterator &it);
    
    void markNode(FObj* obj);
};

#endif /* Gc_hpp */
