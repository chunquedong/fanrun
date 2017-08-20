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

class Env;

class LLVMCodeGen {
    std::string &name;
    IRMethod *irMethod;
    llvm::IRBuilder<> Builder;
    llvm::LLVMContext &Context;
    
    llvm::Function *function;
    llvm::Function *callee;
    
    std::vector<llvm::Value*> primLocals;
    llvm::Value *refLocals;
    
    //temp
    llvm::Value *envValue;
    llvm::Value *localsPtr;
    
    llvm::Type *ptrType;
    llvm::Type *pptrType;
    llvm::Type *valueType;
    llvm::Type *pvalueType;
    
public:
    Env *env;
    
    LLVMCodeGen(llvm::LLVMContext &Context, Env *env, IRMethod *irMethod, std::string &name);
    
    llvm::Function *gen(llvm::Module *M);
    
private:
    void genBlock(Block *block);
    void genStmt(Stmt *stmt);
    llvm::Value *genExpr(Expr *expr);
    llvm::Value *ptrConst(void *ptr);
};

#endif /* LLVMCodeGen_hpp */
