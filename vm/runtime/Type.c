//
//  Type.cpp
//  fcode
//
//  Created by yangjiandong on 15/8/2.
//  Copyright (c) 2015年 yangjiandong. All rights reserved.
//

#include "Type.h"
#include "Env.h"

bool fr_Type_is(fr_Type self, fr_Obj obj) {
    return true;
}

void fr_VTable_init(fr_Type type) {
    type->name = "";
}

fr_Type fr_getType(fr_Obj obj) {
    GcObj *g = fr_toGcObj(obj);
    //return obj->super.header;
    fr_Type type = (fr_Type)gc_getType(g);
    return type;
}
