//
// Copyright (c) 2017, chunquedong
// Licensed under the Apache Licene 2.0
//
//  Created by yangjiandong on 16/9/10.
//

#include "IRMethod.h"

IRMethod::IRMethod(FPod *curPod, FMethod *method) :
    curPod(curPod),
    method(method) {
}

void IRMethod::initLocals() {
    primLocalsCount = 0;
    refLocalsCount = 0;
    
    for (Var &var : locals) {
        bool isRef = var.isRef;
        if (isRef) {
            var.newIndex = refLocalsCount;
            ++refLocalsCount;
        } else {
            var.newIndex = primLocalsCount;
            ++primLocalsCount;
        }
    }
    
    for (auto *b : blocks) {
        for (Var &var : b->locals) {
            bool isRef = var.isRef;
            if (isRef) {
                var.newIndex = refLocalsCount;
                ++refLocalsCount;
            } else {
                var.newIndex = primLocalsCount;
                ++primLocalsCount;
            }
        }
    }
}

void IRMethod::compile() {
    method->code.initOps();
    
    bool isStatic = (method->flags & FFlags::Static) != 0;
    if (!isStatic) {
        Var &var = newVar();
        //var.typeRef = curPod-
        var.name = "__self";
    }
    for(int i=0; i<method->vars.size(); ++i) {
        FMethodVar *fvar = &method->vars[i];
        Var &var = newVar();
        var.methodVar = fvar;
        var.name = curPod->names[fvar->name];
    }
    
    initJumpTarget();
    initBlock();
    linkBlock();
    
    for (auto *b : blocks) {
        parseBlock(b, nullptr);
    }
    
    initLocals();
}

void IRMethod::print(Printer& printer, int pass) {
    
    if (pass == 0) {
        printer.printf("%s(", curPod->names[method->name].c_str());
        //int varPos = 0;
        for(int i=0; i<method->paramCount; ++i) {
            FMethodVar *var = &method->vars[i];
            printer.printf("%s, ", curPod->names[var->name].c_str());
            //varPos++;
        }
        printer.println(")");
    }
    else if (pass == 1) {
        printer.indent();
        
        for(int i=method->paramCount; i<locals.size(); ++i) {
            Var v = locals[i];
            printer.printf("v__%s_%d, ", v.name.c_str(), v.index);
        }
        printer.newLine();
        
        
        for (Block *b : blocks) {
            b->print(this, printer, 0);
        }
        for (Block *b : blocks) {
            b->print(this, printer, 1);
        }
        printer.unindent();
    }
}

bool IRMethod::isVoidTypeRef(uint16_t typeRefId) {
    FTypeRef &typeRef = curPod->typeRefs[typeRefId];
    if (curPod->names[typeRef.podName] == "sys"
        && curPod->names[typeRef.typeName] == "Void") {
        return true;
    }
    return false;
}

void IRMethod::initJumpTarget() {
    std::unordered_map<int16_t, FOpObj*> posToOp;
    for (int i=0; i<method->code.ops.size(); ++i) {
        FOpObj *opObj = &method->code.ops[i];
        posToOp[opObj->pos] = opObj;
        opObj->blockBegin = false;
    }
    
    for (int i=0; i<method->code.ops.size(); ++i) {
        FOpObj &opObj = method->code.ops[i];
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
                if (i+1 < method->code.ops.size()) {
                    FOpObj *next = &method->code.ops[i+1];
                    next->blockBegin = true;
                }
                
                break;
            }
            default:
                break;
        }
    }
}

void IRMethod::linkBlock() {
    std::unordered_map<int16_t, Block*> posToBlock;
    for (auto *b : blocks) {
        posToBlock[b->pos] = b;
    }
    
    for (int i=0; i<blocks.size(); ++i) {
        Block *b = blocks[i];
        FOpObj &lastOp = method->code.ops[b->endOp-1];
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
            case FOp::Leave:
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
//        Stmt *stmt = b->stmts.back();
//        JmpStmt *jmpStmt = dynamic_cast<JmpStmt*>(stmt);
//        if (jmpStmt) {
//            jmpStmt->targetBlock = posToBlock[jmpStmt->pos];
//            if (!jmpStmt->targetBlock) {
//                printf("ERROR");
//            }
//        }
    }
}

