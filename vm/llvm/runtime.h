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

    void std_throw(void *err);
    void *std_alloc(void *type);

#ifdef __cplusplus
}
#endif

#endif /* runtime_h */
