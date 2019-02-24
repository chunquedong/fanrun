//
//  sys_Err.c
//  run
//
//  Created by yangjiandong on 2017/12/17.
//  Copyright © 2017年 yangjiandong. All rights reserved.
//

#include "sys.h"

#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *getTraceString() {
    void *array[100];
    int size;
    char **strings;
    size_t i;
    
    int strSize = 0;
    size_t strAlloc;
    size_t nameSize;
    char *str;
    char *name;
    
    str = (char*)malloc(256);
    if (str == NULL) {
        abort();
    }
    strAlloc = 255;
    
    size = backtrace (array, 100);
    strings = backtrace_symbols (array, size);
    if (NULL == strings) {
        str[strSize] = 0;
        return str;
    }
    
    for (i = 0; i < size; i++) {
        name = strrchr(strings[i], '/');
        if (!name) continue;
        
        nameSize = strlen(name)+1;
        if (strSize + nameSize > strAlloc) {
            strAlloc = (strSize + nameSize)*3/2;
            str = (char*)realloc(str, strAlloc+1);
            if (str == NULL) {
                abort();
            }
        }
        strcpy(str+strSize, name);
        strSize += nameSize;
        str[strSize-1] = ',';
        str[strSize] = '\0';
    }
    free (strings);
    
    str[strSize] = 0;
    return str;
}

//void sys_Err_make0(fr_Env __env, sys_Err_ref __self){ return; }
//void sys_Err_make1(fr_Env __env, sys_Err_ref __self, sys_Str msg){ return; }
void sys_Err_make2(fr_Env __env, sys_Err_ref __self, sys_Str msg, sys_Err_null cause){
    __self->msg = msg;
    __self->cause = cause;
    
    char *data = getTraceString();
    sys_Str str = (sys_Str)fr_newStrUtf8(__env, data);
    free(data);
    __self->traceToStr = str;
}

sys_Str sys_Err_msg0(fr_Env __env, sys_Err_ref __self) { return __self->msg; }
sys_Err_null sys_Err_cause0(fr_Env __env, sys_Err_ref __self) { return __self->cause; }
sys_Err sys_Err_trace0(fr_Env __env, sys_Err_ref __self) {
    printf("%s", fr_getStrUtf8(__env, __self->traceToStr, NULL));
    return __self;
}
sys_Str sys_Err_traceToStr0(fr_Env __env, sys_Err_ref __self) { return __self->traceToStr; }
sys_Str sys_Err_toStr0(fr_Env __env, sys_Err_ref __self) { return __self->msg; }
