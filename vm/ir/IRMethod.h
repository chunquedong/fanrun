//
// Copyright (c) 2017, chunquedong
// Licensed under the Apache Licene 2.0
//
//  Created by yangjiandong on 16/9/10.
//

#ifndef ____IRMethod__
#define ____IRMethod__

#include "Stmt.hpp"


class IRMethod {
public:
    FMethod *method;
    std::vector<Block *> blocks;
    std::vector<Var> locals;
    
    int primLocalsCount;
    int refLocalsCount;
    
    //Env *context;
    FPod *curPod;
    
    IRMethod(FPod *curPod, FMethod *method);
    
    void compile();
    void print(PodLoader *podManager, Printer& printer, int pass);
private:
    
    Var &newVar() {
        Var var;
        var.index = (int)locals.size();
        var.newIndex = -1;
        var.block = -1;
        var.isExport = true;
        var.methodVar = nullptr;
        var.isRef = true;
        
        locals.push_back(var);
        return locals.back();
    }

    void initJumpTarget();
    
    void initBlock();
    
    void linkBlock();
    
    void initLocals();
    
    void call(Block *block, FOpObj &opObj, bool isVirtual, bool isStatic);
    
    void parseBlock(Block *block, Block *previous);
    
    bool isVoidTypeRef(uint16_t typeRef);
};

#endif /* defined(____IRMethod__) */
