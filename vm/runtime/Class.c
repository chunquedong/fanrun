//
//  Type.cpp
//  fcode
//
//  Created by yangjiandong on 15/8/2.
//  Copyright (c) 2015年 yangjiandong. All rights reserved.
//

#include "runtime.h"
#include <stdio.h>

bool fr_isType(fr_Env self, fr_Obj obj, fr_Type type) {
    fr_Type tempType = fr_getType(self, obj);
    while (true) {
        if (tempType == type) return true;
        tempType = tempType->base;
        if (!tempType) return false;
    }
    return false;
}

void fr_VTable_init(fr_Env self, fr_Type type) {
    type->name = "";
    type->base = NULL;
    type->mixinCount = 0;
    type->allocSize = 0;
    type->sysType = NULL;
}

fr_Type fr_getType(fr_Env self, fr_Obj obj) {
    GcObj *g = fr_toGcObj(obj);
    //return obj->super.header;
    fr_Type type = (fr_Type)gc_getType(g);
    return type;
}

fr_Type fr_getInterfaceVTable(fr_Env self, fr_Obj obj, fr_Type itype) {
    fr_Type type = fr_getType(self, obj);
    for (int i=0; i<type->mixinCount; ++i) {
        struct fr_IVTableMapItem *item = &type->interfaceVTableMap[i];
        if (item->type == itype) {
            return item->vtable;
        }
    }
    printf("ERROR: not found interface vtable %s\n", itype->name);
    return NULL;
}
