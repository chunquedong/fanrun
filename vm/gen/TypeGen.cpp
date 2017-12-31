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
#include <stdlib.h>

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
    if (name == "sys_Obj" || baseName == "sys_Obj") {
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
    genTypeInit(printer);
    printer->newLine();
}

void TypeGen::genVTable(Printer *printer) {
    
    printer->println("struct %s_vtable {", name.c_str());
    
    printer->indent();
    
    std::string baseName = podGen->getTypeRefName(type->meta.base);
    
    if (name == "sys_Obj") {
        printer->println("struct fr_Class_ super__;");
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
    
    printer->println("fr_Class %s_class__(fr_Env __env);", name.c_str());
}

void TypeGen::genTypeMetadata(Printer *printer) {
    FTypeRef &typeRef = type->c_pod->typeRefs[type->meta.self];
    std::string &rawTypeName = type->c_pod->names[typeRef.typeName];
    printer->println("((fr_Class)vtable)->name = \"%s\";", rawTypeName.c_str());
    
    printer->println("((fr_Class)vtable)->allocSize = sizeof(struct %s_struct);", name.c_str());
    
    std::string baseName = podGen->getTypeRefName(type->meta.base);
    printer->println("((fr_Class)vtable)->base = (fr_Class)%s_class__(__env);", baseName.c_str());
    
    printer->println("((fr_Class)vtable)->fieldCount = %d;", type->fields.size());
    
    printer->println("((fr_Class)vtable)->methodCount = %d;", type->methods.size());
}

void TypeGen::genVTableInit(Printer *printer) {
    printer->println("void %s_initVTable(fr_Env __env, struct %s_vtable *vtable) {", name.c_str(), name.c_str());
    
    printer->indent();
    
    std::string baseName = podGen->getTypeRefName(type->meta.base);
    
    bool isRootType = false;
    if (name == "sys_Obj") {
        isRootType = true;
        printer->println("fr_VTable_init(__env, &vtable->super__);");
    } else {
        printer->println("%s_initVTable(__env, &vtable->super__);", baseName.c_str());
    }
    
    std::string base;
    int minxinSize = (int)type->meta.mixin.size();
    if (minxinSize > 10) {
        printf("ERROR: too many mixin size %d > MAX_INTERFACE_SIZE\n", minxinSize);
        abort();
    }
    for (int i=0; i<minxinSize; ++i) {
        base = podGen->getTypeRefName(type->meta.mixin[i]);
        printer->println("%s_initVTable(__env, &vtable->%s_super__);", base.c_str(), base.c_str());
        printer->println("((fr_Class)vtable)->interfaceVTableMap[%d].type = %s_class__(__env);"
                         , i, base.c_str());
        printer->println("((fr_Class)vtable)->interfaceVTableMap[%d].vtable = &vtable->%s_super__;"
                         , i, base.c_str());
    }
    
    printer->println("((fr_Class)vtable)->mixinCount = %d;", minxinSize);
    
    genTypeMetadata(printer);
    
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
            if ((method->flags & FFlags::Override) == 0) {
                continue;
            }
            std::string rawMethodName = podGen->pod->names[method->name];
            if (name == "sys_Type" && rawMethodName == "make") {
                continue;
            }
            
            MethodGen gmethod(this, method);
            genOverrideVTable(type->meta.base, rawMethodName, printer, gmethod, "vtable->");
        }
    }
    
    printer->unindent();
    printer->println("};");
}

