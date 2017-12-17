//
//  runtime.h
//  gen
//
//  Created by yangjiandong on 2017/9/10.
//  Copyright © 2017年 yangjiandong. All rights reserved.
//

#ifndef runtime_h
#define runtime_h

//#include "common.h"
#include "miss.h"
#include "Env.h"

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

#define FR_TYPE(type) (type)(0)
#define FR_TYPE_IS(obj, type) (true)
#define FR_TYPE_AS(obj, type) (obj)
#define FR_ALLOC(type) (type)(0)

#define FR_TRY if(setjmp(*fr_pushJmpBuf(__env)))
#define FR_CATCH else
#define FR_ERR_TYPE(type) (FR_TYPE_IS(fr_getErr(__env), type))
#define FR_THROW(err) { fr_setErr(__env, err); longjmp(*fr_popJmpBuf(__env), 1);}

#define FR_VTABLE(typeName, self) ( (struct typeName##_vtable*)(gc_getType( ((GcObj*)self) )) )
#define FR_VCALL(type, method, self, ...) FR_VTABLE(type, self)->method(__env, self, ## __VA_ARGS__)
#define FR_ICALL(type, method, self, ...) FR_VTABLE(type, self)->method(__env, ((self) + FR_VTABLE(type, self)->offset), ## __VA_ARGS__)

#define FR_BOX(val, fromType, toType) ((toType)val)
#define FR_UNBOX(obj, fromType, toType) ((toType)obj)
#define FR_CAST(obj, fromType, toType) ((toType)obj)



#endif /* runtime_h */
