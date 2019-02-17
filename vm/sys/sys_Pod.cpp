#include "vm.h"
#include "pod_sys_struct.h"
#include "pod_sys_native.h"
#include "Env.h"

fr_Obj sys_Pod_of_f(fr_Env env, fr_Obj obj) {
    return 0;
}
fr_Obj sys_Pod_list_f(fr_Env env) {
    return 0;
}
fr_Obj sys_Pod_find_f(fr_Env env, fr_Obj name, fr_Bool checked) {
    const char *sname = fr_getStrUtf8(env, name, nullptr);
    Env *senv = (Env*)env;
    FPod *fpod = senv->podManager->findPod(sname);
    if (!fpod) {
        if (checked) {
            fr_throwNew(env, "sys", "UnknownPodErr", sname);
        }
        return NULL;
    }
    
    fr_Type type = fr_findType(env, "sys", "Pod");
    fr_Obj opod = fr_allocObj(env, type, sizeof(struct sys_Pod_));
    opod = fr_newGlobalRef(env, opod);
    
    //fr_lock(env);
    struct sys_Pod_* pod = reinterpret_cast<struct sys_Pod_*>(fr_getPtr(env, opod));
    
    pod->fpod = fpod;
    fpod->c_wrappedPod = pod;
    
    pod->name = name;
    //TODO
    //fr_attachInstance(env, (fr_Obj)pod, NULL, name);
    
    //TODO
    
    //fr_unlockPointer(env, opod, pod);
    
    //fr_unlock(env);
    return opod;
}
fr_Obj sys_Pod_load_f(fr_Env env, fr_Obj in) {
    return 0;
}
void sys_Pod_make_f(fr_Env env, fr_Obj self) {
    return;
}
fr_Obj sys_Pod_name_f(fr_Env env, fr_Obj self) {
    struct sys_Pod_* pod = (struct sys_Pod_*)self;
    return (fr_Obj)pod->name;
}
fr_Obj sys_Pod_version_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Obj sys_Pod_depends_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Obj sys_Pod_uri_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Obj sys_Pod_toStr_f(fr_Env env, fr_Obj self) {
    return sys_Pod_name_f(env, self);
}
fr_Obj sys_Pod_meta_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Obj sys_Pod_types_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Obj sys_Pod_type_f(fr_Env env, fr_Obj self, fr_Obj name, fr_Bool checked) {
    struct sys_Pod_* pod;
    
    //fr_lock(env);
    pod = reinterpret_cast<struct sys_Pod_*>(fr_getPtr(env, self));
    FPod *fpod = (FPod *)pod->fpod;
    //fr_unlock(env);
    
    const char *sname = fr_getStrUtf8(env, name, nullptr);
    auto found = fpod->c_typeMap.find(sname);
    if (found == fpod->c_typeMap.end()) {
        if (checked) {
            fr_throwNew(env, "sys", "UnknownTypeErr", sname);
        }
        return NULL;
    }
    
    FType *ftype = found->second;
    fr_Obj type = fr_getTypeObj(env, ftype);
    return type;
}
fr_Obj sys_Pod_files_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Obj sys_Pod_file_f(fr_Env env, fr_Obj self, fr_Obj uri, fr_Bool checked) {
    return 0;
}
fr_Obj sys_Pod_doc_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Obj sys_Pod_log_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Obj sys_Pod_props_f(fr_Env env, fr_Obj self, fr_Obj uri, fr_Obj maxAge) {
    return 0;
}
fr_Obj sys_Pod_config_f(fr_Env env, fr_Obj self, fr_Obj name, fr_Obj def) {
    return 0;
}
fr_Obj sys_Pod_locale_f(fr_Env env, fr_Obj self, fr_Obj name, fr_Obj def) {
    return 0;
}
CF_BEGIN
void sys_Pod_static__init(fr_Env env) {
    return;
}
CF_END
