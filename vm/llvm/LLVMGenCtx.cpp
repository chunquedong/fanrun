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

using namespace llvm;

LLVMGenCtx::LLVMGenCtx(llvm::LLVMContext *context) : context(context) {
    ptrType = Type::getInt8PtrTy(*context);
    pptrType = ptrType->getPointerTo();
}

LLVMStruct *LLVMGenCtx::getStruct(FPod *curPod, int16_t type) {
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
}

LLVMStruct *LLVMGenCtx::getLLVMStruct(FType *ftype) {
    std::string name = ftype->c_name;
    std::map<std::string, LLVMStruct*>::iterator itr  = structMap.find(name);
    if (itr != structMap.end()) {
        return itr->second;
    }
    
    LLVMStruct *sty = new LLVMStruct(this, ftype, name);
    structMap[name] = sty;
    
    sty->init();
    return sty;
}

llvm::Type *LLVMGenCtx::toLlvmType(FPod *curPod, int16_t type) {
    FType *ftype = FCodeUtil::getFTypeFromTypeRef(curPod, type);
    std::string name = ftype->c_name;
    if (name == "sys_Void") {
        return Type::getVoidTy(*context);
    }
    
    LLVMStruct *sty = getLLVMStruct(ftype);
    return sty->structTy;
}

int LLVMGenCtx::fieldIndex(FPod *curPod, FFieldRef *ref) {
    FType *ftype = FCodeUtil::getFTypeFromTypeRef(curPod, ref->parent);
    LLVMStruct *s = getLLVMStruct(ftype);
    
    std::string name = curPod->names[ref->name];
    return s->fieldIndex[name];
}
