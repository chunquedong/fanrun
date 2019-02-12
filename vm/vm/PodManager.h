//
//  PodManager.h
//  vm
//
//  Created by yangjiandong on 15/9/26.
//  Copyright (c) 2015, yangjiandong. All rights reserved.
//

#ifndef __vm__PodManager__
#define __vm__PodManager__

#include <stdio.h>
#include "FPod.h"
#include <unordered_map>
#include "fni.h"
#include "ObjFactory.h"
#include "PodLoader.h"

class Env;
class Fvm;

class PodManager {
    PodLoader podLoader;
    std::unordered_map<std::string, fr_NativeFunc> nativeFuncMap;
private:
    FType *intType;
    FType *floatType;
    FType *boolType;
    FType *objType;
    FType *voidType;
    FType *typeType;
    FType *npeType;
public:
    ObjFactory objFactory;
    Fvm *vm;
    
public:
    bool load(std::string path, std::string name);
    
    PodManager();
    ~PodManager();
    
public:
    void registerMethod(std::string name, fr_NativeFunc func);
    
    FMethod *getMethod(Env *env, FPod *curPod, uint16_t mid, int *paramCount);
    FMethod *getVirtualMethod(Env *env, FType *instanceType, FPod *curPod, uint16_t mid, bool isSetter);

    FMethod *findMethod(Env *env, std::string pod, std::string type, std::string name);
    FMethod *findMethodInType(Env *env, FType *type, std::string name);
    FMethod *toVirtualMethod(Env *env, FType *type, FMethod *method);
    FMethod *findVirtualMethod(Env *env, FType *type, std::string name);
    
public:
    FField *getField(Env *env, FPod *curPod, uint16_t fid);
    FField *findFieldByName(Env *env, std::string podName, std::string typeName, std::string fieldName);
    FField *findFieldInType(Env *env, FType *type, std::string fieldName);
    FField *findFieldByType(FType *type, std::string fieldName);
    
    fr_Value *getInstanceFieldValue(FObj * obj, FField *field);
    fr_Value *getStaticFieldValue(FField *field);
    
public:
    FPod *findPod(std::string podName) { return podLoader.findPod(podName); }
    FType *getType(Env *env, FPod *curPod, uint16_t tid);
    FType *findType(Env *env, std::string pod, std::string type, bool initType = true);
    bool fitType(Env *env, FType *type, FPod *curPod, uint16_t tid);
    bool fitTypeByType(Env *env, FType *typeA, FType *typeB);
    FObj * getWrappedType(Env *env, FType *type);
    FType *getFType(Env *env, FObj *otype);
public:
    FType *getSysType(Env *env, fr_ValueType vt);
    FType *getTypeType(Env *env);
    FType *getNpeType(Env *env);
    bool isVoidType(Env *env, FType *type);
    bool isNullableType(Env *env, FPod *curPod, uint16_t tid);
    bool isPrimitiveType(Env *env, FPod *curPod, uint16_t tid);
    
    void initTypeAllocSize(Env *env, FType *type);
    FType *getInstanceType(Env *env, fr_TagValue &val);
    fr_ValueType getExactValueType(FPod *curPod, uint16_t tid, bool &nullable, bool *isVoid = nullptr);
    fr_ValueType getValueType(Env *env, FPod *curPod, uint16_t tid);
    fr_ValueType getValueTypeByType(Env *env, FType *type);
    
private:
    void loadNativeMethod(FMethod *method);
    void initSysType(Env *env);
    bool isRootType(Env *env, FType *type);
};

#endif /* defined(__vm__PodManager__) */
