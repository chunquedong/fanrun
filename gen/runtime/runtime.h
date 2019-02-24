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
#include <string.h>

//#define LONG_JMP_EXCEPTION

struct fr_Env_ {
    bool needStop;
    bool isStoped;
};
typedef struct fr_Env_ *fr_Env;
typedef void *fr_Fvm;

////////////////////////////
// VM
////////////////////////////

fr_Env fr_getEnv(fr_Fvm vm);
void fr_releaseEnv(fr_Fvm vm, fr_Env env);
    
int fr_getFuncArity(fr_Env, fr_Type clz);

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

fr_Obj fr_addGlobalRef(fr_Env self, fr_Obj obj);
void fr_deleteGlobalRef(fr_Env self, fr_Obj obj);
void fr_addStaticRef(fr_Env self, fr_Obj *obj);
    
fr_Obj fr_malloc(fr_Env self, fr_Type vtable);
void fr_gc(fr_Env self);
//GcObj *fr_toGcObj(fr_Obj obj);
//fr_Obj fr_fromGcObj(GcObj *g);
#define fr_toGcObj(obj) ((GcObj*)(obj))
#define fr_fromGcObj(g) ((fr_Obj)(g))
void fr_checkPoint(fr_Env self);
void fr_yieldGc(fr_Env self);

////////////////////////////
// Util
////////////////////////////
fr_Obj fr_newStr(fr_Env __env, const wchar_t *data, size_t size, bool copy);
fr_Obj fr_newStrUtf8(fr_Env self, const char *bytes);
//NullTerminated
fr_Obj fr_newStrNT(fr_Env __env, const wchar_t *data, bool copy);
const char *fr_getStrUtf8(fr_Env env__, fr_Obj str, bool *isCopy);
    
fr_Obj fr_toTypeObj(fr_Env env, fr_Type);
void fr_throwNPE(fr_Env __env);

////////////////////////////
// Buildin type
////////////////////////////
typedef int64_t sys_Int_val;
typedef double sys_Float_val;
typedef bool sys_Bool_val;

fr_Obj fr_box_int(fr_Env, sys_Int_val val);
fr_Obj fr_box_float(fr_Env, sys_Float_val val);
fr_Obj fr_box_bool(fr_Env, sys_Bool_val val);

////////////////////////////
// Other
////////////////////////////

#define FR_TYPE(type) (sys_Type)fr_toTypeObj(__env, type##_class__)
#define FR_TYPE_IS(obj, type) fr_isClass(__env, obj, type##_class__)
#define FR_TYPE_AS(obj, type) (type)(FR_TYPE_IS(obj, type)?obj:NULL)
#define FR_CAST(obj, type, toType) (FR_TYPE_IS(obj, type)?(toType)obj:(fr_throwNPE(__env),(toType)0) )

#define FR_ALLOC(type) ((type##_ref)fr_malloc(__env, type##_class__))
#define FR_INIT_VAL(val, type) (memset(&val, 0, sizeof(struct type##_struct)))

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
    fromType##_ref tmp__ = FR_ALLOC(fromType);\
    *tmp__ = value;\
    tagert = (toType)tmp__;}
    
#define FR_BOXING_VAL(tagert, value, fromType, toType) {\
    fromType##_ref tmp__ = FR_ALLOC(fromType);\
    tmp__->_val = value;\
    tagert = (toType)tmp__;}

#define FR_BOX_INT(value) ((sys_Int_ref)fr_box_int(__env, value))
#define FR_BOX_FLOAT(value) ((sys_Float_ref)fr_box_float(__env, value))
#define FR_BOX_BOOL(value) ((sys_Bool_ref)fr_box_bool(__env, value))

#define FR_UNBOXING(obj, toType) (*((toType##_null)obj))
#define FR_UNBOXING_VAL(obj, toType) (((toType##_null)obj)->_val)
#define FR_NOT_NULL(obj, toType) ( (obj?(toType)obj:(fr_throwNPE(__env),(toType)0)) )
    
#define FR_CHECK_POINT {if(__env->needStop)fr_checkPoint(__env);}
#define FR_SET_DIRTY(obj) gc_setDirty(fr_toGcObj((fr_Obj)obj), 1);
    
#define FR_STATIC_INIT(type) {if(!type##_class__->staticInited) {type##_class__->staticInited=true;type##_static__init0(__env);}}

#ifdef  __cplusplus
}
#endif

#endif /* runtime_h */