void TypeGen::genTypeInit(Printer *printer) {
    genVTableInit(printer);
    
    printer->println("fr_Class %s_class__(fr_Env __env) {", name.c_str());
    printer->indent();
    
    printer->println("static struct %s_vtable *%s_class_instance = NULL;", name.c_str(), name.c_str());
    
    printer->println("if (%s_class_instance == NULL) {", name.c_str());
    printer->indent();
    printer->println("%s_class_instance = (struct %s_vtable*)"
                     "malloc(sizeof(struct %s_vtable));"
                     , name.c_str(), name.c_str(), name.c_str());
    printer->println("%s_initVTable(__env, %s_class_instance);", name.c_str(), name.c_str());
    
    for (int i=0; i<type->methods.size(); ++i) {
        FMethod *method = &type->methods[i];
        std::string mname = FCodeUtil::getIdentifierName(podGen->pod, method->name);
        if (mname == "static__init") {
            printer->println("%s_static__init0(__env);", name.c_str());
        }
    }
    
    printer->unindent();
    printer->println("}");
    printer->println("return %s_class_instance;", name.c_str());
    printer->unindent();
    printer->println("}");
}

void TypeGen::genOverrideVTable(uint16_t tid, std::string &rawMethodName
                                , Printer *printer, MethodGen &gmethod, std::string from) {
    FTypeRef &typeRef = podGen->pod->typeRefs[tid];
    std::string &podName = podGen->pod->names[typeRef.podName];
    std::string &typeName = podGen->pod->names[typeRef.typeName];
    FPod *tpod = podGen->podMgr->findPod(podName);
    FType *ttype = tpod->c_typeMap[typeName];
    
    auto found = ttype->c_methodMap.find(rawMethodName);
    
    if (found != ttype->c_methodMap.end()) {
        if ((found->second->flags & FFlags::Private)) {
            return;
        }
        
        for (int j=gmethod.beginDefaultParam; j<=gmethod.method->paramCount; ++j) {
            printer->println("%ssuper__.%s%d = %s_%s%d;", from.c_str()
                             , gmethod.name.c_str(),
                             j, name.c_str(), gmethod.name.c_str(), j);
        }
    }
    if (podName == "sys" && typeName == "Obj") return;
    genOverrideVTable(ttype->meta.base, rawMethodName, printer, gmethod, from + "super__.");
    
    for (int i=0; i<type->meta.mixin.size(); ++i) {
        uint16_t mixin = type->meta.mixin[i];
        if (mixin == tid) continue;
        std::string base = podGen->getTypeRefName(mixin);
        from  = from + base + "_";
        genOverrideVTable(mixin, rawMethodName, printer, gmethod, from);
    }
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

void TypeGen::genMethodWrap(Printer *printer) {
    for (int i=0; i<type->methods.size(); ++i) {
        FMethod *method = &type->methods[i];
        if ((method->flags & FFlags::Abstract) != 0) {
            continue;
        }
        MethodGen gmethod(this, method);
        gmethod.genRegisterWrap(printer);
    }
}

void TypeGen::genMethodRegister(Printer *printer) {
    for (int i=0; i<type->methods.size(); ++i) {
        FMethod *method = &type->methods[i];
        if ((method->flags & FFlags::Abstract) != 0) {
            continue;
        }
        MethodGen gmethod(this, method);
        gmethod.genRegister(printer);
    }
}

void TypeGen::genMethodStub(Printer *printer) {
    for (int i=0; i<type->methods.size(); ++i) {
        FMethod *method = &type->methods[i];
        if ((type->meta.flags & FFlags::Native) != 0
            || (method->flags & FFlags::Native) != 0
            || (method->flags & FFlags::Abstract) != 0) {
            continue;
        }
        MethodGen gmethod(this, method);
        gmethod.genStub(printer);
    }
    printer->println("struct %s_vtable *%s_class__(fr_Env __env) {", name.c_str(), name.c_str());
    printer->indent();
    printer->println("return (struct %s_vtable*)fr_findType(__env, \"%s\");"
                     , name.c_str(), name.c_str());
    printer->unindent();
    printer->println("}");
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
            printer->println("%s %s_%s;", typeName.c_str(), this->name.c_str(), name.c_str());
        } else {
            printer->println("%s %s_%s = 0;", typeName.c_str(), this->name.c_str(), name.c_str());
        }
        
    }
}

