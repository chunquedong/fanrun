//
// Copyright (c) 2017, chunquedong
// Licensed under the Apache Licene 2.0
//
//  Created by yangjiandong on 2017/8/20.
//

#include "Generator.hpp"
#include "escape.h"
#include "IRMethod.h"

GType::GType(PodLoader *podMgr, FPod *pod, FType *type)
    : podMgr(podMgr), pod(pod), type(type) {
    name = typeRefName(type->meta.self);
}

void GType::genTypeDeclare(Printer *printer) {
    printer->println("struct %s_struct;", name.c_str());
    printer->println("typedef %s_struct *%s_null;", name.c_str(), name.c_str());
    if (isValType()) {
        //printer->println("typedef %s_struct %s;", name.c_str(), name.c_str());
    } else {
        printer->println("typedef %s_struct *%s;", name.c_str(), name.c_str());
    }
}

void GType::genStruct(Printer *printer) {
    
    std::string baseName = typeRefName(type->meta.base);
    
    printer->println("struct %s_struct {", name.c_str());
    
    printer->indent();
    printer->println("%s_struct super;", baseName.c_str());
    genField(printer);
    printer->unindent();
    
    printer->println("};");
}

void GType::genInline(Printer *printer) {
    
}

void GType::genImple(Printer *printer) {
    for (int i=0; i<type->methods.size(); ++i) {
        FMethod *method = &type->methods[i];
        GMethod gmethod;
        gmethod.method = method;
        gmethod.parent = this;
        gmethod.genPrototype(printer);
        printer->printf(" {");
        printer->newLine();
        gmethod.genCode(printer);
        printer->newLine();
        printer->printf("}");
        printer->newLine();
        printer->newLine();
    }
}

void GType::genMethodDeclare(Printer *printer) {
    for (int i=0; i<type->methods.size(); ++i) {
        FMethod *method = &type->methods[i];
        GMethod gmethod;
        gmethod.method = method;
        gmethod.parent = this;
        gmethod.genPrototype(printer);
        printer->printf(";");
        printer->newLine();
    }
}

void GType::genField(Printer *printer) {
    for (int i=0; i<type->fields.size(); ++i) {
        FField *field = &type->fields[i];
        auto name = getName(field->name);
        auto typeName = typeRefName(field->type);
        printer->println("%s %s;", typeName.c_str(), name.c_str());
    }
}

std::string GType::typeRefName(uint16_t tid) {
    FTypeRef &typeRef = pod->typeRefs[tid];
    std::string &podName = pod->names[typeRef.podName];
    std::string &typeName = pod->names[typeRef.typeName];
    std::string &sig = typeRef.signature;
    
    std::string res = podName + "_" + typeName;
    if (sig.size() > 0 && sig[sig.size()-1] == '?') {
        res += "_null";
    }
    
    escape(res);
    return res;
}

std::string GType::getName(uint16_t nid) {
    std::string name = pod->names[nid];
    escape(name);
    escapeKeyword(name);
    return name;
}

bool GType::isValType() {
    if (name == "sys_Int"
        || name == "sys_Float"
        || name == "sys_Bool") {
        return true;
    }
    return false;
}

void GMethod::genPrototype(Printer *printer) {
    name = parent->getName(method->name);
    auto typeName = parent->typeRefName(method->returnType);
    printer->printf("%s %s_%s(", typeName.c_str(), parent->name.c_str(), name.c_str());
    
    printer->printf("fr_Env __env");
    
    bool isStatic = (method->flags & FFlags::Static);
    if (!isStatic) {
        printer->printf(", %s __self", parent->name.c_str());
    }
    
    for (int j=0; j<method->paramCount; ++j) {
        FMethodVar &var = method->vars[j];
        auto var_name = parent->getName(var.name);
        auto var_typeName = parent->typeRefName(var.type);
        
        printer->printf(", %s %s", var_typeName.c_str(), var_name.c_str());
    }
    printer->printf(")");
}

void GMethod::genCode(Printer *printer) {
    IRMethod irMethod(parent->pod, method);
    irMethod.compile();
    irMethod.print(parent->podMgr, *printer, 1);
}



/////////////////////////////////////////////

void Generator::gen(std::string podName) {
    FPod *pod = podMgr->findPod(podName);
    if (!pod) {
        return;
    }
    
    std::string headerFile = path + podName + ".h";
    Printer headerPrinter(headerFile.c_str());
    genHeader(pod, &headerPrinter);
    
    std::string impleFile = path + podName + ".c";
    Printer implePrinter(impleFile.c_str());
    genImple(pod, &implePrinter);
}

void Generator::horizontalLine(Printer *printer, const char *name) {
    printer->newLine();
    printer->_print("//");
    for (int i=0; i<80; ++i) {
        printer->_print("#");
    }
    if (name) {
        printer->_print("  ");
        printer->_print(name);
    }
    printer->newLine();
    printer->newLine();
}

void Generator::genHeader(FPod *pod, Printer *printer) {
    horizontalLine(printer, "type declare");
    for (int i=0; i<pod->types.size(); ++i) {
        FType *type = &pod->types[i];
        GType gtype(podMgr, pod, type);
        gtype.genTypeDeclare(printer);
        printer->newLine();
    }
    
    horizontalLine(printer, "struct");
    for (int i=0; i<pod->types.size(); ++i) {
        FType *type = &pod->types[i];
        GType gtype(podMgr, pod, type);
        gtype.genStruct(printer);
        printer->newLine();
    }
    
    horizontalLine(printer, "method declare");
    for (int i=0; i<pod->types.size(); ++i) {
        FType *type = &pod->types[i];
        GType gtype(podMgr, pod, type);
        gtype.genMethodDeclare(printer);
        printer->newLine();
    }
}

void Generator::genImple(FPod *pod, Printer *printer) {
    for (int i=0; i<pod->types.size(); ++i) {
        FType *type = &pod->types[i];
        GType gtype(podMgr, pod, type);
        gtype.genImple(printer);
    }
}
