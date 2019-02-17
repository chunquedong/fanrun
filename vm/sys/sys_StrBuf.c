#include "vm.h"
#include "pod_sys_struct.h"
#include "pod_sys_native.h"
#include <stdlib.h>
#include <string.h>

void sys_StrBuf_make_f(fr_Env env, fr_Obj self, fr_Int capacity) {
    struct sys_StrBuf_ *str;
    //fr_lock(env);
    str = (struct sys_StrBuf_ *)fr_getPtr(env, self);
    
    str->data = (wchar_t*)malloc(sizeof(wchar_t)*capacity);;
    str->size = 0;
    str->capacity= capacity;
    return;
}
fr_Bool sys_StrBuf_isEmpty_f(fr_Env env, fr_Obj self) {
    struct sys_StrBuf_ *str;
    str = (struct sys_StrBuf_ *)fr_getPtr(env, self);
    return str->size == 0;
}
fr_Int sys_StrBuf_size_f(fr_Env env, fr_Obj self) {
    struct sys_StrBuf_ *str;
    str = (struct sys_StrBuf_ *)fr_getPtr(env, self);
    return str->size;
}
fr_Int sys_StrBuf_capacity_f(fr_Env env, fr_Obj self) {
    struct sys_StrBuf_ *str;
    str = (struct sys_StrBuf_ *)fr_getPtr(env, self);
    return str->capacity;
}
void sys_StrBuf_capacity__f(fr_Env env, fr_Obj self, fr_Int it) {
    return;
}
fr_Int sys_StrBuf_get_f(fr_Env env, fr_Obj self, fr_Int index) {
    struct sys_StrBuf_ *str;
    str = (struct sys_StrBuf_ *)fr_getPtr(env, self);
    return str->data[index];
}
fr_Obj sys_StrBuf_getRange_f(fr_Env env, fr_Obj self, fr_Obj range) {
    return 0;
}
fr_Obj sys_StrBuf_set_f(fr_Env env, fr_Obj self, fr_Int index, fr_Int ch) {
    return 0;
}

fr_Obj sys_StrBuf_add_f(fr_Env env, fr_Obj self, fr_Obj x) {
    struct sys_StrBuf_ *strbuf;
    struct sys_Str_ *str;
    fr_Obj strObj;
    fr_Value val;
    
    strbuf = (struct sys_StrBuf_ *)fr_getPtr(env, self);
    
    val.h = x;
    strObj = fr_objToStr(env, val, fr_vtHandle);
    str = (struct sys_Str_ *)fr_getPtr(env, strObj);
    
    size_t newSize = strbuf->size + str->size;
    if (newSize > strbuf->capacity) {
        size_t capacity = strbuf->capacity * 1.2 + 64;
        wchar_t *p = (wchar_t*)realloc(strbuf->data, capacity);
        if (!p) {
            //TODO throw outofmem error.
            fr_throwUnsupported(env);
        }
        strbuf->data = p;
        strbuf->capacity = capacity;
    }
    
    memcpy(strbuf->data+strbuf->size, str->data, str->size*sizeof(wchar_t));
    strbuf->size = newSize;
    
    return self;
}
//TODO
fr_Obj sys_StrBuf_addStr_f(fr_Env env, fr_Obj self, fr_Obj str, fr_Int off, fr_Int len) {
    return NULL;
}
fr_Obj sys_StrBuf_addChar_f(fr_Env env, fr_Obj self, fr_Int ch) {
    return 0;
}
fr_Obj sys_StrBuf_join_f(fr_Env env, fr_Obj self, fr_Obj x, fr_Obj sep) {
    return 0;
}
fr_Obj sys_StrBuf_insert_f(fr_Env env, fr_Obj self, fr_Int index, fr_Obj x) {
    return 0;
}
fr_Obj sys_StrBuf_remove_f(fr_Env env, fr_Obj self, fr_Int index) {
    return 0;
}
fr_Obj sys_StrBuf_removeRange_f(fr_Env env, fr_Obj self, fr_Obj r) {
    return 0;
}
fr_Obj sys_StrBuf_replaceRange_f(fr_Env env, fr_Obj self, fr_Obj r, fr_Obj str) {
    return 0;
}
fr_Obj sys_StrBuf_clear_f(fr_Env env, fr_Obj self) {
    struct sys_StrBuf_ *str;
    str = (struct sys_StrBuf_ *)fr_getPtr(env, self);
    str->size = 0;
    return self;
}

FObj * sys_Str_fromUnicode(fr_Env env__, const wchar_t *data, size_t size);

fr_Obj sys_StrBuf_toStr_f(fr_Env env, fr_Obj self) {
    struct sys_StrBuf_ *strbuf;
    strbuf = (struct sys_StrBuf_ *)fr_getPtr(env, self);
    FObj * str = sys_Str_fromUnicode(env, strbuf->data, strbuf->size);
    return fr_toHandle(env,str);
}

void sys_StrBuf_static__init(fr_Env env) {
    return;
}
void sys_StrBuf_finalize_f(fr_Env env, fr_Obj self) {
    struct sys_StrBuf_ *str;
    //fr_lock(env);
    str = (struct sys_StrBuf_ *)fr_getPtr(env, self);
    
    free(str->data);
    str->data = NULL;
    str->size = 0;
    str->capacity = 0;
    
    //fr_unlock(env);
    return;
}
