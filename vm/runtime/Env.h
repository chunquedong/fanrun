//
//  Env.h
//  fcode
//
//  Created by yangjiandong on 15/8/2.
//  Copyright (c) 2015年 yangjiandong. All rights reserved.
//

#ifndef __fcode__Env__
#define __fcode__Env__

#include "Gc.h"
#include <assert.h>
#include <vector>
#include "runtime.h"

struct FVM_ : public GcSupport {
    Gc *gc;
    std::vector<GcObj*> globalRef;
    
    FVM_() {
        gc = new Gc();
        gc->gcSupport = this;
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


#endif /* defined(__fcode__Env__) */
