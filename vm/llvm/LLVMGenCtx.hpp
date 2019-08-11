//
//  LLVMGenCtx.hpp
//  vm
//
//  Created by yangjiandong on 2019/8/11.
//  Copyright © 2019 yangjiandong. All rights reserved.
//

#ifndef LLVMGenCtx_hpp
#define LLVMGenCtx_hpp

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
#include <algorithm>
#include <cassert>
#include <memory>
#include <vector>
#include <map>
#include <string>

#include "IRMethod.h"


class LLVMStruct;

class LLVMGenCtx {
public:
    llvm::LLVMContext *context;
    llvm::Module *module;
    
    std::map<std::string, LLVMStruct*> structMap;
    
    llvm::Type *ptrType;
    llvm::Type *pptrType;
    //llvm::Type *valueType;
    //llvm::Type *pvalueType;
    
    LLVMGenCtx(llvm::LLVMContext *context);
    
    llvm::Type *toLlvmType(FPod *curPod, int16_t type);
    
    LLVMStruct *getStruct(FPod *curPod, int16_t type);
    
    int fieldIndex(FPod *curPod, FFieldRef *ref);
private:
    LLVMStruct *getLLVMStruct(FType *ftype);
};

#endif /* LLVMGenCtx_hpp */
