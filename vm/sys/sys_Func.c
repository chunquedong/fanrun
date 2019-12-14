#include "vm.h"
#include "pod_sys_struct.h"
#include "pod_sys_native.h"

void sys_Func_make_f(fr_Env env, fr_Obj self) {
    //struct sys_Func_ *p = (struct sys_Func_*)fr_getPtr(env, self);
    return;
}
fr_Obj sys_Func_callList_f(fr_Env env, fr_Obj self, fr_Obj args) {
    return 0;
}
fr_Obj sys_Func_callOn_f(fr_Env env, fr_Obj self, fr_Obj target, fr_Obj args) {
    return 0;
}
fr_Obj sys_Func_bind_f(fr_Env env, fr_Obj self, fr_Obj args) {
    return 0;
}
void sys_Func_static__init_f(fr_Env env) {
    return;
}
fr_Obj sys_Func_call__0_f(fr_Env env, fr_Obj self) {
    fr_throwNew(env, "sys", "ArgErr", "arg size err");
    return NULL;
}
fr_Obj sys_Func_call__1_f(fr_Env env, fr_Obj self, fr_Obj a) {
    return sys_Func_call__0_f(env, self);
}
fr_Obj sys_Func_call__2_f(fr_Env env, fr_Obj self, fr_Obj a, fr_Obj b) {
    return sys_Func_call__1_f(env, self, a);
}
fr_Obj sys_Func_call__3_f(fr_Env env, fr_Obj self, fr_Obj a, fr_Obj b, fr_Obj c) {
    return sys_Func_call__2_f(env, self, a, b);
}
fr_Obj sys_Func_call__4_f(fr_Env env, fr_Obj self, fr_Obj a, fr_Obj b, fr_Obj c, fr_Obj d) {
    return sys_Func_call__3_f(env, self, a, b, c);
}
fr_Obj sys_Func_call__5_f(fr_Env env, fr_Obj self, fr_Obj a, fr_Obj b, fr_Obj c, fr_Obj d, fr_Obj e) {
    return sys_Func_call__4_f(env, self, a, b, c, d);
}
fr_Obj sys_Func_call__6_f(fr_Env env, fr_Obj self, fr_Obj a, fr_Obj b, fr_Obj c, fr_Obj d, fr_Obj e, fr_Obj f) {
    return sys_Func_call__5_f(env, self, a, b, c, d, e);
}
fr_Obj sys_Func_call__7_f(fr_Env env, fr_Obj self, fr_Obj a, fr_Obj b, fr_Obj c, fr_Obj d, fr_Obj e, fr_Obj f, fr_Obj g) {
    return sys_Func_call__6_f(env, self, a, b, c, d, e, f);
}
fr_Obj sys_Func_call_f(fr_Env env, fr_Obj self, fr_Obj a, fr_Obj b, fr_Obj c, fr_Obj d, fr_Obj e, fr_Obj f, fr_Obj g, fr_Obj h) {
    return sys_Func_call__7_f(env, self, a, b, c, d, e, f, g);
}
