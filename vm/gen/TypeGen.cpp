//
//  GenType.c
//  gen
//
//  Created by yangjiandong on 2017/9/10.
//  Copyright © 2017年 yangjiandong. All rights reserved.
//

#include "TypeGen.h"
#include "escape.h"
#include "PodGen.hpp"
#include "MethodGen.h"

TypeGen::TypeGen(PodGen *podGen, FType *type)
: podGen(podGen), type(type) {
    name = podGen->getTypeRefName(type->meta.self);
}

void TypeGen::genTypeDeclare(Printer *printer) {
    printer->println("struct %s_struct;", name.c_str());
    printer->println("typedef struct %s_struct *%s_null;", name.c_str(), name.c_str());
    if (isValType()) {
        //printer->println("typedef %s_struct %s;", name.c_str(), name.c_str());
    } else {
        printer->println("typedef struct %s_struct *%s;", name.c_str(), name.c_str());
    }
}

void TypeGen::genStruct(Printer *printer) {
    
    std::string baseName = podGen->getTypeRefName(type->meta.base);
    
    printer->println("struct %s_struct {", name.c_str());
    
    printer->indent();
    if (name == "sys_Obj") {
        printer->println("fr_Obj super__;");
    } else {
        printer->println("struct %s_struct super__;", baseName.c_str());
    }
    /*
    std::string base;
    for (int i=0; i<type->meta.mixin.size(); ++i) {
        base = podGen->getTypeRefName(type->meta.mixin[i]);
        printer->println("struct %s_struct %s_super__;", base.c_str(), base.c_str());
    }
    */
    genField(printer);
    printer->unindent();
    
    printer->println("};");
}

void TypeGen::genInline(Printer *printer) {
    
}

void TypeGen::genImple(Printer *printer) {
    for (int i=0; i<type->methods.size(); ++i) {
        FMethod *method = &type->methods[i];
        
        if ((type->meta.flags & FFlags::Native) != 0
            || (method->flags & FFlags::Native) != 0) {
            continue;
        }
        
        MethodGen gmethod(this, method);
        gmethod.genPrototype(printer, false);
        printer->printf(" {");
        printer->newLine();
        gmethod.genCode(printer);
        printer->newLine();
        printer->printf("}");
        printer->newLine();
        printer->newLine();
    }
    genVTableInit(printer);
    printer->newLine();
}

void TypeGen::genVTable(Printer *printer) {
    
    printer->println("struct %s_vtable {", name.c_str());
    
    printer->indent();
    
    std::string baseName = podGen->getTypeRefName(type->meta.base);
    
    if (name == "sys_Obj") {
        printer->println("fr_Type supper__;");
    } else {
        printer->println("struct %s_vtable super__;", baseName.c_str());
    }
    
    std::string base;
    for (int i=0; i<type->meta.mixin.size(); ++i) {
        base = podGen->getTypeRefName(type->meta.mixin[i]);
        printer->println("struct %s_vtable %s_super__;", base.c_str(), base.c_str());
    }
    
    for (int i=0; i<type->methods.size(); ++i) {
        FMethod *method = &type->methods[i];
        if ((method->flags & FFlags::Virtual) == 0) {
            //TODO: why call novirtual function by callVirutal instruct?
            //continue;
        }
        MethodGen gmethod(this, method);
        gmethod.genPrototype(printer, true);
        printer->printf(";");
        printer->newLine();
    }
    
    printer->unindent();
    
    printer->println("};");
}

void TypeGen::genVTableInit(Printer *printer) {
    printer->println("void %s_initVTable(struct %s_vtable *vtable) {", name.c_str(), name.c_str());
    
    printer->indent();
    
    std::string baseName = podGen->getTypeRefName(type->meta.base);
    
    if (name == "sys_Obj") {
        printer->println("VTable_init(&vtable->supper__);");
    } else {
        printer->println("%s_initVTable(&vtable->super__);", baseName.c_str());
    }
    
    std::string base;
    for (int i=0; i<type->meta.mixin.size(); ++i) {
        base = podGen->getTypeRefName(type->meta.mixin[i]);
        printer->println("%s_initVTable(&vtable->%s_super__);", base.c_str(), base.c_str());
    }
    
    for (int i=0; i<type->methods.size(); ++i) {
        FMethod *method = &type->methods[i];
        if ((method->flags & FFlags::Virtual) == 0) {
            //continue;
        }
        MethodGen gmethod(this, method);
        printer->println("vtable->%s = %s_%s;", gmethod.name.c_str(), baseName.c_str(), gmethod.name.c_str());
    }
    
    for (int i=0; i<type->methods.size(); ++i) {
        FMethod *method = &type->methods[i];
        if ((method->flags & FFlags::Virtual) == 0) {
            //continue;
        }
        std::string raw_name = podGen->pod->names[method->name];
        
        if (isOverrideFrom(type->meta.base, raw_name)) {
            MethodGen gmethod(this, method);
            printer->println("vtable->supper__->%s = %s_%s;", gmethod.name.c_str(), baseName.c_str(), gmethod.name.c_str());
        }
        for (int i=0; i<type->meta.mixin.size(); ++i) {
            if (isOverrideFrom(type->meta.mixin[i], raw_name)) {
                MethodGen gmethod(this, method);
                std::string base = podGen->getTypeRefName(type->meta.mixin[i]);
                printer->println("vtable->%s_supper__->%s = %s_%s;", base.c_str(), gmethod.name.c_str(), baseName.c_str(), gmethod.name.c_str());
            }
        }
    }
    
    printer->unindent();
    printer->println("};");
}

bool TypeGen::isOverrideFrom(uint16_t tid, std::string &name) {
    FTypeRef &typeRef = podGen->pod->typeRefs[tid];
    std::string &podName = podGen->pod->names[typeRef.podName];
    std::string &typeName = podGen->pod->names[typeRef.typeName];
    FPod *tpod = podGen->podMgr->findPod(podName);
    FType *ttype = tpod->c_typeMap[typeName];
    return ttype->c_methodMap.find(name) != ttype->c_methodMap.end();
}

void TypeGen::genMethodDeclare(Printer *printer) {
    for (int i=0; i<type->methods.size(); ++i) {
        FMethod *method = &type->methods[i];
        MethodGen gmethod(this, method);
        gmethod.genPrototype(printer, false);
        printer->printf(";");
        printer->newLine();
    }
}

void TypeGen::genField(Printer *printer) {
    for (int i=0; i<type->fields.size(); ++i) {
        FField *field = &type->fields[i];
        auto name = podGen->getIdentifierName(field->name);
        auto typeName = podGen->getTypeRefName(field->type);
        printer->println("%s %s;", typeName.c_str(), name.c_str());
    }
}

bool TypeGen::isValType() {
    if (name == "sys_Int"
        || name == "sys_Float"
        || name == "sys_Bool") {
        return true;
    }
    return false;
}


