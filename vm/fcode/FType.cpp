//
// Copyright (c) 2017, chunquedong
// Licensed under the Apache Licene 2.0
//
//  Created by chunquedong on 15/6/26.
//

#include "FType.h"
#include "FPod.h"

void FType::readMethod(FMethod &method, Buffer &buffer) {
    method.name = buffer.readUInt16();
    method.flags = buffer.readUInt32();
    method.returnType = buffer.readUInt16();
    method.inheritReturenType = buffer.readUInt16();
    method.maxStack = buffer.readUInt8();
    method.paramCount = buffer.readUInt8();
    method.localCount = buffer.readUInt8();
    method.c_native = NULL;
    method.c_wrappedMethod = NULL;
    method.c_jit = NULL;
    
    for (int j=0,n=method.paramCount+method.localCount; j<n; ++j) {
        FMethodVar var;
        var.name = buffer.readUInt16();
        var.type = buffer.readUInt16();
        var.flags = buffer.readUInt8();
        var.attrCount = buffer.readUInt16();
        //var.attrs.resize(attrCount);
        for (int i=0; i<var.attrCount; ++i) {
            FAttr *attr = FAttr::readAttr(c_pod, buffer);
            if (attr) {
                var.attrs.push_back(attr);
            }
        }
        method.vars.push_back(var);
    }
    
    method.code.read(buffer);
    
    int attrCount = buffer.readUInt16();
    method.attrCount = attrCount;
    for (int i=0; i<attrCount; ++i) {
        FAttr *attr = FAttr::readAttr(c_pod, buffer);
        if (attr) {
            method.attrs.push_back(attr);
        }
    }

    method.c_parent = this;
}

void FType::read(FPod *pod, FTypeMeta &meta, Buffer &buffer) {
    c_allocSize = -1;
    c_allocStaticSize = -1;
    c_staticData = NULL;
    c_wrappedType = NULL;
    this->meta = meta;
    this->c_pod = pod;
    FTypeRef &typeRef = pod->typeRefs[meta.self];
    this->c_name = pod->names[typeRef.typeName];
    typeRef.c_type = this;
    
    {
        int fieldCount = buffer.readUInt16();
        fields.resize(fieldCount);
        for (int i=0; i<fieldCount; ++i) {
            fields[i].name = buffer.readUInt16();
            fields[i].flags = buffer.readUInt32();
            fields[i].type = buffer.readUInt16();
            int attrCount = buffer.readUInt16();
            fields[i].attrCount = attrCount;
            fields[i].c_offset = -1;
            fields[i].c_parent = this;
            for (int i=0; i<attrCount; ++i) {
                FAttr *attr = FAttr::readAttr(pod, buffer);
                if (attr) {
                    fields[i].attrs.push_back(attr);
                }
            }
            
            std::string &name = pod->names[fields[i].name];
            c_fieldMap[name] = &fields[i];
        }
    }
    {
        int methodCount = buffer.readUInt16();
        methods.resize(methodCount);
        for (int i=0; i<methodCount; ++i) {
            readMethod(methods[i], buffer);
            
            std::string name = pod->names[methods[i].name];
            if (methods[i].flags & FFlags::Setter) {
                name += "$";
            }
            c_methodMap[name] = &methods[i];
        }
    }
    {
        int attrCount = buffer.readUInt16();
        //attrs.resize(attrCount);
        for (int i=0; i<attrCount; ++i) {
            FAttr *attr = FAttr::readAttr(pod, buffer);
            if (attr) {
                attrs.push_back(attr);
            }
        }
    }
}


FType::~FType() {
    for (int i=0; i<attrs.size(); ++i) {
        delete attrs[i];
    }
    attrs.clear();
}
