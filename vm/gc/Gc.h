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


class Gc;

class GcSupport {
public:
    virtual void getNodeChildren(Gc *gc, GcObj *obj, std::vector<GcObj*> *list) = 0;
    virtual void walkRoot(Gc *gc) = 0;
    virtual void onStartGc() = 0;
    
    virtual void finalizeObj(GcObj *obj) = 0;
    virtual void puaseWorld(bool bloking) = 0;
    virtual void resumeWorld() = 0;
    virtual void printObj(GcObj *obj) = 0;
    virtual int allocSize(void *type) = 0;
};

class Gc {
    std::list<GcObj*> pinObjs;
    std::vector<GcObj*> newAllocRef;
    std::set<GcObj*> allRef;
    
    std::vector<GcObj*> tempGcRoot;
    std::vector<GcObj*> tempArrived;
    
    std::recursive_mutex lock;
    bool isStopWorld;
    int marker;
    bool running;
public:
    GcSupport *gcSupport;
    int lastAllocSize;
    int allocSize;
    bool trace;
    
    GcObj *maxAddress;
    GcObj *minAddress;
    
    Gc();
    ~Gc();
    
    GcObj* alloc(void *type, int size);
    
    void pinObj(GcObj* obj);
    void unpinObj(GcObj* obj);
    
    void onRoot(GcObj* obj);
 
    void collect();
    
private:
    void puaseWorld(bool bloking) {
        isStopWorld = true;
        gcSupport->puaseWorld(bloking);
    }
    
    void resumeWorld() {
        gcSupport->resumeWorld();
        isStopWorld = false;
    }
    
    void mergeNewAlloc();
    bool mark(std::vector<GcObj*> &root, std::vector<GcObj*> *arrived);
    void getRoot();
    void sweep();
//    bool remark();
    void remove(GcObj* obj, std::set<GcObj*>::iterator &it);
    
    bool markNode(GcObj* obj);
};

#endif /* Gc_hpp */