void IRMethod::initBlock() {
    for (int i=0; i<method->code.ops.size(); ++i) {
        FOpObj &opObj = method->code.ops[i];
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
        block->endOp = method->code.ops.size();
    }
}

void IRMethod::call(Block *block, FOpObj &opObj, bool isVirtual, bool isStatic) {
    CallStmt *stmt = new CallStmt();
    stmt->isStatic = isStatic;
    stmt->isVirtual = isVirtual;
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
    
    bool isVoid = isVoidTypeRef(stmt->methodRef->retType);
    stmt->isVoid = isVoid;
    if (!isVoid) {
        Var var = block->newVar();
        stmt->retValue.type = ExprType::tempVar;
        stmt->retValue.varRef.index = var.index;
        stmt->retValue.varRef.block = var.block;
        block->push(stmt->retValue);
    }
    block->stmts.push_back(stmt);
}

void IRMethod::parseBlock(Block *block, Block *previous) {
    
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
                    newVar = block->newVar();
                    newVar.isExport = true;
                    
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
        FOpObj &opObj = method->code.ops[i];
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
                
                Var var = block->newVar();
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
                
                Var var = block->newVar();
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
                
                Var var = block->newVar();
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
                Var var = block->newVar();
                Expr value;
                value.type = ExprType::tempVar;
                value.varRef.index = var.index;
                value.varRef.block = var.block;
                block->push(value);
                call(block, opObj, false, false);
                block->push(value);
                break;
            }
            case FOp::CallStatic:
            case FOp::CallMixinStatic: {
                call(block, opObj, false, true);
                break;
            }
            case FOp::CallVirtual:
            case FOp::CallMixinVirtual: {
                call(block, opObj, true, false);
                break;
            }
                
            case FOp::CallCtor:
            case FOp::CallNonVirtual:
            case FOp::CallMixinNonVirtual: {
                call(block, opObj, false, false);
                break;
            }
                
            case FOp::Jump: {
                JmpStmt *stmt = new JmpStmt();
                stmt->jmpType = JmpStmt::allJmp;
                stmt->opObj = opObj;
                stmt->pos = opObj.i1;
                stmt->targetBlock = block->branchs.back();
                
                block->stmts.push_back(stmt);
                break;
            }
            case FOp::JumpTrue:{
                JmpStmt *stmt = new JmpStmt();
                stmt->jmpType = JmpStmt::trueJmp;
                stmt->expr = block->pop();
                stmt->opObj = opObj;
                stmt->pos = opObj.i1;
                stmt->targetBlock = block->branchs.back();
                
                block->stmts.push_back(stmt);
                break;
            }
            case FOp::JumpFalse:{
                JmpStmt *stmt = new JmpStmt();
                stmt->jmpType = JmpStmt::falseJmp;
                stmt->expr = block->pop();
                stmt->opObj = opObj;
                stmt->pos = opObj.i1;
                stmt->targetBlock = block->branchs.back();
                
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
                Var var = block->newVar();
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
                Var var = block->newVar();
                stmt->result.type = ExprType::tempVar;
                stmt->result.varRef.index = var.index;
                stmt->result.varRef.block = var.block;
                block->stmts.push_back(stmt);
                
                block->push(stmt->result);
                break;
            }
            
            case FOp::Return: {
                RetStmt *stmt = new RetStmt();
                
                bool isVoid = isVoidTypeRef(method->returnType);
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
                //newBlock();
                //box unbox
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
                //newBlock();
                break;
            }
            case FOp::JumpFinally:{
                //newBlock();
                break;
            }
            case FOp::CatchAllStart:
                //newBlock();
                break;
                
            case FOp::CatchErrStart: {
                Var var = block->newVar();
                Expr value;
                value.type = ExprType::tempVar;
                value.varRef.index = var.index;
                value.varRef.block = var.block;
                /*
                StoreStmt *stmt = new StoreStmt();
                stmt->src = block->pop();
                stmt->dst = value;
                block->stmts.push_back(stmt);
                */
                block->push(value);
            }
                break;
            case FOp::CatchEnd:
                //newBlock();
                break;
                
            case FOp::FinallyStart:
                //newBlock();
                break;
                
            case FOp::FinallyEnd:
                //newBlock();
                break;
                
            default:
                break;
        }

    }
    
    for (Block *b : block->branchs) {
        parseBlock(b, block);
    }
}
