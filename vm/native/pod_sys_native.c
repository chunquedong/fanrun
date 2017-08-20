#include "pod_sys_native.h"
#include "pod_sys_struct.h"

int sys_Bool__allocSize__() {return sizeof(struct sys_Bool_);}
void sys_Bool_static__init(fr_Env self, void *param, void *ret);

void sys_Bool_fromStr(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Bool arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.b;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Bool_fromStr_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Bool_privateMake(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Bool arg_0; 

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.b;


    sys_Bool_privateMake_f(env, arg_0);
}

void sys_Bool_equals(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Bool arg_0; 
    fr_Value value_1;
    fr_Obj arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.h;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.b;


    retValue.b = sys_Bool_equals_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Bool_hash(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Bool arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.b;


    retValue.i = sys_Bool_hash_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Bool_toStr(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Bool arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.b;


    retValue.h = sys_Bool_toStr_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Bool_toLocale(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Bool arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.b;


    retValue.h = sys_Bool_toLocale_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Bool_not(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Bool arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.b;


    retValue.b = sys_Bool_not_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Bool_and(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Bool arg_0; 
    fr_Value value_1;
    fr_Bool arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.b;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.b;


    retValue.b = sys_Bool_and_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Bool_or(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Bool arg_0; 
    fr_Value value_1;
    fr_Bool arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.b;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.b;


    retValue.b = sys_Bool_or_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Bool_xor(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Bool arg_0; 
    fr_Value value_1;
    fr_Bool arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.b;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.b;


    retValue.b = sys_Bool_xor_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Bool_toCode(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Bool arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.b;


    retValue.h = sys_Bool_toCode_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

int sys_Err__allocSize__() {return sizeof(struct sys_Err_);}
void sys_Err_static__init(fr_Env self, void *param, void *ret);

void sys_Err_make(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Obj arg_1; 
    fr_Value value_2;
    fr_Obj arg_2; 

    fr_getParam(env, param, &value_2, 2);
    arg_2 = value_2.h;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.h;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    sys_Err_make_f(env, arg_0, arg_1, arg_2);
}

void sys_Err_msg(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Err_msg_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Err_cause(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Err_cause_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Err_traceToStr(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Err_traceToStr_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Err_toStr(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Err_toStr_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

int sys_Num__allocSize__() {return sizeof(struct sys_Num_);}
void sys_Num_static__init(fr_Env self, void *param, void *ret);

void sys_Num_make(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    sys_Num_make_f(env, arg_0);
}

void sys_Num_toInt(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.i = sys_Num_toInt_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Num_toFloat(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.f = sys_Num_toFloat_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Num_localeDecimal(fr_Env env, void *param, void *ret) {
    fr_Value retValue;


    retValue.h = sys_Num_localeDecimal_f(env);
    *((fr_Value*)ret) = retValue;
}

void sys_Num_localeGrouping(fr_Env env, void *param, void *ret) {
    fr_Value retValue;


    retValue.h = sys_Num_localeGrouping_f(env);
    *((fr_Value*)ret) = retValue;
}

void sys_Num_localeMinus(fr_Env env, void *param, void *ret) {
    fr_Value retValue;


    retValue.h = sys_Num_localeMinus_f(env);
    *((fr_Value*)ret) = retValue;
}

void sys_Num_localePercent(fr_Env env, void *param, void *ret) {
    fr_Value retValue;


    retValue.h = sys_Num_localePercent_f(env);
    *((fr_Value*)ret) = retValue;
}

void sys_Num_localePosInf(fr_Env env, void *param, void *ret) {
    fr_Value retValue;


    retValue.h = sys_Num_localePosInf_f(env);
    *((fr_Value*)ret) = retValue;
}

void sys_Num_localeNegInf(fr_Env env, void *param, void *ret) {
    fr_Value retValue;


    retValue.h = sys_Num_localeNegInf_f(env);
    *((fr_Value*)ret) = retValue;
}

void sys_Num_localeNaN(fr_Env env, void *param, void *ret) {
    fr_Value retValue;


    retValue.h = sys_Num_localeNaN_f(env);
    *((fr_Value*)ret) = retValue;
}

int sys_Float__allocSize__() {return sizeof(struct sys_Float_);}
void sys_Float_static__init(fr_Env self, void *param, void *ret);

void sys_Float_makeBits(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Int arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.i;


    retValue.f = sys_Float_makeBits_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Float_makeBits32(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Int arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.i;


    retValue.f = sys_Float_makeBits32_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Float_fromStr(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Bool arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.b;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Float_fromStr_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Float_random(fr_Env env, void *param, void *ret) {
    fr_Value retValue;


    retValue.f = sys_Float_random_f(env);
    *((fr_Value*)ret) = retValue;
}

void sys_Float_privateMake(fr_Env env, void *param, void *ret) {
    fr_Value retValue;


    retValue.h = sys_Float_privateMake_f(env);
    *((fr_Value*)ret) = retValue;
}

void sys_Float_equals(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Float arg_0; 
    fr_Value value_1;
    fr_Obj arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.h;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.f;


    retValue.b = sys_Float_equals_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Float_approx(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Float arg_0; 
    fr_Value value_1;
    fr_Float arg_1; 
    fr_Value value_2;
    fr_Obj arg_2; 
    fr_Value retValue;

    fr_getParam(env, param, &value_2, 2);
    arg_2 = value_2.h;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.f;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.f;


    retValue.b = sys_Float_approx_f(env, arg_0, arg_1, arg_2);
    *((fr_Value*)ret) = retValue;
}

void sys_Float_compare(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Float arg_0; 
    fr_Value value_1;
    fr_Obj arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.h;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.f;


    retValue.i = sys_Float_compare_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Float_isNaN(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Float arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.f;


    retValue.b = sys_Float_isNaN_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Float_hash(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Float arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.f;


    retValue.i = sys_Float_hash_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Float_negate(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Float arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.f;


    retValue.f = sys_Float_negate_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Float_increment(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Float arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.f;


    retValue.f = sys_Float_increment_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Float_decrement(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Float arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.f;


    retValue.f = sys_Float_decrement_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Float_mult(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Float arg_0; 
    fr_Value value_1;
    fr_Float arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.f;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.f;


    retValue.f = sys_Float_mult_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Float_multInt(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Float arg_0; 
    fr_Value value_1;
    fr_Int arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.i;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.f;


    retValue.f = sys_Float_multInt_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Float_div(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Float arg_0; 
    fr_Value value_1;
    fr_Float arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.f;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.f;


    retValue.f = sys_Float_div_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Float_divInt(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Float arg_0; 
    fr_Value value_1;
    fr_Int arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.i;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.f;


    retValue.f = sys_Float_divInt_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Float_mod(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Float arg_0; 
    fr_Value value_1;
    fr_Float arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.f;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.f;


    retValue.f = sys_Float_mod_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Float_modInt(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Float arg_0; 
    fr_Value value_1;
    fr_Int arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.i;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.f;


    retValue.f = sys_Float_modInt_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Float_plus(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Float arg_0; 
    fr_Value value_1;
    fr_Float arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.f;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.f;


    retValue.f = sys_Float_plus_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Float_plusInt(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Float arg_0; 
    fr_Value value_1;
    fr_Int arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.i;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.f;


    retValue.f = sys_Float_plusInt_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Float_minus(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Float arg_0; 
    fr_Value value_1;
    fr_Float arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.f;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.f;


    retValue.f = sys_Float_minus_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Float_minusInt(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Float arg_0; 
    fr_Value value_1;
    fr_Int arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.i;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.f;


    retValue.f = sys_Float_minusInt_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Float_abs(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Float arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.f;


    retValue.f = sys_Float_abs_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Float_min(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Float arg_0; 
    fr_Value value_1;
    fr_Float arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.f;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.f;


    retValue.f = sys_Float_min_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Float_max(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Float arg_0; 
    fr_Value value_1;
    fr_Float arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.f;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.f;


    retValue.f = sys_Float_max_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Float_ceil(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Float arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.f;


    retValue.f = sys_Float_ceil_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Float_floor(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Float arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.f;


    retValue.f = sys_Float_floor_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Float_round(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Float arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.f;


    retValue.f = sys_Float_round_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Float_exp(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Float arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.f;


    retValue.f = sys_Float_exp_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Float_log(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Float arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.f;


    retValue.f = sys_Float_log_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Float_log10(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Float arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.f;


    retValue.f = sys_Float_log10_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Float_pow(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Float arg_0; 
    fr_Value value_1;
    fr_Float arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.f;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.f;


    retValue.f = sys_Float_pow_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Float_sqrt(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Float arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.f;


    retValue.f = sys_Float_sqrt_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Float_acos(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Float arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.f;


    retValue.f = sys_Float_acos_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Float_asin(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Float arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.f;


    retValue.f = sys_Float_asin_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Float_atan(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Float arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.f;


    retValue.f = sys_Float_atan_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Float_atan2(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Float arg_0; 
    fr_Value value_1;
    fr_Float arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.f;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.f;


    retValue.f = sys_Float_atan2_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Float_cos(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Float arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.f;


    retValue.f = sys_Float_cos_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Float_cosh(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Float arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.f;


    retValue.f = sys_Float_cosh_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Float_sin(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Float arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.f;


    retValue.f = sys_Float_sin_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Float_sinh(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Float arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.f;


    retValue.f = sys_Float_sinh_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Float_tan(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Float arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.f;


    retValue.f = sys_Float_tan_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Float_tanh(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Float arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.f;


    retValue.f = sys_Float_tanh_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Float_toDegrees(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Float arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.f;


    retValue.f = sys_Float_toDegrees_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Float_toRadians(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Float arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.f;


    retValue.f = sys_Float_toRadians_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Float_bits(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Float arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.f;


    retValue.i = sys_Float_bits_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Float_bits32(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Float arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.f;


    retValue.i = sys_Float_bits32_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Float_toStr(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Float arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.f;


    retValue.h = sys_Float_toStr_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Float_toCode(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Float arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.f;


    retValue.h = sys_Float_toCode_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Float_make(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Float arg_0; 

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.f;


    sys_Float_make_f(env, arg_0);
}

int sys_Int__allocSize__() {return sizeof(struct sys_Int_);}
void sys_Int_static__init(fr_Env self, void *param, void *ret);

void sys_Int_fromStr(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Int arg_1; 
    fr_Value value_2;
    fr_Bool arg_2; 
    fr_Value retValue;

    fr_getParam(env, param, &value_2, 2);
    arg_2 = value_2.b;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.i;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Int_fromStr_f(env, arg_0, arg_1, arg_2);
    *((fr_Value*)ret) = retValue;
}

void sys_Int_random(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.i = sys_Int_random_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Int_privateMake(fr_Env env, void *param, void *ret) {
    fr_Value retValue;


    retValue.h = sys_Int_privateMake_f(env);
    *((fr_Value*)ret) = retValue;
}

void sys_Int_equals(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Int arg_0; 
    fr_Value value_1;
    fr_Obj arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.h;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.i;


    retValue.b = sys_Int_equals_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Int_compare(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Int arg_0; 
    fr_Value value_1;
    fr_Obj arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.h;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.i;


    retValue.i = sys_Int_compare_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Int_hash(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Int arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.i;


    retValue.i = sys_Int_hash_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Int_negate(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Int arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.i;


    retValue.i = sys_Int_negate_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Int_increment(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Int arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.i;


    retValue.i = sys_Int_increment_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Int_decrement(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Int arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.i;


    retValue.i = sys_Int_decrement_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Int_mult(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Int arg_0; 
    fr_Value value_1;
    fr_Int arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.i;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.i;


    retValue.i = sys_Int_mult_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Int_multFloat(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Int arg_0; 
    fr_Value value_1;
    fr_Float arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.f;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.i;


    retValue.f = sys_Int_multFloat_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Int_div(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Int arg_0; 
    fr_Value value_1;
    fr_Int arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.i;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.i;


    retValue.i = sys_Int_div_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Int_divFloat(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Int arg_0; 
    fr_Value value_1;
    fr_Float arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.f;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.i;


    retValue.f = sys_Int_divFloat_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Int_mod(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Int arg_0; 
    fr_Value value_1;
    fr_Int arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.i;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.i;


    retValue.i = sys_Int_mod_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Int_modFloat(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Int arg_0; 
    fr_Value value_1;
    fr_Float arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.f;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.i;


    retValue.f = sys_Int_modFloat_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Int_plus(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Int arg_0; 
    fr_Value value_1;
    fr_Int arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.i;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.i;


    retValue.i = sys_Int_plus_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Int_plusFloat(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Int arg_0; 
    fr_Value value_1;
    fr_Float arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.f;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.i;


    retValue.f = sys_Int_plusFloat_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Int_minus(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Int arg_0; 
    fr_Value value_1;
    fr_Int arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.i;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.i;


    retValue.i = sys_Int_minus_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Int_minusFloat(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Int arg_0; 
    fr_Value value_1;
    fr_Float arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.f;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.i;


    retValue.f = sys_Int_minusFloat_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Int_not(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Int arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.i;


    retValue.i = sys_Int_not_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Int_and(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Int arg_0; 
    fr_Value value_1;
    fr_Int arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.i;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.i;


    retValue.i = sys_Int_and_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Int_or(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Int arg_0; 
    fr_Value value_1;
    fr_Int arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.i;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.i;


    retValue.i = sys_Int_or_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Int_xor(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Int arg_0; 
    fr_Value value_1;
    fr_Int arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.i;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.i;


    retValue.i = sys_Int_xor_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Int_shiftl(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Int arg_0; 
    fr_Value value_1;
    fr_Int arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.i;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.i;


    retValue.i = sys_Int_shiftl_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Int_shiftr(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Int arg_0; 
    fr_Value value_1;
    fr_Int arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.i;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.i;


    retValue.i = sys_Int_shiftr_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Int_abs(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Int arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.i;


    retValue.i = sys_Int_abs_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Int_min(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Int arg_0; 
    fr_Value value_1;
    fr_Int arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.i;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.i;


    retValue.i = sys_Int_min_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Int_max(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Int arg_0; 
    fr_Value value_1;
    fr_Int arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.i;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.i;


    retValue.i = sys_Int_max_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Int_pow(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Int arg_0; 
    fr_Value value_1;
    fr_Int arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.i;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.i;


    retValue.i = sys_Int_pow_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Int_isEven(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Int arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.i;


    retValue.b = sys_Int_isEven_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Int_isOdd(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Int arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.i;


    retValue.b = sys_Int_isOdd_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Int_isSpace(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Int arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.i;


    retValue.b = sys_Int_isSpace_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Int_isAlpha(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Int arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.i;


    retValue.b = sys_Int_isAlpha_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Int_isAlphaNum(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Int arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.i;


    retValue.b = sys_Int_isAlphaNum_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Int_isUpper(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Int arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.i;


    retValue.b = sys_Int_isUpper_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Int_isLower(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Int arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.i;


    retValue.b = sys_Int_isLower_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Int_upper(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Int arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.i;


    retValue.i = sys_Int_upper_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Int_lower(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Int arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.i;


    retValue.i = sys_Int_lower_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Int_isDigit(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Int arg_0; 
    fr_Value value_1;
    fr_Int arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.i;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.i;


    retValue.b = sys_Int_isDigit_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Int_toDigit(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Int arg_0; 
    fr_Value value_1;
    fr_Int arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.i;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.i;


    retValue.h = sys_Int_toDigit_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Int_fromDigit(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Int arg_0; 
    fr_Value value_1;
    fr_Int arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.i;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.i;


    retValue.h = sys_Int_fromDigit_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Int_equalsIgnoreCase(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Int arg_0; 
    fr_Value value_1;
    fr_Int arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.i;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.i;


    retValue.b = sys_Int_equalsIgnoreCase_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Int_localeIsUpper(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Int arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.i;


    retValue.b = sys_Int_localeIsUpper_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Int_localeIsLower(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Int arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.i;


    retValue.b = sys_Int_localeIsLower_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Int_localeUpper(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Int arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.i;


    retValue.i = sys_Int_localeUpper_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Int_localeLower(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Int arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.i;


    retValue.i = sys_Int_localeLower_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Int_toStr(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Int arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.i;


    retValue.h = sys_Int_toStr_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Int_toHex(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Int arg_0; 
    fr_Value value_1;
    fr_Obj arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.h;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.i;


    retValue.h = sys_Int_toHex_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Int_toRadix(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Int arg_0; 
    fr_Value value_1;
    fr_Int arg_1; 
    fr_Value value_2;
    fr_Obj arg_2; 
    fr_Value retValue;

    fr_getParam(env, param, &value_2, 2);
    arg_2 = value_2.h;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.i;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.i;


    retValue.h = sys_Int_toRadix_f(env, arg_0, arg_1, arg_2);
    *((fr_Value*)ret) = retValue;
}

void sys_Int_toChar(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Int arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.i;


    retValue.h = sys_Int_toChar_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Int_toCode(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Int arg_0; 
    fr_Value value_1;
    fr_Int arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.i;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.i;


    retValue.h = sys_Int_toCode_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Int_times(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Int arg_0; 
    fr_Value value_1;
    fr_Obj arg_1; 

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.h;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.i;


    sys_Int_times_f(env, arg_0, arg_1);
}

void sys_Int_make(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Int arg_0; 

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.i;


    sys_Int_make_f(env, arg_0);
}

int sys_Obj__allocSize__() {return sizeof(struct sys_Obj_);}
void sys_Obj_static__init(fr_Env self, void *param, void *ret);

void sys_Obj_make(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    sys_Obj_make_f(env, arg_0);
}

void sys_Obj_equals(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Obj arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.h;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.b = sys_Obj_equals_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Obj_compare(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Obj arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.h;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.i = sys_Obj_compare_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Obj_hash(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.i = sys_Obj_hash_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Obj_toStr(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Obj_toStr_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Obj_trap(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Obj arg_1; 
    fr_Value value_2;
    fr_Obj arg_2; 
    fr_Value retValue;

    fr_getParam(env, param, &value_2, 2);
    arg_2 = value_2.h;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.h;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Obj_trap_f(env, arg_0, arg_1, arg_2);
    *((fr_Value*)ret) = retValue;
}

void sys_Obj_with(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Obj arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.h;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Obj_with_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Obj_isImmutable(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.b = sys_Obj_isImmutable_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Obj_toImmutable(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Obj_toImmutable_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Obj_typeof(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Obj_typeof_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Obj_finalize(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    sys_Obj_finalize_f(env, arg_0);
}

void sys_Obj_echo(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    sys_Obj_echo_f(env, arg_0);
}

int sys_Str__allocSize__() {return sizeof(struct sys_Str_);}
void sys_Str_static__init(fr_Env self, void *param, void *ret);

void sys_Str_privateMake(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    sys_Str_privateMake_f(env, arg_0);
}

void sys_Str_fromChars(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Str_fromChars_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Str_equals(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Obj arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.h;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.b = sys_Str_equals_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Str_equalsIgnoreCase(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Obj arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.h;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.b = sys_Str_equalsIgnoreCase_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Str_compare(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Obj arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.h;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.i = sys_Str_compare_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Str_compareIgnoreCase(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Obj arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.h;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.i = sys_Str_compareIgnoreCase_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Str_hash(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.i = sys_Str_hash_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Str_toStr(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Str_toStr_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Str_toLocale(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Str_toLocale_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Str_isEmpty(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.b = sys_Str_isEmpty_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Str_size(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.i = sys_Str_size_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Str_intern(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Str_intern_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Str_startsWith(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Obj arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.h;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.b = sys_Str_startsWith_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Str_endsWith(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Obj arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.h;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.b = sys_Str_endsWith_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Str_index(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Obj arg_1; 
    fr_Value value_2;
    fr_Int arg_2; 
    fr_Value retValue;

    fr_getParam(env, param, &value_2, 2);
    arg_2 = value_2.i;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.h;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Str_index_f(env, arg_0, arg_1, arg_2);
    *((fr_Value*)ret) = retValue;
}

void sys_Str_indexr(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Obj arg_1; 
    fr_Value value_2;
    fr_Int arg_2; 
    fr_Value retValue;

    fr_getParam(env, param, &value_2, 2);
    arg_2 = value_2.i;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.h;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Str_indexr_f(env, arg_0, arg_1, arg_2);
    *((fr_Value*)ret) = retValue;
}

void sys_Str_indexIgnoreCase(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Obj arg_1; 
    fr_Value value_2;
    fr_Int arg_2; 
    fr_Value retValue;

    fr_getParam(env, param, &value_2, 2);
    arg_2 = value_2.i;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.h;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Str_indexIgnoreCase_f(env, arg_0, arg_1, arg_2);
    *((fr_Value*)ret) = retValue;
}

void sys_Str_indexrIgnoreCase(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Obj arg_1; 
    fr_Value value_2;
    fr_Int arg_2; 
    fr_Value retValue;

    fr_getParam(env, param, &value_2, 2);
    arg_2 = value_2.i;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.h;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Str_indexrIgnoreCase_f(env, arg_0, arg_1, arg_2);
    *((fr_Value*)ret) = retValue;
}

void sys_Str_contains(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Obj arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.h;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.b = sys_Str_contains_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Str_containsChar(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Int arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.i;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.b = sys_Str_containsChar_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Str_get(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Int arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.i;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.i = sys_Str_get_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Str_getSafe(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Int arg_1; 
    fr_Value value_2;
    fr_Int arg_2; 
    fr_Value retValue;

    fr_getParam(env, param, &value_2, 2);
    arg_2 = value_2.i;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.i;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.i = sys_Str_getSafe_f(env, arg_0, arg_1, arg_2);
    *((fr_Value*)ret) = retValue;
}

void sys_Str_getRange(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Obj arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.h;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Str_getRange_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Str_plus(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Obj arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.h;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Str_plus_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Str_chars(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Str_chars_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Str_each(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Obj arg_1; 

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.h;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    sys_Str_each_f(env, arg_0, arg_1);
}

void sys_Str_eachr(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Obj arg_1; 

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.h;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    sys_Str_eachr_f(env, arg_0, arg_1);
}

void sys_Str_any(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Obj arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.h;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.b = sys_Str_any_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Str_all(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Obj arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.h;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.b = sys_Str_all_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Str_spaces(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Int arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.i;


    retValue.h = sys_Str_spaces_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Str_lower(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Str_lower_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Str_upper(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Str_upper_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Str_capitalize(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Str_capitalize_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Str_decapitalize(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Str_decapitalize_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Str_toDisplayName(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Str_toDisplayName_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Str_fromDisplayName(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Str_fromDisplayName_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Str_justl(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Int arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.i;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Str_justl_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Str_justr(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Int arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.i;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Str_justr_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Str_padl(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Int arg_1; 
    fr_Value value_2;
    fr_Int arg_2; 
    fr_Value retValue;

    fr_getParam(env, param, &value_2, 2);
    arg_2 = value_2.i;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.i;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Str_padl_f(env, arg_0, arg_1, arg_2);
    *((fr_Value*)ret) = retValue;
}

void sys_Str_padr(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Int arg_1; 
    fr_Value value_2;
    fr_Int arg_2; 
    fr_Value retValue;

    fr_getParam(env, param, &value_2, 2);
    arg_2 = value_2.i;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.i;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Str_padr_f(env, arg_0, arg_1, arg_2);
    *((fr_Value*)ret) = retValue;
}

void sys_Str_reverse(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Str_reverse_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Str_trim(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Str_trim_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Str_trimToNull(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Str_trimToNull_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Str_trimStart(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Str_trimStart_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Str_trimEnd(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Str_trimEnd_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Str_split(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Obj arg_1; 
    fr_Value value_2;
    fr_Bool arg_2; 
    fr_Value retValue;

    fr_getParam(env, param, &value_2, 2);
    arg_2 = value_2.b;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.h;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Str_split_f(env, arg_0, arg_1, arg_2);
    *((fr_Value*)ret) = retValue;
}

void sys_Str_splitLines(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Str_splitLines_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Str_replace(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Obj arg_1; 
    fr_Value value_2;
    fr_Obj arg_2; 
    fr_Value retValue;

    fr_getParam(env, param, &value_2, 2);
    arg_2 = value_2.h;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.h;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Str_replace_f(env, arg_0, arg_1, arg_2);
    *((fr_Value*)ret) = retValue;
}

void sys_Str_numNewlines(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.i = sys_Str_numNewlines_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Str_isAscii(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.b = sys_Str_isAscii_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Str_isSpace(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.b = sys_Str_isSpace_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Str_isUpper(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.b = sys_Str_isUpper_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Str_isLower(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.b = sys_Str_isLower_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Str_isAlpha(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.b = sys_Str_isAlpha_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Str_isAlphaNum(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.b = sys_Str_isAlphaNum_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Str_localeCompare(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Obj arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.h;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.i = sys_Str_localeCompare_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Str_localeLower(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Str_localeLower_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Str_localeUpper(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Str_localeUpper_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Str_localeCapitalize(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Str_localeCapitalize_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Str_localeDecapitalize(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Str_localeDecapitalize_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Str_toBool(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Bool arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.b;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Str_toBool_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Str_toInt(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Int arg_1; 
    fr_Value value_2;
    fr_Bool arg_2; 
    fr_Value retValue;

    fr_getParam(env, param, &value_2, 2);
    arg_2 = value_2.b;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.i;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Str_toInt_f(env, arg_0, arg_1, arg_2);
    *((fr_Value*)ret) = retValue;
}

void sys_Str_toFloat(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Bool arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.b;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Str_toFloat_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Str_toCode(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Obj arg_1; 
    fr_Value value_2;
    fr_Bool arg_2; 
    fr_Value retValue;

    fr_getParam(env, param, &value_2, 2);
    arg_2 = value_2.b;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.h;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Str_toCode_f(env, arg_0, arg_1, arg_2);
    *((fr_Value*)ret) = retValue;
}

void sys_Str_toXml(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Str_toXml_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Str_finalize(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    sys_Str_finalize_f(env, arg_0);
}

void sys_Str_static__init(fr_Env env, void *param, void *ret) {


    sys_Str_static__init_f(env);
}

int sys_StrBuf__allocSize__() {return sizeof(struct sys_StrBuf_);}
void sys_StrBuf_static__init(fr_Env self, void *param, void *ret);

void sys_StrBuf_make(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Int arg_1; 

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.i;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    sys_StrBuf_make_f(env, arg_0, arg_1);
}

void sys_StrBuf_isEmpty(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.b = sys_StrBuf_isEmpty_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_StrBuf_size(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.i = sys_StrBuf_size_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_StrBuf_capacity(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.i = sys_StrBuf_capacity_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_StrBuf_capacity_(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Int arg_1; 

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.i;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    sys_StrBuf_capacity__f(env, arg_0, arg_1);
}

void sys_StrBuf_get(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Int arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.i;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.i = sys_StrBuf_get_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_StrBuf_getRange(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Obj arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.h;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_StrBuf_getRange_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_StrBuf_set(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Int arg_1; 
    fr_Value value_2;
    fr_Int arg_2; 
    fr_Value retValue;

    fr_getParam(env, param, &value_2, 2);
    arg_2 = value_2.i;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.i;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_StrBuf_set_f(env, arg_0, arg_1, arg_2);
    *((fr_Value*)ret) = retValue;
}

void sys_StrBuf_add(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Obj arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.h;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_StrBuf_add_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_StrBuf_addChar(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Int arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.i;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_StrBuf_addChar_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_StrBuf_join(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Obj arg_1; 
    fr_Value value_2;
    fr_Obj arg_2; 
    fr_Value retValue;

    fr_getParam(env, param, &value_2, 2);
    arg_2 = value_2.h;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.h;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_StrBuf_join_f(env, arg_0, arg_1, arg_2);
    *((fr_Value*)ret) = retValue;
}

void sys_StrBuf_insert(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Int arg_1; 
    fr_Value value_2;
    fr_Obj arg_2; 
    fr_Value retValue;

    fr_getParam(env, param, &value_2, 2);
    arg_2 = value_2.h;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.i;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_StrBuf_insert_f(env, arg_0, arg_1, arg_2);
    *((fr_Value*)ret) = retValue;
}

void sys_StrBuf_remove(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Int arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.i;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_StrBuf_remove_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_StrBuf_removeRange(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Obj arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.h;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_StrBuf_removeRange_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_StrBuf_replaceRange(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Obj arg_1; 
    fr_Value value_2;
    fr_Obj arg_2; 
    fr_Value retValue;

    fr_getParam(env, param, &value_2, 2);
    arg_2 = value_2.h;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.h;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_StrBuf_replaceRange_f(env, arg_0, arg_1, arg_2);
    *((fr_Value*)ret) = retValue;
}

void sys_StrBuf_clear(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_StrBuf_clear_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_StrBuf_toStr(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_StrBuf_toStr_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_StrBuf_finalize(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    sys_StrBuf_finalize_f(env, arg_0);
}

int sys_This__allocSize__() {return sizeof(struct sys_This_);}
void sys_This_static__init(fr_Env self, void *param, void *ret);

void sys_This_make(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    sys_This_make_f(env, arg_0);
}

int sys_Void__allocSize__() {return sizeof(struct sys_Void_);}
void sys_Void_static__init(fr_Env self, void *param, void *ret);

void sys_Void_make(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    sys_Void_make_f(env, arg_0);
}

int sys_ByteArray__allocSize__() {return sizeof(struct sys_ByteArray_);}
void sys_ByteArray_static__init(fr_Env self, void *param, void *ret);

void sys_ByteArray_make(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Int arg_1; 

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.i;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    sys_ByteArray_make_f(env, arg_0, arg_1);
}

void sys_ByteArray_get(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Int arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.i;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.i = sys_ByteArray_get_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_ByteArray_set(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Int arg_1; 
    fr_Value value_2;
    fr_Int arg_2; 
    fr_Value retValue;

    fr_getParam(env, param, &value_2, 2);
    arg_2 = value_2.i;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.i;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.i = sys_ByteArray_set_f(env, arg_0, arg_1, arg_2);
    *((fr_Value*)ret) = retValue;
}

void sys_ByteArray_size(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.i = sys_ByteArray_size_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_ByteArray_realloc(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Int arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.i;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.b = sys_ByteArray_realloc_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_ByteArray_copyFrom(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Obj arg_1; 
    fr_Value value_2;
    fr_Int arg_2; 
    fr_Value value_3;
    fr_Int arg_3; 
    fr_Value value_4;
    fr_Int arg_4; 
    fr_Value retValue;

    fr_getParam(env, param, &value_4, 4);
    arg_4 = value_4.i;

    fr_getParam(env, param, &value_3, 3);
    arg_3 = value_3.i;

    fr_getParam(env, param, &value_2, 2);
    arg_2 = value_2.i;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.h;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_ByteArray_copyFrom_f(env, arg_0, arg_1, arg_2, arg_3, arg_4);
    *((fr_Value*)ret) = retValue;
}

void sys_ByteArray_finalize(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    sys_ByteArray_finalize_f(env, arg_0);
}

int sys_IntArray__allocSize__() {return sizeof(struct sys_IntArray_);}
void sys_IntArray_static__init(fr_Env self, void *param, void *ret);

void sys_IntArray_make(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Int arg_1; 

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.i;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    sys_IntArray_make_f(env, arg_0, arg_1);
}

void sys_IntArray_get(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Int arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.i;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.i = sys_IntArray_get_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_IntArray_set(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Int arg_1; 
    fr_Value value_2;
    fr_Int arg_2; 
    fr_Value retValue;

    fr_getParam(env, param, &value_2, 2);
    arg_2 = value_2.i;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.i;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.i = sys_IntArray_set_f(env, arg_0, arg_1, arg_2);
    *((fr_Value*)ret) = retValue;
}

void sys_IntArray_size(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.i = sys_IntArray_size_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_IntArray_realloc(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Int arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.i;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.b = sys_IntArray_realloc_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_IntArray_copyFrom(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Obj arg_1; 
    fr_Value value_2;
    fr_Int arg_2; 
    fr_Value value_3;
    fr_Int arg_3; 
    fr_Value value_4;
    fr_Int arg_4; 
    fr_Value retValue;

    fr_getParam(env, param, &value_4, 4);
    arg_4 = value_4.i;

    fr_getParam(env, param, &value_3, 3);
    arg_3 = value_3.i;

    fr_getParam(env, param, &value_2, 2);
    arg_2 = value_2.i;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.h;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_IntArray_copyFrom_f(env, arg_0, arg_1, arg_2, arg_3, arg_4);
    *((fr_Value*)ret) = retValue;
}

void sys_IntArray_finalize(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    sys_IntArray_finalize_f(env, arg_0);
}

int sys_ObjArray__allocSize__() {return sizeof(struct sys_ObjArray_);}
void sys_ObjArray_static__init(fr_Env self, void *param, void *ret);

void sys_ObjArray_make(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Int arg_1; 

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.i;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    sys_ObjArray_make_f(env, arg_0, arg_1);
}

void sys_ObjArray_get(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Int arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.i;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_ObjArray_get_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_ObjArray_set(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Int arg_1; 
    fr_Value value_2;
    fr_Obj arg_2; 

    fr_getParam(env, param, &value_2, 2);
    arg_2 = value_2.h;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.i;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    sys_ObjArray_set_f(env, arg_0, arg_1, arg_2);
}

void sys_ObjArray_size(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.i = sys_ObjArray_size_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_ObjArray_realloc(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Int arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.i;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.b = sys_ObjArray_realloc_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_ObjArray_copyFrom(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Obj arg_1; 
    fr_Value value_2;
    fr_Int arg_2; 
    fr_Value value_3;
    fr_Int arg_3; 
    fr_Value value_4;
    fr_Int arg_4; 
    fr_Value retValue;

    fr_getParam(env, param, &value_4, 4);
    arg_4 = value_4.i;

    fr_getParam(env, param, &value_3, 3);
    arg_3 = value_3.i;

    fr_getParam(env, param, &value_2, 2);
    arg_2 = value_2.i;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.h;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_ObjArray_copyFrom_f(env, arg_0, arg_1, arg_2, arg_3, arg_4);
    *((fr_Value*)ret) = retValue;
}

void sys_ObjArray_finalize(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    sys_ObjArray_finalize_f(env, arg_0);
}

int sys_Slot__allocSize__() {return sizeof(struct sys_Slot_);}
void sys_Slot_static__init(fr_Env self, void *param, void *ret);

void sys_Slot_find(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Bool arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.b;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Slot_find_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Slot_findMethod(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Bool arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.b;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Slot_findMethod_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Slot_findField(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Bool arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.b;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Slot_findField_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Slot_findFunc(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Bool arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.b;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Slot_findFunc_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Slot_make(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    sys_Slot_make_f(env, arg_0);
}

void sys_Slot_parent(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Slot_parent_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Slot_name(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Slot_name_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Slot_qname(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Slot_qname_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Slot_isField(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.b = sys_Slot_isField_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Slot_isMethod(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.b = sys_Slot_isMethod_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Slot_isAbstract(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.b = sys_Slot_isAbstract_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Slot_isConst(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.b = sys_Slot_isConst_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Slot_isCtor(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.b = sys_Slot_isCtor_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Slot_isInternal(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.b = sys_Slot_isInternal_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Slot_isNative(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.b = sys_Slot_isNative_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Slot_isOverride(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.b = sys_Slot_isOverride_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Slot_isPrivate(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.b = sys_Slot_isPrivate_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Slot_isProtected(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.b = sys_Slot_isProtected_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Slot_isPublic(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.b = sys_Slot_isPublic_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Slot_isStatic(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.b = sys_Slot_isStatic_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Slot_isSynthetic(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.b = sys_Slot_isSynthetic_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Slot_isVirtual(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.b = sys_Slot_isVirtual_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Slot_facets(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Slot_facets_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Slot_facet(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Obj arg_1; 
    fr_Value value_2;
    fr_Bool arg_2; 
    fr_Value retValue;

    fr_getParam(env, param, &value_2, 2);
    arg_2 = value_2.b;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.h;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Slot_facet_f(env, arg_0, arg_1, arg_2);
    *((fr_Value*)ret) = retValue;
}

void sys_Slot_hasFacet(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Obj arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.h;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.b = sys_Slot_hasFacet_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Slot_doc(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Slot_doc_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Slot_toStr(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Slot_toStr_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Slot_signature(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Slot_signature_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

int sys_Field__allocSize__() {return sizeof(struct sys_Field_);}
void sys_Field_static__init(fr_Env self, void *param, void *ret);

void sys_Field_makeSetFunc(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Field_makeSetFunc_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Field_privateMake(fr_Env env, void *param, void *ret) {
    fr_Value retValue;


    retValue.h = sys_Field_privateMake_f(env);
    *((fr_Value*)ret) = retValue;
}

void sys_Field_type(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Field_type_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Field_get(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Obj arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.h;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Field_get_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Field_set(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Obj arg_1; 
    fr_Value value_2;
    fr_Obj arg_2; 

    fr_getParam(env, param, &value_2, 2);
    arg_2 = value_2.h;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.h;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    sys_Field_set_f(env, arg_0, arg_1, arg_2);
}

void sys_Field_make(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    sys_Field_make_f(env, arg_0);
}

int sys_Func__allocSize__() {return sizeof(struct sys_Func_);}
void sys_Func_static__init(fr_Env self, void *param, void *ret);

void sys_Func_make(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    sys_Func_make_f(env, arg_0);
}

void sys_Func_returns(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Func_returns_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Func_arity(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.i = sys_Func_arity_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Func_params(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Func_params_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Func_method(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Func_method_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Func_callList(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Obj arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.h;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Func_callList_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Func_callOn(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Obj arg_1; 
    fr_Value value_2;
    fr_Obj arg_2; 
    fr_Value retValue;

    fr_getParam(env, param, &value_2, 2);
    arg_2 = value_2.h;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.h;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Func_callOn_f(env, arg_0, arg_1, arg_2);
    *((fr_Value*)ret) = retValue;
}

void sys_Func_call(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Obj arg_1; 
    fr_Value value_2;
    fr_Obj arg_2; 
    fr_Value value_3;
    fr_Obj arg_3; 
    fr_Value value_4;
    fr_Obj arg_4; 
    fr_Value value_5;
    fr_Obj arg_5; 
    fr_Value value_6;
    fr_Obj arg_6; 
    fr_Value value_7;
    fr_Obj arg_7; 
    fr_Value value_8;
    fr_Obj arg_8; 
    fr_Value retValue;

    fr_getParam(env, param, &value_8, 8);
    arg_8 = value_8.h;

    fr_getParam(env, param, &value_7, 7);
    arg_7 = value_7.h;

    fr_getParam(env, param, &value_6, 6);
    arg_6 = value_6.h;

    fr_getParam(env, param, &value_5, 5);
    arg_5 = value_5.h;

    fr_getParam(env, param, &value_4, 4);
    arg_4 = value_4.h;

    fr_getParam(env, param, &value_3, 3);
    arg_3 = value_3.h;

    fr_getParam(env, param, &value_2, 2);
    arg_2 = value_2.h;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.h;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Func_call_f(env, arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8);
    *((fr_Value*)ret) = retValue;
}

void sys_Func_bind(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Obj arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.h;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Func_bind_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Func_retype(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Obj arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.h;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Func_retype_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Func_enterCtor(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    sys_Func_enterCtor_f(env, arg_0);
}

void sys_Func_exitCtor(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    sys_Func_exitCtor_f(env, arg_0);
}

int sys_Method__allocSize__() {return sizeof(struct sys_Method_);}
void sys_Method_static__init(fr_Env self, void *param, void *ret);

void sys_Method_privateMake(fr_Env env, void *param, void *ret) {
    fr_Value retValue;


    retValue.h = sys_Method_privateMake_f(env);
    *((fr_Value*)ret) = retValue;
}

void sys_Method_returns(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Method_returns_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Method_params(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Method_params_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Method_func(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Method_func_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Method_callList(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Obj arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.h;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Method_callList_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Method_callOn(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Obj arg_1; 
    fr_Value value_2;
    fr_Obj arg_2; 
    fr_Value retValue;

    fr_getParam(env, param, &value_2, 2);
    arg_2 = value_2.h;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.h;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Method_callOn_f(env, arg_0, arg_1, arg_2);
    *((fr_Value*)ret) = retValue;
}

void sys_Method_call(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Obj arg_1; 
    fr_Value value_2;
    fr_Obj arg_2; 
    fr_Value value_3;
    fr_Obj arg_3; 
    fr_Value value_4;
    fr_Obj arg_4; 
    fr_Value value_5;
    fr_Obj arg_5; 
    fr_Value value_6;
    fr_Obj arg_6; 
    fr_Value value_7;
    fr_Obj arg_7; 
    fr_Value value_8;
    fr_Obj arg_8; 
    fr_Value retValue;

    fr_getParam(env, param, &value_8, 8);
    arg_8 = value_8.h;

    fr_getParam(env, param, &value_7, 7);
    arg_7 = value_7.h;

    fr_getParam(env, param, &value_6, 6);
    arg_6 = value_6.h;

    fr_getParam(env, param, &value_5, 5);
    arg_5 = value_5.h;

    fr_getParam(env, param, &value_4, 4);
    arg_4 = value_4.h;

    fr_getParam(env, param, &value_3, 3);
    arg_3 = value_3.h;

    fr_getParam(env, param, &value_2, 2);
    arg_2 = value_2.h;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.h;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Method_call_f(env, arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8);
    *((fr_Value*)ret) = retValue;
}

void sys_Method_make(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    sys_Method_make_f(env, arg_0);
}

int sys_Param__allocSize__() {return sizeof(struct sys_Param_);}
void sys_Param_static__init(fr_Env self, void *param, void *ret);

void sys_Param_make(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    sys_Param_make_f(env, arg_0);
}

void sys_Param_name(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Param_name_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Param_type(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Param_type_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Param_hasDefault(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.b = sys_Param_hasDefault_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Param_toStr(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Param_toStr_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

int sys_Pod__allocSize__() {return sizeof(struct sys_Pod_);}
void sys_Pod_static__init(fr_Env self, void *param, void *ret);

void sys_Pod_of(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Pod_of_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Pod_list(fr_Env env, void *param, void *ret) {
    fr_Value retValue;


    retValue.h = sys_Pod_list_f(env);
    *((fr_Value*)ret) = retValue;
}

void sys_Pod_find(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Bool arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.b;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Pod_find_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Pod_load(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Pod_load_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Pod_make(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    sys_Pod_make_f(env, arg_0);
}

void sys_Pod_name(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Pod_name_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Pod_version(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Pod_version_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Pod_depends(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Pod_depends_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Pod_uri(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Pod_uri_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Pod_toStr(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Pod_toStr_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Pod_meta(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Pod_meta_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Pod_types(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Pod_types_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Pod_type(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Obj arg_1; 
    fr_Value value_2;
    fr_Bool arg_2; 
    fr_Value retValue;

    fr_getParam(env, param, &value_2, 2);
    arg_2 = value_2.b;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.h;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Pod_type_f(env, arg_0, arg_1, arg_2);
    *((fr_Value*)ret) = retValue;
}

void sys_Pod_files(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Pod_files_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Pod_file(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Obj arg_1; 
    fr_Value value_2;
    fr_Bool arg_2; 
    fr_Value retValue;

    fr_getParam(env, param, &value_2, 2);
    arg_2 = value_2.b;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.h;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Pod_file_f(env, arg_0, arg_1, arg_2);
    *((fr_Value*)ret) = retValue;
}

void sys_Pod_doc(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Pod_doc_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Pod_log(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Pod_log_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Pod_props(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Obj arg_1; 
    fr_Value value_2;
    fr_Obj arg_2; 
    fr_Value retValue;

    fr_getParam(env, param, &value_2, 2);
    arg_2 = value_2.h;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.h;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Pod_props_f(env, arg_0, arg_1, arg_2);
    *((fr_Value*)ret) = retValue;
}

void sys_Pod_config(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Obj arg_1; 
    fr_Value value_2;
    fr_Obj arg_2; 
    fr_Value retValue;

    fr_getParam(env, param, &value_2, 2);
    arg_2 = value_2.h;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.h;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Pod_config_f(env, arg_0, arg_1, arg_2);
    *((fr_Value*)ret) = retValue;
}

void sys_Pod_locale(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Obj arg_1; 
    fr_Value value_2;
    fr_Obj arg_2; 
    fr_Value retValue;

    fr_getParam(env, param, &value_2, 2);
    arg_2 = value_2.h;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.h;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Pod_locale_f(env, arg_0, arg_1, arg_2);
    *((fr_Value*)ret) = retValue;
}

int sys_Type__allocSize__() {return sizeof(struct sys_Type_);}
void sys_Type_static__init(fr_Env self, void *param, void *ret);

void sys_Type_privateMake(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    sys_Type_privateMake_f(env, arg_0);
}

void sys_Type_of(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Type_of_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Type_find(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Bool arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.b;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Type_find_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Type_pod(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Type_pod_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Type_name(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Type_name_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Type_qname(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Type_qname_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Type_signature(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Type_signature_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Type_base(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Type_base_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Type_mixins(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Type_mixins_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Type_inheritance(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Type_inheritance_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Type_fits(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Obj arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.h;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.b = sys_Type_fits_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Type_isVal(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.b = sys_Type_isVal_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Type_isNullable(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.b = sys_Type_isNullable_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Type_toNullable(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Type_toNullable_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Type_toNonNullable(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Type_toNonNullable_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Type_isGeneric(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.b = sys_Type_isGeneric_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Type_params(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Type_params_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Type_parameterize(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Obj arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.h;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Type_parameterize_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Type_toListOf(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Type_toListOf_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Type_emptyList(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Type_emptyList_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Type_isAbstract(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.b = sys_Type_isAbstract_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Type_isClass(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.b = sys_Type_isClass_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Type_isConst(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.b = sys_Type_isConst_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Type_isEnum(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.b = sys_Type_isEnum_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Type_isFacet(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.b = sys_Type_isFacet_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Type_isFinal(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.b = sys_Type_isFinal_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Type_isInternal(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.b = sys_Type_isInternal_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Type_isMixin(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.b = sys_Type_isMixin_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Type_isPublic(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.b = sys_Type_isPublic_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Type_isSynthetic(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.b = sys_Type_isSynthetic_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Type_fields(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Type_fields_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Type_methods(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Type_methods_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Type_slots(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Type_slots_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Type_field(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Obj arg_1; 
    fr_Value value_2;
    fr_Bool arg_2; 
    fr_Value retValue;

    fr_getParam(env, param, &value_2, 2);
    arg_2 = value_2.b;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.h;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Type_field_f(env, arg_0, arg_1, arg_2);
    *((fr_Value*)ret) = retValue;
}

void sys_Type_method(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Obj arg_1; 
    fr_Value value_2;
    fr_Bool arg_2; 
    fr_Value retValue;

    fr_getParam(env, param, &value_2, 2);
    arg_2 = value_2.b;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.h;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Type_method_f(env, arg_0, arg_1, arg_2);
    *((fr_Value*)ret) = retValue;
}

void sys_Type_slot(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Obj arg_1; 
    fr_Value value_2;
    fr_Bool arg_2; 
    fr_Value retValue;

    fr_getParam(env, param, &value_2, 2);
    arg_2 = value_2.b;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.h;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Type_slot_f(env, arg_0, arg_1, arg_2);
    *((fr_Value*)ret) = retValue;
}

void sys_Type_make(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Obj arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.h;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Type_make_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Type_facets(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Type_facets_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Type_facet(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Obj arg_1; 
    fr_Value value_2;
    fr_Bool arg_2; 
    fr_Value retValue;

    fr_getParam(env, param, &value_2, 2);
    arg_2 = value_2.b;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.h;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Type_facet_f(env, arg_0, arg_1, arg_2);
    *((fr_Value*)ret) = retValue;
}

void sys_Type_hasFacet(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value value_1;
    fr_Obj arg_1; 
    fr_Value retValue;

    fr_getParam(env, param, &value_1, 1);
    arg_1 = value_1.h;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.b = sys_Type_hasFacet_f(env, arg_0, arg_1);
    *((fr_Value*)ret) = retValue;
}

void sys_Type_doc(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Type_doc_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Type_toStr(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Type_toStr_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

void sys_Type_toLocale(fr_Env env, void *param, void *ret) {
    fr_Value value_0;
    fr_Obj arg_0; 
    fr_Value retValue;

    fr_getParam(env, param, &value_0, 0);
    arg_0 = value_0.h;


    retValue.h = sys_Type_toLocale_f(env, arg_0);
    *((fr_Value*)ret) = retValue;
}

