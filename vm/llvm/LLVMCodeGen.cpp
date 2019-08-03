//
//  LLVMCodeGen.cpp
//  vm
//
//  Created by yangjiandong on 16/9/16.
//  Copyright © 2017 chunquedong. All rights reserved.
//

#include "LLVMCodeGen.hpp"
#include "Env.h"
#include "FCodeUtil.hpp"

using namespace llvm;

LLVMGenCtx::LLVMGenCtx(llvm::LLVMContext *context) : context(context) {
    ptrType = Type::getInt8PtrTy(*context);
    pptrType = ptrType->getPointerTo();
    valueType = Type::getInt64Ty(*context);
    pvalueType = valueType->getPointerTo();
}

LLVMStruct *LLVMGenCtx::getLLVMStruct(FType *ftype) {
    std::string name = ftype->c_name;
    std::map<std::string, LLVMStruct*>::iterator itr  = structMap.find(name);
    if (itr != structMap.end()) {
        return itr->second;
    }
    
    LLVMStruct *sty = new LLVMStruct();
    sty->ftype = ftype;
    sty->structTy = llvm::StructType::create(*context, name);
    
    structMap[name] = sty;
    
    std::vector<llvm::Type*> fieldTypes;
    fieldTypes.push_back(ptrType);
    for (int i=0; i<ftype->fields.size(); ++i) {
        FField &field = ftype->fields[i];
        llvm::Type *t = toLlvmType(ftype->c_pod, field.type);
        fieldTypes.push_back(t);
    }
    
    sty->structTy->setBody(std::move(fieldTypes));
    
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

LLVMCodeGen::LLVMCodeGen(llvm::LLVMContext &Context, IRMethod *irMethod, std::string &name)
    : Context(Context), Builder(Context), irMethod(irMethod), name(name) {

    FCodeUtil::escapeIdentifierName(name);
}

llvm::Function* LLVMCodeGen::getFunctionProto(IRMethod *irMethod) {
    if (auto* function = module->getFunction(name)) return function;
    
    llvm::SmallVector<llvm::Type*, 16> paramTypes;
    for (int i=0; i < irMethod->method->paramCount; ++i) {
        FMethodVar &v = irMethod->method->vars[i];
        paramTypes.push_back(ctx->toLlvmType(irMethod->curPod, v.type));
    }
    llvm::Type *returnType = ctx->toLlvmType(irMethod->curPod, irMethod->returnType);
    
    auto* llvmFunctionType = llvm::FunctionType::get(returnType, paramTypes, false);
    auto* function = llvm::Function::Create(llvmFunctionType, llvm::Function::ExternalLinkage, name, module);
    
    return function;
}

llvm::Function *LLVMCodeGen::gen(Module *M) {
    module = M;
    function = getFunctionProto(irMethod);
    
    //BasicBlock *BB = BasicBlock::Create(Context, "entry", function);
    //Builder.SetInsertPoint(BB);

    Argument *argx = &*function->arg_begin();// Get the arg
    argx->setName("env");
    ++argx;
    for (int i=0; i < irMethod->method->paramCount; ++i) {
        FMethodVar &v = irMethod->method->vars[i];
        argx->setName(irMethod->curPod->names[v.name]);
        ++argx;
    }
    
    /*
    envValue = ArgX;
    
    int frameOffset = offsetof(Env, curFrame);
    Value *framePtr = Builder.CreateGEP(envValue, Builder.getInt32(frameOffset));
    Value *framePtr2 = Builder.CreateBitOrPointerCast(framePtr, pptrType);
    Value *frameValue = Builder.CreateLoad(framePtr2);
    localsPtr = Builder.CreateGEP(frameValue, Builder.getInt32(sizeof(StackFrame)));
    */
        /*
    for (Var &var : irMethod->locals) {
        Value *v = Builder.CreateAlloca(Type::getInt32Ty(Context), nullptr, var.name);
        primLocals.push_back(v);
    }
    ArrayType *type = ArrayType::get(Type::getInt8PtrTy(Context), irMethod->refLocalsCount);
    refLocals = Builder.CreateAlloca(type, nullptr, "refLocals");
*/
    
    //init for branch
    for (int i=0; i<irMethod->blocks.size(); ++i) {
        Block *b = irMethod->blocks[i];
        BasicBlock *BB = BasicBlock::Create(Context, "", function);
        b->llvmBlock = BB;
    }
    
    for (int i=0; i<irMethod->blocks.size(); ++i) {
        Block *b = irMethod->blocks[i];
        genBlock(b);
    }
    
    //Builder.CreateRetVoid();
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
/*
Value *LLVMCodeGen::ptrConst(void *ptr) {
    ConstantInt* CI = ConstantInt::get(Type::getInt64Ty(Context),
                                       uint64_t(ptr));
    Value *val = ConstantExpr::getIntToPtr(CI, ptrType);
    return val;
}
*/
void LLVMCodeGen::genStmt(Stmt *stmt) {
    FPod *curPod = irMethod->curPod;
    
    if (ConstStmt *s = dynamic_cast<ConstStmt*>(stmt)) {
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
    else if (StoreStmt *s = dynamic_cast<StoreStmt*>(stmt)) {
        //StoreStmt *s = dynamic_cast<StoreStmt*>(stmt);
        Value *src = genExpr(&s->src);
        Value *dst = genExpr(&s->dst);
        
        //fr_Value *locals = ((fr_Value*)(env->curFrame+1)) + index;
        //Value *CI = Builder.CreateGEP(localsPtr, Builder.getInt32(sizeof(fr_Value) * index));
        //Value *ptr = Builder.CreateBitOrPointerCast(CI, pvalueType);
        //Value *v = Builder.CreateBitOrPointerCast(val, valueType);
        Builder.CreateStore(src, dst);
    }
    else if (FieldStmt *s = dynamic_cast<FieldStmt*>(stmt)) {
        
        FFieldRef *fref = s->fieldRef;
        int index = ctx->fieldIndex(irMethod->curPod, fref);
        llvm::Type *t = ctx->toLlvmType(irMethod->curPod, fref->parent);
        llvm::Value *baseValue = genExpr(&s->instance);
        
        std::string memberName = curPod->names[fref->name];
        llvm::Value *pos = Builder.CreateStructGEP(t, baseValue, index, memberName);
        
        llvm::Value *value = genExpr(&s->value);
        if (s->isLoad) {
            Builder.CreateStore(pos, value);
        }
        else {
            Builder.CreateStore(value, pos);
        }
    }
    else if (CallStmt *s = dynamic_cast<CallStmt*>(stmt)) {
        //int paramCount;
        FMethod *method = env->podManager->getMethod(env, curPod, *s->methodRef);
        /*
        for (int i=0; i<s->params.size(); ++i) {
            Expr &expr = s->params[i];
            Value *val = genExpr(&expr);
            int index = irMethod->refLocalsCount + i;
            Value *CI = Builder.CreateGEP(localsPtr, Builder.getInt32(sizeof(fr_Value) * index));
            Value *ptr = Builder.CreateBitOrPointerCast(CI, pvalueType);
            Value *v = Builder.CreateBitOrPointerCast(val, valueType);
            Builder.CreateStore(v, ptr);
        }

        Builder.CreateCall(callee, {envValue, ptrConst(method)
            , Builder.getInt32(paramCount), Builder.getInt32(s->isVirtual)});
        
        if (!s->isVoid) {
            int index = 0;
            if (s->retValue.type == ExprType::localVar) {
                index = s->retValue.varRef.index;
            } else if (s->retValue.type == ExprType::tempVar) {
                Expr::VarRef &varRef = s->retValue.varRef;
                index = irMethod->blocks[varRef.block]->locals[varRef.index].newIndex;
            }

            Value *CI = Builder.CreateGEP(localsPtr, Builder.getInt32(sizeof(fr_Value) * index));
            Value *ptr = Builder.CreateBitOrPointerCast(CI, pvalueType);
            
            Value *vp = Builder.CreateGEP(localsPtr, Builder.getInt32(sizeof(fr_Value) * irMethod->refLocalsCount));
            Value *vvp = Builder.CreateBitOrPointerCast(vp, pvalueType);
            Value *v = Builder.CreateLoad(vvp);
            Builder.CreateStore(v, ptr);
        }
         */
    }
    else if (CmpStmt *s = dynamic_cast<CmpStmt*>(stmt)) {
    }
    else if (RetStmt *s = dynamic_cast<RetStmt*>(stmt)) {
        if (s->isVoid) {
            Builder.CreateRetVoid();
        }
        else {
            Builder.CreateRet(genExpr(&s->retValue));
        }
    }
    else if (JmpStmt *s = dynamic_cast<JmpStmt*>(stmt)) {
        llvm::Value *condition = NULL;
        if (s->trueJmp) {
            condition = genExpr(&s->expr);
            Builder.CreateCondBr(condition, (llvm::BasicBlock*)s->targetBlock->llvmBlock, NULL);
        }
        else if (s->falseJmp) {
            //condition = Builder.CreateNot(genExpr(&s->expr));
            condition = genExpr(&s->expr);
            Builder.CreateCondBr(condition, NULL, (llvm::BasicBlock*)s->targetBlock->llvmBlock);
        }
        else {
            Builder.CreateBr((llvm::BasicBlock*)s->targetBlock->llvmBlock);
            //return;
        }
        //Builder.CreateCondBr(condition, thenBlock, elseBlock);
    }
}

llvm::Value *LLVMCodeGen::genExpr(Expr *expr) {
    int pos = expr->block->locals[expr->index].newIndex;
    return locals[pos];
}

