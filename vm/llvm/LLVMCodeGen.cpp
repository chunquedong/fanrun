//
//  LLVMCodeGen.cpp
//  vm
//
//  Created by yangjiandong on 16/9/16.
//  Copyright © 2017 chunquedong. All rights reserved.
//

#include "LLVMCodeGen.hpp"
//#include "Env.h"
#include "FCodeUtil.hpp"
#include "LLVMGenCtx.hpp"
#include "LLVMStruct.hpp"

using namespace llvm;

LLVMCodeGen::LLVMCodeGen(llvm::LLVMContext &Context, IRMethod *irMethod, std::string &name)
    : Context(Context), Builder(Context), irMethod(irMethod), name(name) {

    FCodeUtil::escapeIdentifierName(name);
}

llvm::Function* LLVMCodeGen::getFunctionProto(IRMethod *irMethod) {
    if (auto* function = module->getFunction(name)) return function;
    
    llvm::SmallVector<llvm::Type*, 16> paramTypes;
    if (!irMethod->method->isStatic()) {
        paramTypes.push_back(ctx->toLlvmType(irMethod->curPod, irMethod->method->c_parent->meta.self));
    }
    
    for (int i=0; i < irMethod->method->paramCount; ++i) {
        FMethodVar &v = irMethod->method->vars[i];
        paramTypes.push_back(ctx->toLlvmType(irMethod->curPod, v.type));
    }
    llvm::Type *returnType = ctx->toLlvmType(irMethod->curPod, irMethod->returnType);
    
    auto* llvmFunctionType = llvm::FunctionType::get(returnType, paramTypes, false);
    auto* function = llvm::Function::Create(llvmFunctionType, llvm::Function::ExternalLinkage, name, module);
    
    return function;
}

llvm::Function* LLVMCodeGen::getFunctionProtoByRef(FPod *curPod, FMethodRef *ref, bool isStatic) {
    std::string name = curPod->names[ref->name];
    if (auto* function = module->getFunction(name)) return function;
    
    llvm::SmallVector<llvm::Type*, 16> paramTypes;
    if (!isStatic) {
        paramTypes.push_back(ctx->toLlvmType(curPod, ref->parent));
    }
    for (int i=0; i < ref->paramCount; ++i) {
        uint16_t tf = ref->params[i];
        paramTypes.push_back(ctx->toLlvmType(curPod, tf));
    }
    llvm::Type *returnType = ctx->toLlvmType(curPod, ref->retType);
    
    auto* llvmFunctionType = llvm::FunctionType::get(returnType, paramTypes, false);
    auto* function = llvm::Function::Create(llvmFunctionType, llvm::Function::ExternalLinkage, name, module);
    
    return function;
}

llvm::Function *LLVMCodeGen::gen(Module *M) {
    module = M;
    function = getFunctionProto(irMethod);
    
    //set args name
    Argument *argx = &*function->arg_begin();// Get the arg
    argx->setName("env");
    ++argx;
    for (int i=0; i < irMethod->method->paramCount; ++i) {
        FMethodVar &v = irMethod->method->vars[i];
        argx->setName(irMethod->curPod->names[v.name]);
        ++argx;
    }
    
    //init for branch
    for (int i=0; i<irMethod->blocks.size(); ++i) {
        Block *b = irMethod->blocks[i];
        BasicBlock *BB = BasicBlock::Create(Context, "", function);
        b->llvmBlock = BB;
        
        for (int i=0; i<b->locals.size(); ++i) {
            llvm::Value *var = Builder.CreateAlloca(ctx->ptrType);
            locals.push_back(var);
        }
    }
    
    for (int i=0; i<irMethod->blocks.size(); ++i) {
        Block *b = irMethod->blocks[i];
        genBlock(b);
    }
    
    return function;
}

