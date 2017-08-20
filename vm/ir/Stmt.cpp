//
// Copyright (c) 2017, chunquedong
// Licensed under the Apache Licene 2.0
//
//  Created by yangjiandong on 16/9/10.
//

#include "Stmt.hpp"

void printValue(Printer& printer, FPod *curPod, FOpObj &opObj) {
    fr_TagValue val;
    switch (opObj.opcode) {
        case FOp::LoadNull: {
            val.type = fr_vtObj;
            val.any.o = nullptr;
            break;
        }
        case FOp::LoadFalse: {
            val.type = fr_vtBool;
            val.any.b = false;
            break;
        }
        case FOp::LoadTrue: {
            val.type = fr_vtBool;
            val.any.b = true;
            break;
        }
        case FOp::LoadInt: {
            fr_Int i = curPod->constantas.ints[opObj.i1];
            val.type = fr_vtInt;
            val.any.i = i;
            break;
        }
        case FOp::LoadFloat: {
            double i = curPod->constantas.reals[opObj.i1];
            val.type = fr_vtFloat;
            val.any.f = i;
            break;
        }
        case FOp::LoadDecimal: {
            break;
        }
        case FOp::LoadStr: {
            //TODO
            break;
        }
        case FOp::LoadDuration: {
            //TODO
            break;
        }
        case FOp::LoadUri: {
            //TODO
            break;
        }
        case FOp::LoadType: {
            break;
        }
        default: {
            //compare null
            val.type = fr_vtObj;
            val.any.o = nullptr;
        }
            break;
    }
    
    switch (val.type) {
        case fr_vtBool:
            printer.printf(val.any.b ? "true" : "false");
            break;
        case fr_vtInt:
            printer.printf("%lld", val.any.i);
            break;
        case fr_vtFloat:
            printer.printf("%g", val.any.f);
            break;
        case fr_vtObj:
            if (val.any.o) {
                //TODO
                //printer.printf("%s(%p)", ((FObj*)val.any.o)->type->c_name.c_str()
                //               , val.any.o);
            } else {
                printer.printf("null");
            }
            break;
        default:
            printer.printf("other:%p", val.any.o);
            break;
    }
}

void Expr::print(PodLoader *podManager, FPod *curPod, Printer& printer, int pass) {
    switch (type) {
        case ExprType::constant: {
            printValue(printer, curPod, opObj);
            break;
        }
        case ExprType::localVar: {
            printer.printf("v%d_%d", varRef.block, varRef.index);
            break;
        }
        case ExprType::tempVar:
            printer.printf("t%d_%d", varRef.block, varRef.index);
            break;
        default:
            break;
    }
}

void StoreStmt::print(PodLoader *podManager, FPod *curPod, Printer& printer, int pass) {
    dst.print(podManager, curPod, printer, pass);
    printer.printf("=");
    src.print(podManager, curPod, printer, pass);
    printer.printf(";");
}

void CallStmt::print(PodLoader *podManager, FPod *curPod, Printer& printer, int pass) {
    if (!isVoid) {
        retValue.print(podManager, curPod, printer, pass);
        printer.printf("=");
    }
    
    int s = 0;
    if (isStatic) {
        printer.printf("%s::", curPod->names[methodRef->parent].c_str());
    } else {
        params[0].print(podManager, curPod, printer, pass);
        printer.printf("->");
        s = 1;
    }
    
    printer.printf("%s(", curPod->names[methodRef->name].c_str());
    
    for (int i=s; i<params.size(); ++i) {
        if (i != s) {
            printer.printf(",");
        }
        params[i].print(podManager, curPod, printer, pass);
    }
    printer.printf(");");
}

void FieldStmt::print(PodLoader *podManager, FPod *curPod, Printer& printer, int pass) {
    if (isLoad) {
        value.print(podManager, curPod, printer, pass);
    } else {
        if (isStatic) {
            printer.printf("%s::%s", curPod->names[fieldRef->parent].c_str()
                           , curPod->names[fieldRef->name].c_str());
        } else {
            instance.print(podManager, curPod, printer, pass);
            printer.printf("->%s", curPod->names[fieldRef->name].c_str());
        }
    }
    printer.printf("=");
    if (isLoad) {
        if (isStatic) {
            printer.printf("%s::%s", curPod->names[fieldRef->parent].c_str()
                           , curPod->names[fieldRef->name].c_str());
        } else {
            instance.print(podManager, curPod, printer, pass);
            printer.printf("->%s", curPod->names[fieldRef->name].c_str());
        }
    } else {
        value.print(podManager, curPod, printer, pass);
    }
    printer.printf(";");
}

void JmpStmt::print(PodLoader *podManager, FPod *curPod, Printer& printer, int pass) {
    if (jmpType == allJmp) {
        printer.printf("goto ");
    }
    else if (jmpType == trueJmp) {
        printer.printf("if (");
        expr.print(podManager, curPod, printer, pass);
        printer.printf(") goto ");
    }
    else if (jmpType == falseJmp) {
        printer.printf("if (!");
        expr.print(podManager, curPod, printer, pass);
        printer.printf(") goto ");
    }
    printer.printf("l%d;", targetBlock->pos);
}

void CmpStmt::print(PodLoader *podManager, FPod *curPod, Printer& printer, int pass) {
    result.print(podManager, curPod, printer, pass);
    printer.printf("=");
    param1.print(podManager, curPod, printer, pass);
    printer.printf("<=>");
    param2.print(podManager, curPod, printer, pass);
    printer.printf(";");
}

void RetStmt::print(PodLoader *podManager, FPod *curPod, Printer& printer, int pass) {
    if (isVoid) {
        printer.printf("return;");
    } else {
        printer.printf("return ");
        retValue.print(podManager, curPod, printer, pass);
        printer.printf(";");
    }
}

void Block::print(PodLoader *podManager, FPod *curPod, Printer& printer, int pass) {
    char *s = printer.format("l%d:\n", pos);
    printer._print(s);
    for (Stmt *stmt : stmts) {
        stmt->print(podManager, curPod, printer, pass);
        printer.newLine();
    }
}
