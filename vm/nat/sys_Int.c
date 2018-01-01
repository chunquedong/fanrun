#include "sys.h"
#include <stdio.h>
#include <wchar.h>
#include <math.h>

//sys_Int_null sys_Int_fromStr1(fr_Env __env, sys_Str s) {
//    return sys_Int_fromStr2(__env, s, 10);
//}
//sys_Int_null sys_Int_fromStr2(fr_Env __env, sys_Str s, sys_Int radix){
//    return sys_Int_fromStr3(__env, s, 10, true);
//}
sys_Int_null sys_Int_fromStr3(fr_Env __env, sys_Str s, sys_Int radix, sys_Bool checked){
    wchar_t *str_end;
    sys_Int res = wcstoll(s->data, &str_end, (int)radix);
    if (checked && str_end == s->data) {
        sys_ParseErr e = FR_ALLOC(sys_ParseErr);
        FR_THROW(e);
    }
    return fr_box_int(__env, res);
}
//sys_Int sys_Int_random0(fr_Env __env){
//    return sys_Int_random1(__env, NULL);
//}
sys_Int sys_Int_random1(fr_Env __env, sys_Range_null r){
    if (r == NULL) {
        sys_Int t = rand();
        sys_Int p = rand();
        sys_Int res = t | (p<<32);
        return res;
    }
    else {
        sys_Int res = rand();
        sys_Int size = r->_end - r->_start;
        res = r->_start + (res % size);
        return res;
    }
}
sys_Int_null sys_Int_privateMake0(fr_Env __env){ return 0; }
sys_Bool sys_Int_equals1_val(fr_Env __env, sys_Int_val __self, sys_Obj_null obj){
    if (!obj) return false;
    if (FR_TYPE_IS(obj, sys_Int)) {
        sys_Int_ref other = (sys_Int_ref)obj;
        return __self == other->_val;
    }
    return false;
}
sys_Int sys_Int_compare1_val(fr_Env __env, sys_Int_val __self, sys_Obj obj){
    if (!obj) fr_throwNPE(__env);
    if (FR_TYPE_IS(obj, sys_Int)) {
        sys_Int_ref other = (sys_Int_ref)obj;
        return __self - other->_val;
    }
    else {
        sys_Int other = (sys_Int)obj;
        return __self - other;
    }
}
sys_Int sys_Int_hash0_val(fr_Env __env, sys_Int_val __self){
    return __self;
}
sys_Int sys_Int_negate0_val(fr_Env __env, sys_Int_val __self){
    return -__self;
}
sys_Int sys_Int_increment0_val(fr_Env __env, sys_Int_val __self){
    return ++__self;
}
sys_Int sys_Int_decrement0_val(fr_Env __env, sys_Int_val __self){
    return --__self;
}
sys_Int sys_Int_mult1_val(fr_Env __env, sys_Int_val __self, sys_Int b){
    return __self * b;
}
sys_Float sys_Int_multFloat1_val(fr_Env __env, sys_Int_val __self, sys_Float b){
    return (sys_Float)__self * b;
}
sys_Int sys_Int_div1_val(fr_Env __env, sys_Int_val __self, sys_Int b){
    if (b == 0) {
        sys_Err e = FR_ALLOC(sys_Err);
        FR_THROW(e);
    }
    return __self / b;
}
sys_Float sys_Int_divFloat1_val(fr_Env __env, sys_Int_val __self, sys_Float b){
    return __self / b;
}
sys_Int sys_Int_mod1_val(fr_Env __env, sys_Int_val __self, sys_Int b){
    return __self % b;
}
sys_Float sys_Int_modFloat1_val(fr_Env __env, sys_Int_val __self, sys_Float b){
    return fmod(__self, b);
}
sys_Int sys_Int_plus1_val(fr_Env __env, sys_Int_val __self, sys_Int b){
    return __self + b;
}
sys_Float sys_Int_plusFloat1_val(fr_Env __env, sys_Int_val __self, sys_Float b){
    return __self+b;
}
sys_Int sys_Int_minus1_val(fr_Env __env, sys_Int_val __self, sys_Int b){
    return __self - b;
}
sys_Float sys_Int_minusFloat1_val(fr_Env __env, sys_Int_val __self, sys_Float b){
    return __self - b;
}
sys_Int sys_Int_not0_val(fr_Env __env, sys_Int_val __self){
    return ~__self;
}
sys_Int sys_Int_and1_val(fr_Env __env, sys_Int_val __self, sys_Int b){
    return __self & b;
}
sys_Int sys_Int_or1_val(fr_Env __env, sys_Int_val __self, sys_Int b){
    return __self | b;
}
sys_Int sys_Int_xor1_val(fr_Env __env, sys_Int_val __self, sys_Int b){
    return __self ^ b;
}
sys_Int sys_Int_shiftl1_val(fr_Env __env, sys_Int_val __self, sys_Int b){
    return __self << b;
}
sys_Int sys_Int_shiftr1_val(fr_Env __env, sys_Int_val __self, sys_Int b){
    return __self >> b;
}
sys_Int sys_Int_abs0_val(fr_Env __env, sys_Int_val __self){
    return llabs(__self);
}
sys_Int sys_Int_min1_val(fr_Env __env, sys_Int_val __self, sys_Int that){
    return __self > that ? that : __self;
}
sys_Int sys_Int_max1_val(fr_Env __env, sys_Int_val __self, sys_Int that){
    return __self > that ? __self : that;
}
sys_Int sys_Int_pow1_val(fr_Env __env, sys_Int_val __self, sys_Int pow){
    if (pow < 0) {
        sys_ArgErr e = FR_ALLOC(sys_ArgErr);
        FR_THROW(e);
    }
    return powf(__self, pow);
}
sys_Bool sys_Int_isEven0_val(fr_Env __env, sys_Int_val __self){
    return (__self & 1) == 0;
}
sys_Bool sys_Int_isOdd0_val(fr_Env __env, sys_Int_val __self){
    return (__self & 1) == 1;
}
sys_Bool sys_Int_isSpace0_val(fr_Env __env, sys_Int_val __self){
    return iswspace((wchar_t)__self);
}
sys_Bool sys_Int_isAlpha0_val(fr_Env __env, sys_Int_val __self){
    return iswalpha((wchar_t)__self);
}
sys_Bool sys_Int_isAlphaNum0_val(fr_Env __env, sys_Int_val __self){
    return iswalnum((wchar_t)__self);
}
sys_Bool sys_Int_isUpper0_val(fr_Env __env, sys_Int_val __self){
    return iswupper((wchar_t)__self);
}
sys_Bool sys_Int_isLower0_val(fr_Env __env, sys_Int_val __self){
    return iswlower((wchar_t)__self);
}
sys_Int sys_Int_upper0_val(fr_Env __env, sys_Int_val __self){
    return towupper((wchar_t)__self);
}
sys_Int sys_Int_lower0_val(fr_Env __env, sys_Int_val __self){
    return towlower((wchar_t)__self);
}
//sys_Bool sys_Int_isDigit0_val(fr_Env __env, sys_Int_val __self){
//    return iswdigit((wchar_t)__self);
//}
sys_Bool sys_Int_isDigit1_val(fr_Env __env, sys_Int_val __self, sys_Int radix){
    if (radix <= 10) {
        return iswdigit((wchar_t)__self);
    }
    else if (radix <= 16) {
        return iswxdigit((wchar_t)__self);
    }
    else {
        FR_ALLOC_THROW(sys_UnsupportedErr);
        return false;
    }
}
//sys_Int_null sys_Int_toDigit0_val(fr_Env __env, sys_Int_val __self){
//    return sys_Int_toDigit1_val(__env, __self, 10);
//}
sys_Int_null sys_Int_toDigit1_val(fr_Env __env, sys_Int_val __self, sys_Int radix){
    const wchar_t *str= L"0123456789abcdef";
    if (__self < 16 && __self < radix) {
        sys_Int res = str[__self];
        return fr_box_int(__env, res);
    }
    return NULL;
}
//sys_Int_null sys_Int_fromDigit0_val(fr_Env __env, sys_Int_val __self){
//    return sys_Int_fromDigit1_val(__env, __self, 10);
//}
sys_Int_null sys_Int_fromDigit1_val(fr_Env __env, sys_Int_val __self, sys_Int radix){
    wchar_t c = (wchar_t)__self;
    sys_Int res = 0;
    if (radix == 10) {
        if (c >= L'0' && c <= L'9') {
            res = c - L'0';
            return fr_box_int(__env, res);
        }
    }
    else if (radix == 16) {
        if (c >= L'0' && c <= L'9') {
            res = c - L'0';
            return fr_box_int(__env, res);
        }
        c = towlower(c);
        if (c >= L'a' && c <= L'f') {
            res = (c - L'a')+10;
            return fr_box_int(__env, res);
        }
    }
    return NULL;
}
sys_Bool sys_Int_equalsIgnoreCase1_val(fr_Env __env, sys_Int_val __self, sys_Int ch){
    wchar_t a = towlower((wchar_t)__self);
    wchar_t b = towlower((wchar_t)ch);
    return a == b;
}
sys_Bool sys_Int_localeIsUpper0_val(fr_Env __env, sys_Int_val __self){
    return iswupper((wchar_t)__self);
}
sys_Bool sys_Int_localeIsLower0_val(fr_Env __env, sys_Int_val __self){
    return iswlower((wchar_t)__self);
}
sys_Int sys_Int_localeUpper0_val(fr_Env __env, sys_Int_val __self){
    return towupper((wchar_t)__self);
}
sys_Int sys_Int_localeLower0_val(fr_Env __env, sys_Int_val __self){
    return towlower((wchar_t)__self);
}
sys_Str sys_Int_toStr0_val(fr_Env __env, sys_Int_val __self){
    wchar_t buf[256];
    swprintf(buf, 256, L"%lld", __self);
    return fr_newStrNT(__env, buf);
}

