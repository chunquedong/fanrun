#include "vm.h"
#include "pod_sys_struct.h"
#include "pod_sys_native.h"

#include <stdlib.h>
#include <string.h>

void sys_ByteArray_make_f(fr_Env env, fr_Obj self, fr_Int size) {
    struct sys_ByteArray_ *array = NULL;
    //fr_lock(env);
    array = (struct sys_ByteArray_ *)fr_getPtr(env, self);
    fr_Int len = size;
    array->size = size;
    array->data = (char*)malloc(len);
    memset(array->data, 0, len);
    
    //fr_unlock(env);
    return;
}
fr_Int sys_ByteArray_get_f(fr_Env env, fr_Obj self, fr_Int pos) {
    struct sys_ByteArray_ *array = NULL;
    fr_Int result;
    //fr_lock(env);
    array = (struct sys_ByteArray_ *)fr_getPtr(env, self);
    result = array->data[pos];
    //fr_unlock(env);
    return result;
}
void sys_ByteArray_set_f(fr_Env env, fr_Obj self, fr_Int pos, fr_Int val) {
    struct sys_ByteArray_ *array = NULL;
   // fr_Int result;
    //fr_lock(env);
    array = (struct sys_ByteArray_ *)fr_getPtr(env, self);
    array->data[pos] = val;
    //fr_unlock(env);
    //return result;
}
fr_Int sys_ByteArray_size_f(fr_Env env, fr_Obj self) {
    struct sys_ByteArray_ *array = NULL;
    fr_Int result;
    //fr_lock(env);
    array = (struct sys_ByteArray_ *)fr_getPtr(env, self);
    result = array->size;
    //fr_unlock(env);
    return result;
}
fr_Obj sys_ByteArray_realloc_f(fr_Env env, fr_Obj self, fr_Int newSize) {
    struct sys_ByteArray_ *array = NULL;
    char *p;
    
    //fr_lock(env);
    array = (struct sys_ByteArray_ *)fr_getPtr(env, self);
    
    p = realloc(array->data, newSize);
    if (p) {
        array->data = p;
        array->size = newSize;
        //result = true;
    }
    //result = false;
    //fr_unlock(env);
    return self;
}
fr_Obj sys_ByteArray_copyFrom_f(fr_Env env, fr_Obj self, fr_Obj that, fr_Int thatOffset, fr_Int thisOffset, fr_Int length) {
    struct sys_ByteArray_ *array;
    struct sys_ByteArray_ *other;
    
    //fr_lock(env);
    array = (struct sys_ByteArray_ *)fr_getPtr(env, self);
    other = (struct sys_ByteArray_ *)fr_getPtr(env, that);
    memccpy(array->data+thisOffset, other->data, thatOffset, length);
    //fr_unlock(env);
    return self;
}
void sys_ByteArray_finalize_f(fr_Env env, fr_Obj self) {
    struct sys_ByteArray_ *array;
    //fr_lock(env);
    array = (struct sys_ByteArray_ *)fr_getPtr(env, self);
    
    free(array->data);
    array->data = NULL;
    array->size = 0;
    
    //fr_unlock(env);
}
void sys_ByteArray_static__init_f(fr_Env env) {
    return;
}
fr_Obj sys_ByteArray_fill_f(fr_Env env, fr_Obj self, fr_Int byte, fr_Int times) {
    return self;
}
