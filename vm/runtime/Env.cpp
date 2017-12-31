//
//  Env.cpp
//  fcode
//
//  Created by yangjiandong on 15/8/2.
//  Copyright (c) 2015年 yangjiandong. All rights reserved.
//

#include "Env.h"

Env::Env(Vm *vm) : vm(vm), error(0)
, isStoped(false), needStop(false) {
}

void Env::walkLocalRoot(Gc *gc) {
}

////////////////////////////
// Exception
////////////////////////////
#ifdef LONG_JMP_EXCEPTION
jmp_buf *fr_pushJmpBuf(fr_Env self) {
    Env *env = (Env*)self;
    JmpBuf buf;
    env->exception.push_back(buf);
    return &env->exception.back().buf;
}

jmp_buf *fr_popJmpBuf(fr_Env self) {
    Env *env = (Env*)self;
    JmpBuf &back = env->exception.back();
    env->exception.pop_back();
    return &back.buf;
}
#endif

fr_Obj fr_getErr(fr_Env self) {
    Env *env = (Env*)self;
    return env->error;
}
void fr_setErr(fr_Env self, fr_Obj err) {
    Env *env = (Env*)self;
    env->error = err;
}
void fr_clearErr(fr_Env self) {
    Env *env = (Env*)self;
    env->error = nullptr;
}



