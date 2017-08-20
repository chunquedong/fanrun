//
// Copyright (c) 2017, chunquedong
// Licensed under the Apache Licene 2.0
//
//  Created by yangjiandong on 2016/9/22.
//

#ifndef common_h
#define common_h

#include <stdio.h>
#include "miss.h"

CF_BEGIN

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

/**
 * internal type
 */
struct fr_ObjHeader;
typedef struct fr_ObjHeader FObj;

/**
 * typedef for Fantom
 */
typedef int64_t fr_Int;
typedef double fr_Float;
typedef bool fr_Bool;

/**
 * user client handle type
 */
typedef FObj **fr_Obj;

struct FType;
typedef struct FType *fr_Type;

struct FField;
typedef struct FField *fr_Field;

struct FMethod;
typedef struct FMethod *fr_Method;

/**
 * union type, store any thing
 */
typedef union fr_Value_ {
  fr_Int i;
  fr_Float f;
  FObj *o;
  fr_Obj h;
  fr_Bool b;
} fr_Value;

/**
 * fr_Value type with a type tag
 */
typedef struct fr_TagValue_ {
  fr_Value any;
  fr_ValueType type;
} fr_TagValue;

CF_END

#endif /*  */
