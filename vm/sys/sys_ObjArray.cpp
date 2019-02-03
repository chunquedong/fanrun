//
//  sys_ObjArray.c
//  run
//
//  Created by yangjiandong on 2017/12/17.
//  Copyright © 2017年 yangjiandong. All rights reserved.
//

#include "sys.h"

void sys_ObjArray_make2(fr_Env __env, sys_ObjArray_ref __self, sys_Int size, sys_Type_null type) {
    return;
}
sys_Obj_null sys_ObjArray_get1(fr_Env __env, sys_ObjArray_ref __self, sys_Int pos){ return 0; }
void sys_ObjArray_set2(fr_Env __env, sys_ObjArray_ref __self, sys_Int pos, sys_Obj_null val){ return; }
sys_Int sys_ObjArray_size0(fr_Env __env, sys_ObjArray_ref __self){ return 0; }
sys_ObjArray sys_ObjArray_realloc1(fr_Env __env, sys_ObjArray_ref __self, sys_Int newSize){ return 0; }
sys_ObjArray sys_ObjArray_copyFrom4(fr_Env __env, sys_ObjArray_ref __self, sys_ObjArray that, sys_Int thatOffset, sys_Int thisOffset, sys_Int length){ return 0; }
void sys_ObjArray_finalize0(fr_Env __env, sys_ObjArray_ref __self){ return; }
sys_ObjArray sys_ObjArray_fill2(fr_Env __env, sys_ObjArray_ref __self, sys_Obj_null obj, sys_Int times) {
    return __self;
}
sys_ObjArray sys_ObjArray_fromJava2(fr_Env __env, sys_Type of, sys_Obj array) {
    return NULL;
}
sys_Obj sys_ObjArray_toJava1(fr_Env __env, sys_ObjArray_ref __self, sys_Obj clz) {
    return NULL;
}

