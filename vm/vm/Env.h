//
//  Interpreter.h
//  vm
//
//  Created by yangjiandong on 15/9/26.
//  Copyright (c) 2015, yangjiandong. All rights reserved.
//

#ifndef __vm__Env__
#define __vm__Env__

#include <stdio.h>
#include "Fvm.h"
#include <vector>
#include <set>
#include "tinycthread.h"
#include "system.h"

struct StackFrame {
    StackFrame *preFrame;
    FMethod *method;
    int paddingSize;
    int paramCount;
};

class Env : public fr_Env_ {
    ExeEngine *interpreter;
public:
    PodManager *podManager;
//private:
    StackFrame *blockingFrame;
    
    FObj *error;
    FObj *thread;
    
    char *stackBottom;
    char *stackTop;
    char *stackMemEnd;
    int stackMemSize;
    
public:
    StackFrame *curFrame;
    Fvm *vm;
    bool trace;
    
public:
    Env(Fvm *vm);
    ~Env();
    
    void start(const char*, const char* type, const char* name, FObj *args);
    
    ////////////////////////////
    // frame
    ////////////////////////////
    
    bool popFrame();
    
    ////////////////////////////
    // Param
    ////////////////////////////
    
    void push(fr_TagValue *val);
    bool pop(fr_TagValue *val);
    bool popAll(int count);
    fr_TagValue *peek(int pos = -1);
    void insertBack(fr_TagValue *entry, int count);

    //bool getParam(void *param, fr_TagValue *val, int pos);
    
    ////////////////////////////
    // GC
    ////////////////////////////
    
    void checkSafePoint();
    
    fr_Obj newLocalRef(FObj * obj);
    void deleteLocalRef(fr_Obj obj);
    fr_Obj newGlobalRef(FObj * obj);
    void deleteGlobalRef(fr_Obj obj);
    
    FObj * allocObj(FType *type, int addRef, int size = 0);
    void walkLocalRoot(Gc *gc);
    void gc();
    
    ////////////////////////////
    // other
    ////////////////////////////
    
    FObj * box(fr_Value &value, fr_ValueType vtype);
    bool unbox(FObj * obj, fr_Value &value);
    
    ////////////////////////////
    // type
    ////////////////////////////
    
    FType * findType(std::string pod, std::string type);
    FType * getSysType(fr_ValueType vt);
    FType * getInstanceType(fr_TagValue *obj);
    bool fitType(FType * a, FType * b);
    
    ////////////////////////////
    // call
    ////////////////////////////
public:

    void call(FMethod *method, int paramCount);
    
    FMethod * findMethod(const char *pod, const char *type, const char *name);
    void callNonVirtual(FMethod * method, int paramCount);
    void newObj(FType *type, FMethod * method, int paramCount);
    void callVirtual(FMethod * method, int paramCount);
    
    void callVirtualByName(const char *name, int paramCount);
    void newObjByName(const char * pod, const char * type, const char * name, int paramCount);
public:
    void setStaticField(FField *field, fr_Value *val);
    bool getStaticField(FField *field, fr_Value *val);
    
    void setInstanceField(fr_Value &bottom, FField *field, fr_Value *val);
    bool getInstanceField(fr_Value &bottom, FField *field, fr_Value *val);
    
    ////////////////////////////
    // exception
    ////////////////////////////
    
    FObj * getError();
    void throwError(FObj * err);
    void throwNPE();
    void throwNew(const char* podName, const char* typeName, const char* msg, int addRef);
    void clearError();
    void printError(FObj * err);
    
    void printOperandStack();
    void stackTrace(char *buf, int size, const char *delimiter);
    void printStackTrace();
};

#endif /* defined(__vm__Interpreter__) */
