//
//  Vm.cpp
//  vm
//
//  Created by yangjiandong on 2017/12/31.
//  Copyright © 2017年 yangjiandong. All rights reserved.
//

#include "Vm.hpp"
#include "Env.hpp"
#include "system.h"

Vm::Vm() {
    gc = new Gc();
    gc->gcSupport = this;
}

Vm::~Vm() {
}

void Vm::start() {
    
}
void Vm::stop() {
}

Env *Vm::getEnv() {
    std::lock_guard<std::recursive_mutex> lock_guard(lock);
    
    std::thread::id tid = std::this_thread::get_id();
    auto found = threads.find(tid);
    Env *env;
    if (found != threads.end()) {
        env = found->second;
    } else {
        env = new Env(this);
        threads[tid] = env;
    }
    return env;
}

void Vm::releaseEnv(Env *env) {
    std::lock_guard<std::recursive_mutex> lock_guard(lock);
    
    std::thread::id tid = std::this_thread::get_id();
    threads.erase(tid);
    delete env;
}

void Vm::getNodeChildren(Gc *gc, GcObj *gcobj, std::list<GcObj*> *list) {
    fr_Obj obj = fr_fromGcObj(gcobj);
    fr_Class type = (fr_Class)gc_getType(gcobj);
    for (int i=0; i<type->fieldCount; ++i) {
        fr_Field &f = type->fieldList[i];
        if (!f.isStatic && !f.isValType) {
            fr_Obj* objAddress = (fr_Obj*)(((char*)(obj)) + f.offset);
            if (*objAddress == NULL) continue;
            GcObj *gp = fr_toGcObj(*objAddress);
            list->push_back(gp);
        }
    }
}

void Vm::walkRoot(Gc *gc) {
    //static field
    for (auto it = staticFieldRef.begin(); it != staticFieldRef.end(); ++it) {
        fr_Obj *obj = *it;
        if (*obj == NULL) continue;
        GcObj *gobj = fr_toGcObj(*obj);
        gc->onRoot(gobj);
    }
    
    //local
    for (auto it = threads.begin(); it != threads.end(); ++it) {
        Env *env = it->second;
        env->walkLocalRoot(gc);
    }
}

void Vm::finalizeObj(GcObj *gcobj) {
    //fr_Obj obj = fr_fromGcObj(gcobj);
    //fr_Class type = (fr_Class)gc_getType(gcobj);
    //printf("release %s %p\n", type->name, obj);
}

void Vm::onStartGc() {
    void *statckVar = 0;
    //set statckEnd address
    std::thread::id tid = std::this_thread::get_id();
    for (auto it = threads.begin(); it != threads.end(); ++it) {
        Env *env = it->second;
        //is current thread
        if (it->first == tid) {
            env->statckEnd = &statckVar;
            continue;
        }
    }
}

void Vm::puaseWorld(bool bloking) {
    for (auto it = threads.begin(); it != threads.end(); ++it) {
        Env *env = it->second;
        env->needStop = true;
    }
    System_barrier();
    if (bloking) {
        std::thread::id tid = std::this_thread::get_id();
        for (auto it = threads.begin(); it != threads.end(); ++it) {
            Env *env = it->second;
            //is current thread
            if (it->first == tid) {
                continue;
            }
            
            while (!env->isStoped) {
                System_sleep(10);
            }
        }
    }
}

void Vm::resumeWorld() {
    for (auto it = threads.begin(); it != threads.end(); ++it) {
        Env *env = it->second;
        env->needStop = false;
    }
}
void Vm::printObj(GcObj *gcobj) {
    fr_Obj obj = fr_fromGcObj(gcobj);
    fr_Class type = (fr_Class)gc_getType(gcobj);
    printf("%s %p", type->name, obj);
}

int Vm::allocSize(void *type) {
    fr_Class t = (fr_Class)type;
    return t->allocSize;
}

void Vm::addStaticRef(fr_Obj *objAddress) {
    std::lock_guard<std::recursive_mutex> lock_guard(lock);
    staticFieldRef.push_back(objAddress);
}

void Vm::registerClass(const char *pod, const char *clz, fr_Class type) {
    std::lock_guard<std::recursive_mutex> lock_guard(lock);
    std::string podName = pod;
    std::string clzName = clz;
    typeDb[podName][clzName] = type;
    classSet.insert(type);
    for (int i=0; i<type->fieldCount; ++i) {
        fr_Field &f = type->fieldList[i];
        if (f.isStatic && !f.isValType) {
            fr_Obj* objAddress = (fr_Obj*)(f.pointer);
            addStaticRef(objAddress);
        }
    }
}
fr_Class Vm::findClass(const char *pod, const char *clz) {
    std::lock_guard<std::recursive_mutex> lock_guard(lock);
    auto itr = typeDb.find(pod);
    if (itr == typeDb.end()) return NULL;
    auto type = itr->second.find(clz);
    if (type == itr->second.end()) return NULL;
    return type->second;
}
