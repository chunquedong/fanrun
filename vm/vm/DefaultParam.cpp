//
//  DefaultParam.cpp
//  vm
//
//  Created by yangjiandong on 10/25/15.
//  Copyright © 2015 chunquedong. All rights reserved.
//

#include "DefaultParam.h"
#include "Env.h"

bool DefaultParam::getDefaultParam(Env *context, int index
                    , FMethodVar &var, fr_TagValue &val, FMethod *method) {
    FParamDefault *attr = NULL;
    for (int i=0; i<var.attrs.size(); ++i) {
        attr = dynamic_cast<FParamDefault*>(var.attrs[i]);
        if (attr) {
            break;
        }
    }
    if(!attr) {
        return false;
    }
    
    if (context->trace) {
        printf("get default param:%s\n"
               , method->c_parent->c_pod->names[var.name].c_str());
    }
    context->call(method, index, attr);
    
    context->pop(&val);
    context->popFrame();
    return true;
}

void DefaultParam::initDefaultParam(Env *context, int paramCount, FMethod *method) {
    //closure may reduce the param
    for (int i = paramCount; i > method->paramCount; --i) {
        fr_TagValue entry;
        context->pop(&entry);
    }
    
    //add default param if absent
    for (int i=paramCount;
         i<method->paramCount; ++i) {
        FMethodVar &var = method->vars[i];
        fr_TagValue val;
        bool ok = getDefaultParam(context, i, var, val, method);
        assert(ok);
        context->push(&val);
    }
}
