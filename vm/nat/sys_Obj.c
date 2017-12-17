//
//  sys_Obj.c
//  run
//
//  Created by yangjiandong on 2017/12/17.
//  Copyright © 2017年 yangjiandong. All rights reserved.
//

#include "sys.h"


void sys_Obj_make0(fr_Env __env, sys_Obj_ref __self){ return; }
sys_Bool sys_Obj_equals1(fr_Env __env, sys_Obj_ref __self, sys_Obj_null that){ return 0; }
sys_Int sys_Obj_compare1(fr_Env __env, sys_Obj_ref __self, sys_Obj that){ return 0; }
sys_Int sys_Obj_hash0(fr_Env __env, sys_Obj_ref __self){ return 0; }
sys_Str sys_Obj_toStr0(fr_Env __env, sys_Obj_ref __self){ return 0; }
sys_Obj_null sys_Obj_trap1(fr_Env __env, sys_Obj_ref __self, sys_Str name){ return 0; }
sys_Obj_null sys_Obj_trap2(fr_Env __env, sys_Obj_ref __self, sys_Str name, sys_List_null args){ return 0; }
sys_This sys_Obj_with1(fr_Env __env, sys_Obj_ref __self, sys_Func f){ return 0; }
sys_Bool sys_Obj_isImmutable0(fr_Env __env, sys_Obj_ref __self){ return 0; }
sys_This sys_Obj_toImmutable0(fr_Env __env, sys_Obj_ref __self){ return 0; }
sys_Type sys_Obj_typeof_0(fr_Env __env, sys_Obj_ref __self){ return 0; }
void sys_Obj_finalize0(fr_Env __env, sys_Obj_ref __self){ return; }
void sys_Obj_echo0(fr_Env __env){ return; }
void sys_Obj_echo1(fr_Env __env, sys_Obj_null x){ return; }
