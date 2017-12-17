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

struct fr_Obj_;
typedef struct fr_Obj_ *fr_Obj;
typedef void *fr_Env;

struct Field {
    const char *name;
    uint32_t flags;
    const char *type;
    int offset;
    //Obj *pointer;
  
    int facetCount;
    //Obj facetList;
};

struct MethodVar {
    const char *name;
    uint32_t flags;
    const char *type;
    
    int facetCount;
    //Obj facetList;
};

typedef void (*Function)(fr_Env env__, void *self__, void *returnVar__, int varCount__, ...);

struct Method {
    const char *name;
    uint32_t flags;
    const char *retType;
    const char *inheritReturenType;
    Function func;
    int varCount;
    struct MethodVar *varList;
    
    int facetCount;
    //Obj facetList;
};

typedef struct fr_Type_ {
    const char *name;
    uint32_t flags;
  
    struct Type_ *base;
    int mixinCount;
    struct Type_ **mixinList;
  
    int fieldCount;
    struct Field *fieldList;
    
    int methodCount;
    struct Method *methodList;
    
    int facetCount;
    //Obj facetList;
  
    Function finalize;
} *fr_Type;

void VTable_init(fr_Type type);

bool fr_Type_is(fr_Type self, fr_Obj obj);


#endif /* defined(__fcode__Type__) */
