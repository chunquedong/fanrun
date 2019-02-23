#include "vm.h"
#include "pod_sys_struct.h"
#include "pod_sys_native.h"
#include "FType.h"

extern  "C"  {
FObj *sys_Type_fromFType(fr_Env env, FType* ftype) {
    fr_Type type = fr_findType(env, "sys", "Type");
    //fr_lock(env);
    FObj *otype = fr_allocObj_internal(env, type, sizeof(struct sys_Type_));
    struct sys_Type_ *stype = reinterpret_cast<struct sys_Type_*>((otype));
    stype->ftype = ftype;
    //fr_unlock(env);

    return reinterpret_cast<FObj*>(stype);
}

FType* sys_Type_toFType(fr_Env env__, FObj* otype) {
    struct sys_Type_ *stype = reinterpret_cast<struct sys_Type_*>((otype));
    return stype->ftype;
}
}

void sys_Type_privateMake_f(fr_Env env, fr_Obj self) {
    return;
}
fr_Obj sys_Type_of_f(fr_Env env, fr_Obj obj) {
    return 0;
}
fr_Obj sys_Type_find_f(fr_Env env, fr_Obj qname, fr_Bool checked) {
    return 0;
}
fr_Obj sys_Type_pod_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Obj sys_Type_name_f(fr_Env env, fr_Obj self) {
    struct sys_Type_ *stype;
    fr_Obj result;
    //fr_lock(env);
    stype = reinterpret_cast<struct sys_Type_ *>(fr_getPtr(env, self));
    if (!stype->name) {
        std::string &name = ((FType*)stype->ftype)->c_name;
        stype->name = fr_newGlobalRef(env, fr_newStrUtf8(env, name.c_str()));
    }
    result = stype->name;
    //fr_unlock(env);
    return result;
}
fr_Obj sys_Type_qname_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Obj sys_Type_signature_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Obj sys_Type_base_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Obj sys_Type_mixins_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Obj sys_Type_inheritance_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Bool sys_Type_fits_f(fr_Env env, fr_Obj self, fr_Obj t) {
    return 0;
}
fr_Bool sys_Type_isVal_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Bool sys_Type_isNullable_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Obj sys_Type_toNullable_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Obj sys_Type_toNonNullable_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Bool sys_Type_isGeneric_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Obj sys_Type_params_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Obj sys_Type_parameterize_f(fr_Env env, fr_Obj self, fr_Obj params) {
    return 0;
}
fr_Obj sys_Type_toListOf_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Obj sys_Type_emptyList_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Bool sys_Type_isAbstract_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Bool sys_Type_isClass_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Bool sys_Type_isConst_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Bool sys_Type_isEnum_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Bool sys_Type_isFacet_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Bool sys_Type_isFinal_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Bool sys_Type_isInternal_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Bool sys_Type_isMixin_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Bool sys_Type_isPublic_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Bool sys_Type_isSynthetic_f(fr_Env env, fr_Obj self) {
    return 0;
}
/*
fr_Obj sys_Type_fields_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Obj sys_Type_methods_f(fr_Env env, fr_Obj self) {
    struct sys_Type_ *stype;
    fr_Obj result;
    //fr_lock(env);
    stype = reinterpret_cast<struct sys_Type_ *>(fr_getPtr(env, self));
    
    if (!stype->methods) {
        fr_Value val[2];
        fr_Type typeType = fr_getObjType(env, self);
        //val[0].type = fr_vtHandle;
        val[0].h = fr_getTypeObj(env, typeType);
        
        //val[1].type = fr_vtInt;
        val[1].i = ((FType*)stype->ftype)->methods.size();

        fr_Value list[2];
        fr_newObj(env, "sys", "List", "make", 2, val, &list[0]);
        
        stype->methods = list[0].h;
        fr_Type listType = fr_findType(env, "sys", "List");
        fr_Method fmethod = fr_findMethod(env, listType, "add");
        
        for (int i=0; i<((FType*)stype->ftype)->methods.size(); ++i) {
            FMethod &method = ((FType*)stype->ftype)->methods[i];
            fr_Obj smethod;
            smethod = sys_Method_fromFMethod(env, &method);
            
            fr_Value met;
            //met.type = fr_vtHandle;
            met.h = smethod;

            list[1] = met;
            
            fr_callMethod(env, fmethod, 1+1, list, NULL);
            
            if (fr_errorOccurred(env)) {
                return NULL;
            }
        }
    }
    result = stype->methods;
    //fr_unlock(env);
    return result;
}
fr_Obj sys_Type_slots_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Obj sys_Type_field_f(fr_Env env, fr_Obj self, fr_Obj name, fr_Bool checked) {
    return 0;
}
fr_Obj sys_Type_method_f(fr_Env env, fr_Obj self, fr_Obj name, fr_Bool checked) {
    return 0;
}
fr_Obj sys_Type_slot_f(fr_Env env, fr_Obj self, fr_Obj name, fr_Bool checked) {
    return 0;
}
fr_Obj sys_Type_make_f(fr_Env env, fr_Obj self, fr_Obj args) {
    struct sys_Type_ *stype;
    //fr_lock(env);
    stype = reinterpret_cast<struct sys_Type_ *>(fr_getPtr(env, self));
    fr_Type ftype = stype->ftype;
    fr_Method method = fr_findMethod(env, ftype, "make");
    
    fr_Value arg;
    fr_Value ret;
    if (args == NULL || fr_getPtr(env, args) == NULL) {
        fr_newObjM(env, ftype, method, 0, &arg, &ret);
    } else {
        //TODO
        fr_throwUnsupported(env);
    }
    return ret.h;
}
fr_Obj sys_Type_facets_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Obj sys_Type_facet_f(fr_Env env, fr_Obj self, fr_Obj type, fr_Bool checked) {
    return 0;
}
fr_Bool sys_Type_hasFacet_f(fr_Env env, fr_Obj self, fr_Obj type) {
    return 0;
}
 */
fr_Obj sys_Type_doc_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Obj sys_Type_toStr_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Obj sys_Type_toLocale_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Bool sys_Type_isJava_f(fr_Env env, fr_Obj self) {
    return false;
}

CF_BEGIN
void sys_Type_static__init_f(fr_Env env) {
    return;
}
CF_END
