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

    bool isVoidTypeRef(FPod *curPod, uint16_t typeRefId) {
        FTypeRef &typeRef = curPod->typeRefs[typeRefId];
        if (curPod->names[typeRef.podName] == "sys"
            && curPod->names[typeRef.typeName] == "Void") {
            return true;
        }
        return false;
    }
    
    bool isValType(const std::string& name) {
        if (name == "sys_Int"
            || name == "sys_Float"
            || name == "sys_Bool") {
            return true;
        }
        return false;
    }
    
    bool isNullableType(const std::string& name) {
        auto pos = name.find("_null");
        if (pos != std::string::npos) {
            return true;
        }
        return false;
    }
    
    void getTypeInfo(FPod *curPod, FTypeRef &typeRef, bool &isVal, bool &isNullable) {
        std::string &podName = curPod->names[typeRef.podName];
        std::string &typeName = curPod->names[typeRef.typeName];
        std::string &signature = typeRef.signature;
        if (podName == "sys" &&
            (typeName == "Int" || typeName == "Float" || typeName == "Bool")) {
            isVal = true;
        } else {
            isVal = false;
        }
        if (signature.size() > 0 && signature[0] == '?') {
            isNullable = true;
        } else {
            isNullable = false;
        }
        
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
