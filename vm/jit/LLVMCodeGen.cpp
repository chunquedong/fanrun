//
//  LLVMCodeGen.cpp
//  vm
//
//  Created by yangjiandong on 16/9/16.
//  Copyright © 2017 chunquedong. All rights reserved.
//

#include "LLVMCodeGen.hpp"
#include "Env.h"

using namespace llvm;

LLVMCodeGen::LLVMCodeGen(llvm::LLVMContext &Context, Env *env, IRMethod *irMethod, std::string &name)
    : Context(Context), Builder(Context), env(env), irMethod(irMethod), name(name) {
        ptrType = Type::getInt8PtrTy(Context);
        pptrType = ptrType->getPointerTo();
        valueType = Type::getInt64Ty(Context);
        pvalueType = valueType->getPointerTo();
}

llvm::Function *LLVMCodeGen::gen(Module *M) {
    function =
        cast<Function>(M->getOrInsertFunction(name, Type::getVoidTy(Context),
                                          ptrType,
                                          nullptr));
    
    callee = cast<Function>(M->getOrInsertFunction("jit_callMethod", Type::getInt32Ty(Context),
                                                   ptrType, ptrType,
                                                   Type::getInt32Ty(Context), Type::getInt32Ty(Context),
                                                   nullptr));
    
    BasicBlock *BB = BasicBlock::Create(Context, "entry", function);
    Builder.SetInsertPoint(BB);

    Argument *ArgX = &*function->arg_begin();// Get the arg
    ArgX->setName("env");
    envValue = ArgX;
    
    int frameOffset = offsetof(Env, curFrame);
    Value *framePtr = Builder.CreateGEP(envValue, Builder.getInt32(frameOffset));
    Value *framePtr2 = Builder.CreateBitOrPointerCast(framePtr, pptrType);
    Value *frameValue = Builder.CreateLoad(framePtr2);
    localsPtr = Builder.CreateGEP(frameValue, Builder.getInt32(sizeof(StackFrame)));
    
        /*
    for (Var &var : irMethod->locals) {
        Value *v = Builder.CreateAlloca(Type::getInt32Ty(Context), nullptr, var.name);
        primLocals.push_back(v);
    }
    ArrayType *type = ArrayType::get(Type::getInt8PtrTy(Context), irMethod->refLocalsCount);
    refLocals = Builder.CreateAlloca(type, nullptr, "refLocals");
*/
    
    
    for (int i=0; i<irMethod->blocks.size(); ++i) {
        Block *b = irMethod->blocks[i];
        genBlock(b);
    }
    
    Builder.CreateRetVoid();
    return function;
}

void LLVMCodeGen::genBlock(Block *block) {
    //BasicBlock *parent = Builder.GetInsertBlock();
    BasicBlock *BB = BasicBlock::Create(Context, "", function);
    Builder.CreateBr(BB);
    
    Builder.SetInsertPoint(BB);
    
    for (Stmt *t : block->stmts) {
        genStmt(t);
    }
}

Value *LLVMCodeGen::ptrConst(void *ptr) {
    ConstantInt* CI = ConstantInt::get(Type::getInt64Ty(Context),
                                       uint64_t(ptr));
    Value *val = ConstantExpr::getIntToPtr(CI, ptrType);
    return val;
}

void LLVMCodeGen::genStmt(Stmt *stmt) {
    FPod *curPod = irMethod->curPod;
    StmtType type =  stmt->getType();
    switch (type) {
        case StmtType::store: {
            StoreStmt *s = dynamic_cast<StoreStmt*>(stmt);
            Value *val = genExpr(&s->src);
            
            int index = 0;
            if (s->dst.type == ExprType::localVar) {
                index = s->dst.varRef.index;
            } else if (s->dst.type == ExprType::tempVar) {
                Expr::VarRef &varRef = s->dst.varRef;
                index = irMethod->blocks[varRef.block]->locals[varRef.index].newIndex;
            }
            //fr_Value *locals = ((fr_Value*)(env->curFrame+1)) + index;
            Value *CI = Builder.CreateGEP(localsPtr, Builder.getInt32(sizeof(fr_Value) * index));
            Value *ptr = Builder.CreateBitOrPointerCast(CI, pvalueType);
            Value *v = Builder.CreateBitOrPointerCast(val, valueType);
            Builder.CreateStore(v, ptr);
        }
            
            break;
            
        case StmtType::field: {
            FieldStmt *s = dynamic_cast<FieldStmt*>(stmt);
        }
            
            break;
            
        case StmtType::call: {
            CallStmt *s = dynamic_cast<CallStmt*>(stmt);
            int paramCount;
            FMethod *method = env->podManager->getMethod(env, curPod, s->methodRefId, &paramCount);
            
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
        }
            
            break;
            
        case StmtType::cmp: {
            CmpStmt *s = dynamic_cast<CmpStmt*>(stmt);
        }
            
            break;
            
        case StmtType::ret: {
            RetStmt *s = dynamic_cast<RetStmt*>(stmt);
        }
            
            break;
            
        case StmtType::jmp: {
            JmpStmt *s = dynamic_cast<JmpStmt*>(stmt);
        }
            
            break;
            
        default:
            break;
    }
}

llvm::Value *LLVMCodeGen::genExpr(Expr *expr) {
    FPod *curPod = irMethod->curPod;
    llvm::Value *val = nullptr;
    switch (expr->type) {
        case ExprType::constant: {
            FOpObj &opObj = expr->opObj;
            switch (opObj.opcode) {
                case FOp::LoadNull: {
                    Type* Ty = Type::getInt8PtrTy(Context);
                    val = Constant::getNullValue(Ty);
                    break;
                }
                case FOp::LoadFalse: {
                    val = Builder.getFalse();
                    break;
                }
                case FOp::LoadTrue: {
                    val = Builder.getTrue();
                    break;
                }
                case FOp::LoadInt: {
                    fr_Int i = curPod->constantas.ints[opObj.i1];
                    val = Builder.getInt64(i);
                    break;
                }
                case FOp::LoadFloat: {
                    double i = curPod->constantas.reals[opObj.i1];
                    val = ConstantFP::get(Type::getDoubleTy(Context), i);
                    break;
                }
                case FOp::LoadDecimal: {
                    break;
                }
                case FOp::LoadStr: {
                    FObj * str = env->podManager->objFactory.getString(env, curPod, opObj.i1);
                    val = ptrConst(str);
                    break;
                }
                case FOp::LoadDuration: {
                    //TODO
                    break;
                }
                case FOp::LoadUri: {
                    //TODO
                    break;
                }
                case FOp::LoadType: {
                    break;
                }
                default: {
                    //compare null
                    val = Builder.getInt64(0);
                }
                    break;
            }
        }
            break;
        case ExprType::localVar: {
            int index = expr->varRef.index;
            Value *CI = Builder.CreateGEP(localsPtr, Builder.getInt32(sizeof(fr_Value) * index));
            Value *ppval = Builder.CreateBitOrPointerCast(CI, pvalueType);
            val = Builder.CreateLoad(ppval);
        }
            break;
        case ExprType::tempVar: {
            Expr::VarRef &varRef = expr->varRef;
            int index = irMethod->blocks[varRef.block]->locals[varRef.index].newIndex;
            Value *CI = Builder.CreateGEP(localsPtr, Builder.getInt32(sizeof(fr_Value) * index));
            Value *ppval = Builder.CreateBitOrPointerCast(CI, pvalueType);
            val = Builder.CreateLoad(ppval);
        }
            break;
        default:
            break;
    }
    return val;
}

