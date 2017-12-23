//
//  main.c
//  run
//
//  Created by yangjiandong on 2017/12/17.
//  Copyright © 2017年 yangjiandong. All rights reserved.
//

#include "Env.h"
#include "testlib.h"

int main() {
    fr_FVM vm = fr_startVm();
    fr_Env env = fr_getEnv(vm);
    
    testlib_Sub_main0(env);
    
    fr_releaseEnv(env);
    fr_stopVm(vm);
}
