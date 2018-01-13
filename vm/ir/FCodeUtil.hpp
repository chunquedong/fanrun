//
//  FCodeUtil.hpp
//  gen
//
//  Created by yangjiandong on 2017/11/5.
//  Copyright © 2017年 yangjiandong. All rights reserved.
//

#ifndef FCodeUtil_hpp
#define FCodeUtil_hpp

#include <stdio.h>
#include "PodLoader.h"

namespace FCodeUtil {
    std::string getTypeRefName(FPod *pod, uint16_t tid, bool checkNullable);
    bool isVoidTypeRef(FPod *curPod, uint16_t typeRefId);
    bool isValType(const std::string& name);
    bool isNullableType(const std::string& name);
    
    void getTypeInfo(FPod *curPod, FTypeRef &typeRef, bool &isVal, bool &isNullable);
    
    std::string getIdentifierName(FPod *pod, uint16_t nid);
    void escapeIdentifierName(std::string &name);
}

#endif /* FCodeUtil_hpp */
