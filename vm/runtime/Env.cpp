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

class FVM_ : public GcSupport {
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

class Env_ {
    
};

////////////////////////////
// VM
////////////////////////////

fr_FVM fr_startVm();
void fr_stopVm(fr_FVM vm);
fr_Env fr_getEnv(fr_FVM vm);

void fr_initEnv(fr_Env env);
void fr_releaseEnv(fr_Env env);

////////////////////////////
// Exception
////////////////////////////

void fr_pushFrame(const char*func);
void fr_popFrame();

jmp_buf *fr_pushJmpBuf(fr_Env self);
jmp_buf *fr_popJmpBuf(fr_Env self);

fr_Obj fr_getErr();
void fr_throwErr(fr_Obj err);
fr_Obj fr_clearErr();

////////////////////////////
// GC
////////////////////////////

void fr_addGlobalRef(fr_Env self, fr_Obj obj);
fr_Obj fr_malloc(fr_Env self, int size, fr_Type vtable);
void fr_gc(fr_Env self);


