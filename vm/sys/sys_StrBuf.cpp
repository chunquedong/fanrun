//
//  sys_StrBuf.c
//  run
//
//  Created by yangjiandong on 2017/12/17.
//  Copyright © 2017年 yangjiandong. All rights reserved.
//

#include "sys.h"
#include <wchar.h>
#include <wctype.h>
#include <string.h>

//void sys_StrBuf_make0(fr_Env __env, sys_StrBuf_ref __self){
//    sys_StrBuf_make1(__env, __self, 16);
//}
void sys_StrBuf_make1(fr_Env __env, sys_StrBuf_ref __self, sys_Int capacity){
    __self->capacity = capacity;
    __self->data = (wchar_t*)malloc((capacity+1) * sizeof(wchar_t));
    __self->size = 0;
}
sys_Bool sys_StrBuf_isEmpty0(fr_Env __env, sys_StrBuf_ref __self){
    return __self->size == 0;
}
sys_Int sys_StrBuf_size0(fr_Env __env, sys_StrBuf_ref __self){
    return __self->size;
}
sys_Int sys_StrBuf_capacity0(fr_Env __env, sys_StrBuf_ref __self){
    return __self->capacity;
}
void sys_StrBuf_capacity1(fr_Env __env, sys_StrBuf_ref __self, sys_Int it){
    if (__self->capacity == it) return;
    wchar_t *p = (wchar_t*)realloc(__self->data, it+1);
    if (p) {
        __self->capacity = it;
        __self->data = p;
        if (__self->size > it) {
            __self->size = it;
        }
    } else {
        sys_Err e = FR_ALLOC(sys_Err);
        FR_THROW(e);
    }
}
sys_Int sys_StrBuf_get1(fr_Env __env, sys_StrBuf_ref __self, sys_Int index){
    if (index < 0) {
        index += __self->size;
    }
    if (index < 0 || index >= __self->size) {
        sys_IndexErr e = FR_ALLOC(sys_IndexErr);
        FR_THROW(e);
    }
    return __self->data[index];
}
sys_Str sys_StrBuf_getRange1(fr_Env __env, sys_StrBuf_ref __self, sys_Range range){
    sys_Int start = range._start;
    sys_Int end = range._end;
    if (start < 0) {
        start += __self->size;
    }
    if (end < 0) {
        end += __self->size;
    }
    if (!range._exclusive) ++end;
    
    if (start < 0 || start > __self->size) {
        sys_IndexErr e = FR_ALLOC(sys_IndexErr);
        FR_THROW(e);
    }
    if (end < 0 || end > __self->size) {
        sys_IndexErr e = FR_ALLOC(sys_IndexErr);
        FR_THROW(e);
    }
    sys_Int size = end - start;
    if (size < 0) {
        sys_IndexErr e = FR_ALLOC(sys_IndexErr);
        FR_THROW(e);
    }
    sys_Str str = (sys_Str)fr_newStr(__env, __self->data+start, size);
    return str;
}
sys_StrBuf sys_StrBuf_set2(fr_Env __env, sys_StrBuf_ref __self, sys_Int index, sys_Int ch){
    if (index < 0) {
        index += __self->size;
    }
    if (index < 0 || index >= __self->size) {
        sys_IndexErr e = FR_ALLOC(sys_IndexErr);
        FR_THROW(e);
    }
    __self->data[index] = (wchar_t)ch;
    return __self;
}
sys_StrBuf sys_StrBuf_add1(fr_Env __env, sys_StrBuf_ref __self, sys_Obj_null x){
    sys_Str str = FR_VCALL(sys_Obj, toStr0, x);
    if (str->size + __self->size > __self->capacity) {
        sys_Int newSize = (str->size + __self->size)*.15 + 8;
        sys_StrBuf_capacity1(__env, __self, newSize);
    }
    wcsncpy(__self->data+__self->size, str->data, str->size);
    __self->size += str->size;
    return __self;
}

sys_StrBuf sys_StrBuf_addStr3(fr_Env __env, sys_StrBuf_ref __self, sys_Str str, sys_Int off, sys_Int len) {
    if (len > str->size) {
        len = str->size;
    }
    else if (len <= 0) {
        return __self;
    }
    
    if (len + __self->size > __self->capacity) {
        sys_Int newSize = (len + __self->size)*.15 + 8;
        sys_StrBuf_capacity1(__env, __self, newSize);
    }
    wcsncpy(__self->data+__self->size, str->data+off, len);
    __self->size += len;
    return __self;
}

