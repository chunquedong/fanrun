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
    isValueType = FCodeUtil::isValueType(type);
}

void TypeGen::genTypeDeclare(Printer *printer) {
    printer->println("struct %s_struct;", name.c_str());
    printer->println("typedef struct %s_struct *%s_ref;", name.c_str(), name.c_str());
    printer->println("typedef %s_ref %s_null;", name.c_str(), name.c_str());
    if (isValueType) {
        if (!FCodeUtil::isBuildinValType(type)) {
            printer->println("typedef struct %s_struct %s_val;", name.c_str(), name.c_str());
        }
        printer->println("typedef %s_val %s;", name.c_str(), name.c_str());
    } else {
        printer->println("typedef %s_ref %s;", name.c_str(), name.c_str());
    }
}

void TypeGen::genStruct(Printer *printer) {
    
    if (FCodeUtil::isBuildinValType(type)) return;
    
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
    
    //if (name != "testlib_GcTest") return;
    
    genStaticField(printer, false);
    printer->newLine();
    for (int i=0; i<type->methods.size(); ++i) {
        FMethod *method = &type->methods[i];
        
        MethodGen gmethod(this, method);
        
        gmethod.genImples(printer);
        
        if (!gmethod.isStatic && isValueType) {
            gmethod.genImplesToVal(printer);
        }
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
    
    //printer->println("fr_Class %s_class__(fr_Env __env);", name.c_str());
    printer->println("extern fr_Class %s_class__;", name.c_str());
    
    printer->println("void %s_initVTable(fr_Env __env, struct %s_vtable *vtable);"
                     , name.c_str(), name.c_str());
}

void TypeGen::genTypeMetadata(Printer *printer) {
    FTypeRef &typeRef = type->c_pod->typeRefs[type->meta.self];
    std::string &rawTypeName = type->c_pod->names[typeRef.typeName];
    printer->println("((fr_Class)vtable)->name = \"%s\";", rawTypeName.c_str());
    
    printer->println("((fr_Class)vtable)->allocSize = sizeof(struct %s_struct);", name.c_str());
    
    std::string baseName = podGen->getTypeRefName(type->meta.base);
    //sys::Obj's base class is NULL
    if (baseName.size() == 0) {
        printer->println("((fr_Class)vtable)->base = (fr_Class)NULL;");
    }
    else {
        printer->println("((fr_Class)vtable)->base = (fr_Class)%s_class__;", baseName.c_str());
    }
    printer->println("((fr_Class)vtable)->fieldCount = %d;", type->fields.size());
    printer->println("((fr_Class)vtable)->fieldList = (struct fr_Field*)malloc(sizeof(struct fr_Field)*%d);", type->fields.size());
    //int offset = 0;
    for (int i=0; i<type->fields.size(); ++i) {
        FField &field = type->fields[i];
        std::string fieldName = type->c_pod->names[field.name];
        std::string fieldIdName = fieldName;
        FCodeUtil::escapeIdentifierName(fieldIdName);
        
        printer->println("((fr_Class)vtable)->fieldList[%d].name = \"%s\";", i, fieldName.c_str());
        std::string typeName = podGen->getTypeRefName(field.type);
        printer->println("((fr_Class)vtable)->fieldList[%d].type = \"%s\";", i, typeName.c_str());
    
        bool isValType = isValueType;
        printer->println("((fr_Class)vtable)->fieldList[%d].isValType = %s;", i, isValType ? "true" : "false");
        
        if (field.flags & FFlags::Static) {
            printer->println("((fr_Class)vtable)->fieldList[%d].isStatic = true;", i);
            printer->println("((fr_Class)vtable)->fieldList[%d].pointer = (void*)(&%s_%s);"
                             , i, name.c_str(), fieldIdName.c_str());
        } else {
            printer->println("((fr_Class)vtable)->fieldList[%d].isStatic = false;", i);
            
            printer->println("((fr_Class)vtable)->fieldList[%d].offset = offsetof(struct %s_struct, %s);"
                         , i, name.c_str(), fieldIdName.c_str());
        }
    }
    
    printer->println("((fr_Class)vtable)->methodCount = %d;", type->methods.size());
    
    if (baseName == "sys_Func") {
        auto itr = type->c_methodMap.find("doCall");
        if (itr != type->c_methodMap.end()) {
            int funcArity = itr->second->paramCount;
            printer->println("((fr_Class)vtable)->funcArity = %d;", funcArity);
        }
    }
    
    printer->println("fr_registerClass(__env, \"%s\", \"%s\", (fr_Class)%s_class__);"
                     , podGen->podName.c_str(), rawTypeName.c_str(), name.c_str());
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
        printer->println("((fr_Class)vtable)->interfaceVTableMap[%d].type = %s_class__;"
                         , i, base.c_str());
        printer->println("((fr_Class)vtable)->interfaceVTableMap[%d].vtable = (fr_Class)&vtable->%s_super__;"
                         , i, base.c_str());
    }
    
    printer->println("((fr_Class)vtable)->mixinCount = %d;", minxinSize);
    
    //set self virutal func
    for (int i=0; i<type->methods.size(); ++i) {
        FMethod *method = &type->methods[i];
        if ((method->flags & FFlags::Ctor) != 0 || (method->flags & FFlags::Static) != 0) {
            continue;
        }
        MethodGen gmethod(this, method);
        int j = method->paramCount;
        if ((method->flags & FFlags::Abstract) != 0) {
            printer->println("vtable->%s%d = NULL;", gmethod.name.c_str(),j);
        } else {
            printer->println("vtable->%s%d = %s_%s%d;", gmethod.name.c_str(),
                             j, name.c_str(), gmethod.name.c_str(), j);
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
            genOverrideVTable(type, rawMethodName, printer, gmethod, "vtable->");
        }
    }
    
    genTypeMetadata(printer);
    
    printer->unindent();
    printer->println("};");
}

