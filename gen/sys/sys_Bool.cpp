//
//  sys_Bool.c
//  run
//
//  Created by yangjiandong on 2017/12/17.
//  Copyright © 2017年 yangjiandong. All rights reserved.
//

#include "sys.h"
#include <wchar.h>

sys_Bool sys_Bool_defVal = false;

void sys_Bool_privateMake0_val(fr_Env __env, sys_Bool_val __self){ __self = 0; }
sys_Bool sys_Bool_equals1_val(fr_Env __env, sys_Bool_val __self, sys_Obj_null obj){
    if (!obj) return false;
    if (FR_TYPE_IS(obj, sys_Bool)) {
        sys_Bool_ref other = (sys_Bool_ref)obj;
        return __self == other->_val;
    }
    return false;
}

sys_Bool sys_Bool_not0_val(fr_Env __env, sys_Bool_val __self){
    return !__self;
}
sys_Bool sys_Bool_and1_val(fr_Env __env, sys_Bool_val __self, sys_Bool b){
    return __self && b;
}
sys_Bool sys_Bool_or1_val(fr_Env __env, sys_Bool_val __self, sys_Bool b){
    return __self || b;
}
sys_Bool sys_Bool_xor1_val(fr_Env __env, sys_Bool_val __self, sys_Bool b){
    return __self != b;
}

void sys_Bool_static__init0(fr_Env __env) {
}
