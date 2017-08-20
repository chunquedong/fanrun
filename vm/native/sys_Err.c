#include "vm.h"
#include "pod_sys_struct.h"
#include "pod_sys_native.h"

void sys_Err_make_f(fr_Env env, fr_Obj self, fr_Obj msg, fr_Obj cause) {
    struct sys_Err_ *err;
    char buf[1024] = {0};
    
    //fr_lock(env);
    err = (struct sys_Err_ *)fr_getPtr(env, self);
    
    err->msg = fr_getPtr(env, msg);
    err->cause = fr_getPtr(env, cause);
    
    fr_stackTrace(env, buf, 1024, "\n  ");
    err->traceToStr = fr_getPtr(env, fr_newStrUtf8(env, buf));
    
    //fr_unlock(env);
    return;
}
fr_Obj sys_Err_msg_f(fr_Env env, fr_Obj self) {
    struct sys_Err_ *err;
    fr_Obj result;
    //fr_lock(env);
    err = (struct sys_Err_ *)fr_getPtr(env, self);
    
    result = fr_toHandle(env, err->msg);
    
    //fr_unlock(env);
    return result;
}
fr_Obj sys_Err_cause_f(fr_Env env, fr_Obj self) {
    struct sys_Err_ *err;
    fr_Obj result;
    //fr_lock(env);
    err = (struct sys_Err_ *)fr_getPtr(env, self);
    
    result = fr_toHandle(env, err->cause);
    
    //fr_unlock(env);
    return result;
}
fr_Obj sys_Err_trace_f(fr_Env env, fr_Obj self) {
    struct sys_Err_ *err;
    err = (struct sys_Err_ *)fr_getPtr(env, self);
    
    fr_Obj str;
    const char *msg;
    const char *stack;
    fr_Value val;
    val.h = fr_toHandle(env, err->msg);
    str = fr_objToStr(env, val, fr_vtHandle);
    msg = fr_getStrUtf8(env, str, NULL);
    
    val.h = fr_toHandle(env, err->traceToStr);
    str = fr_objToStr(env, val, fr_vtHandle);
    stack = fr_getStrUtf8(env, str, NULL);
    
    printf("Error:%s\n  %s\n", msg, stack);
    
    return self;
}
fr_Obj sys_Err_traceToStr_f(fr_Env env, fr_Obj self) {
    struct sys_Err_ *err;
    err = (struct sys_Err_ *)fr_getPtr(env, self);
    return fr_toHandle(env, err->traceToStr);
}
fr_Obj sys_Err_toStr_f(fr_Env env, fr_Obj self) {
    return sys_Err_msg_f(env, self);
}
void sys_Err_static__init(fr_Env env) {
    return;
}
