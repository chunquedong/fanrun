//
// Copyright (c) 2017, chunquedong
// Licensed under the Apache Licene 2.0
//
//  Created by yangjiandong on 2017/8/20.
//

#include "PodGen.hpp"
#include "FCodeUtil.hpp"


PodGen::PodGen(PodLoader *podMgr, const std::string& podName) : podMgr(podMgr), podName(podName) {
    pod = podMgr->findPod(podName);
    
    allTypes.clear();
    allTypes.reserve(pod->types.size());
    for (int i=0; i<pod->types.size(); ++i) {
        FType *type = &pod->types[i];
        TypeGen gtype(this, type);
        gtype.c_sortFlag = 0;
        
        //if (gtype.name != "testlib_Main") continue;
        allTypes.push_back(gtype);
    }
    
    for (int i=0; i<allTypes.size(); ++i) {
        TypeGen *t = &allTypes[i];
        typeMap[t->name] = t;
    }
    
    topoSortType();
}

void PodGen::gen(std::string &path) {
    std::string headerFile = path + podName + ".h";
    Printer headerPrinter(headerFile.c_str());
    genHeader(&headerPrinter);
    
    std::string impleFile = path + podName + ".c";
    Printer implePrinter(impleFile.c_str());
    genImple(&implePrinter);
    
    std::string regisFile = path + podName + "_register.c";
    Printer regisPrinter(regisFile.c_str());
    genRegister(&regisPrinter);
    
    std::string stubFile = path + podName + "_stub.c";
    Printer stubPrinter(stubFile.c_str());
    genStub(&stubPrinter);
}

