//
//  sys_Bool.c
//  run
//
//  Created by yangjiandong on 2017/12/17.
//  Copyright © 2017年 yangjiandong. All rights reserved.
//

#include "sys.h"

sys_Bool_null sys_Bool_fromStr1(fr_Env __env, sys_Str s){ return 0; }
sys_Bool_null sys_Bool_fromStr2(fr_Env __env, sys_Str s, sys_Bool checked){ return 0; }
void sys_Bool_privateMake0(fr_Env __env, sys_Bool_ref __self){ return; }
void sys_Bool_privateMake0_val(fr_Env __env, sys_Bool_val __self){ return; }
sys_Bool sys_Bool_equals1(fr_Env __env, sys_Bool_ref __self, sys_Obj_null obj){ return 0; }
sys_Bool sys_Bool_equals1_val(fr_Env __env, sys_Bool_val __self, sys_Obj_null obj){ return 0; }
sys_Int sys_Bool_hash0(fr_Env __env, sys_Bool_ref __self){ return 0; }
sys_Int sys_Bool_hash0_val(fr_Env __env, sys_Bool_val __self){ return 0; }
sys_Str sys_Bool_toStr0(fr_Env __env, sys_Bool_ref __self){
    return sys_Bool_toStr0_val(__env, __self->val);
}
sys_Str sys_Bool_toStr0_val(fr_Env __env, sys_Bool_val __self){
    if (__self) {
        return fr_newStrUtf8(__env, "true");
    } else {
        return fr_newStrUtf8(__env, "false");
    }
}
sys_Str sys_Bool_toLocale0(fr_Env __env, sys_Bool_ref __self){ return 0; }
sys_Str sys_Bool_toLocale0_val(fr_Env __env, sys_Bool_val __self){ return 0; }
sys_Bool sys_Bool_not0(fr_Env __env, sys_Bool_ref __self){ return 0; }
sys_Bool sys_Bool_not0_val(fr_Env __env, sys_Bool_val __self){ return 0; }
sys_Bool sys_Bool_and1(fr_Env __env, sys_Bool_ref __self, sys_Bool b){ return 0; }
sys_Bool sys_Bool_and1_val(fr_Env __env, sys_Bool_val __self, sys_Bool b){ return 0; }
sys_Bool sys_Bool_or1(fr_Env __env, sys_Bool_ref __self, sys_Bool b){ return 0; }
sys_Bool sys_Bool_or1_val(fr_Env __env, sys_Bool_val __self, sys_Bool b){ return 0; }
sys_Bool sys_Bool_xor1(fr_Env __env, sys_Bool_ref __self, sys_Bool b){ return 0; }
sys_Bool sys_Bool_xor1_val(fr_Env __env, sys_Bool_val __self, sys_Bool b){ return 0; }
sys_Str sys_Bool_toCode0(fr_Env __env, sys_Bool_ref __self){ return 0; }
sys_Str sys_Bool_toCode0_val(fr_Env __env, sys_Bool_val __self){ return 0; }
