//
//  common.h
//  gen
//
//  Created by yangjiandong on 2017/9/16.
//  Copyright © 2017年 yangjiandong. All rights reserved.
//

#ifndef common_h
#define common_h


/**
 * fr_Value union type
 */
typedef enum fr_ValueType_ {
    fr_vtOther, //unsed
    fr_vtObj,
    fr_vtInt,
    fr_vtFloat,
    fr_vtBool,
    fr_vtHandle,
} fr_ValueType;

typedef int64_t fr_Int;
typedef double fr_Float;
typedef bool fr_Bool;
struct fr_Obj_;
typedef struct fr_Obj_ *fr_Obj;
typedef fr_Obj* fr_Handle;

/**
 * union type, store any thing
 */
typedef union fr_Value_ {
    fr_Int i;
    fr_Float f;
    fr_Obj o;
    fr_Handle h;
    fr_Bool b;
} fr_Value;

/**
 * fr_Value type with a type tag
 */
typedef struct fr_TagValue_ {
    fr_Value any;
    fr_ValueType type;
} fr_TagValue;



#endif /* common_h */
