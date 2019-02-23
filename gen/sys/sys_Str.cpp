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

extern "C" {
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
}//extern "C" {
/////////////////////////////////////////////////////////////

sys_Str sys_Str_defVal = NULL;

void sys_Str_privateMake0(fr_Env __env, sys_Str_ref __self){
    __self->data = NULL;
    __self->size = 0;
    __self->hashCode = 0;
    __self->utf8 = NULL;
}
sys_Int sys_Str_hash0(fr_Env __env, sys_Str_ref __self){
    return __self->hashCode;
}

sys_Int sys_Str_size0(fr_Env __env, sys_Str_ref __self){
    return __self->size;
}
sys_Str sys_Str_intern0(fr_Env __env, sys_Str_ref __self){ return 0; }

sys_Int sys_Str_find2(fr_Env __env, sys_Str_ref __self, sys_Str s, sys_Int offset) {
    if (offset >= __self->size) {
        return -1;
    }
    wchar_t *str = __self->data + offset;
    wchar_t *found = wcsstr(str, s->data);
    if (!found) return -1;
    sys_Int diff = (found - __self->data);
    return diff;
}
//TODO
sys_Int sys_Str_findr2(fr_Env __env, sys_Str_ref __self, sys_Str s, sys_Int offset) {
    return 0;
}
sys_Int sys_Str_get1(fr_Env __env, sys_Str_ref __self, sys_Int index){
    if (index < 0) {
        index += __self->size;
    }
    if (index < 0 || index > __self->size) {
        FR_ALLOC_THROW(sys_IndexErr);
    }
    return __self->data[index];
}

sys_Str sys_Str_getRange1(fr_Env __env, sys_Str_ref __self, sys_Range range){ return 0; }
sys_Str sys_Str_plus1(fr_Env __env, sys_Str_ref __self, sys_Obj_null obj){ return 0; }
sys_List sys_Str_chars0(fr_Env __env, sys_Str_ref __self){ return 0; }

sys_Str sys_Str_replace2(fr_Env __env, sys_Str_ref __self, sys_Str from, sys_Str to){ return 0; }

void sys_Str_finalize0(fr_Env __env, sys_Str_ref __self){
    free(__self->data);
    free((void*)__self->utf8);
    __self->data = NULL;
    __self->utf8 = NULL;
    __self->size = 0;
    __self->hashCode = 0;
    return;
}
void sys_Str_static__init0(fr_Env __env){
    sys_Str_defVal = (sys_Str)fr_newStrUtf8(__env, "");
}
//TODO
sys_Str sys_Str_fromChars3(fr_Env __env, sys_List chars, sys_Int offset, sys_Int len) {
    return NULL;
}

//TODO
sys_ByteArray sys_Str_toUtf80(fr_Env __env, sys_Str_ref __self) {
    return NULL;
}
//TODO
sys_Str sys_Str_fromUtf83(fr_Env __env, sys_ByteArray ba, sys_Int offset, sys_Int len) {
    return NULL;
}
sys_Str sys_Str_format2(fr_Env __env, sys_Str format, sys_List args) {
    return NULL;
}