void LLVMCodeGen::genBlock(Block *block) {
    //BasicBlock *parent = Builder.GetInsertBlock();
    BasicBlock *BB = (BasicBlock*)block->llvmBlock;
    Builder.CreateBr(BB);
    
    Builder.SetInsertPoint(BB);
    
    for (Stmt *t : block->stmts) {
        genStmt(t);
    }
}

void LLVMCodeGen::genCall(CallStmt *s) {
    llvm::Function *callee = getFunctionProtoByRef(irMethod->curPod, s->methodRef, s->isStatic);
    
    if (s->isVirtual || s->isMixin) {
        llvm::Value *vtable = NULL;
        LLVMStruct *clz = ctx->getStruct(irMethod->curPod, s->methodRef->parent);
        
        llvm::Value *instance = genExpr(&s->params.at(0));
        llvm::Value *vtablePtr = Builder.CreateBitCast(instance, clz->structPtr);
        vtable = Builder.CreateLoad(vtablePtr);
    
        std::map<std::string, IRVirtualMethod>::iterator it = clz->irType->resolvedMethods.find(s->mthName);
        if (it == clz->irType->resolvedMethods.end()) {
            printf("ERROR: not found method:%s\n", s->mthName.c_str());
            return;
        }
        llvm::Value *mth = Builder.CreateStructGEP(vtable, it->second.offsetVTable);
        callee = (llvm::Function*)Builder.CreateBitCast(mth, callee->getType());
    }
    
    llvm::SmallVector<llvm::Value*, 16> args;
    for (int i=0; i<s->params.size(); ++i) {
        Expr &expr = s->params[i];
        Value *val = genExpr(&expr);
        args.push_back(val);
    }
    
    Builder.CreateCall(callee, args);
}

void LLVMCodeGen::genCompare(CompareStmt *stmt) {
    
}

void LLVMCodeGen::getConst(ConstStmt *s) {
    FPod *curPod = irMethod->curPod;
    llvm::Value *v = NULL;
    switch (s->opObj.opcode) {
        case FOp::LoadNull: {
            llvm::PointerType *t = Type::getInt8PtrTy(*ctx->context);
            v = llvm::ConstantPointerNull::get(t);
            break;
        }
        case FOp::LoadFalse: {
            v = llvm::ConstantInt::getFalse(*ctx->context);
            break;
        }
        case FOp::LoadTrue: {
            v = llvm::ConstantInt::getTrue(*ctx->context);
            break;
        }
        case FOp::LoadInt: {
            llvm::Type *t = llvm::Type::getInt64Ty(*ctx->context);
            v = llvm::ConstantInt::get(t, curPod->constantas.ints[s->opObj.i1]);
            break;
        }
        case FOp::LoadFloat: {
            llvm::Type *t = llvm::Type::getDoubleTy(*ctx->context);
            v = llvm::ConstantFP::get(t, curPod->constantas.reals[s->opObj.i1]);
            break;
        }
        case FOp::LoadDecimal: {
            //res.name = "Decimal";
            break;
        }
        case FOp::LoadStr: {
            //res.name = "Str";
            const std::string &str = curPod->constantas.strings[s->opObj.i1];
            llvm::Value *cstring = Builder.CreateGlobalStringPtr(str.c_str());
            llvm::Type *t = llvm::Type::getInt32Ty(*ctx->context);
            llvm::Value *size = llvm::ConstantInt::get(t, str.size());
            
            //TODO
            break;
        }
        case FOp::LoadDuration: {
            //res.name = "Duration";
            break;
        }
        case FOp::LoadUri: {
            //res.name = "Uri";
            break;
        }
        case FOp::LoadType: {
            //res.name = "Type";
            break;
        }
        default: {
            //res.name = "Obj";
            break;
        }
    }
    int pos = s->dst.block->locals[s->dst.index].newIndex;
    locals[pos] = v;
}

