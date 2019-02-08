//
//  sys_Func.c
//  run
//
//  Created by yangjiandong on 2017/12/17.
//  Copyright © 2017年 yangjiandong. All rights reserved.
//

#include "sys.h"


void sys_Func_make0(fr_Env __env, sys_Func_ref __self){ return; }
sys_Type sys_Func_returns0(fr_Env __env, sys_Func_ref __self){ return 0; }
sys_Int sys_Func_arity0(fr_Env __env, sys_Func_ref __self){ return 0; }
sys_List sys_Func_params0(fr_Env __env, sys_Func_ref __self){ return 0; }
//sys_Method_null sys_Func_method0(fr_Env __env, sys_Func_ref __self){ return 0; }
sys_Obj_null sys_Func_callList1(fr_Env __env, sys_Func_ref __self, sys_List_null args){ return 0; }
sys_Obj_null sys_Func_callOn2(fr_Env __env, sys_Func_ref __self, sys_Obj_null target, sys_List_null args){ return 0; }
sys_Obj_null sys_Func_call0(fr_Env __env, sys_Func_ref __self){
    fr_Class clz = fr_getClass(__env, __self);
    switch (fr_getFuncArity(__env, clz)) {
        case 0:
            return FR_VCALL(sys_Func, call0, __self);
            break;
        case 1:
            return FR_VCALL(sys_Func, call1, __self, NULL);
            break;
        case 2:
            return FR_VCALL(sys_Func, call2, __self, NULL, NULL);
            break;
        case 3:
            return FR_VCALL(sys_Func, call3, __self, NULL, NULL, NULL);
            break;
        case 4:
            return FR_VCALL(sys_Func, call4, __self, NULL, NULL, NULL, NULL);
            break;
        case 5:
            return FR_VCALL(sys_Func, call5, __self, NULL, NULL, NULL, NULL, NULL);
            break;
        case 6:
            return FR_VCALL(sys_Func, call6, __self, NULL, NULL, NULL, NULL, NULL, NULL);
            break;
        case 7:
            return FR_VCALL(sys_Func, call7, __self, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
            break;
        case 8:
            return FR_VCALL(sys_Func, call8, __self, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
            break;
        default:
            FR_ALLOC_THROW(sys_ArgErr);
            break;
    }
    return NULL;
}
sys_Obj_null sys_Func_call1(fr_Env __env, sys_Func_ref __self, sys_Obj_null a){
    fr_Class clz = fr_getClass(__env, __self);
    switch (fr_getFuncArity(__env, clz)) {
        case 0:
            return FR_VCALL(sys_Func, call0, __self);
            break;
        case 1:
            return FR_VCALL(sys_Func, call1, __self, a);
            break;
        case 2:
            return FR_VCALL(sys_Func, call2, __self, a, NULL);
            break;
        case 3:
            return FR_VCALL(sys_Func, call3, __self, a, NULL, NULL);
            break;
        case 4:
            return FR_VCALL(sys_Func, call4, __self, a, NULL, NULL, NULL);
            break;
        case 5:
            return FR_VCALL(sys_Func, call5, __self, a, NULL, NULL, NULL, NULL);
            break;
        case 6:
            return FR_VCALL(sys_Func, call6, __self, a, NULL, NULL, NULL, NULL, NULL);
            break;
        case 7:
            return FR_VCALL(sys_Func, call7, __self, a, NULL, NULL, NULL, NULL, NULL, NULL);
            break;
        case 8:
            return FR_VCALL(sys_Func, call8, __self, a, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
            break;
        default:
            FR_ALLOC_THROW(sys_ArgErr);
            break;
    }
    return NULL;
}
sys_Obj_null sys_Func_call2(fr_Env __env, sys_Func_ref __self, sys_Obj_null a, sys_Obj_null b){
    fr_Class clz = fr_getClass(__env, __self);
    switch (fr_getFuncArity(__env, clz)) {
        case 0:
            return FR_VCALL(sys_Func, call0, __self);
            break;
        case 1:
            return FR_VCALL(sys_Func, call1, __self, a);
            break;
        case 2:
            return FR_VCALL(sys_Func, call2, __self, a, b);
            break;
        case 3:
            return FR_VCALL(sys_Func, call3, __self, a, b, NULL);
            break;
        case 4:
            return FR_VCALL(sys_Func, call4, __self, a, b, NULL, NULL);
            break;
        case 5:
            return FR_VCALL(sys_Func, call5, __self, a, b, NULL, NULL, NULL);
            break;
        case 6:
            return FR_VCALL(sys_Func, call6, __self, a, b, NULL, NULL, NULL, NULL);
            break;
        case 7:
            return FR_VCALL(sys_Func, call7, __self, a, b, NULL, NULL, NULL, NULL, NULL);
            break;
        case 8:
            return FR_VCALL(sys_Func, call8, __self, a, b, NULL, NULL, NULL, NULL, NULL, NULL);
            break;
        default:
            FR_ALLOC_THROW(sys_ArgErr);
            break;
    }
    return NULL;
}
sys_Obj_null sys_Func_call3(fr_Env __env, sys_Func_ref __self, sys_Obj_null a, sys_Obj_null b, sys_Obj_null c){
    fr_Class clz = fr_getClass(__env, __self);
    switch (fr_getFuncArity(__env, clz)) {
        case 0:
            return FR_VCALL(sys_Func, call0, __self);
            break;
        case 1:
            return FR_VCALL(sys_Func, call1, __self, a);
            break;
        case 2:
            return FR_VCALL(sys_Func, call2, __self, a, b);
            break;
        case 3:
            return FR_VCALL(sys_Func, call3, __self, a, b, c);
            break;
        case 4:
            return FR_VCALL(sys_Func, call4, __self, a, b, c, NULL);
            break;
        case 5:
            return FR_VCALL(sys_Func, call5, __self, a, b, c, NULL, NULL);
            break;
        case 6:
            return FR_VCALL(sys_Func, call6, __self, a, b, c, NULL, NULL, NULL);
            break;
        case 7:
            return FR_VCALL(sys_Func, call7, __self, a, b, c, NULL, NULL, NULL, NULL);
            break;
        case 8:
            return FR_VCALL(sys_Func, call8, __self, a, b, c, NULL, NULL, NULL, NULL, NULL);
            break;
        default:
            FR_ALLOC_THROW(sys_ArgErr);
            break;
    }
    return NULL;
}
sys_Obj_null sys_Func_call4(fr_Env __env, sys_Func_ref __self, sys_Obj_null a, sys_Obj_null b, sys_Obj_null c, sys_Obj_null d){
    fr_Class clz = fr_getClass(__env, __self);
    switch (fr_getFuncArity(__env, clz)) {
        case 0:
            return FR_VCALL(sys_Func, call0, __self);
            break;
        case 1:
            return FR_VCALL(sys_Func, call1, __self, a);
            break;
        case 2:
            return FR_VCALL(sys_Func, call2, __self, a, b);
            break;
        case 3:
            return FR_VCALL(sys_Func, call3, __self, a, b, c);
            break;
        case 4:
            return FR_VCALL(sys_Func, call4, __self, a, b, c, d);
            break;
        case 5:
            return FR_VCALL(sys_Func, call5, __self, a, b, c, d, NULL);
            break;
        case 6:
            return FR_VCALL(sys_Func, call6, __self, a, b, c, d, NULL, NULL);
            break;
        case 7:
            return FR_VCALL(sys_Func, call7, __self, a, b, c, d, NULL, NULL, NULL);
            break;
        case 8:
            return FR_VCALL(sys_Func, call8, __self, a, b, c, d, NULL, NULL, NULL, NULL);
            break;
        default:
            FR_ALLOC_THROW(sys_ArgErr);
            break;
    }
    return NULL;
}
sys_Obj_null sys_Func_call5(fr_Env __env, sys_Func_ref __self, sys_Obj_null a, sys_Obj_null b, sys_Obj_null c, sys_Obj_null d, sys_Obj_null e){
    fr_Class clz = fr_getClass(__env, __self);
    switch (fr_getFuncArity(__env, clz)) {
        case 0:
            return FR_VCALL(sys_Func, call0, __self);
            break;
        case 1:
            return FR_VCALL(sys_Func, call1, __self, a);
            break;
        case 2:
            return FR_VCALL(sys_Func, call2, __self, a, b);
            break;
        case 3:
            return FR_VCALL(sys_Func, call3, __self, a, b, c);
            break;
        case 4:
            return FR_VCALL(sys_Func, call4, __self, a, b, c, d);
            break;
        case 5:
            return FR_VCALL(sys_Func, call5, __self, a, b, c, d, e);
            break;
        case 6:
            return FR_VCALL(sys_Func, call6, __self, a, b, c, d, e, NULL);
            break;
        case 7:
            return FR_VCALL(sys_Func, call7, __self, a, b, c, d, e, NULL, NULL);
            break;
        case 8:
            return FR_VCALL(sys_Func, call8, __self, a, b, c, d, e, NULL, NULL, NULL);
            break;
        default:
            FR_ALLOC_THROW(sys_ArgErr);
            break;
    }
    return NULL;
}
sys_Obj_null sys_Func_call6(fr_Env __env, sys_Func_ref __self, sys_Obj_null a, sys_Obj_null b, sys_Obj_null c, sys_Obj_null d, sys_Obj_null e, sys_Obj_null f){
    fr_Class clz = fr_getClass(__env, __self);
    switch (fr_getFuncArity(__env, clz)) {
        case 0:
            return FR_VCALL(sys_Func, call0, __self);
            break;
        case 1:
            return FR_VCALL(sys_Func, call1, __self, a);
            break;
        case 2:
            return FR_VCALL(sys_Func, call2, __self, a, b);
            break;
        case 3:
            return FR_VCALL(sys_Func, call3, __self, a, b, c);
            break;
        case 4:
            return FR_VCALL(sys_Func, call4, __self, a, b, c, d);
            break;
        case 5:
            return FR_VCALL(sys_Func, call5, __self, a, b, c, d, e);
            break;
        case 6:
            return FR_VCALL(sys_Func, call6, __self, a, b, c, d, e, f);
            break;
        case 7:
            return FR_VCALL(sys_Func, call7, __self, a, b, c, d, e, f, NULL);
            break;
        case 8:
            return FR_VCALL(sys_Func, call8, __self, a, b, c, d, e, f, NULL, NULL);
            break;
        default:
            FR_ALLOC_THROW(sys_ArgErr);
            break;
    }
    return NULL;
}
sys_Obj_null sys_Func_call7(fr_Env __env, sys_Func_ref __self, sys_Obj_null a, sys_Obj_null b, sys_Obj_null c, sys_Obj_null d, sys_Obj_null e, sys_Obj_null f, sys_Obj_null g){
    fr_Class clz = fr_getClass(__env, __self);
    switch (fr_getFuncArity(__env, clz)) {
        case 0:
            return FR_VCALL(sys_Func, call0, __self);
            break;
        case 1:
            return FR_VCALL(sys_Func, call1, __self, a);
            break;
        case 2:
            return FR_VCALL(sys_Func, call2, __self, a, b);
            break;
        case 3:
            return FR_VCALL(sys_Func, call3, __self, a, b, c);
            break;
        case 4:
            return FR_VCALL(sys_Func, call4, __self, a, b, c, d);
            break;
        case 5:
            return FR_VCALL(sys_Func, call5, __self, a, b, c, d, e);
            break;
        case 6:
            return FR_VCALL(sys_Func, call6, __self, a, b, c, d, e, f);
            break;
        case 7:
            return FR_VCALL(sys_Func, call7, __self, a, b, c, d, e, f, g);
            break;
        case 8:
            return FR_VCALL(sys_Func, call8, __self, a, b, c, d, e, f, g, NULL);
            break;
        default:
            FR_ALLOC_THROW(sys_ArgErr);
            break;
    }
    return NULL;
}
sys_Obj_null sys_Func_call8(fr_Env __env, sys_Func_ref __self, sys_Obj_null a, sys_Obj_null b, sys_Obj_null c, sys_Obj_null d, sys_Obj_null e, sys_Obj_null f, sys_Obj_null g, sys_Obj_null h){
    fr_Class clz = fr_getClass(__env, __self);
    switch (fr_getFuncArity(__env, clz)) {
        case 0:
            return FR_VCALL(sys_Func, call0, __self);
            break;
        case 1:
            return FR_VCALL(sys_Func, call1, __self, a);
            break;
        case 2:
            return FR_VCALL(sys_Func, call2, __self, a, b);
            break;
        case 3:
            return FR_VCALL(sys_Func, call3, __self, a, b, c);
            break;
        case 4:
            return FR_VCALL(sys_Func, call4, __self, a, b, c, d);
            break;
        case 5:
            return FR_VCALL(sys_Func, call5, __self, a, b, c, d, e);
            break;
        case 6:
            return FR_VCALL(sys_Func, call6, __self, a, b, c, d, e, f);
            break;
        case 7:
            return FR_VCALL(sys_Func, call7, __self, a, b, c, d, e, f, g);
            break;
        case 8:
            return FR_VCALL(sys_Func, call8, __self, a, b, c, d, e, f, g, h);
            break;
        default:
            FR_ALLOC_THROW(sys_ArgErr);
            break;
    }
    return NULL;
}
sys_Func sys_Func_bind1(fr_Env __env, sys_Func_ref __self, sys_List args){ return 0; }
sys_Func sys_Func_retype1(fr_Env __env, sys_Func_ref __self, sys_Type t){ return 0; }

void sys_Func_enterCtor1(fr_Env __env, sys_Func_ref __self, sys_Obj obj) {
    
}
void sys_Func_exitCtor0(fr_Env __env, sys_Func_ref __self) {
    
}
void sys_Func_checkInCtor1(fr_Env __env, sys_Func_ref __self, sys_Obj obj) {
    
}
