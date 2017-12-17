//
//  Env.cpp
//  fcode
//
//  Created by yangjiandong on 15/8/2.
//  Copyright (c) 2015年 yangjiandong. All rights reserved.
//

#include "Env.h"
#include "Gc.h"
#include <assert.h>
#include <vector>

struct FVM_ : public GcSupport {
    Gc *gc;
    std::vector<GcObj*> globalRef;
    
    FVM_() {
        gc = new Gc();
    }
    
    virtual void walkNodeChildren(Gc *gc, GcObj *obj) override {
        
    }
    virtual void walkRoot(Gc *gc) override {
        
    }
    
    virtual void finalizeObj(GcObj *obj) override {
        
    }
    virtual void puaseWorld() override {
        
    }
    virtual void resumeWorld() override {
        
    }
    virtual void printObj(GcObj *obj) override {
        
    }
    virtual int allocSize(void *type) override {
        return 0;
    }
};

struct JmpBuf {
    jmp_buf buf;
};

struct Env_ {
    FVM_ *vm;
    fr_Obj error;
    std::vector<const char*> stackTrace;
    std::vector<JmpBuf> exception;
    
    Env_() : vm(nullptr), error(0) {
    }
};

////////////////////////////
// VM
////////////////////////////

FVM_ *fvm = nullptr;

fr_FVM fr_startVm() {
    if (fvm == nullptr) {
        fvm = new FVM_();
    }
    return fvm;
}

void fr_stopVm(fr_FVM vm) {
    FVM_ *fvm = (FVM_ *)vm;
    delete fvm;
    if (fvm == ::fvm) {
        ::fvm = nullptr;
    }
}

fr_Env fr_getEnv(fr_FVM vm) {
    Env_ *env = new Env_();
    FVM_ *fvm = (FVM_ *)vm;
    env->vm = fvm;
    return env;
}

void fr_initEnv(fr_Env self) {
    Env_ *env = (Env_*)self;
    env->vm = fvm;
}

void fr_releaseEnv(fr_Env self) {
    Env_ *env = (Env_*)self;
    delete env;
}

////////////////////////////
// Exception
////////////////////////////

void fr_pushFrame(fr_Env self, const char*func) {
    Env_ *env = (Env_*)self;
    env->stackTrace.push_back(func);
}
void fr_popFrame(fr_Env self) {
    Env_ *env = (Env_*)self;
    env->stackTrace.pop_back();
}

jmp_buf *fr_pushJmpBuf(fr_Env self) {
    Env_ *env = (Env_*)self;
    JmpBuf buf;
    env->exception.push_back(buf);
    return &env->exception.back().buf;
}

jmp_buf *fr_popJmpBuf(fr_Env self) {
    Env_ *env = (Env_*)self;
    JmpBuf &back = env->exception.back();
    env->exception.pop_back();
    return &back.buf;
}

fr_Obj fr_getErr(fr_Env self) {
    Env_ *env = (Env_*)self;
    return env->error;
}
void fr_throwErr(fr_Env self, fr_Obj err) {
    Env_ *env = (Env_*)self;
    env->error = err;
}
void fr_clearErr(fr_Env self) {
    Env_ *env = (Env_*)self;
    env->error = nullptr;
}

////////////////////////////
// GC
////////////////////////////

GcObj *fr_toGcObj(fr_Obj obj) {
    GcObj *g = (GcObj*)obj;
    --g;
    return g;
}

void fr_addGlobalRef(fr_Env self, fr_Obj obj) {
    Env_ *env = (Env_*)self;
    env->vm->globalRef.push_back(fr_toGcObj(obj));
}
fr_Obj fr_malloc(fr_Env self, int size, fr_Type vtable) {
    Env_ *env = (Env_*)self;
    GcObj *gcobj = env->vm->gc->alloc(vtable, size);
    fr_Obj obj = (fr_Obj)(++gcobj);
    return obj;
}

void fr_gc(fr_Env self) {
    Env_ *env = (Env_*)self;
    env->vm->gc->collect();
}

fr_Obj fr_newStrUtf8(fr_Env self, const char *bytes) {
    //TODO
    return nullptr;
}
