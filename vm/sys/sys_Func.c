#include "vm.h"
#include "pod_sys_struct.h"
#include "pod_sys_native.h"

void sys_Func_make_f(fr_Env env, fr_Obj self) {
    struct sys_Func_ *p = (struct sys_Func_*)fr_getPtr(env, self);
    p->arity = -1;
    return;
}
fr_Obj sys_Func_returns_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Int sys_Func_arity_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Obj sys_Func_params_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Obj sys_Func_method_f(fr_Env env, fr_Obj self) {
    return 0;
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
fr_Obj sys_Func_retype_f(fr_Env env, fr_Obj self, fr_Obj t) {
    return 0;
}
void sys_Func_enterCtor_f(fr_Env env, fr_Obj self, fr_Obj obj) {
    return;
}
void sys_Func_exitCtor_f(fr_Env env, fr_Obj self) {
    return;
}
void sys_Func_checkInCtor_f(fr_Env env, fr_Obj self, fr_Obj obj) {
    
}
void sys_Func_static__init_f(fr_Env env) {
    return;
}
static int funcArity(fr_Env env, fr_Obj self) {
    struct sys_Func_ *p = (struct sys_Func_*)fr_getPtr(env, self);
    if (p->arity == -1) {
        fr_Type t = fr_findType(env, "sys", "Func");
        fr_Method m = fr_findMethod(env, t, "arity");
        fr_Value args[2];
        args[0].h = self;
        fr_callVirtualM(env, m, 0, &args[0], &args[1]);
        p->arity = args[1].i;
    }
    return (int)p->arity;
}
fr_Obj sys_Func_call__0_f(fr_Env env, fr_Obj self) {
    int arity = funcArity(env, self);
    fr_Obj c = NULL;
    fr_Obj b = NULL;
    fr_Obj a = NULL;
    switch (arity) {
        case 0:
        return sys_Func_call__0_f(env, self);
        break;
        case 1:
        return sys_Func_call__1_f(env, self, a);
        break;
        case 2:
        return sys_Func_call__2_f(env, self, a, b);
        break;
        case 3:
        return sys_Func_call__3_f(env, self, a, b, c);
        break;
        case 4:
        return sys_Func_call__4_f(env, self, a, b, c, NULL);
        break;
        case 5:
        return sys_Func_call__5_f(env, self, a, b, c, NULL, NULL);
        break;
        case 6:
        return sys_Func_call__6_f(env, self, a, b, c, NULL, NULL, NULL);
        break;
        case 7:
        return sys_Func_call__7_f(env, self, a, b, c, NULL, NULL, NULL, NULL);
        break;
        case 8:
        return sys_Func_call_f(env, self, a, b, c, NULL, NULL, NULL, NULL, NULL);
        break;
        default:
        fr_throwNew(env, "sys", "ArgErr", "arg size err");
        break;
    }
    return NULL;
}
fr_Obj sys_Func_call__1_f(fr_Env env, fr_Obj self, fr_Obj a) {
    int arity = funcArity(env, self);
    fr_Obj c = NULL;
    fr_Obj b = NULL;
    switch (arity) {
        case 0:
        return sys_Func_call__0_f(env, self);
        break;
        case 1:
        return sys_Func_call__1_f(env, self, a);
        break;
        case 2:
        return sys_Func_call__2_f(env, self, a, b);
        break;
        case 3:
        return sys_Func_call__3_f(env, self, a, b, c);
        break;
        case 4:
        return sys_Func_call__4_f(env, self, a, b, c, NULL);
        break;
        case 5:
        return sys_Func_call__5_f(env, self, a, b, c, NULL, NULL);
        break;
        case 6:
        return sys_Func_call__6_f(env, self, a, b, c, NULL, NULL, NULL);
        break;
        case 7:
        return sys_Func_call__7_f(env, self, a, b, c, NULL, NULL, NULL, NULL);
        break;
        case 8:
        return sys_Func_call_f(env, self, a, b, c, NULL, NULL, NULL, NULL, NULL);
        break;
        default:
        fr_throwNew(env, "sys", "ArgErr", "arg size err");
        break;
    }
    return NULL;
}
fr_Obj sys_Func_call__2_f(fr_Env env, fr_Obj self, fr_Obj a, fr_Obj b) {
    int arity = funcArity(env, self);
    fr_Obj c = NULL;
    switch (arity) {
        case 0:
        return sys_Func_call__0_f(env, self);
        break;
        case 1:
        return sys_Func_call__1_f(env, self, a);
        break;
        case 2:
        return sys_Func_call__2_f(env, self, a, b);
        break;
        case 3:
        return sys_Func_call__3_f(env, self, a, b, c);
        break;
        case 4:
        return sys_Func_call__4_f(env, self, a, b, c, NULL);
        break;
        case 5:
        return sys_Func_call__5_f(env, self, a, b, c, NULL, NULL);
        break;
        case 6:
        return sys_Func_call__6_f(env, self, a, b, c, NULL, NULL, NULL);
        break;
        case 7:
        return sys_Func_call__7_f(env, self, a, b, c, NULL, NULL, NULL, NULL);
        break;
        case 8:
        return sys_Func_call_f(env, self, a, b, c, NULL, NULL, NULL, NULL, NULL);
        break;
        default:
        fr_throwNew(env, "sys", "ArgErr", "arg size err");
        break;
    }
    return NULL;
}
fr_Obj sys_Func_call__3_f(fr_Env env, fr_Obj self, fr_Obj a, fr_Obj b, fr_Obj c) {
    int arity = funcArity(env, self);
    switch (arity) {
        case 0:
        return sys_Func_call__0_f(env, self);
        break;
        case 1:
        return sys_Func_call__1_f(env, self, a);
        break;
        case 2:
        return sys_Func_call__2_f(env, self, a, b);
        break;
        case 3:
        return sys_Func_call__3_f(env, self, a, b, c);
        break;
        case 4:
        return sys_Func_call__4_f(env, self, a, b, c, NULL);
        break;
        case 5:
        return sys_Func_call__5_f(env, self, a, b, c, NULL, NULL);
        break;
        case 6:
        return sys_Func_call__6_f(env, self, a, b, c, NULL, NULL, NULL);
        break;
        case 7:
        return sys_Func_call__7_f(env, self, a, b, c, NULL, NULL, NULL, NULL);
        break;
        case 8:
        return sys_Func_call_f(env, self, a, b, c, NULL, NULL, NULL, NULL, NULL);
        break;
        default:
        fr_throwNew(env, "sys", "ArgErr", "arg size err");
        break;
    }
    return NULL;
}
fr_Obj sys_Func_call__4_f(fr_Env env, fr_Obj self, fr_Obj a, fr_Obj b, fr_Obj c, fr_Obj d) {
    int arity = funcArity(env, self);
    switch (arity) {
        case 0:
        return sys_Func_call__0_f(env, self);
        break;
        case 1:
        return sys_Func_call__1_f(env, self, a);
        break;
        case 2:
        return sys_Func_call__2_f(env, self, a, b);
        break;
        case 3:
        return sys_Func_call__3_f(env, self, a, b, c);
        break;
        case 4:
        return sys_Func_call__4_f(env, self, a, b, c, d);
        break;
        case 5:
        return sys_Func_call__5_f(env, self, a, b, c, d, NULL);
        break;
        case 6:
        return sys_Func_call__6_f(env, self, a, b, c, d, NULL, NULL);
        break;
        case 7:
        return sys_Func_call__7_f(env, self, a, b, c, d, NULL, NULL, NULL);
        break;
        case 8:
        return sys_Func_call_f(env, self, a, b, c, d, NULL, NULL, NULL, NULL);
        break;
        default:
        fr_throwNew(env, "sys", "ArgErr", "arg size err");
        break;
    }
    return NULL;
}
fr_Obj sys_Func_call__5_f(fr_Env env, fr_Obj self, fr_Obj a, fr_Obj b, fr_Obj c, fr_Obj d, fr_Obj e) {
    int arity = funcArity(env, self);
    switch (arity) {
        case 0:
        return sys_Func_call__0_f(env, self);
        break;
        case 1:
        return sys_Func_call__1_f(env, self, a);
        break;
        case 2:
        return sys_Func_call__2_f(env, self, a, b);
        break;
        case 3:
        return sys_Func_call__3_f(env, self, a, b, c);
        break;
        case 4:
        return sys_Func_call__4_f(env, self, a, b, c, d);
        break;
        case 5:
        return sys_Func_call__5_f(env, self, a, b, c, d, e);
        break;
        case 6:
        return sys_Func_call__6_f(env, self, a, b, c, d, e, NULL);
        break;
        case 7:
        return sys_Func_call__7_f(env, self, a, b, c, d, e, NULL, NULL);
        break;
        case 8:
        return sys_Func_call_f(env, self, a, b, c, d, e, NULL, NULL, NULL);
        break;
        default:
        fr_throwNew(env, "sys", "ArgErr", "arg size err");
        break;
    }
    return NULL;
}
fr_Obj sys_Func_call__6_f(fr_Env env, fr_Obj self, fr_Obj a, fr_Obj b, fr_Obj c, fr_Obj d, fr_Obj e, fr_Obj f) {
    int arity = funcArity(env, self);
    switch (arity) {
        case 0:
        return sys_Func_call__0_f(env, self);
        break;
        case 1:
        return sys_Func_call__1_f(env, self, a);
        break;
        case 2:
        return sys_Func_call__2_f(env, self, a, b);
        break;
        case 3:
        return sys_Func_call__3_f(env, self, a, b, c);
        break;
        case 4:
        return sys_Func_call__4_f(env, self, a, b, c, d);
        break;
        case 5:
        return sys_Func_call__5_f(env, self, a, b, c, d, e);
        break;
        case 6:
        return sys_Func_call__6_f(env, self, a, b, c, d, e, f);
        break;
        case 7:
        return sys_Func_call__7_f(env, self, a, b, c, d, e, f, NULL);
        break;
        case 8:
        return sys_Func_call_f(env, self, a, b, c, d, e, f, NULL, NULL);
        break;
        default:
        fr_throwNew(env, "sys", "ArgErr", "arg size err");
        break;
    }
    return NULL;
}
fr_Obj sys_Func_call__7_f(fr_Env env, fr_Obj self, fr_Obj a, fr_Obj b, fr_Obj c, fr_Obj d, fr_Obj e, fr_Obj f, fr_Obj g) {
    int arity = funcArity(env, self);
    switch (arity) {
        case 0:
        return sys_Func_call__0_f(env, self);
        break;
        case 1:
        return sys_Func_call__1_f(env, self, a);
        break;
        case 2:
        return sys_Func_call__2_f(env, self, a, b);
        break;
        case 3:
        return sys_Func_call__3_f(env, self, a, b, c);
        break;
        case 4:
        return sys_Func_call__4_f(env, self, a, b, c, d);
        break;
        case 5:
        return sys_Func_call__5_f(env, self, a, b, c, d, e);
        break;
        case 6:
        return sys_Func_call__6_f(env, self, a, b, c, d, e, f);
        break;
        case 7:
        return sys_Func_call__7_f(env, self, a, b, c, d, e, f, g);
        break;
        case 8:
        return sys_Func_call_f(env, self, a, b, c, d, e, f, g, NULL);
        break;
        default:
        fr_throwNew(env, "sys", "ArgErr", "arg size err");
        break;
    }
    return NULL;
}
fr_Obj sys_Func_call_f(fr_Env env, fr_Obj self, fr_Obj a, fr_Obj b, fr_Obj c, fr_Obj d, fr_Obj e, fr_Obj f, fr_Obj g, fr_Obj h) {
    int arity = funcArity(env, self);
    switch (arity) {
        case 0:
        return sys_Func_call__0_f(env, self);
        break;
        case 1:
        return sys_Func_call__1_f(env, self, a);
        break;
        case 2:
        return sys_Func_call__2_f(env, self, a, b);
        break;
        case 3:
        return sys_Func_call__3_f(env, self, a, b, c);
        break;
        case 4:
        return sys_Func_call__4_f(env, self, a, b, c, d);
        break;
        case 5:
        return sys_Func_call__5_f(env, self, a, b, c, d, e);
        break;
        case 6:
        return sys_Func_call__6_f(env, self, a, b, c, d, e, f);
        break;
        case 7:
        return sys_Func_call__7_f(env, self, a, b, c, d, e, f, g);
        break;
        case 8:
        return sys_Func_call_f(env, self, a, b, c, d, e, f, g, h);
        break;
        default:
        fr_throwNew(env, "sys", "ArgErr", "arg size err");
        break;
    }
    return NULL;
}
