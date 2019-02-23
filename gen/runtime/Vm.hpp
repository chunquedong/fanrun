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
#include <map>
#include <thread>
#include <string>
#include <set>

class Env;

class Vm : public GcSupport {
    Gc *gc;
    //std::vector<GcObj*> globalRef;
    std::unordered_map<std::thread::id, Env*> threads;
    std::vector<fr_Obj*> staticFieldRef;
    std::recursive_mutex lock;
    //typedef std::unordered_map<std::string, std::unordered_map<std::string, fr_Class> > ClassMap;
    typedef std::map<std::string, fr_Class> ClassMap;
    typedef std::map<std::string, ClassMap > PodMap;
    PodMap typeDb;
public:
    std::set<fr_Class> classSet;
public:
    Vm();
    ~Vm();
    
    void registerClass(const char *pod, const char *clz, fr_Class type);
    fr_Class findClass(const char *pod, const char *clz);
    
    void start();
    void stop();
    
    Gc *getGc() { return gc; }
    Env *getEnv();
    void releaseEnv(Env *env);
    void addStaticRef(fr_Obj *obj);
    
    virtual void getNodeChildren(Gc *gc, GcObj *obj, std::list<GcObj*> *list) override;
    virtual void walkRoot(Gc *gc) override;
    virtual void onStartGc() override;
    virtual void finalizeObj(GcObj *obj) override;
    virtual void puaseWorld(bool bloking) override;
    virtual void resumeWorld() override;
    virtual void printObj(GcObj *obj) override;
    virtual int allocSize(void *type) override;
};

#endif /* Vm_hpp */
