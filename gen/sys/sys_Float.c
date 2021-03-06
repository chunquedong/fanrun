//
//  sys_Float.c
//  run
//
//  Created by yangjiandong on 2017/12/17.
//  Copyright © 2017年 yangjiandong. All rights reserved.
//

#include "sys.h"
#include <float.h>
#include <math.h>

sys_Float sys_Float_defVal = 0;
sys_Float sys_Float_posInf = INFINITY;
sys_Float sys_Float_negInf = -INFINITY;
sys_Float sys_Float_nan = NAN;
sys_Float sys_Float_e = 2.718281828459045;
sys_Float sys_Float_pi= 3.141592653589793;

fr_Err sys_Float_makeBits(fr_Env __env, sys_Float *__ret, sys_Int bits){ return 0; }
fr_Err sys_Float_makeBits32(fr_Env __env, sys_Float *__ret, sys_Int bits){ return 0; }
fr_Err sys_Float_fromStr(fr_Env __env, sys_Float *__ret, sys_Str s, sys_Bool checked){ return 0; }
fr_Err sys_Float_random(fr_Env __env, sys_Float *__ret){ return 0; }
fr_Err sys_Float_equals_val(fr_Env __env, sys_Bool *__ret, sys_Float_val __self, sys_Obj_null obj){ return 0; }
fr_Err sys_Float_isNaN_val(fr_Env __env, sys_Bool *__ret, sys_Float_val __self){ return 0; }
fr_Err sys_Float_negate_val(fr_Env __env, sys_Float *__ret, sys_Float_val __self){ return 0; }
fr_Err sys_Float_mult_val(fr_Env __env, sys_Float *__ret, sys_Float_val __self, sys_Float b){ return 0; }
fr_Err sys_Float_multInt_val(fr_Env __env, sys_Float *__ret, sys_Float_val __self, sys_Int b){ return 0; }
fr_Err sys_Float_div_val(fr_Env __env, sys_Float *__ret, sys_Float_val __self, sys_Float b){ return 0; }
fr_Err sys_Float_divInt_val(fr_Env __env, sys_Float *__ret, sys_Float_val __self, sys_Int b){ return 0; }
fr_Err sys_Float_mod_val(fr_Env __env, sys_Float *__ret, sys_Float_val __self, sys_Float b){ return 0; }
fr_Err sys_Float_modInt_val(fr_Env __env, sys_Float *__ret, sys_Float_val __self, sys_Int b){ return 0; }
fr_Err sys_Float_plus_val(fr_Env __env, sys_Float *__ret, sys_Float_val __self, sys_Float b){ return 0; }
fr_Err sys_Float_plusInt_val(fr_Env __env, sys_Float *__ret, sys_Float_val __self, sys_Int b){ return 0; }
fr_Err sys_Float_minus_val(fr_Env __env, sys_Float *__ret, sys_Float_val __self, sys_Float b){ return 0; }
fr_Err sys_Float_minusInt_val(fr_Env __env, sys_Float *__ret, sys_Float_val __self, sys_Int b){ return 0; }
fr_Err sys_Float_bits_val(fr_Env __env, sys_Int *__ret, sys_Float_val __self){ return 0; }
fr_Err sys_Float_bits32_val(fr_Env __env, sys_Int *__ret, sys_Float_val __self){ return 0; }
fr_Err sys_Float_toStr_val(fr_Env __env, sys_Str *__ret, sys_Float_val __self){ return 0; }
fr_Err sys_Float_toInt_val(fr_Env __env, sys_Int *__ret, sys_Float_val __self){
    *__ret = (sys_Int)__self;
    return NULL;
}
fr_Err sys_Float_toLocale_val(fr_Env __env, sys_Str *__ret, sys_Float_val __self, sys_Str_null pattern){ return 0; }

fr_Err sys_Float_static__init(fr_Env __env) { return 0; }
