//
//  Type.cpp
//  fcode
//
//  Created by yangjiandong on 15/8/2.
//  Copyright (c) 2015年 yangjiandong. All rights reserved.
//

#include "runtime.h"
#include <stdio.h>

bool fr_isClass(fr_Env env, fr_Obj obj, fr_Class type) {
    fr_Class tempType = fr_getClass(env, obj);
    while (true) {
        if (tempType == type) return true;
        if (tempType == tempType->base) break;
        tempType = tempType->base;
        if (!tempType) break;
    }
    return false;
}

void fr_VTable_init(fr_Env env, fr_Class type) {
    type->name = "";
    type->base = NULL;
    type->mixinCount = 0;
    type->allocSize = 0;
    type->sysType = NULL;
}

fr_Class fr_getClass(fr_Env env, fr_Obj obj) {
    if (!obj) {
        fr_throwNPE(env);
    }
    GcObj *g = fr_toGcObj(obj);
    //return obj->super.header;
    fr_Class type = (fr_Class)gc_getType(g);
    return type;
}

fr_Class fr_getInterfaceVTable(fr_Env env, fr_Obj obj, fr_Class itype) {
    fr_Class type = fr_getClass(env, obj);
    for (int i=0; i<type->mixinCount; ++i) {
        struct fr_IVTableMapItem *item = &type->interfaceVTableMap[i];
        if (item->type == itype) {
            return item->vtable;
        }
    }
    printf("ERROR: not found interface vtable %s\n", itype->name);
    return NULL;
}