void TypeGen::genTypeInit(Printer *printer) {
    genVTableInit(printer);
    
    printer->println("fr_Class %s_class__ = NULL;", name.c_str());
    /*
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
     */
}

void TypeGen::genOverrideVTable(FType *type, std::string &rawMethodName
                                , Printer *printer, MethodGen &gmethod, std::string from) {
    /*
    uint16_t tid = type->meta.base;
    FPod *pod = type->c_pod;
    FTypeRef &typeRef = pod->typeRefs[tid];
    std::string &podName = pod->names[typeRef.podName];
    std::string &typeName = pod->names[typeRef.typeName];
    
    FPod *tpod = podGen->podMgr->findPod(podName);
    FType *ttype = tpod->c_typeMap[typeName];
    */
    FType *ttype = FCodeUtil::getFTypeFromTypeRef(type->c_pod, type->meta.base);
    if (ttype == NULL) return;
    
    auto found = ttype->c_methodMap.find(rawMethodName);
    
    if (found != ttype->c_methodMap.end()) {
        if ((found->second->flags & FFlags::Private)) {
            return;
        }
        int j = gmethod.method->paramCount;
        //FMethod *parentMethod = found->second;
        if (gmethod.method->flags & FFlags::Abstract) {
            printer->println("*((int**)(&(%ssuper__.%s%d))) = NULL;", from.c_str()
                             , gmethod.name.c_str(), j);
        }
        else {
            printer->println("*((int**)(&(%ssuper__.%s%d))) = (int*)%s_%s%d;", from.c_str()
                             , gmethod.name.c_str(), j
                             , name.c_str(), gmethod.name.c_str(), j);
        }
    }
    //if (podName == "sys" && typeName == "Obj") return;
    genOverrideVTable(ttype, rawMethodName, printer, gmethod, from + "super__.");
    
    for (int i=0; i<type->meta.mixin.size(); ++i) {
        uint16_t mixin = type->meta.mixin[i];
        if (mixin == type->meta.base) continue;
        
        //from  = from + base + "_";
        FType *mixinType = FCodeUtil::getFTypeFromTypeRef(type->c_pod, mixin);
        std::string base = mixinType->c_name;
        genOverrideVTable(mixinType, rawMethodName, printer, gmethod, from + base + "_");
    }
}

void TypeGen::genMethodDeclare(Printer *printer) {
    for (int i=0; i<type->methods.size(); ++i) {
        FMethod *method = &type->methods[i];
        MethodGen gmethod(this, method);
        gmethod.genDeclares(printer, false, false);
        
        bool isStatic = (method->flags & FFlags::Static);
        if (!isStatic && isValueType) {
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
        /*
        if ((type->meta.flags & FFlags::Native) != 0
            || (method->flags & FFlags::Native) != 0
            || (method->flags & FFlags::Abstract) != 0) {
            continue;
        }
         */
        if ((method->flags & FFlags::Native) != 0) {
            continue;
        }
        if ((type->meta.flags & FFlags::Native) != 0
            && (method->flags & FFlags::Overload) == 0) {
            continue;
        }
        MethodGen gmethod(this, method);
        gmethod.genStub(printer);
    }
    /*
    printer->println("struct %s_vtable *%s_class__(fr_Env __env) {", name.c_str(), name.c_str());
    printer->indent();
    printer->println("return (struct %s_vtable*)fr_findType(__env, \"%s\");"
                     , name.c_str(), name.c_str());
    printer->unindent();
    printer->println("}");
     */
}

void TypeGen::genField(Printer *printer) {
    for (int i=0; i<type->fields.size(); ++i) {
        FField *field = &type->fields[i];
        if ((field->flags & FFlags::Static) != 0) {
            continue;
        }
        auto name = FCodeUtil::getIdentifierName(podGen->pod, field->name);
        std::string typeName = podGen->getTypeRefName(field->type);
        if (typeName == "sys_Int") {
            /*TODO
            for (FAttr *attr : field->attrs) {
                FFacets *facets = dynamic_cast<FFacets*>(attr);
                if (facets) {
                    for (FFacet &facet : facets->facets) {
                        std::string tname = FCodeUtil::getTypeRefName(podGen->pod, facet.type, false);
                        if (tname == "sys_T8") {
                            typeName = "int8_t";
                            break;
                        }
                        else if (tname == "sys_T16") {
                            typeName = "int16_t";
                            break;
                        }
                        else if (tname == "sys_T32") {
                            typeName = "int32_t";
                            break;
                        }
                        else if (tname == "sys_T64") {
                            typeName = "int64_t";
                            break;
                        }
                    }
                }
            }
             */
        }
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
            if (FCodeUtil::isBuildinVal(typeName)) {
                printer->println("%s %s_%s = 0;", typeName.c_str(), this->name.c_str(), name.c_str());
            } else {
                printer->println("%s %s_%s;", typeName.c_str(), this->name.c_str(), name.c_str());
            }
        }
    }
}

