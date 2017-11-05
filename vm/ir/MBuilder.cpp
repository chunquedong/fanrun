//
//  MBuilder.cpp
//  gen
//
//  Created by yangjiandong on 2017/11/5.
//  Copyright © 2017年 yangjiandong. All rights reserved.
//

#include "MBuilder.hpp"
#include "FCodeUtil.hpp"

MBuilder::MBuilder(Code &code, IRMethod &irMethod) :
        curPod(irMethod.curPod), code(code)
        , irMethod(irMethod) {
}

void MBuilder::rewriteLocals() {
    allLocalsCount = 0;
    
    for (int i=0; i<locals.size(); ++i) {
        Var &var = locals[i];
        //bool isRef = var.isRef;
        var.newIndex = allLocalsCount;
        ++allLocalsCount;
        if (var.typeName.size() == 0 && var.typeRef != 0) {
            var.typeName = FCodeUtil::getTypeRefName(curPod, var.typeRef, true);
        }
        
        if (i >= irMethod.paramCount) {
            var.name = var.name + "_" + std::to_string(var.index);
        }
        FCodeUtil::escapeIdentifierName(var.name);
    }
    
    for (auto *b : blocks) {
        for (Var &var : b->locals) {
            var.newIndex = allLocalsCount;
            ++allLocalsCount;
            if (var.typeName.size() == 0 && var.typeRef != 0) {
                var.typeName = FCodeUtil::getTypeRefName(curPod, var.typeRef, true);
            }
            var.name = "_t_" + std::to_string(var.block) +"_"+ std::to_string(var.index);
        }
    }
}

bool MBuilder::build(FMethod *method) {
    for (FAttr *itr : method->attrs) {
        FErrTable *et = dynamic_cast<FErrTable*>(itr);
        if (et != nullptr) {
            this->attrs.push_back(et);
        }
    }
    
    code.initOps();
    
    irMethod.paramCount = method->paramCount;
    bool isStatic = (method->flags & FFlags::Static) != 0;
    if (!isStatic) {
        Var &var = newVar(irMethod.selfType);
        //var.typeRef = method->c_parent->meta.self;
        var.name = "__self";
        irMethod.paramCount++;
    }
    
    for(int i=0; i<method->vars.size(); ++i) {
        FMethodVar *fvar = &method->vars[i];
        Var &var = newVar(fvar->type);
        var.methodVar = fvar;
        //var.typeRef = fvar->type;
        var.name = curPod->names[fvar->name];
    }
    
    initJumpTarget();
    initBlock();
    linkBlock();
    
    for (auto *b : blocks) {
        parseBlock(b, nullptr);
    }
    
    insertException();
    rewriteLocals();
    
    irMethod.locals.swap(this->locals);
    irMethod.blocks.swap(this->blocks);
    return true;
}

CoerceStmt::CType MBuilder::typeCoerce(uint16_t from, uint16_t to) {
    FTypeRef &typeRef1 = curPod->typeRefs[from];
    FTypeRef &typeRef2 = curPod->typeRefs[to];
    
    //TODO: type fif
    
    bool isVal1, isVal2, isNullable1, isNullable2;
    FCodeUtil::getTypeInfo(curPod, typeRef1, isVal1, isNullable1);
    FCodeUtil::getTypeInfo(curPod, typeRef2, isVal2, isNullable2);
    
    if ((isVal1 && !isNullable1) && (!isVal2 || isNullable2)) {
        return CoerceStmt::boxing;
    }
    if ((!isVal1 || isNullable1 )&& (isVal2 & !isNullable2)) {
        return CoerceStmt::unboxing;
    }
    
    return CoerceStmt::cast;
}

