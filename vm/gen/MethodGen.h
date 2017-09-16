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
    
    MethodGen(TypeGen *parent, FMethod *method);
    
    void genPrototype(Printer *printer, bool funcPtr);
    void genCode(Printer *printer);
};

#endif /* MethodGen_h */
