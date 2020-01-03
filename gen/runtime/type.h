//
//  Type.h
//  fcode
//
//  Created by yangjiandong on 15/8/2.
//  Copyright (c) 2015年 yangjiandong. All rights reserved.
//

#ifndef __fcode__Type__
#define __fcode__Type__

#include <inttypes.h>
#include "miss.h"

#ifdef  __cplusplus
extern  "C" {
#endif

typedef void *fr_Obj;
struct fr_Env_;
typedef void *fr_Env;

struct fr_Field {
    const char *name;
    uint32_t flags;
    const char *type;
    int offset;
    bool isStatic;
    bool isValType;
    void *pointer;
  
    int facetCount;
    //Obj facetList;
};

struct fr_MethodVar {
    const char *name;
    uint32_t flags;
    const char *type;
    
    int facetCount;
    //Obj facetList;
};

typedef void (*fr_Function)(fr_Env env__, void *self__, void *returnVar__, int varCount__, ...);

struct fr_Method {
    const char *name;
    uint32_t flags;
    const char *retType;
    const char *inheritReturenType;
    fr_Function func;
    int varCount;
    struct MethodVar *varList;
    
    int facetCount;
    //Obj facetList;
};

typedef struct fr_Class_ *fr_Type;
struct fr_IVTableMapItem {
    fr_Type type;
    uint64_t vtableOffset;
};

#define MAX_INTERFACE_SIZE 20

struct fr_Class_ {
    const char *name;
    uint32_t flags;
    
    int allocSize;
    fr_Obj typeObj;
  
    struct fr_Class_ *base;
    int mixinCount;
  
    int fieldCount;
    struct fr_Field *fieldList;
    
    int methodCount;
    struct fr_Method *methodList;
    
    int facetCount;
    //Obj facetList;
    
    bool staticInited;
  
    //fr_Function finalize;
    
    struct fr_IVTableMapItem interfaceVTableIndex[MAX_INTERFACE_SIZE];
};

void fr_VTable_init(fr_Env env, fr_Type type);

bool fr_isClass(fr_Env env, fr_Obj obj, fr_Type type);

fr_Type fr_getClass(fr_Env env, fr_Obj obj);

void **fr_getInterfaceVTable(fr_Env env, fr_Obj obj, fr_Type itype);

void fr_registerClass(fr_Env env, const char *pod, const char *clz, fr_Type type);
fr_Type fr_findClass(fr_Env env, const char *pod, const char *clz);

#ifdef  __cplusplus
}//extern  "C" {
#endif
#endif /* defined(__fcode__Type__) */
