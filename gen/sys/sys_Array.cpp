//
//  sys_Array.c
//  run
//
//  Created by yangjiandong on 2017/12/17.
//  Copyright © 2017年 yangjiandong. All rights reserved.
//

#include "sys.h"


fr_Err sys_Array_make(fr_Env __env, sys_Array_ref __self, sys_Int size){ return 0; }
fr_Err sys_Array_size(fr_Env __env, sys_Int *__ret, sys_Array_ref __self){ return 0; }
fr_Err sys_Array_get(fr_Env __env, sys_Obj_null *__ret, sys_Array_ref __self, sys_Int pos){ return 0; }
fr_Err sys_Array_set(fr_Env __env, sys_Array_ref __self, sys_Int pos, sys_Obj_null val){ return 0; }
fr_Err sys_Array_realloc(fr_Env __env, sys_Obj *__ret, sys_Obj array, sys_Int newSize){ return 0; }
fr_Err sys_Array_arraycopy(fr_Env __env, sys_Obj src, sys_Int srcOffset, sys_Obj dest, sys_Int destOffset, sys_Int length){ return 0; }
fr_Err sys_Array_fill(fr_Env __env, sys_Obj array, sys_Obj_null val, sys_Int times){ return 0; }
fr_Err sys_Array_finalize(fr_Env __env, sys_Array_ref __self){ return 0; }

