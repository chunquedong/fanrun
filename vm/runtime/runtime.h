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
#include "Class.h"
#include "gcobj.h"

#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>

//#define LONG_JMP_EXCEPTION

typedef void *fr_Env;

////////////////////////////
// VM
////////////////////////////

fr_Env fr_getEnv();
void fr_releaseEnv(fr_Env env);

////////////////////////////
// Exception
////////////////////////////
#ifdef LONG_JMP_EXCEPTION
jmp_buf *fr_pushJmpBuf(fr_Env self);
jmp_buf *fr_popJmpBuf(fr_Env self);
jmp_buf *fr_topJmpBuf(fr_Env self);
#endif

fr_Obj fr_getErr(fr_Env self);
void fr_setErr(fr_Env self, fr_Obj err);
void fr_clearErr(fr_Env self);

////////////////////////////
// GC
////////////////////////////

void fr_addGlobalRef(fr_Env self, fr_Obj obj);
void fr_deleteGlobalRef(fr_Env self, fr_Obj obj);
void fr_addStaticRef(fr_Env self, fr_Obj *obj);
    
fr_Obj fr_malloc(fr_Env self, fr_Class vtable);
void fr_gc(fr_Env self);
GcObj *fr_toGcObj(fr_Obj obj);
fr_Obj fr_fromGcObj(GcObj *g);
void fr_checkPoint(fr_Env self);

////////////////////////////
// Util
////////////////////////////
fr_Obj fr_newStr(fr_Env __env, const wchar_t *data, size_t size);
fr_Obj fr_newStrUtf8(fr_Env self, const char *bytes);
//NullTerminated
fr_Obj fr_newStrNT(fr_Env __env, const wchar_t *data);
const char *fr_getStrUtf8(fr_Env env__, fr_Obj str);
    
fr_Obj fr_sysType(fr_Env env, fr_Class);
void fr_throwNPE(fr_Env __env);

////////////////////////////
// Buildin type
////////////////////////////
typedef int64_t sys_Int_val;
typedef double sys_Float_val;
typedef bool sys_Bool_val;

struct sys_Int_struct {
    int64_t _val;
};
struct sys_Float_struct {
    double _val;
};
struct sys_Bool_struct {
    bool _val;
};

fr_Obj fr_box_int(fr_Env, sys_Int_val val);
fr_Obj fr_box_float(fr_Env, sys_Float_val val);
fr_Obj fr_box_bool(fr_Env, sys_Bool_val val);

////////////////////////////
// Other
////////////////////////////

#define FR_TYPE(type) fr_sysType(__env, type##_class__)
#define FR_TYPE_IS(obj, type) fr_isClass(__env, obj, type##_class__)
#define FR_TYPE_AS(obj, type) (type)(FR_TYPE_IS(obj, type)?obj:NULL)
#define FR_ALLOC(type) ((type##_ref)fr_malloc(__env, type##_class__))

#define FR_TRY try
#define FR_CATCH catch(...)
#define FR_THROW(err) {fr_setErr(__env, err); throw 1;}
#define FR_ERR_TYPE(type) (FR_TYPE_IS(fr_getErr(__env), type))
#define FR_ALLOC_THROW(errType) FR_THROW(FR_ALLOC(errType))

#define _FR_VTABLE(typeName, self) ( (struct typeName##_vtable*)fr_getClass(__env, self) )
#define _FR_IVTABLE(typeName, self) ( (struct typeName##_vtable*)fr_getInterfaceVTable(__env, self, typeName##_class__) )

#define FR_VCALL(type, method, self, ...)  _FR_VTABLE(type, self)->method(__env, self, ## __VA_ARGS__)
#define FR_ICALL(type, method, self, ...) _FR_IVTABLE(type, self)->method(__env, self, ## __VA_ARGS__)

#define FR_BOXING(tagert, value, fromType, toType) {\
    fromType##_ref tmp##__LINE__ = FR_ALLOC(fromType);\
    tmp##__LINE__->_val = value;\
    tagert = (toType)tmp##__LINE__;}

#define FR_BOX_INT(value, fromType, toType) (toType)fr_box_int(__env, value)
#define FR_BOX_FLOAT(value, fromType, toType) (toType)fr_box_float(__env, value)
#define FR_BOX_BOOL(value, fromType, toType) (toType)fr_box_bool(__env, value)

#define FR_UNBOXING(obj, fromType, toType) (((toType##_null)obj)->_val)
#define FR_NNULL(obj, fromType, toType) ( (obj?(toType)obj:(fr_throwNPE(__env),(toType)0)) )
    
#define FR_CHECK_POINT fr_checkPoint(__env);

#ifdef  __cplusplus
}
#endif

#endif /* runtime_h */
