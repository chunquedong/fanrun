//
//  DefaultParam.hpp
//  vm
//
//  Created by yangjiandong on 10/25/15.
//  Copyright © 2015 chunquedong. All rights reserved.
//

#ifndef DefaultParam_hpp
#define DefaultParam_hpp

#include <stdio.h>
#include "vm.h"
#include "FType.h"

class Env;

class DefaultParam {
public:
    static void initDefaultParam(Env *context, int paramCount, FMethod *method);
private:
    static bool getDefaultParam(Env *context, int index,
                    FMethodVar &var, fr_TagValue &val, FMethod *method);
};

#endif /* DefaultParam_hpp */
