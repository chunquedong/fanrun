//
//  LLVMGenCtx.cpp
//  vm
//
//  Created by yangjiandong on 2019/8/11.
//  Copyright © 2019 yangjiandong. All rights reserved.
//

#include "LLVMGenCtx.hpp"
#include "FCodeUtil.hpp"
#include "LLVMStruct.hpp"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Support/SourceMgr.h"

using namespace llvm;

LLVMGenCtx::LLVMGenCtx() {
    context = new llvm::LLVMContext();
    module = new llvm::Module("test", *context);
    ptrType = Type::getInt8PtrTy(*context);
    pptrType = ptrType->getPointerTo();
    
    llvm::SMDiagnostic err;
    runtimeModule = parseIRFile("runtime.ll", err, *context);
    
    irModule = new IRModule();
}

LLVMGenCtx::~LLVMGenCtx() {
    delete module;
    delete context;
    delete irModule;
}

llvm::Function *LLVMGenCtx::getRuntimeFunc(const std::string &name) {
    llvm::Function *func = runtimeModule->getFunction(name);
    //TODO
    return func;
}

LLVMStruct *LLVMGenCtx::getStruct(FPod *curPod, int16_t type) {
    
    IRType *irType = irModule->getType(curPod, type);
    if (irType->llvmStruct == NULL) {
        irType->llvmStruct = new LLVMStruct(this, irType, irType->ftype->c_mangledName);
    }
    return (LLVMStruct*)irType->llvmStruct;
    /*
    //FTypeRef &ref = curPod->typeRefs[type];
    std::string name = FCodeUtil::getTypeRefName(curPod, type, false);
    std::map<std::string, LLVMStruct*>::iterator itr  = structMap.find(name);
    if (itr != structMap.end()) {
        return itr->second;
    }
    
    FType *ftype = FCodeUtil::getFTypeFromTypeRef(curPod, type);
    LLVMStruct *sty = new LLVMStruct(this, ftype, name);
    structMap[name] = sty;
    
    sty->init();
    return sty;
     */
}

llvm::Type *LLVMGenCtx::toLlvmType(FPod *curPod, int16_t type) {
    FType *ftype = FCodeUtil::getFTypeFromTypeRef(curPod, type);
    std::string name = ftype->c_mangledName;
    if (name == "sys_Void") {
        return Type::getVoidTy(*context);
    }
    
    LLVMStruct *sty = getStruct(curPod, type);
    return sty->structTy;
}

int LLVMGenCtx::fieldIndex(FPod *curPod, FFieldRef *ref) {
    LLVMStruct *s = getStruct(curPod, ref->parent);
    
    std::string name = curPod->names[ref->name];
    return s->fieldIndex[name];
}
