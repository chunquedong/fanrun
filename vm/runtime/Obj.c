//
//  Obj.cpp
//  fcode
//
//  Created by yangjiandong on 15/8/2.
//  Copyright (c) 2015年 yangjiandong. All rights reserved.
//

#include "Obj.h"

fr_Type getType(fr_Obj obj) {
    return obj->super.header;
}
