//
//  FCodeUtil.cpp
//  gen
//
//  Created by yangjiandong on 2017/11/5.
//  Copyright © 2017年 yangjiandong. All rights reserved.
//

#include "FCodeUtil.hpp"
#include "../gen/escape.h"

namespace FCodeUtil {

    std::string getTypeRefName(FPod *pod, uint16_t tid, bool checkNullable) {
        FTypeRef &typeRef = pod->typeRefs[tid];
        std::string &podName = pod->names[typeRef.podName];
        std::string &typeName = pod->names[typeRef.typeName];
        std::string &sig = typeRef.signature;
        
        std::string res = podName + "_" + typeName;
        if (checkNullable && sig.size() > 0 && sig[sig.size()-1] == '?') {
            res += "_null";
        }
        
        escape(res);
        return res;
    }
    
    bool isBuildinVal(const std::string &name) {
        if (name == "sys_Int" || name == "sys_Bool" || name == "sys_Float") {
            return true;
        }
        return false;
    }
    
    bool isBuildinValType(FType *type) {
        if (type->c_pod->name == "sys") {
            if (type->c_name == "Int" || type->c_name == "Bool" || type->c_name == "Float") {
                return true;
            }
        }
        return false;
    }

    bool isValueType(FType *type) {
        if (type->c_pod->name == "sys") {
            if (type->c_name == "Str"
                || type->c_name == "Pod"
                || type->c_name == "Param"
                || type->c_name == "Method"
                || type->c_name == "Field"
                || type->c_name == "Func") {
                return false;
            }
        }
        
        if ((type->meta.flags & FFlags::Const) && (type->meta.flags & FFlags::Final)) {
            int count = 0;
            for (FField &field : type->fields) {
                if (field.flags & FFlags::Static) {
                    continue;
                }
                ++count;
                if (count > 5) return false;
            }
            return true;
        }
        return false;
    }
    
    bool isNullableTypeRef(FPod *pod, uint16_t tid) {
        FTypeRef &typeRef = pod->typeRefs[tid];
        //std::string &podName = pod->names[typeRef.podName];
        //std::string &typeName = pod->names[typeRef.typeName];
        std::string &sig = typeRef.signature;
        
        if (sig.size() > 0 && sig[sig.size()-1] == '?') {
            return true;
        }
        return false;
    }
    
    bool isValueTypeRef(FPod *pod, uint16_t tid) {
        if (isNullableTypeRef(pod, tid)) return false;
        FTypeRef &typeRef = pod->typeRefs[tid];
        std::string &podName = pod->names[typeRef.podName];
        std::string &typeName = pod->names[typeRef.typeName];
        
        FPod *curPod = pod->c_loader->findPod(podName);
        auto itr = curPod->c_typeMap.find(typeName);
        if (itr == curPod->c_typeMap.end()) {
            printf("ERROR: not found typeRef\n");
            return false;
        }
        return isValueType(itr->second);
    }
    
    bool isInheriteOf(const std::string &podName, const std::string &name
                      , FPod *curPod, uint16_t typeRefId) {
        FPod *pod = curPod->c_loader->findPod(podName);
        auto itr = pod->c_typeMap.find(name);
        if (itr == pod->c_typeMap.end()) {
            printf("ERROR: not found typeRef\n");
            return false;
        }
        FType *type = itr->second;
        if (type->meta.self == typeRefId || type->meta.base == typeRefId) {
            return true;
        }
        for (auto t : type->meta.mixin) {
            if (t == typeRefId) {
                return true;
            }
        }
        return false;
    }
    
    std::string getIdentifierName(FPod *pod, uint16_t nid) {
        std::string name = pod->names[nid];
        escape(name);
        escapeKeyword(name);
        return name;
    }
    
    void escapeIdentifierName(std::string &name) {
        escape(name);
        escapeKeyword(name);
    }
}//ns
