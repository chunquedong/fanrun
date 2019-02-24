//
//  runtime.c
//  gen
//
//  Created by yangjiandong on 2017/9/10.
//  Copyright © 2017年 yangjiandong. All rights reserved.
//

#include "runtime.h"
#include "Env.hpp"
#include "Vm.hpp"
#include "system.h"

Vm *fvm = nullptr;

fr_Env fr_getEnv(fr_Fvm vm) {
    void *statckVar = 0;
    if (fvm == nullptr) {
        fvm = new Vm();
    }
    Env *env = fvm->getEnv();
    if (env->statckStart == NULL) {
        env->statckStart = &statckVar;
    }
    return env;
}

void fr_releaseEnv(fr_Fvm vm, fr_Env env) {
    if (!env || !fvm) return;
    fvm->releaseEnv((Env*)env);
}

int fr_getFuncArity(fr_Env, fr_Type clz) {
    return clz->funcArity;
}

//////////////////////////////////////////
// GC
/*
GcObj *fr_toGcObj(fr_Obj obj) {
    GcObj *g = (GcObj*)obj;
    --g;
    return g;
    
}
fr_Obj fr_fromGcObj(GcObj *g) {
    fr_Obj obj = (fr_Obj)(++g);
    return obj;
}
*/
void fr_checkPoint(fr_Env self) {
    Env *env = (Env*)self;
    if (env->needStop) {
        void *statckVar = 0;
        env->statckEnd = &statckVar;
        env->isStoped = true;
        
        System_barrier();
        do {
            System_sleep(10);
        } while(env->needStop);
        env->isStoped = false;
        System_barrier();
    }
}

void fr_yieldGc(fr_Env self) {
    Env *env = (Env*)self;
    void *statckVar = 0;
    env->statckEnd = &statckVar;
    env->isStoped = true;
    System_barrier();
}

fr_Obj fr_malloc(fr_Env self, fr_Type vtable) {
    Env *env = (Env*)self;
    GcObj *gcobj = env->vm->getGc()->alloc(vtable, vtable->allocSize);
    fr_Obj obj = fr_fromGcObj(gcobj);
    return obj;
}

void fr_gc(fr_Env self) {
    Env *env = (Env*)self;
    env->vm->getGc()->collect();
}

fr_Obj fr_addGlobalRef(fr_Env self, fr_Obj obj) {
    Env *env = (Env*)self;
    env->vm->getGc()->pinObj(fr_toGcObj(obj));
    return obj;
}
void fr_deleteGlobalRef(fr_Env self, fr_Obj obj) {
    Env *env = (Env*)self;
    env->vm->getGc()->unpinObj(fr_toGcObj(obj));
}
void fr_addStaticRef(fr_Env self, fr_Obj *obj) {
    Env *env = (Env*)self;
    env->vm->addStaticRef(obj);
}

