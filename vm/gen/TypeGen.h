//
//  GenType.h
//  gen
//
//  Created by yangjiandong on 2017/9/10.
//  Copyright © 2017年 yangjiandong. All rights reserved.
//

#ifndef GenType_h
#define GenType_h

#include <stdio.h>
#include "PodLoader.h"
#include "Printer.h"

class PodGen;

class TypeGen {
public:
    PodGen *podGen;
    FType *type;
    int c_sortFlag;
public:
    std::string name;
public:
    TypeGen(PodGen *podGen, FType *type);
    
    void genTypeDeclare(Printer *printer);
    void genStruct(Printer *printer);
    void genVTable(Printer *printer);
    void genTypeInit(Printer *printer);
    void genMethodDeclare(Printer *printer);
    void genInline(Printer *printer);
    void genImple(Printer *printer);
    void genStaticField(Printer *printer, bool isExtern);
private:
    void genField(Printer *printer);
    void genTypeMetadata(Printer *printer);
    void genVTableInit(Printer *printer);
    bool isOverrideFrom(uint16_t tid, std::string &name);
    
};



#endif /* GenType_h */