//sys_Str sys_Int_toHex0_val(fr_Env __env, sys_Int_val __self){
//    char buf[256];
//    snprintf(buf, 256, "%llx", __self);
//    return fr_newStrUtf8(__env, buf);
//}
sys_Str sys_Int_toHex1_val(fr_Env __env, sys_Int_val __self, sys_Int_null width){
    char format[256];
    char buf[256];
    
    if (!width) {
        snprintf(buf, 256, "%llx", __self);
    } else {
        snprintf(format, 256, "%%0%lldllx", __self);
        snprintf(buf, 256, format, __self);
    }
    return fr_newStrUtf8(__env, buf);
}
//sys_Str sys_Int_toRadix1_val(fr_Env __env, sys_Int_val __self, sys_Int radix){
//    return sys_Int_toRadix2_val(__env, __self, radix, NULL);
//}
sys_Str sys_Int_toRadix2_val(fr_Env __env, sys_Int_val __self, sys_Int radix, sys_Int_null width){
    if (radix == 10) {
        char format[256];
        char buf[256];
        
        if (!width) {
            snprintf(buf, 256, "%lld", __self);
        } else {
            snprintf(format, 256, "%%0%lldlld", __self);
            snprintf(buf, 256, format, __self);
        }
        return fr_newStrUtf8(__env, buf);
    }
    else if (radix == 16) {
        return sys_Int_toHex1_val(__env, __self, width);
    }
    FR_ALLOC_THROW(sys_UnsupportedErr);
}
sys_Str sys_Int_toChar0_val(fr_Env __env, sys_Int_val __self){
    wchar_t buf[256];
    swprintf(buf, 256, L"%c", (wchar_t)__self);
    return fr_newStrNT(__env, buf);
}
//sys_Str sys_Int_toCode0_val(fr_Env __env, sys_Int_val __self){
//    return sys_Int_toCode1_val(__env, __self, 10);
//}
sys_Str sys_Int_toCode1_val(fr_Env __env, sys_Int_val __self, sys_Int base){
    if (base == 10) {
        char buf[256];
        snprintf(buf, 256, "%lld", __self);
        return fr_newStrUtf8(__env, buf);
    }
    else if (base == 16) {
        char buf[256];
        snprintf(buf, 256, "%llx", __self);
        return fr_newStrUtf8(__env, buf);
    }
    FR_ALLOC_THROW(sys_UnsupportedErr);
}
void sys_Int_times1_val(fr_Env __env, sys_Int_val __self, sys_Func c){
    for (int i=0; i<__self; ++i) {
        fr_Obj a = fr_box_int(__env, i);
        FR_VCALL(sys_Func, call1, c, a);
    }
}
void sys_Int_make0_val(fr_Env __env, sys_Int_val __self){
    __self = 0;
}