void MBuilder::initJumpTarget() {
    std::unordered_map<int16_t, FOpObj*> posToOp;
    for (int i=0; i<code.ops.size(); ++i) {
        FOpObj *opObj = &code.ops[i];
        posToOp[opObj->pos] = opObj;
        opObj->blockBegin = false;
    }
    
    for (int i=0; i<code.ops.size(); ++i) {
        FOpObj &opObj = code.ops[i];
        if (i == 0) {
            opObj.blockBegin = true;
            continue;
        }
        switch (opObj.opcode) {
            case FOp::Jump:
            case FOp::JumpTrue:
            case FOp::JumpFalse:
            case FOp::Leave:
            case FOp::JumpFinally: {
                int16_t pos = opObj.i1;
                FOpObj *op = posToOp[pos];
                if (op) {
                    op->blockBegin = true;
                }
                if (i+1 < code.ops.size()) {
                    FOpObj *next = &code.ops[i+1];
                    next->blockBegin = true;
                }
                
                break;
            }
            default:
                break;
        }
    }
    
    //find block in error table
    for (FErrTable *et : attrs) {
        for (FTrap &trap : et->traps) {
            FOpObj *opObj = posToOp[trap.start];
            opObj->blockBegin = true;
            FOpObj *eObj = posToOp[trap.end];
            eObj->blockBegin = true;
            FOpObj *op = posToOp[trap.handler];
            op->blockBegin = true;
        }
    }
}

void MBuilder::linkBlock() {
    //std::unordered_map<int16_t, Block*> posToBlock;
    for (auto *b : blocks) {
        posToBlock[b->pos] = b;
    }
    
    for (int i=0; i<blocks.size(); ++i) {
        Block *b = blocks[i];
        FOpObj &lastOp = code.ops[b->endOp-1];
        switch (lastOp.opcode) {
            case FOp::JumpTrue:
            case FOp::JumpFalse: {
                if (i+1 < blocks.size()) {
                    Block *next = blocks[i+1];
                    b->branchs.push_back(next);
                    next->incoming.push_back(b);
                }
                Block *target = posToBlock[lastOp.i1];
                b->branchs.push_back(target);
                target->incoming.push_back(b);
            }
                break;
            case FOp::Jump:
            case FOp::Leave:{
                Block *target = posToBlock[lastOp.i1];
                b->branchs.push_back(target);
                target->incoming.push_back(b);
            }
                break;
            case FOp::JumpFinally: {
                Block *target = posToBlock[lastOp.i1];
                b->branchs.push_back(target);
                target->incoming.push_back(b);
            }
                break;
            case FOp::Return:
            case FOp::Throw:
                break;
            default: {
                if (i+1 < blocks.size()) {
                    Block *next = blocks[i+1];
                    b->branchs.push_back(next);
                    next->incoming.push_back(b);
                    b->isForward = true;
                }
            }
                break;
        }
    }
}

void MBuilder::insertException() {
    uint16_t start = -1;
    uint16_t end = -1;
    
    ExceptionStmt *tryStart = nullptr;
    ExceptionStmt *tryEnd = nullptr;
    
    for (FErrTable *et : attrs) {
        for (FTrap &trap : et->traps) {
            if (trap.start != start || trap.end != end) {
                tryStart = new ExceptionStmt();
                tryStart->etype = ExceptionStmt::TryStart;
                
                Block *b = posToBlock[trap.start];
                b->stmts.insert(b->stmts.begin(), tryStart);
                
                start = trap.start;
                end = trap.end;
                
                tryEnd = new ExceptionStmt();
                tryEnd->etype = ExceptionStmt::TryEnd;
                tryEnd->catchType = trap.type;
                tryEnd->handler = trap.handler;
                Block *eb = posToBlock[trap.end];
                eb->stmts.push_back(tryEnd);
            }
            
            Block *cb = posToBlock[trap.handler];
            for (Stmt *s : cb->stmts) {
                ExceptionStmt *catchStart = dynamic_cast<ExceptionStmt*>(s);
                if (!catchStart) continue;
                if (catchStart->pos == trap.handler) {
                    tryEnd->catchs.push_back(catchStart);
                    break;
                }
            }
        }
    }
}

