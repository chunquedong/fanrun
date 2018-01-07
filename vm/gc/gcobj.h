//
//  gcobj.h
//  gen
//
//  Created by yangjiandong on 2017/9/16.
//  Copyright © 2017年 yangjiandong. All rights reserved.
//

#ifndef gcobj_h
#define gcobj_h

#include "miss.h"
typedef struct GcObj_ {
    void *header;
} GcObj;

static const uint64_t headerTypeMask = ~((uint64_t)(3));
static const uint64_t headerMarkMask = ((uint64_t)(1));
static const uint64_t headerDirtyMask = ((uint64_t)(2));
#define gc_getType(obj) ((void*)(((uint64_t)((obj)->header)) & headerTypeMask))
#define gc_getMark(obj) (((uint64_t)((obj)->header)) & headerMarkMask)
#define gc_isDirty(obj) (((uint64_t)((obj)->header)) & headerDirtyMask)

inline void setBitField(uint64_t *target, int pos, int val) {
    if (val) {
        *target |= (1<<pos);
    } else {
        *target &= (~(1<<pos));
    }
}

inline void gc_setDirty(GcObj *obj, int dirty) {
    setBitField((uint64_t *)(&(obj->header)), 1, dirty);
}
inline void gc_setMark(GcObj *obj, int marker) {
    setBitField((uint64_t *)(&(obj->header)), 0, marker);
}


#endif /* gcobj_h */
