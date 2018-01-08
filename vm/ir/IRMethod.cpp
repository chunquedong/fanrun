//
// Copyright (c) 2017, chunquedong
// Licensed under the Apache Licene 2.0
//
//  Created by yangjiandong on 16/9/10.
//

#include "IRMethod.h"
#include "FCodeUtil.hpp"

void Block::print(IRMethod *method, Printer& printer, int pass) {
    //print export temp var
    if (pass == 0) {
        bool has = false;
        for (int i=0; i<locals.size(); ++i) {
            Var &v = locals[i];
            if (v.isExport) {
                printer.printf("%s %s; ", v.typeName.c_str(), v.name.c_str());
                has = true;
            }
        }
        if (has) {
            printer.newLine();
        }
        return;
    }
    
    //print jump label num
    char *s = printer.format("l__%d:\n", pos);
    printer._print(s);
    
    //print first exception try stmt
    int start = 0;
    int end = (int)stmts.size();
    bool printLast = false;
    if (stmts.size() > 0) {
        if (stmts[0]->getType() == StmtType::error) {
            stmts[0]->print(method, printer, pass);
            printer.newLine();
            ++start;
        }
        if (stmts[end-1]->getType() == StmtType::error) {
            printLast = true;
            --end;
        }
    }
    
    printer.println("{");
    //print temp var
    bool has = false;
    for (int i=0; i<locals.size(); ++i) {
        Var &v = locals[i];
        if (!v.isExport) {
            printer.printf("%s %s; ", v.typeName.c_str(), v.name.c_str());
            has = true;
        }
    }
    if (has) {
        printer.newLine();
    }

    //print stmts
    for (int i=start; i<end; ++i) {
        stmts[i]->print(method, printer, pass);
        printer.newLine();
    }
    
    //set temp ver to NULL
    has = false;
    for (int i=0; i<locals.size(); ++i) {
        Var &v = locals[i];
        if (!FCodeUtil::isValType(v.typeName)) {
            printer.printf("%s = NULL; ", v.name.c_str());
            has = true;
        }
    }
    if (has) {
        printer.newLine();
    }
    printer.println("}");
    
    //print last exception tryEnd stmt
    if (printLast) {
        stmts[end]->print(method, printer, pass);
        printer.newLine();
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

