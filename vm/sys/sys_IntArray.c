#include "vm.h"
#include "pod_sys_struct.h"
#include "pod_sys_native.h"

#include <stdlib.h>
#include <string.h>

void sys_IntArray_make_f(fr_Env env, fr_Obj self, fr_Int size) {
    struct sys_IntArray_ *array = NULL;
    //fr_lock(env);
    array = (struct sys_IntArray_ *)fr_getPtr(env, self);
    
    fr_Int len = sizeof(fr_Int)*size;
    array->size = size;
    array->data = (fr_Int*)malloc(len);
    memset(array->data, 0, len);
    
    //fr_unlock(env);
    return;
}
fr_Int sys_IntArray_get_f(fr_Env env, fr_Obj self, fr_Int pos) {
    struct sys_IntArray_ *array = NULL;
    fr_Int result;
    //fr_lock(env);
    array = (struct sys_IntArray_ *)fr_getPtr(env, self);
    
    result = array->data[pos];
    
    //fr_unlock(env);
    return result;
}
fr_Int sys_IntArray_set_f(fr_Env env, fr_Obj self, fr_Int pos, fr_Int val) {
    struct sys_IntArray_ *array = NULL;
    fr_Int result;
    //fr_lock(env);
    array = (struct sys_IntArray_ *)fr_getPtr(env, self);
    
    result = array->data[pos] = val;
    //fr_unlock(env);
    return result;
}
fr_Int sys_IntArray_size_f(fr_Env env, fr_Obj self) {
    struct sys_IntArray_ *array = NULL;
    fr_Int result;
    //fr_lock(env);
    array = (struct sys_IntArray_ *)fr_getPtr(env, self);
    
    result = array->size;
    //fr_unlock(env);
    return result;
}
fr_Bool sys_IntArray_realloc_f(fr_Env env, fr_Obj self, fr_Int newSize) {
    struct sys_IntArray_ *array = NULL;
    bool result;
    fr_Int *p;
    //fr_lock(env);
    array = (struct sys_IntArray_ *)fr_getPtr(env, self);
    
    p = realloc(array->data, newSize * sizeof(fr_Int));
    if (p) {
        array->data = p;
        array->size = newSize;
        result = true;
    }
    result = false;
    //fr_unlock(env);
    return result;
}
fr_Obj sys_IntArray_copyFrom_f(fr_Env env, fr_Obj self, fr_Obj that, fr_Int thatOffset, fr_Int thisOffset, fr_Int length) {
    struct sys_IntArray_ *array;
    struct sys_IntArray_ *other;
    
    //fr_lock(env);
    array = (struct sys_IntArray_ *)fr_getPtr(env, self);
    other = (struct sys_IntArray_ *)fr_getPtr(env, that);
    
    thatOffset *= sizeof(fr_Int);
    length *= sizeof(fr_Int);
    memccpy(array->data+thisOffset, other->data, thatOffset, length);
    
    //fr_unlock(env);
    return self;
}

void sys_IntArray_finalize_f(fr_Env env, fr_Obj self) {
    struct sys_IntArray_ *array = NULL;
    //fr_lock(env);
    array = (struct sys_IntArray_ *)fr_getPtr(env, self);
    
    free(array->data);
    array->data = NULL;
    array->size = 0;
    //fr_unlock(env);
}
void sys_IntArray_static__init(fr_Env env) {
    return;
}
