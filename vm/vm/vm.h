//
//  vm.h
//  vm
//
//  Created by yangjiandong on 2016/9/22.
//  Copyright © 2017 chunquedong. All rights reserved.
//

#ifndef vm_h
#define vm_h

#include "fni.h"
#include <assert.h>

CF_BEGIN

/**
 * internal type
 */
struct FType;
//struct fr_ObjHeader { struct FType * type; bool dirty; int mark;  };

/**
 * internal alloc obj
 */
FObj *fr_allocObj_internal(fr_Env self, fr_Type type, int size);

void fr_stackTrace(fr_Env self, char *buf, int size, const char *delimiter);


CF_END

#endif /* vm_h */