void MBuilder::initBlock() {
    for (int i=0; i<code.ops.size(); ++i) {
        FOpObj &opObj = code.ops[i];
        if (opObj.blockBegin) {
            Block *b = new Block();
            b->index = (int)blocks.size();
            b->pos = opObj.pos;
            b->beginOp = i;
            b->isVisited = false;
            
            if (blocks.size() > 0) {
                Block *block = blocks.back();
                block->endOp = i;
            }
            
            blocks.push_back(b);
        }
    }
    
    if (blocks.size() > 0) {
        Block *block = blocks.back();
        block->endOp = code.ops.size();
    }
}

void MBuilder::call(Block *block, FOpObj &opObj, bool isVirtual, bool isStatic, bool isMixin) {
    CallStmt *stmt = new CallStmt();
    stmt->isStatic = isStatic;
    stmt->isVirtual = isVirtual;
    stmt->isMixin = isMixin;
    stmt->curPod = curPod;
    stmt->methodRefId = opObj.i1;
    stmt->methodRef = &curPod->methodRefs[opObj.i1];
    
    for (int i=0; i<stmt->methodRef->paramCount; ++i) {
        stmt->params.insert(stmt->params.begin(), block->pop());
    }
    
    if (!isStatic) {
        Expr expr = block->pop();
        stmt->params.insert(stmt->params.begin(), expr);
    }
    
    bool isVoid = FCodeUtil::isVoidTypeRef(curPod, stmt->methodRef->retType);
    stmt->isVoid = isVoid;
    if (!isVoid) {
        Var &var = block->newVar(stmt->methodRef->retType);
        //var.typeRef = stmt->methodRef->retType;
        stmt->retValue.type = ExprType::tempVar;
        stmt->retValue.varRef.index = var.index;
        stmt->retValue.varRef.block = var.block;
        block->push(stmt->retValue);
    }
    block->stmts.push_back(stmt);
}

