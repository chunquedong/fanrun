#include "vm.h"
#include "pod_sys_struct.h"
#include "pod_sys_native.h"

fr_Obj sys_Slot_find_f(fr_Env env, fr_Obj qname, fr_Bool checked) {
    return 0;
}
fr_Obj sys_Slot_findMethod_f(fr_Env env, fr_Obj qname, fr_Bool checked) {
    return 0;
}
fr_Obj sys_Slot_findField_f(fr_Env env, fr_Obj qname, fr_Bool checked) {
    return 0;
}
fr_Obj sys_Slot_findFunc_f(fr_Env env, fr_Obj qname, fr_Bool checked) {
    return 0;
}
void sys_Slot_make_f(fr_Env env, fr_Obj self) {
    return;
}
fr_Obj sys_Slot_parent_f(fr_Env env, fr_Obj self) {
    struct sys_Slot_ *slot;
    fr_Obj result;
    //fr_lock(env);
    slot = (struct sys_Slot_ *)fr_getPtr(env, self);
    result = slot->parent;
    //fr_unlock(env);
    return result;
}
fr_Obj sys_Slot_name_f(fr_Env env, fr_Obj self) {
    struct sys_Slot_ *slot;
    fr_Obj result;
    //fr_lock(env);
    slot = (struct sys_Slot_ *)fr_getPtr(env, self);
    
    result = slot->name;
    //fr_unlock(env);
    return result;
}
fr_Obj sys_Slot_qname_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Bool sys_Slot_isField_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Bool sys_Slot_isMethod_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Bool sys_Slot_isAbstract_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Bool sys_Slot_isConst_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Bool sys_Slot_isCtor_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Bool sys_Slot_isInternal_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Bool sys_Slot_isNative_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Bool sys_Slot_isOverride_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Bool sys_Slot_isPrivate_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Bool sys_Slot_isProtected_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Bool sys_Slot_isPublic_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Bool sys_Slot_isStatic_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Bool sys_Slot_isSynthetic_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Bool sys_Slot_isVirtual_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Obj sys_Slot_facets_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Obj sys_Slot_facet_f(fr_Env env, fr_Obj self, fr_Obj type, fr_Bool checked) {
    return 0;
}
fr_Bool sys_Slot_hasFacet_f(fr_Env env, fr_Obj self, fr_Obj type) {
    return 0;
}
fr_Obj sys_Slot_doc_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Obj sys_Slot_toStr_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Obj sys_Slot_signature_f(fr_Env env, fr_Obj self) {
    return 0;
}

void sys_Slot_static__init(fr_Env env) {
    return;
}
