//
//  LLVMStruct.cpp
//  vm
//
//  Created by yangjiandong on 2019/8/3.
//  Copyright © 2019 yangjiandong. All rights reserved.
//

#include "LLVMStruct.hpp"
#include "LLVMGenCtx.hpp"

LLVMStruct::LLVMStruct(LLVMGenCtx *ctx, FType *ftype, std::string &name) : builder(*ctx->context) {
    this->ftype = ftype;
    this->structTy = llvm::StructType::create(*ctx->context, name);
}

void LLVMStruct::init() {
    std::vector<llvm::Type*> fieldTypes;
    fieldTypes.push_back(ctx->ptrType);
    for (int i=0; i<ftype->fields.size(); ++i) {
        FField &field = ftype->fields[i];
        llvm::Type *t = ctx->toLlvmType(ftype->c_pod, field.type);
        fieldTypes.push_back(t);
    }
    
    structTy->setBody(std::move(fieldTypes));
}

void LLVMStruct::initVTableLayout() {
    int virtaulCount = 0;
    if (ftype->meta.base != 0xFFFF) {
        LLVMStruct *base = ctx->getStruct(fpod, ftype->meta.base);
        base->initVTable();
        virtaulCount += base->classVtableSize;
        //copy vtable
        methodMap = base->methodMap;
    }
    
    for (int i =0; i<ftype->methods.size(); ++i) {
        FMethod &m = ftype->methods[i];
        if ((m.flags & FFlags::Virtual) || (m.flags & FFlags::Abstract) || (m.flags & FFlags::Override)) {
            std::string &name = fpod->names[m.name];
            std::map<std::string, VirtualMethod>::iterator itr = methodMap.find(name);
            if (itr != methodMap.end()) {
                itr->second.realMethod = nullptr;
            }
            else {
                VirtualMethod vm;
                vm.realMethod = nullptr;
                vm.offsetVTable = virtaulCount;
                ++virtaulCount;
                methodMap[name] = vm;
            }
        }
    }
    classVtableSize = virtaulCount;
}

void LLVMStruct::overrideMethod(llvm::Value *vtablePos, std::string &name, llvm::Function *func) {
    std::map<std::string, VirtualMethod>::iterator itr = methodMap.find(name);
    if (itr == methodMap.end()) return;
    
    //llvm::Function *func = itr->second.realMethod;
    llvm::Value *casted = builder.CreateBitCast(func, ctx->ptrType);
    
    llvm::Value *ptr = builder.CreateStructGEP(vtablePos, itr->second.offsetVTable);
    builder.CreateStore(casted, ptr);
}

void LLVMStruct::initVTableAt(llvm::Value *vtablePos) {
    for (int i =0; i<ftype->methods.size(); ++i) {
        FMethod &m = ftype->methods[i];
        if ((m.flags & FFlags::Virtual) || (m.flags & FFlags::Abstract)) {
            std::string &name = fpod->names[m.name];
            VirtualMethod &vm = methodMap[name];
            llvm::Function *func = vm.realMethod;
            llvm::Value *casted = builder.CreateBitCast(func, ctx->ptrType);
            
            llvm::Value *ptr = builder.CreateStructGEP(vtablePos, vm.offsetVTable);
            builder.CreateStore(casted, ptr);
        }
    }
}

void LLVMStruct::initVTable() {
    initVTableLayout();
    int virtualTableHeader = 16;
    int virtaulCount = virtualTableHeader + classVtableSize;
    llvm::Type *arrayTy = llvm::ArrayType::get(ctx->ptrType, virtaulCount);
    
    llvm::GlobalVariable *vtable = new llvm::GlobalVariable(*ctx->module, arrayTy, false
                        , llvm::GlobalValue::ExternalLinkage, llvm::ConstantAggregateZero::get(arrayTy));
    vtables.push_back(vtable);
    
    llvm::Value *pos = builder.CreateStructGEP(vtable, virtualTableHeader);
    
    //init supert class vtable
    if (ftype->meta.base != 0xFFFF) {
        LLVMStruct *base = ctx->getStruct(fpod, ftype->meta.base);
        base->initVTableAt(pos);
    }
    
    //init self class vtable
    initVTableAt(pos);
    
    
    //init interface vtable
    for (int i=0; i<ftype->meta.mixinCount; ++i) {
        LLVMStruct *base = ctx->getStruct(fpod, ftype->meta.mixin[i]);
        
        llvm::Type *arrayTy = llvm::ArrayType::get(ctx->ptrType, base->classVtableSize);
        llvm::GlobalVariable *vtable = new llvm::GlobalVariable(*ctx->module, arrayTy, false
                                        , llvm::GlobalValue::ExternalLinkage, llvm::ConstantAggregateZero::get(arrayTy));
        vtables.push_back(vtable);
        
        //int itableOffset = 0;
        //llvm::Value *ipos = builder.CreateStructGEP(vtable, virtualTableHeader+itableOffset);
        
        //override interface method
        for (int i =0; i<ftype->methods.size(); ++i) {
            FMethod &m = ftype->methods[i];
            if ((m.flags & FFlags::Override)) {
                std::string &name = fpod->names[m.name];
                VirtualMethod &vm = methodMap[name];
                llvm::Function *func = vm.realMethod;
                base->overrideMethod(vtable, name, func);
            }
        }
    }
}
