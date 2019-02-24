#include "vm.h"
#include "pod_sys_struct.h"
#include "pod_sys_native.h"

#include <stdlib.h>
#include <string.h>
#include "utf8.h"
#include <wchar.h>

static fr_Int hash(struct sys_Str_ *str) {
    fr_Int hashValue = 0;
    size_t i;
    for (i=0; i<str->size; ++i) {
        hashValue = (str->data[i]) + 31 * hashValue;
    }
    return hashValue;
}

//////////////////////////////////////////////////////////

FObj * sys_Str_fromUtf8_(fr_Env env__, const char *cstr) {
    size_t len;
    struct sys_Str_* str;
    FObj *obj;
    size_t size;
    
    len = strlen(cstr);
    size = len + 1;
    
    fr_Type type = fr_findType(env__, "sys", "Str");
    
    //fr_lock(env__);
    obj = fr_allocObj_internal(env__, type, sizeof(struct sys_Str_));
    str = (struct sys_Str_*)(obj);
    
    str->data = (wchar_t*)malloc(sizeof(wchar_t)*size);
    //mbstowcs();
    //str->size = mbstowcs(cstr, str->data, len);
    str->size = utf8decode(cstr, str->data, size, NULL);
    
    str->hashCode = hash(str);
    str->utf8 = NULL;
    
    //fr_unlock(env__);
    return (FObj*)(str);
}

FObj * sys_Str_fromUnicode(fr_Env env__, const wchar_t *data, size_t size, bool copy) {
    struct sys_Str_* str;
    FObj *obj;

    fr_Type type = fr_findType(env__, "sys", "Str");
    
    //fr_lock(env__);
    obj = fr_allocObj_internal(env__, type, sizeof(struct sys_Str_));
    str = (struct sys_Str_*)(obj);
    
    size_t len = sizeof(wchar_t)*(size+1);
    str->data = (wchar_t*)malloc(len);
    memcpy(str->data, data, len);
    //mbstowcs();
    //str->size = mbstowcs(cstr, str->data, len);
    str->size = size;
    
    str->hashCode = hash(str);
    str->utf8 = NULL;
    
    //fr_unlock(env__);
    return (FObj*)(str);
}

char *sys_Str_getUtf8(fr_Env env__, FObj * self__) {
    size_t size;
    size_t realSize;
    struct sys_Str_ *str = (struct sys_Str_ *)self__;
    if (str->utf8) return str->utf8;
    size = str->size * 4 + 1;
    str->utf8 = malloc(size);
    realSize = utf8encode(str->data, str->utf8, size, NULL);
    str->utf8[realSize] = 0;
    return str->utf8;
}


void sys_Str_privateMake_f(fr_Env env, fr_Obj self) {
    struct sys_Str_ *str;
    //fr_lock(env);
    str = (struct sys_Str_ *)fr_getPtr(env, self);
    
    str->data = NULL;
    str->size = 0;
    
    //fr_unlock(env);
    return;
}
fr_Obj sys_Str_fromChars_f(fr_Env env, fr_Obj chars, fr_Int offset, fr_Int len) {
    return 0;
}
fr_Int sys_Str_hash_f(fr_Env env, fr_Obj self) {
    struct sys_Str_ *str;
    fr_Int result;
    //fr_lock(env);
    str = (struct sys_Str_ *)fr_getPtr(env, self);
    result = str->hashCode;
    //fr_unlock(env);
    return result;
}
fr_Int sys_Str_size_f(fr_Env env, fr_Obj self) {
    struct sys_Str_ *str;
    fr_Int result;
    //fr_lock(env);
    str = (struct sys_Str_ *)fr_getPtr(env, self);
    result = str->size;
    //fr_unlock(env);
    return result;
}
fr_Obj sys_Str_intern_f(fr_Env env, fr_Obj self) {
    //TODO
    return self;
}
fr_Int sys_Str_find_f(fr_Env env, fr_Obj self, fr_Obj s, fr_Int offset) {
    struct sys_Str_ *str;
    struct sys_Str_ *src;
    
    //fr_lock(env);
    str = (struct sys_Str_ *)fr_getPtr(env, self);
    src = (struct sys_Str_ *)fr_getPtr(env, s);
    
    if (offset >= str->size) {
        //fr_unlock(env);
        return -1;
    }
    
    wchar_t *pos = wcsstr(str->data + offset, src->data);
    if (pos == NULL) {
        //fr_unlock(env);
        return -1;
    }
    
    return pos - str->data;
}

//TODO
fr_Int sys_Str_findr_f(fr_Env env, fr_Obj self, fr_Obj s, fr_Int offset) {
    return -1;
}

fr_Int sys_Str_get_f(fr_Env env, fr_Obj self, fr_Int index) {
    struct sys_Str_ *str;
    fr_Int result;
    //fr_lock(env);
    str = (struct sys_Str_ *)fr_getPtr(env, self);
    result = str->data[index];
    //fr_unlock(env);
    return result;
}

fr_Obj sys_Str_getRange_f(fr_Env env, fr_Obj self, fr_Obj range) {
    return 0;
}
fr_Obj sys_Str_plus_f(fr_Env env, fr_Obj self, fr_Obj obj) {
    return 0;
}
fr_Obj sys_Str_chars_f(fr_Env env, fr_Obj self) {
    return 0;
}

//TODO
fr_Obj sys_Str_format_f(fr_Env env, fr_Obj format, fr_Obj args) {
    return NULL;
}
fr_Obj sys_Str_toUtf8_f(fr_Env env, fr_Obj self) {
    return NULL;
}
fr_Obj sys_Str_fromUtf8_f(fr_Env env, fr_Obj ba, fr_Int offset, fr_Int len) {
    return NULL;
}
void sys_Str_finalize_f(fr_Env env, fr_Obj self) {
    struct sys_Str_ *str;
    //fr_lock(env);
    str = (struct sys_Str_ *)fr_getPtr(env, self);
    
    free(str->data);
    free(str->utf8);
    str->data = NULL;
    str->utf8 = NULL;
    str->size = 0;
    str->hashCode = 0;
    
    //fr_unlock(env);
    return;
}
void sys_Str_static__init_f(fr_Env env) {
    return;
}
