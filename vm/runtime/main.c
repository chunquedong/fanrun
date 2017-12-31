//
//  main.c
//  run
//
//  Created by yangjiandong on 2017/12/17.
//  Copyright © 2017年 yangjiandong. All rights reserved.
//

#include "runtime.h"

//#if FR_RUN
#include "testlib.h"

int main() {
    fr_Env env = fr_getEnv();
    sys_init__(env);
    testlib_init__(env);
    
    testlib_BoxingTest_main0(env);
    fr_releaseEnv(env);
}

//#endif
