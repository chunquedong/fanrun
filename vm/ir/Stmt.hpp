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
    bool isValueType(IRMethod *method);
};

enum class StmtType {
    store,
    field,
    alloc,
    call,
    cmp,
    ret,
    jmp,
    error,
    coerce,
    throws,
    typeCheck,
};

class Stmt {
public:
    FPod *curPod;
    virtual void print(IRMethod *method, Printer& printer, int pass) = 0;
    virtual StmtType getType() = 0;
    
    Stmt() : curPod(nullptr) {}
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
    //FMethodRef *methodRef;
    //FMethod *method;
    
    std::string typeName;
    std::string mthName;
    
    std::vector<Expr> params;
    Expr retValue;
    bool isVoid;
    bool isStatic;
    bool isVirtual;
    bool isMixin;
    
    virtual void print(IRMethod *method, Printer& printer, int pass) override;
    
    StmtType getType() override { return StmtType::call; }
};

class AllocStmt : public Stmt {
public:
    uint16_t type;
    Expr obj;
    
    virtual void print(IRMethod *method, Printer& printer, int pass) override;
    
    StmtType getType() override { return StmtType::alloc; }
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

class ThrowStmt : public Stmt {
public:
    Expr var;
    
    virtual void print(IRMethod *method, Printer& printer, int pass) override;
    
    StmtType getType() override { return StmtType::throws; }
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

class CoerceStmt : public Stmt {
public:
    enum CType { nonNull, boxing, unboxing, other };
    CType coerceType;
    Expr from;
    Expr to;
    uint16_t fromType;
    uint16_t toType;
    
    CoerceStmt() : coerceType(nonNull), fromType(0), toType(0) {}
    
    virtual void print(IRMethod *method, Printer& printer, int pass) override;
    
    StmtType getType() override { return StmtType::coerce; }
};

class TypeCheckStmt : public Stmt {
public:
    bool isOrAs;
    Expr obj;
    uint16_t type;
    Expr result;
    
    virtual void print(IRMethod *method, Printer& printer, int pass) override;
    
    StmtType getType() override { return StmtType::typeCheck; }
};


#endif /* Stmt_hpp */