sys_StrBuf sys_StrBuf_addChar1(fr_Env __env, sys_StrBuf_ref __self, sys_Int ch){
    if (1 + __self->size > __self->capacity) {
        sys_Int newSize = (1 + __self->size)*.15 + 8;
        sys_StrBuf_capacity1(__env, __self, newSize);
    }
    __self->data[__self->size] = (wchar_t)ch;
    ++__self->size;
    return __self;
}
//sys_This sys_StrBuf_join1(fr_Env __env, sys_StrBuf_ref __self, sys_Obj_null x){
//    return sys_StrBuf_join2(__env, __self, x, fr_newStrNT(__env, L" "));
//}
sys_StrBuf sys_StrBuf_join2(fr_Env __env, sys_StrBuf_ref __self, sys_Obj_null x, sys_Str sep){
    if (__self->size > 0) {
        sys_StrBuf_add1(__env, __self, (sys_Obj)sep);
    }
    sys_StrBuf_add1(__env, __self, x);
    return __self;
}
sys_StrBuf sys_StrBuf_insert2(fr_Env __env, sys_StrBuf_ref __self, sys_Int index, sys_Obj_null x){
    if (index < 0) {
        index += __self->size;
    }
    if (index < 0 || index > __self->size) {
        sys_IndexErr e = FR_ALLOC(sys_IndexErr);
        FR_THROW(e);
    }
    
    sys_Str str = FR_VCALL(sys_Obj, toStr0, x);
    if (str->size + __self->size > __self->capacity) {
        sys_Int newSize = (str->size + __self->size)*.15 + 8;
        sys_StrBuf_capacity1(__env, __self, newSize);
    }
    memmove(__self->data+index+str->size, __self->data+index, str->size*sizeof(wchar_t));
    memcpy(__self->data+index, str->data, str->size*sizeof(wchar_t));
    __self->size += str->size;
    return __self;
}
sys_StrBuf sys_StrBuf_remove1(fr_Env __env, sys_StrBuf_ref __self, sys_Int index) {
    sys_Int len = __self->size - index+1;
    if (index < 0) {
        index += __self->size;
    }
    if (index < 0 || index >= __self->size) {
        sys_IndexErr e = FR_ALLOC(sys_IndexErr);
        FR_THROW(e);
    }
    memmove(__self->data+index, __self->data+index+1, len*sizeof(wchar_t));
    __self->size--;
    return __self;
}
sys_StrBuf sys_StrBuf_removeRange1(fr_Env __env, sys_StrBuf_ref __self, sys_Range range){
    sys_Int start = range._start;
    sys_Int end = range._end;
    if (start < 0) {
        start += __self->size;
    }
    if (end < 0) {
        end += __self->size;
    }
    if (!range._exclusive) ++end;
    
    if (start < 0 || start > __self->size) {
        sys_IndexErr e = FR_ALLOC(sys_IndexErr);
        FR_THROW(e);
    }
    if (end < 0 || end > __self->size) {
        sys_IndexErr e = FR_ALLOC(sys_IndexErr);
        FR_THROW(e);
    }
    sys_Int size = end - start;
    if (size < 0) {
        sys_IndexErr e = FR_ALLOC(sys_IndexErr);
        FR_THROW(e);
    }
    memmove(__self->data+start, __self->data+end, size*sizeof(wchar_t));
    __self->size-= size;
    return __self;
}
sys_StrBuf sys_StrBuf_replaceRange2(fr_Env __env, sys_StrBuf_ref __self, sys_Range range, sys_Str str){
    sys_Int start = range._start;
    sys_Int end = range._end;
    if (start < 0) {
        start += __self->size;
    }
    if (end < 0) {
        end += __self->size;
    }
    if (!range._exclusive) ++end;
    
    if (start < 0 || start > __self->size) {
        sys_IndexErr e = FR_ALLOC(sys_IndexErr);
        FR_THROW(e);
    }
    if (end < 0 || end > __self->size) {
        sys_IndexErr e = FR_ALLOC(sys_IndexErr);
        FR_THROW(e);
    }
    sys_Int size = end - start;
    if (size < 0) {
        sys_IndexErr e = FR_ALLOC(sys_IndexErr);
        FR_THROW(e);
    }
    sys_Int dsize = str->size - size;
    if (dsize + __self->size > __self->capacity) {
        sys_Int newSize = (str->size + __self->size)*.15 + 8;
        sys_StrBuf_capacity1(__env, __self, newSize);
    }
    
    memmove(__self->data+start+str->size, __self->data+end, size*sizeof(wchar_t));
    memmove(__self->data+start, str->data, str->size*sizeof(wchar_t));
    __self->size+= size;
    return __self;
}
sys_StrBuf sys_StrBuf_clear0(fr_Env __env, sys_StrBuf_ref __self){
    __self->size = 0;
    return __self;
}
sys_Str sys_StrBuf_toStr0(fr_Env __env, sys_StrBuf_ref __self){
    sys_Str str = (sys_Str)fr_newStr(__env, __self->data, __self->size);
    return str;
}
void sys_StrBuf_finalize0(fr_Env __env, sys_StrBuf_ref __self){
    free(__self->data);
    __self->data = NULL;
    __self->size = 0;
    __self->capacity = 0;
}

