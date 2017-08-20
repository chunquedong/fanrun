//
//  FVM.h
//  vm
//
//  Created by yangjiandong on 15/9/27.
//  Copyright (c) 2015, yangjiandong. All rights reserved.
//

#ifndef __vm__FVM__
#define __vm__FVM__

#include <stdio.h>
#include "PodManager.h"
#include "vm.h"
#include "Gc.h"
#include <unordered_map>
#include <thread>
#include "LinkedList.h"
#include "../vm/ExeEngine.h"

class Env;

class Fvm : public GcSupport {
    std::unordered_map<std::thread::id, Env*> threads;
    LinkedList globalRefList;
    std::vector<fr_Obj> staticFieldRef;
    mtx_t lock;
public:
    Gc gc;
    PodManager *podManager;
    ExeEngine *executeEngine;
public:
    Fvm(PodManager *podManager);
    ~Fvm();
    
    void start();
    void stop();
    
    Env *getEnv();
    void releaseEnv(Env *env);
    
    void registerMethod(const char *name, fr_NativeFunc func);
    
    virtual void walkNodeChildren(Gc *gc, FObj* obj);
    virtual void walkRoot(Gc *gc);
    virtual void finalizeObj(FObj* obj);
    virtual void puaseWorld();
    virtual void resumeWorld();
    
    fr_Obj newGlobalRef(FObj * obj);
    void deleteGlobalRef(fr_Obj obj);
    void addStaticRef(fr_Obj obj);
};

#endif /* defined(__vm__FVM__) */
