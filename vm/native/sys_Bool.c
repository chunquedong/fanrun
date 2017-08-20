#include "vm.h"
#include "pod_sys_struct.h"
#include "pod_sys_native.h"

fr_Obj sys_Bool_fromStr_f(fr_Env env, fr_Obj s, fr_Bool checked) {
    return 0;
}
void sys_Bool_privateMake_f(fr_Env env, fr_Bool self) {
    return;
}
fr_Bool sys_Bool_equals_f(fr_Env env, fr_Bool self, fr_Obj obj) {
    fr_Type type;
    bool eq = false;
    if (obj == NULL) {
        return false;
    }
    type = fr_getSysType(env, fr_vtBool);
    
    if (!fr_isInstanceOf(env, obj, type)) {
        return false;
    }
    
    //fr_lock(env);
    struct sys_Bool_ *other = (struct sys_Bool_ *)fr_getPtr(env, obj);
    eq = self == other->value;
    //fr_unlock(env);
    return eq;
}
fr_Int sys_Bool_hash_f(fr_Env env, fr_Bool self) {
    return self;
}
fr_Obj sys_Bool_toStr_f(fr_Env env, fr_Bool self) {
    fr_Obj str;
    if (self) {
        str = fr_newStrUtf8(env, "true");
    } else {
        str = fr_newStrUtf8(env, "false");
    }
    return str;
}
fr_Obj sys_Bool_toLocale_f(fr_Env env, fr_Bool self) {
    return sys_Bool_toStr_f(env, self);
}
fr_Bool sys_Bool_not_f(fr_Env env, fr_Bool self) {
    return !self;
}
fr_Bool sys_Bool_and_f(fr_Env env, fr_Bool self, fr_Bool b) {
    return self && b;
}
fr_Bool sys_Bool_or_f(fr_Env env, fr_Bool self, fr_Bool b) {
    return self || b;
}
fr_Bool sys_Bool_xor_f(fr_Env env, fr_Bool self, fr_Bool b) {
    return self != b;
}
fr_Obj sys_Bool_toCode_f(fr_Env env, fr_Bool self) {
    return sys_Bool_toStr_f(env, self);
}
void sys_Bool_static__init(fr_Env env) {
    fr_Value val;
    //val.type = fr_vtBool;
    val.b = false;
    fr_setStaticField(env, "sys", "Bool", "defVal", &val);
    return;
}
