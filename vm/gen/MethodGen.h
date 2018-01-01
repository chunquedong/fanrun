//
//  CodeGen.h
//  gen
//
//  Created by yangjiandong on 2017/9/16.
//  Copyright © 2017年 yangjiandong. All rights reserved.
//

#ifndef MethodGen_h
#define MethodGen_h

#include "PodLoader.h"
#include "Printer.h"
#include "IRMethod.h"
#include "TypeGen.h"

struct MethodGen {
    TypeGen *parent;
    FMethod *method;
    std::string name;
    
    int beginDefaultParam;
    bool isStatic;
    
    MethodGen(TypeGen *parent, FMethod *method);
    
    void genDeclares(Printer *printer, bool funcPtr, bool isValType);
    void genImples(Printer *printer);
    void genImplesToVal(Printer *printer);
    void genStub(Printer *printer);
    
    void genRegisterWrap(Printer *printer);
    void genRegister(Printer *printer);
private:
    bool genPrototype(Printer *printer, bool funcPtr, bool isValType, int i);
    FParamDefault *getParamDefault(int i);
    void genMethodStub(Printer *printer, bool isValType, int i);
};

#endif /* MethodGen_h */
