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
#include <thread>


#define GC_USE_BITMAP 0

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
    bool isMarking;
    std::thread *gcThread;
    std::mutex cdLock;
    std::condition_variable condition;
public:
    GcSupport *gcSupport;
    
    long collectLimit;
    long lastAllocSize;
    long allocSize;
    int trace;
    
public:

    Gc();
    ~Gc();
    
    bool isRef(void *p);
    
    GcObj* alloc(void *type, int size);
    
    void pinObj(GcObj* obj);
    void unpinObj(GcObj* obj);
    
    void onVisit(GcObj* obj);
 
    void collect();
    
    void setDirty(GcObj *obj);
    
    void gcThreadRun();
    
private:
    void setMarking(bool m);
    void doCollect();
    
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
