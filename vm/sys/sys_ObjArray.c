#include "vm.h"
#include "pod_sys_struct.h"
#include "pod_sys_native.h"

#include <stdlib.h>
#include <string.h>

void sys_ObjArray_make_f(fr_Env env, fr_Obj self, fr_Int size, fr_Obj type) {
    struct sys_ObjArray_ *array;
    //fr_lock(env);
    array = (struct sys_ObjArray_ *)fr_getPtr(env, self);
    
    fr_Int len = sizeof(fr_Obj)*size;
    array->size = size;
    array->data = (FObj**)malloc(len);
    memset(array->data, 0, len);
    
    //fr_unlock(env);
    return;
}
fr_Obj sys_ObjArray_get_f(fr_Env env, fr_Obj self, fr_Int pos) {
    struct sys_ObjArray_ *array;
    fr_Obj result;
    //fr_lock(env);
    array = (struct sys_ObjArray_ *)fr_getPtr(env, self);
    result = fr_toHandle(env, array->data[pos]);
    //fr_unlock(env);
    return result;
}
void sys_ObjArray_set_f(fr_Env env, fr_Obj self, fr_Int pos, fr_Obj val) {
    struct sys_ObjArray_ *array;
    //fr_Obj result;
    //fr_lock(env);
    array = (struct sys_ObjArray_ *)fr_getPtr(env, self);
    array->data[pos] = fr_getPtr(env, val);
    //fr_unlock(env);
    return;
}
fr_Int sys_ObjArray_size_f(fr_Env env, fr_Obj self) {
    struct sys_ObjArray_ *array;
    fr_Int result;
    //fr_lock(env);
    array = (struct sys_ObjArray_ *)fr_getPtr(env, self);
    result = array->size;
    //fr_unlock(env);
    return result;
}
fr_Obj sys_ObjArray_realloc_f(fr_Env env, fr_Obj self, fr_Int newSize) {
    struct sys_ObjArray_ *array;
    FObj **p;
    
    //bool result;
    //fr_lock(env);
    array = (struct sys_ObjArray_ *)fr_getPtr(env, self);
    
    p = realloc(array->data, newSize * sizeof(fr_Obj));
    if (p) {
        if (newSize > array->size) {
            memset(p+array->size, 0, sizeof(fr_Obj)*(newSize - array->size));
        }
        array->data = p;
        array->size = newSize;
        //result = true;
    }
    //result = false;
    //fr_unlock(env);
    return self;
}
fr_Obj sys_ObjArray_copyFrom_f(fr_Env env, fr_Obj self, fr_Obj that, fr_Int thatOffset, fr_Int thisOffset, fr_Int length) {
    struct sys_ObjArray_ *array;
    struct sys_ObjArray_ *other;
    
    //fr_lock(env);
    array = (struct sys_ObjArray_ *)fr_getPtr(env, self);
    other = (struct sys_ObjArray_ *)fr_getPtr(env, that);
    
    memccpy(array->data+thisOffset, other->data, thatOffset, length);
    
    //fr_unlock(env);
    return self;
}
fr_Obj sys_ObjArray_fill_f(fr_Env env, fr_Obj self, fr_Obj obj, fr_Int times) {
    return NULL;
}
fr_Obj sys_ObjArray_fromJava_f(fr_Env env, fr_Obj of, fr_Obj array) {
    return NULL;
}
fr_Obj sys_ObjArray_toJava_f(fr_Env env, fr_Obj self, fr_Obj clz) {
    return NULL;
}
void sys_ObjArray_finalize_f(fr_Env env, fr_Obj self) {
    struct sys_ObjArray_ *array;
    //fr_lock(env);
    array = (struct sys_ObjArray_ *)fr_getPtr(env, self);
    free(array->data);
    array->data = NULL;
    array->size = 0;
    //fr_unlock(env);
}
void sys_ObjArray_static__init(fr_Env env) {
    return;
}
