//
//  Env.h
//  fcode
//
//  Created by yangjiandong on 15/8/2.
//  Copyright (c) 2015年 yangjiandong. All rights reserved.
//

#ifndef __fcode__Env__
#define __fcode__Env__

#ifdef  __cplusplus
extern  "C" {
#endif

#include "Type.h"
#include <setjmp.h>
#include "gcobj.h"

typedef void *fr_FVM;
typedef void *fr_Env;

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
    
void fr_pushFrame(fr_Env self, const char*func);
void fr_popFrame(fr_Env self);

jmp_buf *fr_pushJmpBuf(fr_Env self);
jmp_buf *fr_popJmpBuf(fr_Env self);

fr_Obj fr_getErr(fr_Env self);
void fr_throwErr(fr_Env self, fr_Obj err);
void fr_clearErr(fr_Env self);

////////////////////////////
// GC
////////////////////////////

void fr_addGlobalRef(fr_Env self, fr_Obj obj);
fr_Obj fr_malloc(fr_Env self, int size, fr_Type vtable);
void fr_gc(fr_Env self);
    
////////////////////////////
// Util
////////////////////////////
fr_Obj fr_newStrUtf8(fr_Env self, const char *bytes);
const char *fr_getStrUtf8(fr_Env env__, fr_Obj str);
GcObj *fr_toGcObj(fr_Obj obj);

#ifdef  __cplusplus
}
#endif

#endif /* defined(__fcode__Env__) */
