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

static const char* getUnionTagName(std::string &type) {
    const char* tagName = "";
    if (type == "sys_Int") {
        tagName = "i";
    }
    else if (type == "sys_Bool") {
        tagName = "b";
    }
    else if (type == "sys_Float") {
        tagName = "f";
    }
    else {
        tagName = "o";
    }
    return tagName;
}

MethodGen::MethodGen(TypeGen *parent, FMethod *method) : parent(parent), method(method) {
    name = FCodeUtil::getIdentifierName(parent->podGen->pod, method->name);
    isStatic = (method->flags & FFlags::Static);
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

bool MethodGen::genPrototype(Printer *printer, bool funcPtr, bool isValType, int i) {
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
    
    const char *valFlag = "";
    if (isValType) valFlag = "_val";
    
    if (funcPtr) {
        printer->printf("%s (*%s%d%s)(", typeName.c_str(), name.c_str(), paramNum, valFlag);
    } else {
        printer->printf("%s %s_%s%d%s(", typeName.c_str(), parent->name.c_str(), name.c_str(), paramNum, valFlag);
    }
    
    printer->printf("fr_Env __env");
    
    if (!isStatic) {
        if (isValType) {
            printer->printf(", %s_val __self", parent->name.c_str());
        } else {
            printer->printf(", %s_ref __self", parent->name.c_str());
        }
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

void MethodGen::genDeclares(Printer *printer, bool funcPtr, bool isValType) {
    for (int i=beginDefaultParam; i<=method->paramCount; ++i) {
        genPrototype(printer, funcPtr, isValType, i);
        printer->println(";");
    }
}

void MethodGen::genImples(Printer *printer) {
    bool isVal = !isStatic && FCodeUtil::isValType(parent->name);
    for (int i=beginDefaultParam; i<=method->paramCount; ++i) {
        if (i == method->paramCount) {
            if ((method->flags & FFlags::Native)
                || (method->flags & FFlags::Abstract)
                || (parent->type->meta.flags & FFlags::Native)) {
                continue;
            }
        } else {
            if (parent->name == "sys_Func") {
                continue;
            }
        }
        genPrototype(printer, false, isVal, i);
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
            builder.buildDefParam(method, i, isVal);
            
            printer->indent();
            irMethod.print(*printer, 1);
            printer->unindent();
        }
        printer->println("}");
    }
}

void MethodGen::genImplesToVal(Printer *printer) {
    for (int i=beginDefaultParam; i<=method->paramCount; ++i) {
        genPrototype(printer, false, false, i);
        printer->println(" {");
        printer->indent();
        
        auto typeName = parent->podGen->getTypeRefName(method->returnType);
        
        if (typeName != "sys_Void") {
            printer->printf("return ");
        }
        
        printer->printf("%s_%s%d_val(__env, __self->_val", parent->name.c_str(), name.c_str(), i);
        
        int paramNum = i;
        for (int j=0; j<paramNum; ++j) {
            FMethodVar &var = method->vars[j];
            auto var_name = FCodeUtil::getIdentifierName(parent->podGen->pod, var.name);
            printer->printf(", %s", var_name.c_str());
        }
        printer->println(");");
        printer->unindent();
        printer->println("}");
    }
}
void MethodGen::genMethodStub(Printer *printer, bool isValType, int i) {
    genPrototype(printer, false, isValType, i);
    printer->println(" {");
    
    int paramNum = i;
    auto retTypeName = parent->podGen->getTypeRefName(method->returnType);
    
    printer->indent();
    printer->println("static fr_Method method = NULL;");
    printer->println("fr_Value args[%d];", paramNum);
    
    if (retTypeName != "sys_Void") {
        printer->println("fr_Value __ret;");
    }
    printer->println("if (!method) method = fr_findMethod(__env, \"%s_%s\");"
                    , parent->name.c_str(), name.c_str());
    
    if (!isStatic) {
        if (isValType) {
            printer->println("args[0].%s = __self;", getUnionTagName(parent->name));
        } else {
            printer->println("args[0].o = __self;");
        }
    }
    
    for (int j=0; j<paramNum; ++j) {
        FMethodVar &var = method->vars[j];
        auto var_name = FCodeUtil::getIdentifierName(parent->podGen->pod, var.name);
        auto var_typeName = parent->podGen->getTypeRefName(var.type);
        const char *tag = getUnionTagName(var_typeName);
        if (isStatic) {
            printer->println("args[%d].%s = %s;", j, tag, var_name.c_str());
        } else {
            printer->println("args[%d].%s = %s;", j+1, tag, var_name.c_str());
        }
    }
    printer->println("__ret = fr_callMethod(__env, method, args, %d);", paramNum);
    
    
    if (retTypeName != "sys_Void") {
        printer->println("return __ret.%s;", getUnionTagName(retTypeName));
    }
    printer->unindent();
    printer->println("}");
}
void MethodGen::genStub(Printer *printer) {
    for (int i=beginDefaultParam; i<=method->paramCount; ++i) {
        genMethodStub(printer, false, i);
        if (!isStatic && FCodeUtil::isValType(parent->name)) {
            genMethodStub(printer, true, i);
        }
    }
}

void MethodGen::genRegister(Printer *printer) {
    printer->println("fr_registerMethod(vm, \"%s_%s\", %s_%s_wrap__);"
                     , parent->name.c_str(), name.c_str()
                     , parent->name.c_str(), name.c_str());
}

void MethodGen::genRegisterWrap(Printer *printer) {
    printer->println("void %s_%s_wrap__(fr_Env __env, fr_Value *args, int paramCount, fr_Value *__retVal) {"
                     , parent->name.c_str(), name.c_str());
    printer->indent();
    int paramNum = method->paramCount;
    auto retTypeName = parent->podGen->getTypeRefName(method->returnType);
    
    if (!isStatic) {
        printer->println("%s __self = args[0].%s;", parent->name.c_str(), getUnionTagName(parent->name));
    }
    for (int j=0; j<paramNum; ++j) {
        FMethodVar &var = method->vars[j];
        auto var_name = FCodeUtil::getIdentifierName(parent->podGen->pod, var.name);
        auto var_typeName = parent->podGen->getTypeRefName(var.type);
        
        if (isStatic) {
            printer->println("%s %s = args[%d].%s;"
                    , var_typeName.c_str(), var_name.c_str(), j, getUnionTagName(var_typeName));
        } else {
            printer->println("%s %s = args[%d].%s;"
                    , var_typeName.c_str(), var_name.c_str(), j+1, getUnionTagName(var_typeName));
        }
    }
    
    if (retTypeName != "sys_Void") {
        printer->printf("*__retVal.%s = ", getUnionTagName(retTypeName));
    }
    
    printer->printf("%s_%s(__env", parent->name.c_str(), name.c_str());
    if (!isStatic) {
        printer->printf(", __self");
    }
    for (int j=0; j<paramNum; ++j) {
        FMethodVar &var = method->vars[j];
        auto var_name = FCodeUtil::getIdentifierName(parent->podGen->pod, var.name);
        printer->printf(", %s", var_name.c_str());
    }
    printer->println(");");
    
    printer->unindent();
    printer->println("}");
}
