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
    std::unordered_map<int16_t, Block*> posToBlock;
public:
    FMethod *method;
    std::vector<Block *> blocks;
    std::vector<Var> locals;
    
    int primLocalsCount;
    int refLocalsCount;
    
    //std::string name;
    
    //Env *context;
    FPod *curPod;
    
    IRMethod(FPod *curPod, FMethod *method);
    
    //parse code to basic block graph, and flat temp var to stack for gc
    void compile();
    
    void print(Printer& printer, int pass);
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
    
    void initException();
};

#endif /* defined(____IRMethod__) */
