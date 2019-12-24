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

////////////////////////////
// Exception
////////////////////////////
//#ifdef LONG_JMP_EXCEPTION
//jmp_buf *fr_pushJmpBuf(fr_Env self);
//jmp_buf *fr_popJmpBuf(fr_Env self);
//jmp_buf *fr_topJmpBuf(fr_Env self);
//#endif

typedef fr_Obj fr_Err;
fr_Obj fr_getErr(fr_Env self);
void fr_setErr(fr_Env self, fr_Obj err);
void fr_clearErr(fr_Env self);

////////////////////////////
// GC
////////////////////////////

fr_Obj fr_addGlobalRef(fr_Env self, fr_Obj obj);
void fr_deleteGlobalRef(fr_Env self, fr_Obj obj);
void fr_addStaticRef(fr_Env self, fr_Obj *obj);
    
fr_Obj fr_alloc(fr_Env self, fr_Type vtable, ssize_t size);
void fr_gc(fr_Env self);
//GcObj *fr_toGcObj(fr_Obj obj);
//fr_Obj fr_fromGcObj(GcObj *g);
#define fr_toGcObj(obj) (((GcObj*)(obj))-1)
#define fr_fromGcObj(g) ((fr_Obj)(((GcObj*)(g))+1))
void fr_checkPoint(fr_Env self);
void fr_yieldGc(fr_Env self);

////////////////////////////
// Util
////////////////////////////

typedef enum fr_ValueType_ {
    fr_vtOther, //unsed
    fr_vtObj,
    fr_vtInt,
    fr_vtFloat,
    fr_vtBool,
    fr_vtHandle,
    fr_vtPtr,
} fr_ValueType;

fr_Obj fr_arrayNew(fr_Env self, fr_Type elemType, int extType, size_t len);

//fr_Obj fr_newStr(fr_Env __env, const wchar_t *data, size_t size, bool copy);
fr_Obj fr_newStrUtf8(fr_Env self, const char *bytes, ssize_t size);
//NullTerminated
//fr_Obj fr_newStrNT(fr_Env __env, const wchar_t *data, bool copy);
const char *fr_getStrUtf8(fr_Env env__, fr_Obj str, bool *isCopy);
    
//fr_Obj fr_toTypeObj(fr_Env env, fr_Type);
fr_Err fr_makeNPE(fr_Env __env);

////////////////////////////
// Buildin type
////////////////////////////
typedef int64_t sys_Int_val;
typedef int8_t  sys_Int8_val;
typedef int16_t sys_Int16_val;
typedef int32_t sys_Int32_val;
typedef int64_t sys_Int64_val;
typedef int8_t  sys_Int8;
typedef int16_t sys_Int16;
typedef int32_t sys_Int32;
typedef int64_t sys_Int64;
    
typedef double sys_Float_val;
typedef double sys_Float64_val;
typedef float sys_Float32_val;
typedef double sys_Float64;
typedef float sys_Float32;

typedef bool sys_Bool_val;
typedef void * sys_Ptr_val;
    
//typedef struct fr_Array_ {
//    fr_Type elemType;
//    int32_t valueType;
//    int32_t elemSize;
//    int64_t size;
//    fr_Obj data[1];
//} fr_Array;

fr_Obj fr_box_int(fr_Env, sys_Int_val val);
fr_Obj fr_box_float(fr_Env, sys_Float_val val);
fr_Obj fr_box_bool(fr_Env, sys_Bool_val val);

////////////////////////////
// Other
////////////////////////////

//#define FR_TYPE(type) (sys_Type)fr_toTypeObj(__env, type##_class__)
#define FR_TYPE_IS(obj, type) fr_isClass(__env, obj, type##_class__)
#define FR_TYPE_AS(obj, type) (type)(FR_TYPE_IS(obj, type)?obj:NULL)
#define FR_CAST(ret, obj, type, toType) do{if (FR_TYPE_IS(obj, type)) ret = (toType)obj; else FR_THROW_NPE() }while(0)

#define FR_ALLOC(type) ((type##_ref)fr_alloc(__env, type##_class__, -1))
#define FR_INIT_VAL(val, type) (memset(&val, 0, sizeof(struct type##_struct)))

#define FR_TRY /*try*/
#define FR_CATCH /*catch(...)*/
#define FR_THROW(err) {return err;}
#define FR_THROW_NPE() { return fr_makeNPE(__env); }
#define FR_CHECK_NULL(obj) do{ if (!obj) FR_THROW_NPE() }while(false)
#define FR_ERR_TYPE(type) (FR_TYPE_IS(fr_getErr(__env), type))
#define FR_ALLOC_THROW(errType) FR_THROW(FR_ALLOC(errType))

#define _FR_VTABLE(typeName, self) ( (struct typeName##_vtable*)fr_getClass(__env, self) )
#define _FR_IVTABLE(typeName, self) ( (struct typeName##_vtable*)fr_getInterfaceVTable(__env, self, typeName##_class__) )

#define _FR_CHECK_ERR(expr) { fr_Err __err = expr; if (__err) return __err; }
#define FR_VOID_VCALL(type, method, self, ...) _FR_VTABLE(type, self)->method(__env, self, ## __VA_ARGS__)
#define FR_VOID_ICALL(type, method, self, ...) _FR_IVTABLE(type, self)->method(__env, self, ## __VA_ARGS__)
#define FR_VOID_CALL(type, method, self, ...)  _FR_CHECK_ERR(type##_##method(__env, self, ## __VA_ARGS__))
#define FR_VOID_SCALL(type, method, ...)  _FR_CHECK_ERR(type##_##method(__env, ## __VA_ARGS__))

#define FR_VCALL(type, method, ret, self, ...) _FR_VTABLE(type, self)->method(__env, ret, self, ## __VA_ARGS__)
#define FR_ICALL(type, method, ret, self, ...) _FR_IVTABLE(type, self)->method(__env, ret, self, ## __VA_ARGS__)
#define FR_CALL(type, method, ret, self, ...)  _FR_CHECK_ERR(type##_##method(__env, ret, self, ## __VA_ARGS__))
#define FR_SCALL(type, method, ret, ...)  _FR_CHECK_ERR(type##_##method(__env, ret, ## __VA_ARGS__))


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
#define FR_NOT_NULL(ret, obj, toType) do{if (obj) ret = (toType)obj; else FR_THROW_NPE()}while(0)
    
#define FR_CHECK_POINT {if(__env->needStop)fr_checkPoint(__env);}
#define FR_SET_DIRTY(obj) gc_setDirty(fr_toGcObj((fr_Obj)obj), 1);
    
#define FR_STATIC_INIT(type) do{if(!type##_class__->staticInited) {type##_class__->staticInited=true;type##_static__init(__env);}}while(0)

#ifdef  __cplusplus
}
#endif

#endif /* runtime_h */
