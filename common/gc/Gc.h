//
//  Gc.hpp
//  vm
//
//  Created by yangjiandong on 10/25/15.
//  Copyright © 2015 chunquedong. All rights reserved.
//

#ifndef Gc_hpp
#define Gc_hpp

#include "gcobj.h"

#include <stdio.h>
//#include "vm.h"
#include <list>
#include <vector>
#include <set>
#include <mutex>
#include <map>
#include "Bitmap.hpp"

#define GC_USE_BITMAP 1

class Gc;

class GcSupport {
public:
    virtual void visitChildren(Gc *gc, GcObj *obj) = 0;
    virtual void walkRoot(Gc *gc) = 0;
//    virtual void walkDirtyList(Gc *gc) = 0;
    virtual void onStartGc() = 0;
    
    virtual void finalizeObj(GcObj *obj) = 0;
    virtual void puaseWorld(bool bloking) = 0;
    virtual void resumeWorld() = 0;
    virtual void printObj(GcObj *obj) = 0;
    virtual int allocSize(void *type) = 0;
};

class Gc {
    std::list<GcObj*> pinObjs;

#if GC_USE_BITMAP
    Bitmap allRefs;
#else
    std::map<void *, bool> allRefs;
#endif
    std::vector<GcObj*> markStack;
    
    std::vector<GcObj*> dirtyList;
    
    std::recursive_mutex lock;
    bool isStopWorld;
    int marker;
    bool running;
public:
    GcSupport *gcSupport;
    
    long collectLimit;
    long lastAllocSize;
    long allocSize;
    bool trace;
    
public:
#if GC_USE_BITMAP
    bool isRef(void *p) {
        //lock.lock();
        bool found = allRefs.getPtr(p);
        //lock.unlock();
        return found;
    }
#else
    bool isRef(void *p) {
        //lock.lock();
        bool found = allRefs.find(p) != allRefs.end();
        //lock.unlock();
        return found;
    }
#endif

public:
    Gc();
    ~Gc();
    
    GcObj* alloc(void *type, int size);
    
    void pinObj(GcObj* obj);
    void unpinObj(GcObj* obj);
    
    void onVisit(GcObj* obj);
 
    void collect();
    
    void setDirty(GcObj *obj);
    
private:
    void puaseWorld(bool bloking) {
        isStopWorld = true;
        gcSupport->puaseWorld(bloking);
    }
    
    void resumeWorld() {
        gcSupport->resumeWorld();
        isStopWorld = false;
    }
    
    void beginGc();
    void endGc();
    
    //void mergeNewAlloc();
    bool mark();
    void getRoot();
    void sweep();
//    bool remark();
    void remove(GcObj* obj);
    
    bool markNode(GcObj* obj);
};

#endif /* Gc_hpp */
