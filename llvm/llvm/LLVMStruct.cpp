//
//  LLVMStruct.cpp
//  vm
//
//  Created by yangjiandong on 2019/8/3.
//  Copyright © 2019 yangjiandong. All rights reserved.
//

#include "LLVMStruct.hpp"
#include "LLVMGenCtx.hpp"
#include "LLVMCodeGen.hpp"
#include "MBuilder.hpp"

int LLVMStruct::virtualTableHeader = 16;

LLVMStruct::LLVMStruct(LLVMGenCtx *ctx, IRType *irType, std::string &name)
    : ctx(ctx), builder(*ctx->context), irType(irType) {
    this->structTy = llvm::StructType::create(*ctx->context, name);
    structPtr = structTy->getPointerTo();
    //structPtr = llvm::PointerType::getUnqual(structTy);
}

llvm::GlobalValue::LinkageTypes LLVMStruct::toLinkageType(uint32_t flags) {
    if (flags & FFlags::Private) {
        return llvm::GlobalValue::InternalLinkage;
    }
    else if (flags & FFlags::Internal) {
        return llvm::GlobalValue::InternalLinkage;
    }
    return llvm::GlobalValue::ExternalLinkage;
}

void LLVMStruct::init() {
    //init struct fileds
    std::vector<llvm::Type*> fieldTypes;
    //super class
    if (irType->ftype->meta.base != 0xFFFF && irType->ftype->c_mangledName == "sys_Obj") {
        LLVMStruct *base = ctx->getStruct(irType->fpod, irType->ftype->meta.base);
        fieldTypes.push_back(base->structTy);
    }
    
    FType *ftype = irType->ftype;
    for (int i=0; i<ftype->fields.size(); ++i) {
        FField &field = ftype->fields[i];
        const std::string &name = ftype->c_pod->names[field.name];
        llvm::Type *t = ctx->toLlvmType(ftype->c_pod, field.type);
        if (field.isStatic()) {
            llvm::GlobalVariable *sf = new llvm::GlobalVariable(*ctx->module, t, false
                                                                    , toLinkageType(field.flags), llvm::ConstantAggregateZero::get(t)
                                                                    , ftype->c_mangledName+"_"+name);
            staticFields[name] = sf;
            continue;
        }
        
        fieldTypes.push_back(t);
        fieldIndex[name] = (int)fieldTypes.size()-1;
    }
    
    if (ftype->meta.flags & FFlags::Mixin) {
        fieldTypes.clear();
        llvm::Type *obj = ctx->objPtrType(ftype->c_pod);
        fieldTypes.push_back(obj);
        //mixin vtable
        fieldTypes.push_back(ctx->ptrType);
    }
    
    structTy->setBody(std::move(fieldTypes));
    
    /////////////////////////////////////////////
    //init class var
    irType->initVTable();
    for (int i=0; i<irType->vtables.size(); ++i) {
        IRVTable *irVtable = irType->vtables[i];
        int virtaulCount = virtualTableHeader + (int)irVtable->functions.size();
        
        llvm::Type *arrayTy = llvm::ArrayType::get(ctx->ptrType, virtaulCount);
        
        llvm::GlobalVariable *classVar = new llvm::GlobalVariable(*ctx->module, arrayTy, false
                                                                  , llvm::GlobalValue::ExternalLinkage, llvm::ConstantAggregateZero::get(arrayTy)
                                                                  , irType->ftype->c_mangledName + "_class__");
        vtables.push_back(classVar);
    }

}

void LLVMStruct::genCode() {
    genClassInit();
    
    for (FMethod &method : irType->ftype->methods) {
        IRMethod ir(irType->fpod, &method);
        MBuilder mbuilder(method.code, ir);
        mbuilder.buildMethod(&method);
        
        LLVMCodeGen code(ctx, &ir, method.c_mangledName);
        code.gen(ctx->module);
        //this->declMethods[method.c_mangledName] = f;
    }
}

void LLVMStruct::genVTableAt(llvm::Value *vtable, int base, IRVTable *irVTable) {
    for (int i=0; i<irVTable->functions.size(); ++i) {
        IRVirtualMethod &vm = irVTable->functions[i];
        
        /*
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
         */
        bool isNative;
        llvm::Function *func = LLVMCodeGen::getFunctionProtoByDef(ctx, builder, vm.method, &isNative);
        llvm::Value *casted = builder.CreateBitCast(func, ctx->ptrType);
        llvm::Value *ptr = builder.CreateStructGEP(vtable, base+i);
        builder.CreateStore(casted, ptr);
    }
}

void LLVMStruct::genClassInit() {
    
    llvm::FunctionType *FT = llvm::FunctionType::get(llvm::Type::getVoidTy(*ctx->context), /*not vararg*/false);
    llvm::Function *F = llvm::Function::Create(FT, llvm::Function::ExternalLinkage, irType->ftype->c_mangledName+"_init__", ctx->module);
    llvm::BasicBlock *BB = llvm::BasicBlock::Create(*ctx->context, "EntryBlock", F);
    builder.SetInsertPoint(BB);
    
    //init vtable
    for (int i=0; i<irType->vtables.size(); ++i) {
        IRVTable *irVtable = irType->vtables[i];
        llvm::GlobalVariable *classVar = vtables[i];
        genVTableAt(classVar, virtualTableHeader, irVtable);
    }
    
    builder.CreateRetVoid();
}
