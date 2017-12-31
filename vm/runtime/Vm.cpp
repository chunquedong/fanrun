//
//  Vm.cpp
//  vm
//
//  Created by yangjiandong on 2017/12/31.
//  Copyright © 2017年 yangjiandong. All rights reserved.
//

#include "Vm.hpp"
#include "Env.h"
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

void Vm::addStaticRef(fr_Obj obj) {
    std::lock_guard<std::recursive_mutex> lock_guard(lock);
    
    GcObj *gcobj = fr_toGcObj(obj);
    staticFieldRef.push_back(gcobj);
}

void Vm::walkNodeChildren(Gc *gc, GcObj *obj) {
    
}
void Vm::walkRoot(Gc *gc) {
    //global ref
//    LinkedListElem *it = LinkedList_first(&globalRefList);
//    LinkedListElem *end = LinkedList_end(&globalRefList);
//    while (it != end) {
//        gc->onRoot(static_cast<GcObj*>(it->data));
//        it = it->next;
//    }
    
    //static field
    for (auto it = staticFieldRef.begin(); it != staticFieldRef.end(); ++it) {
        gc->onRoot(static_cast<GcObj*>(*it));
    }
    
//    //local
//    for (auto it = threads.begin(); it != threads.end(); ++it) {
//        Env *env = it->second;
//        env->walkLocalRoot(gc);
//    }
}

void Vm::finalizeObj(GcObj *obj) {
    
}
void Vm::puaseWorld() {
    for (auto it = threads.begin(); it != threads.end(); ++it) {
        Env *env = it->second;
        env->needStop = true;
    }
    
    System_barrier();
    
    for (auto it = threads.begin(); it != threads.end(); ++it) {
        Env *env = it->second;
        while (!env->isStoped) {
            System_sleep(5);
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
    fr_Type type = fr_getType(this, obj);
    printf("%s\n", type->name);
}

int Vm::allocSize(void *type) {
    fr_Type t = (fr_Type)type;
    return t->allocSize;
}
