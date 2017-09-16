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

typedef int64_t sys_Int;
typedef double sys_Float;
typedef bool sys_Bool;

#define FR_TRY if(setjmp(fr_pushJmpBuf(__env)))
#define FR_CATCH else
#define FR_THROW(err) { fr_setErr(__env, err); longjmp(fr_popJmpBuf(__env), 1);}

#define FR_VTABLE(typeName, self) ((typeName##_VTable_)(((Obj)(self))->type))
#define FR_VCALL(type, method, self, ...) FR_VTABLE(type, self)->method(env__, self, ## __VA_ARGS__)
#define FR_ICALL(type, method, self, ...) FR_VTABLE(type, self)->method(env__, ((self) + FR_VTABLE(type, self)->offset), ## __VA_ARGS__)


#endif /* runtime_h */
