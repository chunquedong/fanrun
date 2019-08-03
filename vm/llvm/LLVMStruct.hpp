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

class LLVMStruct {
public:
    FType *ftype;
    llvm::StructType *structTy;
    llvm::PointerType *structPtr;
    
    std::map<std::string, int> fieldIndex;
};

#endif /* LLVMStruct_hpp */
