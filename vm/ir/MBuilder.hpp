//
// Copyright (c) 2017, chunquedong
// Licensed under the Apache Licene 2.0
//
//  Created by yangjiandong on 16/9/10.
//

#ifndef IRBuilder_hpp
#define IRBuilder_hpp

#include <stdio.h>
#include "IRMethod.h"

/**
 * Convert fcode to IR
 */
class MBuilder {
    std::unordered_map<int16_t, Block*> posToBlock;

    std::vector<Block *> blocks;
    std::vector<Var> locals;
    
    int allLocalsCount;
    FPod *curPod;
    
    IRMethod &irMethod;
    Code &code;
    std::vector<FErrTable*> attrs;
    
public:
    MBuilder(Code &code, IRMethod &irMethod);
    
    //parse code to basic block graph, and flat temp var to stack for gc
    bool buildMethod(FMethod *method);
    
    bool buildDefParam(FMethod *method, int paramNum);
    
private:
    
    void doBuild();
    
    Var &newVar(uint16_t typeRef) {
        Var var;
        var.index = (int)locals.size();
        var.block = -1;
        var.typeRef = typeRef;
        locals.push_back(var);
        return locals.back();
    }
    
    void initJumpTarget();
    
    void initBlock();
    
    void linkBlock();
    
    void rewriteLocals();
    
    void call(Block *block, FOpObj &opObj, bool isVirtual, bool isStatic
              , bool isMixin, bool isAlloc = false);
    
    void parseBlock(Block *block, Block *previous);
    
    CoerceStmt::CType typeCoerce(uint16_t from, uint16_t to);
    
    void insertException();
};


#endif /* IRBuilder_hpp */
