//
//  CodeGen.c
//  gen
//
//  Created by yangjiandong on 2017/9/16.
//  Copyright © 2017年 yangjiandong. All rights reserved.
//

#include "MethodGen.h"
#include "IRMethod.h"
#include "PodGen.hpp"

MethodGen::MethodGen(TypeGen *parent, FMethod *method) : parent(parent), method(method) {
    name = parent->podGen->getIdentifierName(method->name);
    //name += std::to_string(method->paramCount);
    
    if (parent->name == "sys_Func" && name == "call") {
        printf("");
    }
    
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
        auto var_name = parent->podGen->getIdentifierName(var.name);
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

void MethodGen::genCode(Printer *printer) {
    IRMethod irMethod(parent->podGen->pod, method);
    irMethod.compile();
    
    printer->indent();
    /*
    for(int i=irMethod.method->paramCount; i<irMethod.locals.size(); ++i) {
        Var v = irMethod.locals[i];
        printer->printf("%s v__%s_%d, ", v.typeName.c_str(), v.name.c_str(), v.index);
    }
    printer->newLine();
    
    
    for (Block *b : irMethod.blocks) {
        b->print(&irMethod, *printer, 0);
    }
    for (Block *b : irMethod.blocks) {
        b->print(&irMethod, *printer, 1);
    }*/
    irMethod.print(*printer, 1);
    printer->unindent();
}
