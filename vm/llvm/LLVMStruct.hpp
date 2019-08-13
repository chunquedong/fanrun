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

#include <map>
#include <string>

class LLVMGenCtx;

struct VirtualMethod {
    llvm::Function *realMethod;
    bool fromObj;
    int offsetVTable;
};

class LLVMStruct {
    bool isVTableInited;
    bool isVTableGened;
public:
    FPod *fpod;
    FType *ftype;
    llvm::StructType *structTy;
    llvm::PointerType *structPtr;
    LLVMGenCtx *ctx;
    llvm::IRBuilder<> builder;
    
    
    std::vector<llvm::GlobalVariable*> vtables;
    
    std::map<std::string, int> fieldIndex;
    std::map<std::string, llvm::Function *> declMethods;
    std::map<std::string, VirtualMethod> resolvedMethods;
    std::map<std::string, VirtualMethod> vtableMethods;
    
    
    LLVMStruct(LLVMGenCtx *ctx, FType *ftype, std::string &name);
    
    void init();
private:
    void genVTableInit();
    void genVTableAt(llvm::Value *vtablePos, std::map<std::string, VirtualMethod> &resolvedMethods);
    
    void initVTable();
    void initVTableLayout();
    void resolveMethod();
    void inheritMethod(LLVMStruct *base, bool isMixin);
};

#endif /* LLVMStruct_hpp */
