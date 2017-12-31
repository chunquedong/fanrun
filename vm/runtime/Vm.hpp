//
//  Vm.hpp
//  vm
//
//  Created by yangjiandong on 2017/12/31.
//  Copyright © 2017年 yangjiandong. All rights reserved.
//

#ifndef Vm_hpp
#define Vm_hpp

#include "Gc.h"
#include <assert.h>
#include <vector>
#include <stdio.h>
#include "runtime.h"
#include <unordered_map>
#include <thread>

class Env;

class Vm : public GcSupport {
    Gc *gc;
    std::vector<GcObj*> globalRef;
    std::unordered_map<std::thread::id, Env*> threads;
    std::vector<GcObj*> staticFieldRef;
    std::recursive_mutex lock;
public:
    Vm();
    ~Vm();
    
    void start();
    void stop();
    
    Gc *getGc() { return gc; }
    Env *getEnv();
    void releaseEnv(Env *env);
    void addStaticRef(fr_Obj obj);
    
    virtual void walkNodeChildren(Gc *gc, GcObj *obj) override;
    virtual void walkRoot(Gc *gc) override;
    virtual void finalizeObj(GcObj *obj) override;
    virtual void puaseWorld() override;
    virtual void resumeWorld() override;
    virtual void printObj(GcObj *obj) override;
    virtual int allocSize(void *type) override;
};

#endif /* Vm_hpp */
