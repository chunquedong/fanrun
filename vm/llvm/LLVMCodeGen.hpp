//
//  LLVMCodeGen.hpp
//  vm
//
//  Created by yangjiandong on 16/9/16.
//  Copyright © 2017 chunquedong. All rights reserved.
//

#ifndef LLVMCodeGen_hpp
#define LLVMCodeGen_hpp

#include <stdio.h>
#include "IRMethod.h"

#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/Argument.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include <algorithm>
#include <cassert>
#include <memory>
#include <vector>
#include <map>
#include <string>

//class Env;
class LLVMStruct;
class LLVMGenCtx;

class LLVMCodeGen {
    std::string name;
    IRMethod *irMethod;
    llvm::IRBuilder<> Builder;
    
    LLVMGenCtx *ctx;
    llvm::Module *module;
    
    llvm::Function *function;
    
    std::vector<llvm::Value*> locals;
    
public:
    
    LLVMCodeGen(LLVMGenCtx *ctx, IRMethod *irMethod, std::string &name);
    
    llvm::Function *gen(llvm::Module *M);
    
    static llvm::Function* getFunctionProtoByDef(LLVMGenCtx *ctx, llvm::IRBuilder<> &Builder, FMethod *method);
    
private:
    llvm::Function* getFunctionProto(IRMethod *irMethod);
    llvm::Function* getFunctionProtoByRef(FPod *curPod, FMethodRef *ref, bool isStatic);
    void genBlock(Block *block);
    void genStmt(Stmt *stmt);
    
    llvm::Value *getExpr(Expr &expr);
    void setExpr(Expr &expr, llvm::Value *v);
    llvm::Value *getVTable(llvm::Value *v);
    
    void genCall(CallStmt *stmt);
    void genCompare(CompareStmt *stmt);
    void getConst(ConstStmt *stmt);
    
};

#endif /* LLVMCodeGen_hpp */
