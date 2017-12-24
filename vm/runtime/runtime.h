//
//  runtime.h
//  gen
//
//  Created by yangjiandong on 2017/9/10.
//  Copyright © 2017年 yangjiandong. All rights reserved.
//

#ifndef runtime_h
#define runtime_h

#ifdef  __cplusplus
extern  "C" {
#endif

//#include "common.h"
#include "miss.h"
#include "Type.h"
#include "gcobj.h"
#include <setjmp.h>

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
GcObj *fr_toGcObj(fr_Obj obj);

////////////////////////////
// Util
////////////////////////////
fr_Obj fr_newStrUtf8(fr_Env self, const char *bytes);
const char *fr_getStrUtf8(fr_Env env__, fr_Obj str);

////////////////////////////
// Buildin type
////////////////////////////
typedef int64_t sys_Int_val;
typedef double sys_Float_val;
typedef bool sys_Bool_val;

struct sys_Int_struct {
    int64_t val;
};
struct sys_Float_struct {
    double val;
};
struct sys_Bool_struct {
    bool val;
};

////////////////////////////
// Other
////////////////////////////
#define FR_TYPE(type) (type)(0)
#define FR_TYPE_IS(obj, type) (true)
#define FR_TYPE_AS(obj, type) (obj)
#define FR_ALLOC(type) fr_malloc(__env, sizeof(struct type##_struct), type##_class__(__env))

#define FR_TRY if(setjmp(*fr_pushJmpBuf(__env)))
#define FR_CATCH else
#define FR_ERR_TYPE(type) (FR_TYPE_IS(fr_getErr(__env), type))
#define FR_THROW(err) { fr_throwErr(__env, err); longjmp(*fr_popJmpBuf(__env), 1);}

#define _FR_VTABLE(typeName, self) ( (struct typeName##_vtable*)fr_getType(__env, self) )
#define _FR_IVTABLE(typeName, self) ( (struct typeName##_vtable*)fr_getInterfaceVTable(__env, self, typeName##_class__(__env)) )

#define FR_VCALL(type, method, self, ...)  _FR_VTABLE(type, self)->method(__env, self, ## __VA_ARGS__)
#define FR_ICALL(type, method, self, ...) _FR_IVTABLE(type, self)->method(__env, self, ## __VA_ARGS__)

#define FR_BOX(val, fromType, toType) ((toType)val)
#define FR_UNBOX(obj, fromType, toType) ((toType)obj)
#define FR_CAST(obj, fromType, toType) ((toType)obj)

#ifdef  __cplusplus
}
#endif

#endif /* runtime_h */