void PodGen::horizontalLine(Printer *printer, const char *name) {
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

void PodGen::genHeader(Printer *printer) {
    printer->println("#ifndef _%s_h_", podName.c_str());
    printer->println("#define _%s_h_", podName.c_str());
    
    printer->println("#ifdef __cplusplus");
    printer->println("extern \"C\" {");
    printer->println("#endif //__cplusplus");
    
    printer->println("#include \"runtime.h\"");
    for (int i=0; i<pod->c_dependPods.size(); ++i) {
        std::string& dep = pod->c_dependPods[i];
        printer->println("#include \"%s.h\"", dep.c_str());
    }
    printer->newLine();
    
    horizontalLine(printer, "type declare");
    for (int i=0; i<sortedTypes.size(); ++i) {
        TypeGen *gtype = sortedTypes[i];
        gtype->genTypeDeclare(printer);
        printer->newLine();
    }
    
    horizontalLine(printer, "struct");
    bool hasNative = false;
    for (int i=0; i<sortedTypes.size(); ++i) {
        TypeGen *gtype = sortedTypes[i];
        if ((gtype->type->meta.flags & FFlags::Native) != 0) {
            hasNative = true;
            break;
        }
    }
    if (hasNative) {
        printer->println("#include \"%s_native.h\"", podName.c_str());
        printer->newLine();
    }
    
    for (int i=0; i<sortedTypes.size(); ++i) {
        TypeGen *gtype = sortedTypes[i];
        gtype->genStruct(printer);
        printer->newLine();
        gtype->genStaticField(printer, true);
        printer->newLine();
    }
    
    horizontalLine(printer, "method declare");
    for (int i=0; i<sortedTypes.size(); ++i) {
        TypeGen *gtype = sortedTypes[i];
        gtype->genMethodDeclare(printer);
        printer->newLine();
    }
    
    horizontalLine(printer, "virtual table");
    for (int i=0; i<sortedTypes.size(); ++i) {
        TypeGen *gtype = sortedTypes[i];
        gtype->genVTable(printer);
        printer->newLine();
    }
    
    printer->println("void %s_init__(fr_Env __env);", podName.c_str());
    
    printer->println("#ifdef __cplusplus");
    printer->println("}//extern C");
    printer->println("#endif //__cplusplus");
    printer->println("#endif //_%s_h_", podName.c_str());
}

void PodGen::genImple(Printer *printer) {
    
    printer->println("#include \"%s.h\"", podName.c_str());
    printer->newLine();
    
    for (int i=0; i<sortedTypes.size(); ++i) {
        TypeGen *gtype = sortedTypes[i];
        gtype->genImple(printer);
        //printer->newLine();
    }
    
    genStaticInit(printer);
}

void PodGen::genStaticInit(Printer *printer) {
    printer->println("void %s_init__(fr_Env __env) {", podName.c_str());
    printer->indent();
    printer->println("static bool inited = false;");
    printer->println("if (inited) { printf(\"ERROR: pod already inited\"); return; }");
    printer->println("inited = true;");
    
    for (int i=0; i<pod->c_dependPods.size(); ++i) {
        std::string& dep = pod->c_dependPods[i];
        if (dep == podName) continue;
        printer->println("%s_init__(__env);", dep.c_str());
    }
    
    for (int i=0; i<sortedTypes.size(); ++i) {
        TypeGen *gtype = sortedTypes[i];
        printer->println("%s_class__ = (fr_Class)"
                         "malloc(sizeof(struct %s_vtable));"
                         , gtype->name.c_str(), gtype->name.c_str());
        printer->println("%s_initVTable(__env, (struct %s_vtable*)%s_class__);"
                         , gtype->name.c_str(), gtype->name.c_str(), gtype->name.c_str());
    }
    printer->newLine();
    printer->newLine();
    for (int i=0; i<sortedTypes.size(); ++i) {
        TypeGen *gtype = sortedTypes[i];
        std::string staticInit = "static$init";
        auto itr = gtype->type->c_methodMap.find(staticInit);
        if (itr != gtype->type->c_methodMap.end()) {
            printer->println("%s_static__init0(__env);", gtype->name.c_str());
        }
    }
    printer->unindent();
    printer->println("}");
}

void PodGen::genRegister(Printer *printer) {
    for (int i=0; i<sortedTypes.size(); ++i) {
        TypeGen *gtype = sortedTypes[i];
        gtype->genMethodWrap(printer);
    }
    printer->println("void %s_register(fr_FVM vm) {", podName.c_str());
    printer->indent();
    for (int i=0; i<sortedTypes.size(); ++i) {
        TypeGen *gtype = sortedTypes[i];
        gtype->genMethodRegister(printer);
    }
    printer->unindent();
    printer->println("}");
}

void PodGen::genStub(Printer *printer) {
    for (int i=0; i<sortedTypes.size(); ++i) {
        TypeGen *gtype = sortedTypes[i];
        gtype->genMethodStub(printer);
    }
}

std::string PodGen::getTypeRefName(uint16_t tid) {
    return FCodeUtil::getTypeRefName(pod, tid, true);
}


//////////////////////////////////////////////////
// sort

static TypeGen *exitsBase(PodGen *pod, std::string &typeName) {
    for (size_t i=0,n=pod->allTypes.size(); i<n; ++i) {
        TypeGen &type = pod->allTypes[i];
        
        if (type.c_sortFlag != 0 ) {
            continue;
        }
        
        if (type.name == typeName) {
            return &type;
        }
    }
    return NULL;
}

static TypeGen *getOne(PodGen *pod) {
    for (size_t i=0,n=pod->allTypes.size(); i<n; ++i) {
        TypeGen &type = pod->allTypes[i];
        if (type.c_sortFlag != 0 ) {
            continue;
        }
        return &type;
    }
    return NULL;
}

void PodGen::topoSortType() {
    sortedTypes.clear();
    
    TypeGen *type = getOne(this);
    while (type) {
        
        if (type->name == "sys_Obj") {
            sortedTypes.push_back(type);
            type->c_sortFlag = 1;
            type = getOne(this);
            continue;
        }
        
        std::string baseName = getTypeRefName(type->type->meta.base);
        
        TypeGen *base = exitsBase(this, baseName);
        if (!base) {
            sortedTypes.push_back(type);
            type->c_sortFlag = 1;
            type = getOne(this);
        } else {
            type = base;
        }
    }
}

////////////////////////////////////////////////////////////

TypeGen* PodGen::findType(std::string &name) {
    auto it = typeMap.find(name);
    if (it == typeMap.end()) {
        return NULL;
    } else {
        return it->second;
    }
}


