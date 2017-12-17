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
#include "FCodeUtil.hpp"

TypeGen::TypeGen(PodGen *podGen, FType *type)
: podGen(podGen), type(type) {
    name = podGen->getTypeRefName(type->meta.self);
}

void TypeGen::genTypeDeclare(Printer *printer) {
    printer->println("struct %s_struct;", name.c_str());
    printer->println("typedef struct %s_struct *%s_ref;", name.c_str(), name.c_str());
    printer->println("typedef %s_ref %s_null;", name.c_str(), name.c_str());
    if (FCodeUtil::isValType(name)) {
        if (podGen->podName != "sys") {
            printer->println("typedef struct %s_struct %s_val;", name.c_str(), name.c_str());
        }
        printer->println("typedef %s_val %s;", name.c_str(), name.c_str());
    } else {
        printer->println("typedef %s_ref %s;", name.c_str(), name.c_str());
    }
}

void TypeGen::genStruct(Printer *printer) {
    
    if (FCodeUtil::isValType(name) && podGen->podName == "sys") return;
    
    if ((type->meta.flags & FFlags::Native) != 0) {
        printer->println("//native struct %s_struct", name.c_str());
        return;
    }
    
    std::string baseName = podGen->getTypeRefName(type->meta.base);
    
    printer->println("struct %s_struct {", name.c_str());
    
    printer->indent();
    if (name == "sys_Obj") {
        //printer->println("fr_Obj super__;");
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
    genStaticField(printer, false);
    printer->newLine();
    for (int i=0; i<type->methods.size(); ++i) {
        FMethod *method = &type->methods[i];
        
        if ((type->meta.flags & FFlags::Native) != 0
            || (method->flags & FFlags::Native) != 0
            || (method->flags & FFlags::Abstract) != 0) {
            continue;
        }
        
        MethodGen gmethod(this, method);
        gmethod.genImples(printer, false);
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
        printer->println("fr_Type super__;");
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
        if ((method->flags & FFlags::Ctor) != 0 || (method->flags & FFlags::Static) != 0) {
            //TODO: why call novirtual function by callVirutal instruct?
            continue;
        }
        MethodGen gmethod(this, method);
        gmethod.genDeclares(printer, true, false);
        //printer->printf(";");
        //printer->newLine();
    }
    
    printer->unindent();
    
    printer->println("};");
}

void TypeGen::genVTableInit(Printer *printer) {
    printer->println("void %s_initVTable(struct %s_vtable *vtable) {", name.c_str(), name.c_str());
    
    printer->indent();
    
    std::string baseName = podGen->getTypeRefName(type->meta.base);
    
    bool isRootType = false;
    if (name == "sys_Obj") {
        isRootType = true;
        printer->println("fr_VTable_init(&vtable->super__);");
    } else {
        printer->println("%s_initVTable(&vtable->super__);", baseName.c_str());
    }
    
    std::string base;
    for (int i=0; i<type->meta.mixin.size(); ++i) {
        base = podGen->getTypeRefName(type->meta.mixin[i]);
        printer->println("%s_initVTable(&vtable->%s_super__);", base.c_str(), base.c_str());
    }
    
    //set self virutal func
    for (int i=0; i<type->methods.size(); ++i) {
        FMethod *method = &type->methods[i];
        if ((method->flags & FFlags::Ctor) != 0 || (method->flags & FFlags::Static) != 0) {
            continue;
        }
        MethodGen gmethod(this, method);
        for (int j=gmethod.beginDefaultParam; j<=method->paramCount; ++j) {
            
            if ((method->flags & FFlags::Abstract) != 0) {
                printer->println("vtable->%s%d = NULL;", gmethod.name.c_str(),j);
            } else {
                printer->println("vtable->%s%d = %s_%s%d;", gmethod.name.c_str(),
                                 j, name.c_str(), gmethod.name.c_str(), j);
            }
        }
    }
    
    //override base and mixin
    if (!isRootType) {
        for (int i=0; i<type->methods.size(); ++i) {
            FMethod *method = &type->methods[i];
            if ((method->flags & FFlags::Ctor) != 0 || (method->flags & FFlags::Static) != 0) {
                continue;
            }
            std::string raw_name = podGen->pod->names[method->name];
            if (name == "sys_Type" && raw_name == "make") {
                continue;
            }
            
            if (isOverrideFrom(type->meta.base, raw_name)) {
                MethodGen gmethod(this, method);
                for (int j=gmethod.beginDefaultParam; j<=method->paramCount; ++j) {
                    printer->println("vtable->super__.%s%d = %s_%s%d;", gmethod.name.c_str(),
                                     j, name.c_str(), gmethod.name.c_str(), j);
                }
            }
            for (int i=0; i<type->meta.mixin.size(); ++i) {
                if (isOverrideFrom(type->meta.mixin[i], raw_name)) {
                    MethodGen gmethod(this, method);
                    std::string base = podGen->getTypeRefName(type->meta.mixin[i]);
                    for (int j=gmethod.beginDefaultParam; j<=method->paramCount; ++j) {
                        printer->println("vtable->%s_super__.%s%d = %s_%s%d;", base.c_str(), gmethod.name.c_str(),
                                    j, name.c_str(), gmethod.name.c_str(), j);
                    }
                }
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
        gmethod.genDeclares(printer, false, false);
        
        bool isStatic = (method->flags & FFlags::Static);
        if (!isStatic && FCodeUtil::isValType(name)) {
            gmethod.genDeclares(printer, false, true);
        }
        
        //printer->newLine();
    }
}

void TypeGen::genField(Printer *printer) {
    for (int i=0; i<type->fields.size(); ++i) {
        FField *field = &type->fields[i];
        if ((field->flags & FFlags::Static) != 0) {
            continue;
        }
        auto name = FCodeUtil::getIdentifierName(podGen->pod, field->name);
        auto typeName = podGen->getTypeRefName(field->type);
        printer->println("%s %s;", typeName.c_str(), name.c_str());
    }
}

void TypeGen::genStaticField(Printer *printer, bool isExtern) {
    for (int i=0; i<type->fields.size(); ++i) {
        FField *field = &type->fields[i];
        if ((field->flags & FFlags::Static) == 0) {
            continue;
        }
        auto name = FCodeUtil::getIdentifierName(podGen->pod, field->name);
        auto typeName = podGen->getTypeRefName(field->type);
        if (isExtern) {
            printer->printf("extern ");
        }
        printer->println("%s %s_%s;", typeName.c_str(), this->name.c_str(), name.c_str());
    }
}

