//
// Copyright (c) 2017, chunquedong
// Licensed under the Apache Licene 2.0
//
//  Created by yangjiandong on 16/9/10.
//

#ifndef Stmt_hpp
#define Stmt_hpp

#include "Code.h"
#include "FPod.h"
//#include "common.h"
#include "Printer.h"

class IRMethod;

enum class ExprType {
    constant,
    localVar,
    tempVar,
};

struct Var {
    int index;
    int newIndex;
    int block;
    //bool isExport;
    
    std::string name;
    std::string typeName;
    
    //fr_ValueType type;
    uint16_t typeRef;
    FMethodVar *methodVar;
    //bool isRef;
    
    Var() : index(-1), newIndex(-1), block(-1),
        typeRef(0), methodVar(nullptr) {
    }
};

class Expr {
public:
    struct VarRef {
        int block;
        int index;
    };
    ExprType type;
    union {
        FOpObj opObj;
        VarRef varRef;
    };
    std::string getConstantType();
    void print(IRMethod *method, Printer& printer, int pass);
};

enum class StmtType {
    store,
    field,
    call,
    cmp,
    ret,
    jmp,
    error,
};

class Stmt {
public:
    FPod *curPod;
    virtual void print(IRMethod *method, Printer& printer, int pass) = 0;
    virtual StmtType getType() = 0;
};

class StoreStmt : public Stmt {
public:
    Expr src;
    Expr dst;
    
    virtual void print(IRMethod *method, Printer& printer, int pass) override;
    
    StmtType getType() override { return StmtType::store; }
};

class FieldStmt : public Stmt {
public:
    bool isLoad;
    bool isStatic;
    Expr instance;
    FFieldRef *fieldRef;
    Expr value;
    
    virtual void print(IRMethod *method, Printer& printer, int pass) override;
    
    StmtType getType() override { return StmtType::field; }
};

class CallStmt : public Stmt {
public:
    uint16_t methodRefId;
    FMethodRef *methodRef;
    std::vector<Expr> params;
    Expr retValue;
    bool isVoid;
    bool isStatic;
    bool isVirtual;
    bool isMixin;
    
    virtual void print(IRMethod *method, Printer& printer, int pass) override;
    
    StmtType getType() override { return StmtType::call; }
};

class CmpStmt : public Stmt {
public:
    Expr param1;
    Expr param2;
    Expr result;
    FOpObj opObj;
    
    virtual void print(IRMethod *method, Printer& printer, int pass) override;
    
    StmtType getType() override { return StmtType::cmp; }
};

class RetStmt : public Stmt {
public:
    Expr retValue;
    bool isVoid;
    
    virtual void print(IRMethod *method, Printer& printer, int pass) override;
    
    StmtType getType() override { return StmtType::ret; }
};

class Block;
class JmpStmt : public Stmt {
public:
    enum JmpType {
        allJmp,
        trueJmp,
        falseJmp,
        leaveJmp,
        finallyJmp,
    };
    
    JmpType jmpType;
    Expr expr;
    uint16_t pos;
    
    Block *targetBlock;
    
    virtual void print(IRMethod *method, Printer& printer, int pass) override;
    
    StmtType getType() override { return StmtType::cmp; }
};

class ExceptionStmt : public Stmt {
public:
    enum EType { TryStart, TryEnd, CatchStart, CatchEnd, FinallyStart, FinallyEnd };
    EType etype;
    int32_t catchType;//err type to catch
    Expr catchVar;
    int32_t handler;
    int pos;
    
    std::vector<ExceptionStmt *> catchs;
    
    ExceptionStmt() : catchType(-1), handler(-1), pos(-1) {}
    
    virtual void print(IRMethod *method, Printer& printer, int pass) override;
    
    StmtType getType() override { return StmtType::error; }
};

//Basic Block is min linear code
class Block {
public:
    int index;//id in method
    uint16_t pos;//position in buffer
    
    uint16_t beginOp;//begin postion in ops
    uint16_t endOp;//next ops position of last of pos
    
    std::vector<Stmt*> stmts;
    
    std::vector<Block*> branchs;
    std::vector<Block*> incoming;
    
    std::vector<Expr> stack;//temp stack
    
    std::vector<Var> locals;
    
    bool isVisited;//flag for builder
    bool isForward;//flag if no jump stmt at last
    
    Block() : index(0), pos(0), beginOp(0), endOp(0), isVisited(false), isForward(false) {
    }
    
    void print(IRMethod *method, Printer& printer, int pass);
    
    Var &newVar(uint16_t typeRef) {
        Var var;
        var.index = (int)locals.size();
        var.block = this->index;
        var.typeRef = typeRef;        
        locals.push_back(var);
        return locals.back();
    }
    
    void push(Expr &var) {
        stack.push_back(var);
    }
    Expr pop() {
        if (stack.size() == 0) {
            printf("ERROR: statck is empty\n");
            //abort();
            Expr var;
            var.type = ExprType::tempVar;
            var.varRef.block = 0;
            var.varRef.index = 0;
            
            return var;
        }
        Expr var = stack.back();
        stack.pop_back();
        return var;
    }
};


#endif /* Stmt_hpp */