void MBuilder::parseBlock(Block *block, Block *previous) {
    
    if (previous != nullptr && previous->stack.size() > 0) {
        if (block->incoming.size() > 1) {
            /*分支合并的时候如果操作数栈中还有值，
             那么我们需要把里面的临时变量赋给下一块的变量，这样就能将不同路径的值合并。
             这相当于变换SSA中的PHI结点的过程
             */
            for (int i=0; i<previous->stack.size(); ++i) {
                Expr &expr = previous->stack[i];
                Var newVar;
                if (block->isVisited) {
                    if (i < block->locals.size()) {
                        newVar = block->locals[i];
                    }
                } else {
                    Var &tVar = block->newVar(0);
                    if (expr.type == ExprType::constant) {
                        tVar.typeName = expr.getConstantType();
                    } else if (expr.type == ExprType::localVar) {
                        Var &pvar = this->locals[expr.varRef.index];
                        tVar.typeRef = pvar.typeRef;
                        tVar.typeName = pvar.typeName;
                    } else if (expr.type == ExprType::tempVar) {
                        Block *pblock = this->blocks[expr.varRef.block];
                        Var &pvar = pblock->locals[expr.varRef.index];
                        tVar.typeRef = pvar.typeRef;
                        tVar.typeName = pvar.typeName;
                    } else {
                        throw "err";
                    }
                    
                    //tVar.isExport = true;
                    newVar = tVar;
                    
                    Expr newExpr;
                    newExpr.type = ExprType::tempVar;
                    newExpr.varRef.index = newVar.index;
                    newExpr.varRef.block = newVar.block;
                    block->push(newExpr);
                }
                
                StoreStmt *stmt = new StoreStmt();
                stmt->src = expr;
                stmt->dst.type = ExprType::tempVar;
                stmt->dst.varRef.index = newVar.index;
                stmt->dst.varRef.block = newVar.block;
                
                if (previous->stmts.size() == 0 || previous->isForward) {
                    previous->stmts.push_back(stmt);
                } else {
                    auto insertPoint = previous->stmts.begin()
                    + previous->stmts.size()-1;
                    previous->stmts.insert(insertPoint, stmt);
                }
            }
        } else if (!block->isVisited) {
            block->stack = (previous->stack);
        }
    }
    
    if (block->isVisited) {
        return;
    }
    block->isVisited = true;
    
    for (int i=block->beginOp; i<block->endOp; ++i) {
        FOpObj &opObj = code.ops[i];
        switch (opObj.opcode)
        {
            case FOp::Nop:
                break;
            case FOp::LoadNull:
            case FOp::LoadFalse:
            case FOp::LoadTrue:
            case FOp::LoadInt:
            case FOp::LoadFloat: {
                Expr tvar;
                tvar.opObj = opObj;
                tvar.type = ExprType::constant;
                block->push(tvar);
                break;
            }
            case FOp::LoadDecimal:
            case FOp::LoadStr:
            case FOp::LoadDuration:
            case FOp::LoadUri:
            case FOp::LoadType:
            {
                Expr tvar;
                tvar.opObj = opObj;
                tvar.type = ExprType::constant;
                //block->push(tvar);
                StoreStmt *stmt = new StoreStmt();
                
                Var &var = block->newVar(0);
                var.typeName = tvar.getConstantType();
                //var.typeRef = opObj.i1;
                stmt->src = tvar;
                stmt->dst.type = ExprType::tempVar;
                stmt->dst.varRef.index = var.index;
                stmt->dst.varRef.block = var.block;
                block->push(stmt->dst);
                
                block->stmts.push_back(stmt);
                break;
            }
            case FOp::LoadVar: {
                Expr var;
                var.opObj = opObj;
                var.type = ExprType::localVar;
                var.varRef.index = opObj.i1;
                var.varRef.block = -1;
                block->push(var);
                break;
            }
            case FOp::StoreVar: {
                StoreStmt *stmt = new StoreStmt();
                stmt->src = block->pop();
                stmt->dst.type = ExprType::localVar;
                stmt->dst.varRef.index = opObj.i1;
                stmt->dst.varRef.block = -1;
                block->stmts.push_back(stmt);
                break;
            }
            case FOp::LoadInstance: {
                FieldStmt *stmt = new FieldStmt();
                stmt->curPod = curPod;
                stmt->isLoad = true;
                stmt->isStatic = false;
                stmt->instance = block->pop();
                stmt->fieldRef = &curPod->fieldRefs[opObj.i1];
                
                Var &var = block->newVar(stmt->fieldRef->type);
                //var.typeRef = stmt->fieldRef->type;
                stmt->value.type = ExprType::tempVar;
                stmt->value.varRef.index = var.index;
                stmt->value.varRef.block = var.block;
                block->push(stmt->value);
                
                block->stmts.push_back(stmt);
                break;
            }
            case FOp::StoreInstance: {
                Expr var = block->pop();
                FieldStmt *stmt = new FieldStmt();
                stmt->curPod = curPod;
                stmt->isLoad = false;
                stmt->isStatic = false;
                stmt->instance = block->pop();
                stmt->fieldRef = &curPod->fieldRefs[opObj.i1];
                
                stmt->value = var;
                block->push(stmt->value);
                
                block->stmts.push_back(stmt);
                break;
            }
            case FOp::LoadStatic:
            case FOp::LoadMixinStatic: {
                FieldStmt *stmt = new FieldStmt();
                stmt->curPod = curPod;
                stmt->isLoad = true;
                stmt->isStatic = true;
                stmt->fieldRef = &curPod->fieldRefs[opObj.i1];
                
                Var &var = block->newVar(stmt->fieldRef->type);
                //var.typeRef = stmt->fieldRef->type;
                stmt->value.type = ExprType::tempVar;
                stmt->value.varRef.index = var.index;
                stmt->value.varRef.block = var.block;
                block->push(stmt->value);
                
                block->stmts.push_back(stmt);
                break;
            }
            case FOp::StoreStatic:
            case FOp::StoreMixinStatic:{
                Expr var = block->pop();
                FieldStmt *stmt = new FieldStmt();
                stmt->curPod = curPod;
                stmt->isLoad = false;
                stmt->isStatic = true;
                stmt->fieldRef = &curPod->fieldRefs[opObj.i1];
                
                stmt->value = var;
                block->push(stmt->value);
                
                block->stmts.push_back(stmt);
                break;
            }
                // route method calls to FMethodRef
            case FOp::CallNew: {
                Var &var = block->newVar(curPod->methodRefs[opObj.i1].parent);
                //var.typeRef = curPod->methodRefs[opObj.i1].parent;
                Expr value;
                value.type = ExprType::tempVar;
                value.varRef.index = var.index;
                value.varRef.block = var.block;
                block->push(value);
                call(block, opObj, false, false, false);
                block->push(value);
                break;
            }
            case FOp::CallStatic:
            case FOp::CallMixinStatic: {
                call(block, opObj, false, true, false);
                break;
            }
            case FOp::CallVirtual: {
                call(block, opObj, true, false, false);
                break;
            }
            case FOp::CallMixinVirtual: {
                call(block, opObj, true, false, true);
                break;
            }
                
            case FOp::CallCtor:
            case FOp::CallNonVirtual: {
                call(block, opObj, false, false, false);
                break;
            }
            case FOp::CallMixinNonVirtual: {
                call(block, opObj, false, false, true);
                break;
            }
                
            case FOp::Jump: {
                JmpStmt *stmt = new JmpStmt();
                stmt->jmpType = JmpStmt::allJmp;
                //stmt->opObj = opObj;
                stmt->pos = opObj.i1;
                stmt->targetBlock = posToBlock[opObj.i1];
                
                block->stmts.push_back(stmt);
                break;
            }
            case FOp::JumpTrue:{
                JmpStmt *stmt = new JmpStmt();
                stmt->jmpType = JmpStmt::trueJmp;
                stmt->expr = block->pop();
                //stmt->opObj = opObj;
                stmt->pos = opObj.i1;
                stmt->targetBlock = posToBlock[opObj.i1];
                
                block->stmts.push_back(stmt);
                break;
            }
            case FOp::JumpFalse:{
                JmpStmt *stmt = new JmpStmt();
                stmt->jmpType = JmpStmt::falseJmp;
                stmt->expr = block->pop();
                //stmt->opObj = opObj;
                stmt->pos = opObj.i1;
                stmt->targetBlock = posToBlock[opObj.i1];
                
                block->stmts.push_back(stmt);
                break;
            }
            case FOp::CompareEQ:
            case FOp::CompareNE:
            case FOp::Compare:
            case FOp::CompareLT:
            case FOp::CompareLE:
            case FOp::CompareGE:
            case FOp::CompareGT:
            case FOp::CompareSame:
            case FOp::CompareNotSame: {
                CmpStmt *stmt = new CmpStmt();
                stmt->param2 = block->pop();
                stmt->param1 = block->pop();
                stmt->opObj = opObj;
                Var &var = block->newVar(0);
                var.typeName = "sys_Bool";
                stmt->result.type = ExprType::tempVar;
                stmt->result.varRef.index = var.index;
                stmt->result.varRef.block = var.block;
                block->stmts.push_back(stmt);
                
                block->push(stmt->result);
                break;
            }
            case FOp::CompareNull:
            case FOp::CompareNotNull:{
                CmpStmt *stmt = new CmpStmt();
                stmt->param2.type = ExprType::constant;
                stmt->param2.opObj = opObj;
                stmt->param2.varRef.index = 0;
                stmt->param1 = block->pop();
                stmt->opObj = opObj;
                Var &var = block->newVar(0);
                var.typeName = "sys_Bool";
                stmt->result.type = ExprType::tempVar;
                stmt->result.varRef.index = var.index;
                stmt->result.varRef.block = var.block;
                block->stmts.push_back(stmt);
                
                block->push(stmt->result);
                break;
            }
                
            case FOp::Return: {
                RetStmt *stmt = new RetStmt();
                
                bool isVoid = FCodeUtil::isVoidTypeRef(curPod, irMethod.returnType);
                stmt->isVoid = isVoid;
                if (!isVoid) {
                    stmt->retValue = block->pop();
                }
                
                block->stmts.push_back(stmt);
                break;
            }
            case FOp::Pop: {
                block->pop();
                break;
            }
            case FOp::Dup: {
                Expr entry = block->pop();
                block->push(entry);
                block->push(entry);
                break;
            }
            case FOp::Is: {
                
                break;
            }
            case FOp::As: {
                //call
                //jmp block2
                //cast
                //block2->load null
                break;
            }
            case FOp::Coerce: {
                CoerceStmt *stmt = new CoerceStmt();
                stmt->curPod = curPod;
                stmt->from = block->pop();
                
                CoerceStmt::CType i = typeCoerce(opObj.i1, opObj.i2);
                stmt->coerceType = i;
                stmt->fromType = opObj.i1;
                stmt->toType = opObj.i2;
                Var &var = block->newVar(opObj.i2);
                
                Expr value;
                value.type = ExprType::tempVar;
                value.varRef.index = var.index;
                value.varRef.block = var.block;
                block->push(value);
                stmt->to = value;
                
                block->stmts.push_back(stmt);
                break;
            }
            case FOp::Switch: {
                //newBlock();
                break;
            }
            case FOp::Throw: {
                //newBlock();
                break;
            }
            case FOp::Leave: {
                JmpStmt *stmt = new JmpStmt();
                stmt->jmpType = JmpStmt::leaveJmp;
                //stmt->opObj = opObj;
                stmt->pos = opObj.i1;
                stmt->targetBlock = posToBlock[opObj.i1];
                
                block->stmts.push_back(stmt);
                break;
            }
            case FOp::JumpFinally:{
                JmpStmt *stmt = new JmpStmt();
                stmt->jmpType = JmpStmt::finallyJmp;
                //stmt->opObj = opObj;
                stmt->pos = opObj.i1;
                stmt->targetBlock = posToBlock[opObj.i1];
                
                block->stmts.push_back(stmt);
                break;
            }
            case FOp::CatchAllStart: {
                ExceptionStmt *estmt = new ExceptionStmt();
                estmt->etype = ExceptionStmt::CatchStart;
                estmt->catchType = -1;
                estmt->pos = opObj.pos;
                block->stmts.push_back(estmt);
            }
                break;
                
            case FOp::CatchErrStart: {
                Var &var = block->newVar(opObj.i1);
                //var.typeRef = opObj.i1;
                Expr value;
                value.type = ExprType::tempVar;
                value.varRef.index = var.index;
                value.varRef.block = var.block;
                
                //                StoreStmt *stmt = new StoreStmt();
                //                stmt->src = block->pop();
                //                stmt->dst = value;
                //                block->stmts.push_back(stmt);
                block->push(value);
                
                ExceptionStmt *estmt = new ExceptionStmt();
                estmt->etype = ExceptionStmt::CatchStart;
                estmt->catchVar = value;
                estmt->catchType = opObj.i1;
                estmt->pos = opObj.pos;
                block->stmts.push_back(estmt);
            }
                break;
            case FOp::CatchEnd: {
                ExceptionStmt *stmt = new ExceptionStmt();
                stmt->etype = ExceptionStmt::CatchEnd;
                block->stmts.push_back(stmt);
            }
                break;
                
            case FOp::FinallyStart: {
                ExceptionStmt *stmt = new ExceptionStmt();
                stmt->etype = ExceptionStmt::FinallyStart;
                block->stmts.push_back(stmt);
            }
                break;
                
            case FOp::FinallyEnd: {
                ExceptionStmt *stmt = new ExceptionStmt();
                stmt->etype = ExceptionStmt::FinallyEnd;
                block->stmts.push_back(stmt);
            }
                break;
                
            default:
                printf("ERROR: unkonw opcode\n");
                break;
        }
        
    }
    
    for (Block *b : block->branchs) {
        parseBlock(b, block);
    }
}
