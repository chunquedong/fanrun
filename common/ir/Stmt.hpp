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
class Block;

struct TypeInfo {
    std::string pod;
    std::string name;
    bool isNullable;
    bool isValue;
    
    std::string getName() const;
    
    TypeInfo() : isNullable(false), isValue(false) {}
    //TypeInfo(const std::string &pod, const std::string &name);
    TypeInfo(FPod *curPod, uint16_t typeRefId) { setFromTypeRef(curPod, typeRefId); }
    
    void makeInt();
    void makeBool();
    
    void setFromTypeRef(FPod *curPod, uint16_t typeRefId);
    
    bool isThis();
    bool isVoid();
    
    bool operator==(const TypeInfo &other) const {
        if (pod != other.pod) return false;
        if (name != other.name) return false;
        if (isNullable != other.isNullable) return false;
        if (isValue != other.isValue) return false;
        return true;
    }
};

//Ref of var
struct Expr {
    //index of parent
    int index;
    
    //parent of block
    Block *block;
    
    Expr() : block(nullptr), index(-1) {}
    
    std::string &getName();
    TypeInfo &getType();
    std::string getTypeName();
    bool isValueType();
};

struct Var {
    //position in block
    int index;
    //parent block
    Block *block;
    
    //ref by other block
    bool isExport;
    //unused
    int newIndex;
    
    //name of var
    std::string name;
    
    //type of var
    TypeInfo type;
    
    Var() : index(-1), newIndex(-1), block(nullptr),
    isExport(false) {
    }
    
    Expr asRef();
};

class Stmt {
public:
    FPod *curPod;
    IRMethod *method;
    virtual void print(Printer& printer) = 0;
    Stmt() : curPod(nullptr), method(nullptr) {}
};

class ConstStmt : public Stmt {
public:
    Expr dst;
    FOpObj opObj;
    
    virtual void print(Printer& printer) override;
    TypeInfo getType();
};

class StoreStmt : public Stmt {
public:
    Expr src;
    Expr dst;
    
    virtual void print(Printer& printer) override;
};

class FieldStmt : public Stmt {
public:
    bool isLoad;
    bool isStatic;
    Expr instance;
    FFieldRef *fieldRef;
    Expr value;
    
    virtual void print(Printer& printer) override;
};

class CallStmt : public Stmt {
public:
    FMethodRef *methodRef;
    
    std::string typeName;
    std::string mthName;
    
    std::vector<Expr> params;
    Expr retValue;
    bool isVoid;
    bool isStatic;
    bool isVirtual;
    bool isMixin;
    
    //for compare which no methodRef
    //std::vector<std::string> argsType;
    
    CallStmt() : methodRef(NULL) {}
    
    virtual void print(Printer& printer) override;
};

class AllocStmt : public Stmt {
public:
    uint16_t type;
    Expr obj;
    
    virtual void print(Printer& printer) override;
};

class CmpStmt : public Stmt {
public:
    Expr param1;
    Expr param2;
    Expr result;
    FOpObj opObj;
    
    virtual void print(Printer& printer) override;
};

class RetStmt : public Stmt {
public:
    Expr retValue;
    bool isVoid;
    
    virtual void print(Printer& printer) override;
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
    uint16_t selfPos;
    uint16_t targetPos;
    
    Block *targetBlock;
    
    virtual void print(Printer& printer) override;
};

class ThrowStmt : public Stmt {
public:
    Expr var;
    
    virtual void print(Printer& printer) override;
};

class ExceptionStmt : public Stmt {
public:
    enum EType { TryStart, TryEnd, CatchStart, CatchEnd, FinallyStart, FinallyEnd };
    EType etype;
    
    int32_t catchType;//err type to catch
    Expr catchVar;
    int32_t handler;
    int pos;
    
    std::vector<ExceptionStmt*> handlerStmt;
    
    ExceptionStmt() : catchType(-1), handler(-1), pos(-1) {}
    
    virtual void print(Printer& printer) override;
};

class CoerceStmt : public Stmt {
public:
    //enum CType { nonNull, boxing, unboxing, other };
    //CType coerceType;
    Expr from;
    Expr to;
    
    int fromType;
    int toType;
    
    //can direct cast
    bool safe;
    //throw err if can't cast
    bool checked;
    
    CoerceStmt() : safe(true), checked(true), fromType(-1), toType(-1) {}
    
    virtual void print(Printer& printer) override;
};

class TypeCheckStmt : public Stmt {
public:
    Expr obj;
    uint16_t type;
    Expr result;
    
    virtual void print(Printer& printer) override;
};


#endif /* Stmt_hpp */