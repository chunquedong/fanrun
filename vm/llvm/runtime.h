//
//  runtime.h
//  vm
//
//  Created by yangjiandong on 2019/8/14.
//  Copyright © 2019 yangjiandong. All rights reserved.
//

#ifndef runtime_h
#define runtime_h

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

    struct sys_Obj { void *type; };
    struct sys_Obj *sys_Str_makeUtf8(const char *utf8);

#ifdef __cplusplus
}
#endif

#endif /* runtime_h */
