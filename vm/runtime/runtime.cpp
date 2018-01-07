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

fr_Env fr_getEnv() {
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

void fr_releaseEnv(fr_Env env) {
    if (!env || !fvm) return;
    fvm->releaseEnv((Env*)env);
}

//////////////////////////////////////////
// GC

GcObj *fr_toGcObj(fr_Obj obj) {
    GcObj *g = (GcObj*)obj;
    --g;
    return g;
}

fr_Obj fr_fromGcObj(GcObj *g) {
    fr_Obj obj = (fr_Obj)(++g);
    return obj;
}

void fr_checkPoint(fr_Env self) {
    Env *env = (Env*)self;
    if (env->needStop) {
        env->isStoped = true;
        void *statckVar = 0;
        env->statckEnd = &statckVar;
        
        System_barrier();
        do {
            System_sleep(10);
        } while(env->needStop);
        env->isStoped = false;
        System_barrier();
    }
}

fr_Obj fr_malloc(fr_Env self, fr_Class vtable) {
    Env *env = (Env*)self;
    GcObj *gcobj = env->vm->getGc()->alloc(vtable, vtable->allocSize);
    fr_Obj obj = (fr_Obj)(++gcobj);
    return obj;
}

void fr_gc(fr_Env self) {
    Env *env = (Env*)self;
    env->vm->getGc()->collect();
}

void fr_addGlobalRef(fr_Env self, fr_Obj obj) {
    Env *env = (Env*)self;
    env->vm->getGc()->pinObj(fr_toGcObj(obj));
}
void fr_deleteGlobalRef(fr_Env self, fr_Obj obj) {
    Env *env = (Env*)self;
    env->vm->getGc()->unpinObj(fr_toGcObj(obj));
}
void fr_addStaticRef(fr_Env self, fr_Obj *obj) {
    Env *env = (Env*)self;
    env->vm->addStaticRef(obj);
}

