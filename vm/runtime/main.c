//
//  main.c
//  run
//
//  Created by yangjiandong on 2017/12/17.
//  Copyright © 2017年 yangjiandong. All rights reserved.
//

#include "runtime.h"

//#if FR_RUN
#include "../temp/baseTest.h"

int main() {
    fr_Env env = fr_getEnv();
    baseTest_init__(env);
    
    baseTest_BoxingTest_main0(env);
    fr_releaseEnv(env);
}

//#endif
