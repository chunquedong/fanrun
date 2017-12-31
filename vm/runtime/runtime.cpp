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

Vm *fvm = nullptr;

fr_Env fr_getEnv() {
    if (fvm == nullptr) {
        fvm = new Vm();
    }
    return fvm->getEnv();
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
void fr_addStaticRef(fr_Env self, fr_Obj obj) {
    Env *env = (Env*)self;
    env->vm->addStaticRef(obj);
}

