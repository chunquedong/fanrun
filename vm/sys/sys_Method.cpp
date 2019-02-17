#include "vm.h"
#include "pod_sys_struct.h"
#include "pod_sys_native.h"

#include "FType.h"
#include "Env.h"

fr_Obj sys_Method_fromFMethod(fr_Env env, void *fmethod) {
    FMethod *method = (FMethod*)fmethod;
    //Env *senv = (Env*)env;
    
    if (method->c_wrappedMethod) {
        fr_Obj smethod = (fr_Obj)method->c_wrappedMethod;
        return smethod;
    }
    
    fr_Type type = fr_findType(env, "sys", "Method");
    fr_Obj omethod = fr_allocObj(env, type, sizeof(struct sys_Method_));
    //add to global ref
    omethod = fr_newGlobalRef(env, omethod);
    
    //fr_lock(env);
    struct sys_Method_* smethod = reinterpret_cast<struct sys_Method_*>(fr_getPtr(env, omethod));
    
    method->c_wrappedMethod = (void*)omethod;
    smethod->fmethod = method;
    
    FPod *pod = method->c_parent->c_pod;
    
    fr_Obj name = fr_newStrUtf8(env, pod->names[method->name].c_str());
    fr_Obj parentType = fr_getTypeObj(env, (FType*)method->c_parent);
    
    smethod->super.name = fr_newGlobalRef(env, name);
    smethod->super.parent = fr_newGlobalRef(env, parentType);
    
    //fr_unlock(env);
    return omethod;
}

fr_Obj sys_Method_privateMake_f(fr_Env env) {
    return 0;
}
fr_Obj sys_Method_returns_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Obj sys_Method_params_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Obj sys_Method_func_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Obj sys_Method_callList_f(fr_Env env, fr_Obj self, fr_Obj args) {
    return 0;
}
fr_Obj sys_Method_callOn_f(fr_Env env, fr_Obj self, fr_Obj target, fr_Obj args) {
    struct sys_Method_*method;
    Env *senv = (Env*)env;
    
    //fr_lock(env);
    method = (struct sys_Method_*)fr_getPtr(env, self);
    FMethod *fmethod = (FMethod*)method->fmethod;
    
    fr_TagValue val;
    val.type = fr_vtObj;
    val.any.o = fr_getPtr(env, target);
    senv->push(&val);
    //fr_unlock(env);
    
    if (args) {
        //TOOD
    }
    
    senv->call(fmethod, 0);
    return 0;
}
fr_Obj sys_Method_call_f(fr_Env env, fr_Obj self, fr_Obj a, fr_Obj b, fr_Obj c, fr_Obj d, fr_Obj e, fr_Obj f, fr_Obj g, fr_Obj h) {
    struct sys_Method_*method;
    Env *senv = (Env*)env;
    
    //fr_lock(env);
    method = (struct sys_Method_*)fr_getPtr(env, self);
    
    FMethod *fmethod = (FMethod*)method->fmethod;
    
    fr_Obj list[] = { a, b, c, d, e, f, g, h };
    int paramCount = fmethod->paramCount;
    if ((fmethod->flags & FFlags::Static) == 0) {
        paramCount++;
    }
    
    
    for (int i=0; i<paramCount; ++i) {
        fr_TagValue val;
        val.type = fr_vtObj;
        val.any.o = fr_getPtr(env, list[i]);
        senv->push(&val);
    }
    //fr_unlock(env);
    
    senv->call(fmethod, 0);
    return 0;
}
void sys_Method_make_f(fr_Env env, fr_Obj self) {
    return;
}
CF_BEGIN
void sys_Method_static__init(fr_Env env) {
    return;
}
CF_END
