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
    const wchar_t *str = __self->data + offset;
    const wchar_t *found = wcsstr(str, s->data);
    if (!found) return -1;
    sys_Int diff = (found - __self->data);
    return diff;
}

sys_Int sys_Str_findr2(fr_Env __env, sys_Str_ref __self, sys_Str s, sys_Int offset) {
    if (offset >= __self->size) {
        return -1;
    }
    const wchar_t *str = __self->data + offset;
    
    const wchar_t *found = NULL;
    while (true) {
        wchar_t *p = wcsstr(str, s->data);
        if (p == NULL) break;
        found = p;
        ++str;
    }
    if (!found) return -1;
    sys_Int diff = (found - __self->data);
    return diff;
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

sys_Str sys_Str_getRange1(fr_Env __env, sys_Str_ref __self, sys_Range range){
    size_t s = sys_Range_startIndex1(__env, range, __self->size);
    size_t e = sys_Range_endIndex1(__env, range, __self->size);

    if (s >= e) return sys_Str_defVal;
    size_t len = e-s;
    wchar_t *data = (wchar_t*)malloc(sizeof(wchar_t)*(len+1));
    return (sys_Str)fr_newStr(__env, data, len, false);
}
sys_Str sys_Str_plus1(fr_Env __env, sys_Str_ref __self, sys_Obj_null obj) {
    const wchar_t *p = L"";
    size_t plen = 0;
    if (obj == NULL) {
        p = L"null";
        plen = 4;
    }
    else {
        sys_Str_ref str = FR_VCALL(sys_Obj, toStr0, obj);
        p = str->data;
        plen = str->size;
    }
    wchar_t *data = (wchar_t*)malloc(sizeof(wchar_t)*(plen+1));
    
    wmemcpy(data, __self->data, __self->size);
    wmemcpy(data+__self->size, p, plen);
    size_t nlen = __self->size+plen;
    data[nlen] = 0;
    return (sys_Str)fr_newStr(__env, data, nlen, false);
}
sys_List sys_Str_chars0(fr_Env __env, sys_Str_ref __self){ return 0; }

sys_Str sys_Str_replace2(fr_Env __env, sys_Str_ref __self, sys_Str from, sys_Str to){ return 0; }

void sys_Str_finalize0(fr_Env __env, sys_Str_ref __self){
    free((void*)(__self->data));
    free((void*)__self->utf8);
    __self->data = NULL;
    __self->utf8 = NULL;
    __self->size = 0;
    __self->hashCode = 0;
    return;
}
void sys_Str_static__init0(fr_Env __env){
    sys_Str_defVal = (sys_Str)fr_newStr(__env, L"", 0, false);
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
