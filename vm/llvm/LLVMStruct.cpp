//
//  LLVMStruct.cpp
//  vm
//
//  Created by yangjiandong on 2019/8/3.
//  Copyright © 2019 yangjiandong. All rights reserved.
//

#include "LLVMStruct.hpp"
#include "LLVMGenCtx.hpp"

LLVMStruct::LLVMStruct(LLVMGenCtx *ctx, FType *ftype, std::string &name) : builder(*ctx->context),
    isVTableInited(false), isVTableGened(false) {
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
        //copy vtable
        vtableMethods = base->vtableMethods;
        virtaulCount = (int)vtableMethods.size();
    }
    
    for (int i =0; i<ftype->methods.size(); ++i) {
        FMethod &m = ftype->methods[i];
        if ((m.flags & FFlags::Virtual) || (m.flags & FFlags::Abstract) || (m.flags & FFlags::Override)) {
            std::string &name = fpod->names[m.name];
            std::map<std::string, VirtualMethod>::iterator itr = vtableMethods.find(name);
            if (itr != vtableMethods.end()) {
                itr->second.realMethod = nullptr;
            }
            else {
                VirtualMethod vm;
                vm.realMethod = nullptr;
                vm.offsetVTable = virtaulCount;
                ++virtaulCount;
                vtableMethods[name] = vm;
            }
        }
    }
}

void LLVMStruct::inheritMethod(LLVMStruct *base, bool isMixin) {
    for (std::map<std::string, VirtualMethod>::iterator itr = base->resolvedMethods.begin(); itr != base->resolvedMethods.end(); ++itr) {
        std::map<std::string, VirtualMethod>::iterator me = resolvedMethods.find(itr->first);
        if (me != resolvedMethods.end()) {
            if (me->second.realMethod == nullptr || (isMixin && me->second.fromObj && itr->second.realMethod != nullptr)) {
                me->second.realMethod = itr->second.realMethod;
                me->second.fromObj = itr->second.fromObj;
            }
        }
        else {
            resolvedMethods[itr->first] = itr->second;
        }
    }
}

void LLVMStruct::resolveMethod() {
    
    if (ftype->meta.base != 0xFFFF) {
        LLVMStruct *base = ctx->getStruct(fpod, ftype->meta.base);
        base->genVTableInit();
        inheritMethod(base, false);
    }
    
    for (int i=0; i<ftype->meta.mixinCount; ++i) {
        LLVMStruct *mixin = ctx->getStruct(fpod, ftype->meta.mixin[i]);
        mixin->genVTableInit();
        inheritMethod(mixin, true);
    }
    
    for (int i =0; i<ftype->methods.size(); ++i) {
        FMethod &m = ftype->methods[i];
        if ((m.flags & FFlags::Virtual) || (m.flags & FFlags::Abstract) || (m.flags & FFlags::Override)) {
            std::string &name = fpod->names[m.name];
            std::map<std::string, llvm::Function *>::iterator found = declMethods.find(name);
            if (found != declMethods.end()) {
                llvm::Function *func = found->second;
                VirtualMethod vm;
                vm.realMethod = func;
                vm.fromObj = ftype->c_name == "sys::Obj";
                vm.offsetVTable = -1;
                resolvedMethods[name] = vm;
            }
        }
    }
}

void LLVMStruct::genVTableAt(llvm::Value *vtablePos, std::map<std::string, VirtualMethod> &resolvedMethods) {
    for (std::map<std::string, VirtualMethod>::iterator itr = vtableMethods.begin(); itr != vtableMethods.end(); ++itr) {
        int offsetVTable = itr->second.offsetVTable;
        
        llvm::Function *func = nullptr;
        std::map<std::string, VirtualMethod>::iterator me = resolvedMethods.find(itr->first);
        if (me != resolvedMethods.end()) {
            func = me->second.realMethod;
        }
        
        llvm::Value *casted = builder.CreateBitCast(func, ctx->ptrType);
        llvm::Value *ptr = builder.CreateStructGEP(vtablePos, offsetVTable);
        builder.CreateStore(casted, ptr);
    }
}

void LLVMStruct::genVTableInit() {
    if (isVTableGened) return;
    isVTableGened = true;
    
    resolveMethod();
    
    //init class vtable
    int virtualTableHeader = 16;
    llvm::Value *pos = builder.CreateStructGEP(vtables[0], virtualTableHeader);
    genVTableAt(pos, resolvedMethods);
    
    //init interface vtable
    for (int i=0; i<ftype->meta.mixinCount; ++i) {
        LLVMStruct *base = ctx->getStruct(fpod, ftype->meta.mixin[i]);
        llvm::Value *pos = builder.CreateStructGEP(vtables[i+1], virtualTableHeader);
        base->genVTableAt(pos, resolvedMethods);
    }
}

void LLVMStruct::initVTable() {
    if (isVTableInited) return;
    isVTableInited = true;
    
    initVTableLayout();
    
    int virtualTableHeader = 16;
    int virtaulCount = virtualTableHeader + (int)vtableMethods.size();
    llvm::Type *arrayTy = llvm::ArrayType::get(ctx->ptrType, virtaulCount);
    
    llvm::GlobalVariable *vtable = new llvm::GlobalVariable(*ctx->module, arrayTy, false
                        , llvm::GlobalValue::ExternalLinkage, llvm::ConstantAggregateZero::get(arrayTy));
    vtables.push_back(vtable);
    
    //init interface vtable var
    for (int i=0; i<ftype->meta.mixinCount; ++i) {
        LLVMStruct *base = ctx->getStruct(fpod, ftype->meta.mixin[i]);
        base->initVTable();
        
        llvm::Type *arrayTy = llvm::ArrayType::get(ctx->ptrType, base->vtableMethods.size());
        llvm::GlobalVariable *vtable = new llvm::GlobalVariable(*ctx->module, arrayTy, false
                                    , llvm::GlobalValue::ExternalLinkage, llvm::ConstantAggregateZero::get(arrayTy));
        vtables.push_back(vtable);
    }
}
