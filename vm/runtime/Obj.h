//
//  Obj.h
//  fcode
//
//  Created by yangjiandong on 15/8/2.
//  Copyright (c) 2015年 yangjiandong. All rights reserved.
//

#ifndef __fcode__Obj__
#define __fcode__Obj__

#include "gcobj.h"

#include "Type.h"

typedef struct fr_Obj_ {
    //GcObj super;
} *fr_Obj;

fr_Type getType(fr_Obj obj);

#endif /* defined(__fcode__Obj__) */
