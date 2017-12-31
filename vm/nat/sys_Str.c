//
//  sys_Str.c
//  run
//
//  Created by yangjiandong on 2017/12/17.
//  Copyright © 2017年 yangjiandong. All rights reserved.
//

#include "sys.h"
#include "runtime.h"

#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include "utf8.h"

sys_Int strHash(sys_Str str) {
    sys_Int hashValue = 0;
    size_t i;
    for (i=0; i<str->size; ++i) {
        hashValue = (str->data[i]) + 31 * hashValue;
    }
    return hashValue;
}

size_t utf8decode(char const *str, wchar_t *des, size_t n, int *illegal) {
    if (n == 0)
        return 0;
    
    char *s = (char *)str;
    size_t i = 0;
    wchar_t uc = 0;
    int r_illegal_all = 0, r_illegal;
    
    while ((uc = getu8c(&s, &r_illegal)))
    {
        if (i < (n - 1))
        {
            des[i++] = uc;
            r_illegal_all += r_illegal;
        }
        else
        {
            break;
        }
    }
    
    des[i] = 0;
    if (illegal)
    {
        *illegal = r_illegal_all + r_illegal;
    }
    
    return i;
}

size_t utf8encode(wchar_t *us, char *des, size_t n, int *illegal)
{
    if (n == 0)
        return 0;
    
    char *s = des;
    size_t left = n;
    size_t len = 0;
    int r_illegal = 0;
    
    *s = 0;
    while (*us)
    {
        int ret = putu8c(*us, &s, &left);
        if (ret > 0)
        {
            len += ret;
        }
        else if (ret == -1)
        {
            r_illegal += 1;
        }
        else
        {
            break;
        }
        
        ++us;
    }
    
    if (illegal)
    {
        *illegal = r_illegal;
    }
    
    return len;
}

/////////////////////////////////////////////////////////////

