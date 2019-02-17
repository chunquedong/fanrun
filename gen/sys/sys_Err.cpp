//
//  sys_Err.c
//  run
//
//  Created by yangjiandong on 2017/12/17.
//  Copyright © 2017年 yangjiandong. All rights reserved.
//

#include "sys.h"


//void sys_Err_make0(fr_Env __env, sys_Err_ref __self){ return; }
//void sys_Err_make1(fr_Env __env, sys_Err_ref __self, sys_Str msg){ return; }
void sys_Err_make2(fr_Env __env, sys_Err_ref __self, sys_Str msg, sys_Err_null cause){ return; }

sys_Str sys_Err_msg0(fr_Env __env, sys_Err_ref __self) { return __self->msg; }
sys_Err_null sys_Err_cause0(fr_Env __env, sys_Err_ref __self) { return __self->cause; }
sys_Err sys_Err_trace0(fr_Env __env, sys_Err_ref __self) {
    printf("%s", fr_getStrUtf8(__env, __self->traceToStr, NULL));
    return __self;
}
sys_Str sys_Err_traceToStr0(fr_Env __env, sys_Err_ref __self) { return __self->traceToStr; }
sys_Str sys_Err_toStr0(fr_Env __env, sys_Err_ref __self) { return __self->msg; }
