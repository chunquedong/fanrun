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

typedef void *fr_Obj;
typedef void *fr_Env;

struct fr_Field {
    const char *name;
    uint32_t flags;
    const char *type;
    int offset;
    //Obj *pointer;
  
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

typedef struct fr_Type_ *fr_Type;
struct fr_IVTableMapItem {
    fr_Type type;
    fr_Type vtable;
};

#define MAX_INTERFACE_SIZE 10

typedef struct fr_Type_ {
    const char *name;
    uint32_t flags;
  
    struct fr_Type_ *base;
    int mixinCount;
  
    int fieldCount;
    struct Field *fieldList;
    
    int methodCount;
    struct Method *methodList;
    
    int facetCount;
    //Obj facetList;
  
    fr_Function finalize;
    
    struct fr_IVTableMapItem interfaceVTableMap[MAX_INTERFACE_SIZE];
} *fr_Type;

void fr_VTable_init(fr_Env self, fr_Type type);

bool fr_Type_is(fr_Type self, fr_Obj obj);

fr_Type fr_getType(fr_Env self, fr_Obj obj);

fr_Type fr_getInterfaceVTable(fr_Env self, fr_Obj obj, fr_Type itype);

#endif /* defined(__fcode__Type__) */
