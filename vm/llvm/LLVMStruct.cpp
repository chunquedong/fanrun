//
//  LLVMStruct.cpp
//  vm
//
//  Created by yangjiandong on 2019/8/3.
//  Copyright © 2019 yangjiandong. All rights reserved.
//

#include "LLVMStruct.hpp"
#include "LLVMGenCtx.hpp"

LLVMStruct::LLVMStruct(LLVMGenCtx *ctx, IRType *irType, std::string &name) : builder(*ctx->context) {
    this->structTy = llvm::StructType::create(*ctx->context, name);
    init();
}

void LLVMStruct::init() {
    std::vector<llvm::Type*> fieldTypes;
    fieldTypes.push_back(ctx->ptrType);
    FType *ftype = irType->ftype;
    for (int i=0; i<ftype->fields.size(); ++i) {
        FField &field = ftype->fields[i];
        llvm::Type *t = ctx->toLlvmType(ftype->c_pod, field.type);
        fieldTypes.push_back(t);
    }
    
    structTy->setBody(std::move(fieldTypes));
}

void LLVMStruct::genVTableAt(llvm::Value *vtablePos, IRVTable *irVTable) {
    for (int i=0; i<irVTable->functions.size(); ++i) {
        IRVirtualMethod &vm = irVTable->functions[i];
        
        LLVMStruct *parent = (LLVMStruct*)vm.parent->llvmStruct;
        std::string &name = parent->irType->fpod->names[vm.method->name];
        std::map<std::string, llvm::Function *>::iterator itr = parent->declMethods.find(name);
        llvm::Function *func = NULL;
        if (itr != parent->declMethods.end()) {
            func = itr->second;
        }
        else {
            printf("ERROR: not found method: %s\n", name.c_str());
        }
        llvm::Value *casted = builder.CreateBitCast(func, ctx->ptrType);
        llvm::Value *ptr = builder.CreateStructGEP(vtablePos, i);
        builder.CreateStore(casted, ptr);
    }
}

void LLVMStruct::genVTable() {
    int virtualTableHeader = 16;
    
    for (int i=0; i<irType->vtables.size(); ++i) {
        IRVTable *irVtable = irType->vtables[i];
        int virtaulCount = virtualTableHeader + (int)irVtable->functions.size();
        
        llvm::Type *arrayTy = llvm::ArrayType::get(ctx->ptrType, virtaulCount);
        
        llvm::GlobalVariable *vtable = new llvm::GlobalVariable(*ctx->module, arrayTy, false
                                                                , llvm::GlobalValue::ExternalLinkage, llvm::ConstantAggregateZero::get(arrayTy));
        
        llvm::Value *pos = builder.CreateStructGEP(vtable, virtualTableHeader);
        genVTableAt(pos, irVtable);
        
        vtables.push_back(vtable);
    }
}
