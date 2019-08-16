//
//  IRClass.hpp
//  vm
//
//  Created by yangjiandong on 2019/8/16.
//  Copyright © 2019 yangjiandong. All rights reserved.
//

#ifndef IRClass_hpp
#define IRClass_hpp

#include <stdio.h>
#include "IRMethod.h"
#include <map>

class IRType;

class IRVirtualMethod {
public:
    IRType *parent;
    FMethod *method;
    
    IRVirtualMethod();
    
    IRVirtualMethod(IRType *parent, FMethod *method);
    
    bool isAbstract();
    bool fromObj();
};

class IRVTable {
public:
    IRType *type;
    IRType *owner;
    
    IRVTable(IRType *owner, IRType *type);
    
    std::vector<IRVirtualMethod> functions;
};

class IRModule {
public:
    std::map<std::string, IRType*> types;
    IRType *getType(FPod *pod, uint16_t typeRefId);
};



class IRType {
    bool isVTableInited;
public:
    FType *ftype;
    FPod *fpod;
    IRModule *module;
    
    std::vector<IRVTable*> vtables;
    
    std::map<std::string, IRVirtualMethod> resolvedMethods;
    
    std::map<IRType*, int> allMinxin;
    
public:
    IRType(FType *ftype);
    void initVTable();
    
private:
    void resolveMethod();
    void inheritMethod(IRType *base, bool isMixin);
    void setVTable(IRVTable *vtable);
    void initMixinVTable();
    void initMainVTable();
};

#endif /* IRClass_hpp */
