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
}

bool MethodGen::genPrototype(Printer *printer, bool funcPtr, bool isValType) {
    int paramNum = method->paramCount;
    
    auto typeName = parent->podGen->getTypeRefName(method->returnType);
    
    if (typeName == "sys_Void") {
        typeName = "void";
    }
    else if (typeName == "sys_This") {
        typeName = parent->name;
    }
    
    const char *valFlag = "";
    if (isValType) valFlag = "_val";
    
    if (funcPtr) {
        //void (*foo3_val)(
        printer->printf("%s (*%s%d%s)(", typeName.c_str(), name.c_str(), paramNum, valFlag);
    } else {
        //void sys_Int_foo3_val(
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
    genPrototype(printer, funcPtr, isValType);
    printer->println(";");
}

void MethodGen::genImples(Printer *printer) {
    //if (name != "flatten") return;
    
    bool isVal = !isStatic && parent->isValueType;

    if ((method->flags & FFlags::Native) != 0 || (method->flags & FFlags::Abstract) != 0) {
        return;
    }
    if ((parent->type->meta.flags & FFlags::Native) != 0
        && ((method->flags & FFlags::Overload) == 0 || parent->name == "sys_Func")) {
        return;
    }
    
    //if (method->code.isEmpty()) return;
    
    genPrototype(printer, false, isVal);
    printer->println(" {");
    
    IRMethod irMethod(parent->podGen->pod, method);
    irMethod.name = this->name;
    MBuilder builder(method->code, irMethod);
    builder.buildMethod(method);
    
    printer->indent();
    irMethod.print(*printer, 1);
    printer->unindent();

    printer->println("}");
}

/**
 ** gen for value type. e.g.
 ** void foo(Obj __self, Int arg) {
 **     foo_val(UNBOXING(__self), arg)
 ** }
 **/
void MethodGen::genImplesToVal(Printer *printer) {
    genPrototype(printer, false, false);
    printer->println(" {");
    printer->indent();
    
    auto typeName = parent->podGen->getTypeRefName(method->returnType);
    
    if (typeName != "sys_Void") {
        printer->printf("return ");
    }
    
    int i = method->paramCount;
    if (FCodeUtil::isBuildinValType(method->c_parent)) {
        printer->printf("%s_%s%d_val(__env, FR_UNBOXING_VAL(__self, %s)"
                        , parent->name.c_str(), name.c_str(), i, parent->name.c_str());
    } else {
        printer->printf("%s_%s%d_val(__env, FR_UNBOXING(__self, %s)"
                        , parent->name.c_str(), name.c_str(), i, parent->name.c_str());
    }
    
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

/**
 ** Gen stub to call VM in native code:
    Type foo(__env, __self, Int arg1, Int arg2) {
      static fr_Method method = NULL;
      fr_Value args[3];
      fr_Value __ret;
 
      if (!method) method = fr_findMethod(__env, Class_foo);
      args[0].o = __self;
      args[1].o = arg1;
      args[2].o = arg2;
      __ret = fr_callMethod(__env, method, args, 3)
    }
 **
 **/
void MethodGen::genMethodStub(Printer *printer, bool isValType) {
    genPrototype(printer, false, isValType);
    printer->println(" {");
    
    int paramNum = method->paramCount;
    auto retTypeName = parent->podGen->getTypeRefName(method->returnType);
    
    printer->indent();
    printer->println("static fr_Method method = NULL;");
    if (isStatic) {
        printer->println("fr_Value args[%d];", paramNum);
    } else {
        printer->println("fr_Value args[%d];", paramNum+1);
    }
    
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
    genMethodStub(printer, false);
    if (!isStatic && parent->isValueType) {
        genMethodStub(printer, true);
    }
}

/**
 ** gen register native to VM
 **/
void MethodGen::genRegister(Printer *printer) {
    printer->println("fr_registerMethod(vm, \"%s_%s\", %s_%s_wrap__);"
                     , parent->name.c_str(), name.c_str()
                     , parent->name.c_str(), name.c_str());
}
/**
 ** gen wrap to call native code for VM
 ** 
   void foo_wrap(__env, args, paramCount, fr_Value *__retVal) {
      Type __self = args[0].o;
      Type2 arg1 = args[1].o;
      Type3 arg2 = args[2].o;
      __retVal.o = foo(__env, __self, arg1, arg2);
   }
 **/
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
