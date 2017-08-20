//
// Copyright (c) 2017, chunquedong
// Licensed under the Apache Licene 2.0
//
//  Created by yangjiandong on 2017/8/20.
//

#ifndef Generator_hpp
#define Generator_hpp

#include <stdio.h>
#include "PodLoader.h"
#include "Printer.h"

class GType {
public:
    FPod *pod;
    FType *type;
    PodLoader *podMgr;

public:
    std::string name;
public:
    GType(PodLoader *podMgr, FPod *pod, FType *type);
    
    void genTypeDeclare(Printer *printer);
    void genStruct(Printer *printer);
    void genVTable(Printer *printer);
    void genMethodDeclare(Printer *printer);
    void genInline(Printer *printer);
    void genImple(Printer *printer);
private:
    void genField(Printer *printer);
    
public:
    std::string typeRefName(uint16_t tid);
    std::string getName(uint16_t nid);
    bool isValType();
};

struct GMethod {
    GType *parent;
    FMethod *method;
    std::string name;
    
    void genPrototype(Printer *printer, bool funcPtr);
    void genCode(Printer *printer);
};

class Generator {
public:
    std::string path;
    PodLoader *podMgr;
    
    void gen(std::string podName);
private:
    void genHeader(FPod *pod, Printer *printer);
    void genImple(FPod *pod, Printer *printer);
    void horizontalLine(Printer *printer, const char *name);
};

#endif /* Generator_hpp */
