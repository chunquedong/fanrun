//
//  sys_native.h
//  run
//
//  Created by yangjiandong on 2017/12/17.
//  Copyright © 2017年 yangjiandong. All rights reserved.
//

#ifndef sys_native_h
#define sys_native_h


/////////////////////////////////
#ifdef  __cplusplus
extern  "C" {
#endif
    
struct sys_Obj_struct {
    struct GcObj_ header;
};

struct sys_Int_struct {
    struct sys_Obj_struct super__;
    int64_t _val;
};
struct sys_Float_struct {
    struct sys_Obj_struct super__;
    double _val;
};
struct sys_Bool_struct {
    struct sys_Obj_struct super__;
    bool _val;
};


struct sys_Err_struct {
    struct sys_Obj_struct super__;
    sys_Str msg;
    sys_Err_null cause;
    sys_Str traceToStr;
};

struct sys_Num_struct {
    struct sys_Obj_struct super__;
};

struct sys_Str_struct {
    struct sys_Obj_struct super__;
    const wchar_t *data;
    size_t size;
    
    size_t hashCode;
    const char *utf8;
};

struct sys_StrBuf_struct {
    struct sys_Obj_struct super__;
    sys_Int capacity;
    wchar_t *data;
    sys_Int size;
};

struct sys_ByteArray_struct {
    struct sys_Obj_struct super__;
    sys_Int size;
    char *data;
};
/*
struct sys_IntArray_struct {
    struct sys_Obj_struct super__;
    sys_Int size;
    sys_Int *data;
};

struct sys_FloatArray_struct {
    sys_Int size;
    sys_Float *data;
};
*/
struct sys_ObjArray_struct {
    struct sys_Obj_struct super__;
    sys_Int size;
    fr_Obj *data;
};
/*
struct sys_BoolArray_struct {
};
*/
struct sys_Func_struct {
    struct sys_Obj_struct super__;
};

struct sys_Type_struct {
    struct sys_Obj_struct super__;
    fr_Class rawClass;
};

struct sys_Void_struct {
    struct sys_Obj_struct super__;
};

#ifdef  __cplusplus
} //end "C"
#endif

#endif /* sys_native_h */
