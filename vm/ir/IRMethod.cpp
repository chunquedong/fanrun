//
// Copyright (c) 2017, chunquedong
// Licensed under the Apache Licene 2.0
//
//  Created by yangjiandong on 16/9/10.
//

#include "IRMethod.h"

void Block::print(IRMethod *method, Printer& printer, int pass) {
    if (pass == 0) {
        for (int i=0; i<locals.size(); ++i) {
            Var &v = locals[i];
            printer.printf("%s %s; ", v.typeName.c_str(), v.name.c_str());
        }
        if (locals.size() > 0) {
            printer.newLine();
        }
        return;
    }
    else {
        char *s = printer.format("l__%d:\n", pos);
        printer._print(s);
        for (Stmt *stmt : stmts) {
            stmt->print(method, printer, pass);
            printer.newLine();
        }
    }
}

IRMethod::IRMethod(FPod *curPod, FMethod *method) :
    curPod(curPod),
    method(method) {
    returnType = method->returnType;
    selfType = method->c_parent->meta.self;
    paramCount = method->paramCount;
}

void IRMethod::print(Printer& printer, int pass) {
    
    if (pass == 0) {
        printer.printf("%s(", name.c_str());
        for(int i=0; i<paramCount; ++i) {
            Var &v = locals[i];
            if (i != 0) printer.printf(", ");
            printer.printf("%s %s", v.typeName.c_str(), v.name.c_str());
        }
        printer.println(")");
    }
    else if (pass == 1) {
        
        for(int i=paramCount; i<locals.size(); ++i) {
            Var &v = locals[i];
            printer.printf("%s %s; ", v.typeName.c_str(), v.name.c_str());
        }
        printer.newLine();
        
        for (Block *b : blocks) {
            b->print(this, printer, 0);
        }
        for (Block *b : blocks) {
            b->print(this, printer, 1);
        }
    }
}