void sys_Str_privateMake0(fr_Env __env, sys_Str_ref __self){ return; }
sys_Str sys_Str_fromChars1(fr_Env __env, sys_List chars){ return 0; }
sys_Bool sys_Str_equals1(fr_Env __env, sys_Str_ref __self, sys_Obj_null obj){ return 0; }
sys_Bool sys_Str_equalsIgnoreCase1(fr_Env __env, sys_Str_ref __self, sys_Str s){ return 0; }
sys_Int sys_Str_compare1(fr_Env __env, sys_Str_ref __self, sys_Obj obj){ return 0; }
sys_Int sys_Str_compareIgnoreCase1(fr_Env __env, sys_Str_ref __self, sys_Str s){ return 0; }
sys_Int sys_Str_hash0(fr_Env __env, sys_Str_ref __self){ return 0; }
sys_Str sys_Str_toStr0(fr_Env __env, sys_Str_ref __self){
    return __self;
}
sys_Str sys_Str_toLocale0(fr_Env __env, sys_Str_ref __self){ return 0; }
sys_Bool sys_Str_isEmpty0(fr_Env __env, sys_Str_ref __self){ return 0; }
sys_Int sys_Str_size0(fr_Env __env, sys_Str_ref __self){ return 0; }
sys_Str sys_Str_intern0(fr_Env __env, sys_Str_ref __self){ return 0; }
sys_Bool sys_Str_startsWith1(fr_Env __env, sys_Str_ref __self, sys_Str s){ return 0; }
sys_Bool sys_Str_endsWith1(fr_Env __env, sys_Str_ref __self, sys_Str s){ return 0; }
sys_Int_null sys_Str_index1(fr_Env __env, sys_Str_ref __self, sys_Str s){ return 0; }
sys_Int_null sys_Str_index2(fr_Env __env, sys_Str_ref __self, sys_Str s, sys_Int offset){ return 0; }
sys_Int_null sys_Str_indexr1(fr_Env __env, sys_Str_ref __self, sys_Str s){ return 0; }
sys_Int_null sys_Str_indexr2(fr_Env __env, sys_Str_ref __self, sys_Str s, sys_Int offset){ return 0; }
sys_Int_null sys_Str_indexIgnoreCase1(fr_Env __env, sys_Str_ref __self, sys_Str s){ return 0; }
sys_Int_null sys_Str_indexIgnoreCase2(fr_Env __env, sys_Str_ref __self, sys_Str s, sys_Int offset){ return 0; }
sys_Int_null sys_Str_indexrIgnoreCase1(fr_Env __env, sys_Str_ref __self, sys_Str s){ return 0; }
sys_Int_null sys_Str_indexrIgnoreCase2(fr_Env __env, sys_Str_ref __self, sys_Str s, sys_Int offset){ return 0; }
sys_Bool sys_Str_contains1(fr_Env __env, sys_Str_ref __self, sys_Str s){ return 0; }
sys_Bool sys_Str_containsChar1(fr_Env __env, sys_Str_ref __self, sys_Int ch){ return 0; }
sys_Int sys_Str_get1(fr_Env __env, sys_Str_ref __self, sys_Int index){ return 0; }
sys_Int sys_Str_getSafe1(fr_Env __env, sys_Str_ref __self, sys_Int index){ return 0; }
sys_Int sys_Str_getSafe2(fr_Env __env, sys_Str_ref __self, sys_Int index, sys_Int def){ return 0; }
sys_Str sys_Str_getRange1(fr_Env __env, sys_Str_ref __self, sys_Range range){ return 0; }
sys_Str sys_Str_plus1(fr_Env __env, sys_Str_ref __self, sys_Obj_null obj){ return 0; }
sys_List sys_Str_chars0(fr_Env __env, sys_Str_ref __self){ return 0; }
void sys_Str_each1(fr_Env __env, sys_Str_ref __self, sys_Func c){ return; }
void sys_Str_eachr1(fr_Env __env, sys_Str_ref __self, sys_Func c){ return; }
sys_Bool sys_Str_any1(fr_Env __env, sys_Str_ref __self, sys_Func c){ return 0; }
sys_Bool sys_Str_all1(fr_Env __env, sys_Str_ref __self, sys_Func c){ return 0; }
sys_Str sys_Str_spaces1(fr_Env __env, sys_Int n){ return 0; }
sys_Str sys_Str_lower0(fr_Env __env, sys_Str_ref __self){ return 0; }
sys_Str sys_Str_upper0(fr_Env __env, sys_Str_ref __self){ return 0; }
sys_Str sys_Str_capitalize0(fr_Env __env, sys_Str_ref __self){ return 0; }
sys_Str sys_Str_decapitalize0(fr_Env __env, sys_Str_ref __self){ return 0; }
sys_Str sys_Str_toDisplayName0(fr_Env __env, sys_Str_ref __self){ return 0; }
sys_Str sys_Str_fromDisplayName0(fr_Env __env, sys_Str_ref __self){ return 0; }
sys_Str sys_Str_justl1(fr_Env __env, sys_Str_ref __self, sys_Int width){ return 0; }
sys_Str sys_Str_justr1(fr_Env __env, sys_Str_ref __self, sys_Int width){ return 0; }
sys_Str sys_Str_padl1(fr_Env __env, sys_Str_ref __self, sys_Int width){ return 0; }
sys_Str sys_Str_padl2(fr_Env __env, sys_Str_ref __self, sys_Int width, sys_Int char_){ return 0; }
sys_Str sys_Str_padr1(fr_Env __env, sys_Str_ref __self, sys_Int width){ return 0; }
sys_Str sys_Str_padr2(fr_Env __env, sys_Str_ref __self, sys_Int width, sys_Int char_){ return 0; }
sys_Str sys_Str_reverse0(fr_Env __env, sys_Str_ref __self){ return 0; }
sys_Str sys_Str_trim0(fr_Env __env, sys_Str_ref __self){ return 0; }
sys_Str_null sys_Str_trimToNull0(fr_Env __env, sys_Str_ref __self){ return 0; }
sys_Str sys_Str_trimStart0(fr_Env __env, sys_Str_ref __self){ return 0; }
sys_Str sys_Str_trimEnd0(fr_Env __env, sys_Str_ref __self){ return 0; }
sys_List sys_Str_split0(fr_Env __env, sys_Str_ref __self){ return 0; }
sys_List sys_Str_split1(fr_Env __env, sys_Str_ref __self, sys_Int_null separator){ return 0; }
sys_List sys_Str_split2(fr_Env __env, sys_Str_ref __self, sys_Int_null separator, sys_Bool trim){ return 0; }
sys_List sys_Str_splitLines0(fr_Env __env, sys_Str_ref __self){ return 0; }
sys_Str sys_Str_replace2(fr_Env __env, sys_Str_ref __self, sys_Str from, sys_Str to){ return 0; }
sys_Int sys_Str_numNewlines0(fr_Env __env, sys_Str_ref __self){ return 0; }
sys_Bool sys_Str_isAscii0(fr_Env __env, sys_Str_ref __self){ return 0; }
sys_Bool sys_Str_isSpace0(fr_Env __env, sys_Str_ref __self){ return 0; }
sys_Bool sys_Str_isUpper0(fr_Env __env, sys_Str_ref __self){ return 0; }
sys_Bool sys_Str_isLower0(fr_Env __env, sys_Str_ref __self){ return 0; }
sys_Bool sys_Str_isAlpha0(fr_Env __env, sys_Str_ref __self){ return 0; }
sys_Bool sys_Str_isAlphaNum0(fr_Env __env, sys_Str_ref __self){ return 0; }
sys_Int sys_Str_localeCompare1(fr_Env __env, sys_Str_ref __self, sys_Str s){ return 0; }
sys_Str sys_Str_localeLower0(fr_Env __env, sys_Str_ref __self){ return 0; }
sys_Str sys_Str_localeUpper0(fr_Env __env, sys_Str_ref __self){ return 0; }
sys_Str sys_Str_localeCapitalize0(fr_Env __env, sys_Str_ref __self){ return 0; }
sys_Str sys_Str_localeDecapitalize0(fr_Env __env, sys_Str_ref __self){ return 0; }
sys_Bool_null sys_Str_toBool0(fr_Env __env, sys_Str_ref __self){ return 0; }
sys_Bool_null sys_Str_toBool1(fr_Env __env, sys_Str_ref __self, sys_Bool checked){ return 0; }
sys_Int_null sys_Str_toInt0(fr_Env __env, sys_Str_ref __self){ return 0; }
sys_Int_null sys_Str_toInt1(fr_Env __env, sys_Str_ref __self, sys_Int radix){ return 0; }
sys_Int_null sys_Str_toInt2(fr_Env __env, sys_Str_ref __self, sys_Int radix, sys_Bool checked){ return 0; }
sys_Float_null sys_Str_toFloat0(fr_Env __env, sys_Str_ref __self){ return 0; }
sys_Float_null sys_Str_toFloat1(fr_Env __env, sys_Str_ref __self, sys_Bool checked){ return 0; }
sys_Str sys_Str_toCode0(fr_Env __env, sys_Str_ref __self){ return 0; }
sys_Str sys_Str_toCode1(fr_Env __env, sys_Str_ref __self, sys_Int_null quote){ return 0; }
sys_Str sys_Str_toCode2(fr_Env __env, sys_Str_ref __self, sys_Int_null quote, sys_Bool escapeUnicode){ return 0; }
sys_Str sys_Str_toXml0(fr_Env __env, sys_Str_ref __self){ return 0; }
void sys_Str_finalize0(fr_Env __env, sys_Str_ref __self){
    free(__self->data);
    free(__self->utf8);
    __self->data = NULL;
    __self->utf8 = NULL;
    __self->size = 0;
    __self->hashCode = 0;
    return;
}
void sys_Str_static__init0(fr_Env __env){
    sys_Str_defVal = fr_newStrUtf8(__env, "");
}