void LLVMCodeGen::genStmt(Stmt *stmt) {
    FPod *curPod = irMethod->curPod;
    
    StmtType stmtType = stmt->stmtType();
    switch (stmtType) {
        case StmtType::Const:
            if (ConstStmt *s = dynamic_cast<ConstStmt*>(stmt)) {
                getConst(s);
            }
            break;
        case StmtType::Store:
            if (StoreStmt *s = dynamic_cast<StoreStmt*>(stmt)) {
                //StoreStmt *s = dynamic_cast<StoreStmt*>(stmt);
                Value *src = genExpr(&s->src);
                Value *dst = genExpr(&s->dst);
                
                Builder.CreateStore(src, dst);
            }
        break;
        case StmtType::Field:
            if (FieldStmt *s = dynamic_cast<FieldStmt*>(stmt)) {
                
                FFieldRef *fref = s->fieldRef;
                int index = ctx->fieldIndex(irMethod->curPod, fref);
                llvm::Type *t = ctx->toLlvmType(irMethod->curPod, fref->parent);
                llvm::Value *baseValue = genExpr(&s->instance);
                
                std::string memberName = curPod->names[fref->name];
                llvm::Value *pos = Builder.CreateStructGEP(t, baseValue, index, memberName);
                
                llvm::Value *value = genExpr(&s->value);
                if (s->isLoad) {
                    llvm::Value *new_value = Builder.CreateLoad(pos);
                    Builder.CreateStore(new_value, value);
                }
                else {
                    Builder.CreateStore(value, pos);
                }
            }
            break;
        case StmtType::Call:
            if (CallStmt *s = dynamic_cast<CallStmt*>(stmt)) {
                genCall(s);
            }
            break;
        case StmtType::Compare:
            if (CompareStmt *s = dynamic_cast<CompareStmt*>(stmt)) {
            genCompare(s);
        }
            break;
        case StmtType::Return:
            if (ReturnStmt *s = dynamic_cast<ReturnStmt*>(stmt)) {
                if (s->isVoid) {
                    Builder.CreateRetVoid();
                }
                else {
                    Builder.CreateRet(genExpr(&s->retValue));
                }
            }
            break;
        case StmtType::Jump:
            if (JumpStmt *s = dynamic_cast<JumpStmt*>(stmt)) {
                if (s->jmpType == JumpStmt::trueJmp) {
                    llvm::Value *condition = genExpr(&s->expr);
                    Builder.CreateCondBr(condition, (llvm::BasicBlock*)s->targetBlock->llvmBlock, NULL);
                }
                else if (s->jmpType == JumpStmt::falseJmp) {
                    //condition = Builder.CreateNot(genExpr(&s->expr));
                    llvm::Value *condition = genExpr(&s->expr);
                    Builder.CreateCondBr(condition, NULL, (llvm::BasicBlock*)s->targetBlock->llvmBlock);
                }
                else {
                    Builder.CreateBr((llvm::BasicBlock*)s->targetBlock->llvmBlock);
                    //return;
                }
            }
            break;
        case StmtType::Alloc:
            if (AllocStmt *s = dynamic_cast<AllocStmt*>(stmt)) {
                
            }
            break;
        case StmtType::Throw:
            if (ThrowStmt *s = dynamic_cast<ThrowStmt*>(stmt)) {
                
            }
            break;
        case StmtType::Exception:
            if (ExceptionStmt *s = dynamic_cast<ExceptionStmt*>(stmt)) {
            
            }
            break;
        case StmtType::Coerce:
            if (CoerceStmt *s = dynamic_cast<CoerceStmt*>(stmt)) {
                
            }
            break;
        case StmtType::TypeCheck:
            if (TypeCheckStmt *s = dynamic_cast<TypeCheckStmt*>(stmt)) {
                
            }
    }
}

llvm::Value *LLVMCodeGen::genExpr(Expr *expr) {
    int pos = expr->block->locals[expr->index].newIndex;
    return locals[pos];
}

