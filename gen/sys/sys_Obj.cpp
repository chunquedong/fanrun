//
//  sys_Obj.c
//  run
//
//  Created by yangjiandong on 2017/12/17.
//  Copyright © 2017年 yangjiandong. All rights reserved.
//

#include "sys.h"
#include <stdio.h>

void sys_Obj_make0(fr_Env __env, sys_Obj_ref __self){ return; }
sys_Bool sys_Obj_equals1(fr_Env __env, sys_Obj_ref __self, sys_Obj_null that){
    return __self == that;
}
sys_Int sys_Obj_compare1(fr_Env __env, sys_Obj_ref __self, sys_Obj that){
    return __self - that;
}
sys_Int sys_Obj_hash0(fr_Env __env, sys_Obj_ref __self){ return (sys_Int)__self; }
sys_Str sys_Obj_toStr0(fr_Env __env, sys_Obj_ref __self){
    sys_Type type = FR_VCALL(sys_Obj, typeof_0, __self);
    sys_Str name = sys_Type_qname0(__env, type);
    
    char buf[64];
    snprintf(buf, 64, "(%p)", __self);
    sys_Obj id = (sys_Obj)fr_newStrUtf8(__env, buf);
    sys_Str str = sys_Str_plus1(__env, name, id);
    return str;
}
//TODO
sys_Obj_null sys_Obj_trap2(fr_Env __env, sys_Obj_ref __self, sys_Str name, sys_List_null args){
    return 0;
}
//TODO
sys_Bool sys_Obj_isImmutable0(fr_Env __env, sys_Obj_ref __self){ return 0; }
sys_Obj sys_Obj_toImmutable0(fr_Env __env, sys_Obj_ref __self){ return 0; }
sys_Type sys_Obj_typeof_0(fr_Env __env, sys_Obj_ref __self){
    fr_Type clz = (fr_Type)gc_getType(fr_toGcObj(__self));
    return (sys_Type)fr_toTypeObj(__env, clz);
}

void sys_Obj_finalize0(fr_Env __env, sys_Obj_ref __self){ return; }

void sys_Obj_echo1(fr_Env __env, sys_Obj_null x){
    if (x == NULL) {
        printf("null\n");
        return;
    }
    fr_Obj str = FR_VCALL(sys_Obj, toStr0, x);
    if (str == NULL) {
        printf("ERROR:null\n");
        return;
    }
    const char *utf8 = fr_getStrUtf8(__env, str, NULL);
    printf("%s\n", utf8);
}
