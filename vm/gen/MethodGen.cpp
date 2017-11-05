//
//  CodeGen.c
//  gen
//
//  Created by yangjiandong on 2017/9/16.
//  Copyright © 2017年 yangjiandong. All rights reserved.
//

#include "MethodGen.h"
#include "MBuilder.hpp"
#include "PodGen.hpp"
#include "FCodeUtil.hpp"


MethodGen::MethodGen(TypeGen *parent, FMethod *method) : parent(parent), method(method) {
    name = FCodeUtil::getIdentifierName(parent->podGen->pod, method->name);
    
    beginDefaultParam = -1;
    for (int j=0; j<method->paramCount; ++j) {
        FMethodVar &var = method->vars[j];
        for (FAttr *attr : var.attrs) {
            if (dynamic_cast<FParamDefault*>(attr)) {
                beginDefaultParam = j;
                break;
            }
        }
        if (beginDefaultParam != -1) break;
    }
    if (beginDefaultParam == -1) {
        beginDefaultParam = method->paramCount;
    }
}

FParamDefault *MethodGen::getParamDefault(int i) {
    FMethodVar &var = method->vars[i];
    for (FAttr *attr : var.attrs) {
        FParamDefault *res = dynamic_cast<FParamDefault*>(attr);
        if (res) {
            return res;
        }
    }
    return nullptr;
}

bool MethodGen::genPrototype(Printer *printer, bool funcPtr, int i) {
    int paramNum = i;
    if (i == -1) {
        paramNum = method->paramCount;
    }
    else if (i < beginDefaultParam) {
        return false;
    }
    else if (i > method->paramCount) {
        printf("ERROR: default param count out index\n");
        return false;
    }
    
    auto typeName = parent->podGen->getTypeRefName(method->returnType);
    
    if (typeName == "sys_Void") {
        typeName = "void";
    }
    
    if (funcPtr) {
        printer->printf("%s (*%s%d)(", typeName.c_str(), name.c_str(), paramNum);
    } else {
        printer->printf("%s %s_%s%d(", typeName.c_str(), parent->name.c_str(), name.c_str(), paramNum);
    }
    
    printer->printf("fr_Env __env");
    
    bool isStatic = (method->flags & FFlags::Static);
    if (!isStatic) {
        printer->printf(", %s __self", parent->name.c_str());
    }
    
    for (int j=0; j<paramNum; ++j) {
        FMethodVar &var = method->vars[j];
        auto var_name = FCodeUtil::getIdentifierName(parent->podGen->pod, var.name);
        auto var_typeName = parent->podGen->getTypeRefName(var.type);
        
        printer->printf(", %s %s", var_typeName.c_str(), var_name.c_str());
    }
    printer->printf(")");
    return true;
}

void MethodGen::genDeclares(Printer *printer, bool funcPtr) {
    for (int i=beginDefaultParam; i<=method->paramCount; ++i) {
        genPrototype(printer, funcPtr, i);
        printer->println(";");
    }
}

void MethodGen::genImples(Printer *printer, bool funcPtr) {
    for (int i=beginDefaultParam; i<=method->paramCount; ++i) {
        genPrototype(printer, funcPtr, i);
        printer->println(" {");
        if (i == method->paramCount) {
            IRMethod irMethod(parent->podGen->pod, method);
            irMethod.name = this->name;
            MBuilder builder(method->code, irMethod);
            builder.buildMethod(method);
            
            printer->indent();
            irMethod.print(*printer, 1);
            printer->unindent();
        } else {
            FParamDefault *def = getParamDefault(i);
            if (def == nullptr) {
                printf("ERROR: get param default fail\n");
                return;
            }
            IRMethod irMethod(parent->podGen->pod, method);
            irMethod.name = this->name;
            MBuilder builder(def->opcodes, irMethod);
            builder.buildDefParam(method, i);
            
            printer->indent();
            irMethod.print(*printer, 1);
            printer->unindent();
        }
        printer->println("}");
    }
}

