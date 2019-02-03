//
//  sys_Bool.c
//  run
//
//  Created by yangjiandong on 2017/12/17.
//  Copyright © 2017年 yangjiandong. All rights reserved.
//

#include "sys.h"
#include <wchar.h>

//sys_Bool_null sys_Bool_fromStr1(fr_Env __env, sys_Str s){
//    return sys_Bool_fromStr2(__env, s, true);
//}
sys_Bool sys_Bool_fromStr2(fr_Env __env, sys_Str s, sys_Bool checked){
    if (wcsncmp(s->data, L"true", s->size) == 0) {
        return true;
    }
    else if (wcsncmp(s->data, L"false", s->size) == 0) {
        return false;
    }
    if (checked) {
        FR_ALLOC_THROW(sys_ParseErr);
    }
    return NULL;
}
void sys_Bool_privateMake0_val(fr_Env __env, sys_Bool_val __self){ __self = 0; }
sys_Bool sys_Bool_equals1_val(fr_Env __env, sys_Bool_val __self, sys_Obj_null obj){
    if (!obj) return false;
    if (FR_TYPE_IS(obj, sys_Bool)) {
        sys_Bool_ref other = (sys_Bool_ref)obj;
        return __self == other->_val;
    }
    return false;
}
sys_Int sys_Bool_hash0_val(fr_Env __env, sys_Bool_val __self){
    return (sys_Int)__self;
}
sys_Str sys_Bool_toStr0_val(fr_Env __env, sys_Bool_val __self){
    if (__self) {
        return (sys_Str)fr_newStrNT(__env, L"true");
    } else {
        return (sys_Str)fr_newStrNT(__env, L"false");
    }
}
sys_Str sys_Bool_toLocale0_val(fr_Env __env, sys_Bool_val __self){
    return sys_Bool_toStr0_val(__env, __self);
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
sys_Str sys_Bool_toCode0_val(fr_Env __env, sys_Bool_val __self){
    return sys_Bool_toStr0_val(__env, __self);
}
