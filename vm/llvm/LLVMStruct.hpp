//
//  LLVMStruct.hpp
//  vm
//
//  Created by yangjiandong on 2019/8/3.
//  Copyright © 2019 yangjiandong. All rights reserved.
//

#ifndef LLVMStruct_hpp
#define LLVMStruct_hpp

#include <stdio.h>
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
#include "FPod.h"
#include "IRType.hpp"

#include <map>
#include <string>

class LLVMGenCtx;

class LLVMStruct {
public:
    IRType *irType;
    
    llvm::StructType *structTy;
    llvm::PointerType *structPtr;
    LLVMGenCtx *ctx;
    llvm::IRBuilder<> builder;
    
    std::vector<llvm::GlobalVariable*> staticFields;
    
    
    std::vector<llvm::GlobalVariable*> vtables;
    
    std::map<std::string, int> fieldIndex;
    std::map<std::string, llvm::Function *> declMethods;
    
    LLVMStruct(LLVMGenCtx *ctx, IRType *irType, std::string &name);
    
public:
    void init();
public:
    void genVTable();
private:
    void genVTableAt(llvm::Value *vtablePos, IRVTable *irVTable);
};

#endif /* LLVMStruct_hpp */
