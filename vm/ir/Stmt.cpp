//
// Copyright (c) 2017, chunquedong
// Licensed under the Apache Licene 2.0
//
//  Created by yangjiandong on 16/9/10.
//

#include "Stmt.hpp"
#include "IRMethod.h"
#include "common.h"

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

void Expr::print(IRMethod *method, Printer& printer, int pass) {
    switch (type) {
        case ExprType::constant: {
            printValue(printer, method->curPod, opObj);
            break;
        }
        case ExprType::localVar: {
            if (varRef.block == -1) {
                Var var = method->locals[varRef.index];
                printer.printf("v__%s_%d", var.name.c_str(), varRef.index);
            } else {
                printf("ERROR: block is %d\n", varRef.block);
            }
            break;
        }
        case ExprType::tempVar:
            printer.printf("t__%d_%d", varRef.block, varRef.index);
            break;
        default:
            break;
    }
}

void StoreStmt::print(IRMethod *method, Printer& printer, int pass) {
    dst.print(method, printer, pass);
    printer.printf("=");
    src.print(method, printer, pass);
    printer.printf(";");
}

void CallStmt::print(IRMethod *method, Printer& printer, int pass) {
    if (!isVoid) {
        retValue.print(method, printer, pass);
        printer.printf("=");
    }
    
    int s = 0;
    if (isStatic) {
        printer.printf("%s::", curPod->names[methodRef->parent].c_str());
    } else {
        params[0].print(method, printer, pass);
        printer.printf("->");
        s = 1;
    }
    
    printer.printf("%s(", curPod->names[methodRef->name].c_str());
    
    for (int i=s; i<params.size(); ++i) {
        if (i != s) {
            printer.printf(",");
        }
        params[i].print(method, printer, pass);
    }
    printer.printf(");");
}

void FieldStmt::print(IRMethod *method, Printer& printer, int pass) {
    if (isLoad) {
        value.print(method, printer, pass);
    } else {
        if (isStatic) {
            printer.printf("%s::%s", curPod->names[fieldRef->parent].c_str()
                           , curPod->names[fieldRef->name].c_str());
        } else {
            instance.print(method, printer, pass);
            printer.printf("->%s", curPod->names[fieldRef->name].c_str());
        }
    }
    printer.printf("=");
    if (isLoad) {
        if (isStatic) {
            printer.printf("%s::%s", curPod->names[fieldRef->parent].c_str()
                           , curPod->names[fieldRef->name].c_str());
        } else {
            instance.print(method, printer, pass);
            printer.printf("->%s", curPod->names[fieldRef->name].c_str());
        }
    } else {
        value.print(method, printer, pass);
    }
    printer.printf(";");
}

void JmpStmt::print(IRMethod *method, Printer& printer, int pass) {
    if (jmpType == allJmp || jmpType == leaveJmp) {
        printer.printf("goto ");
    }
    else if (jmpType == trueJmp) {
        printer.printf("if (");
        expr.print(method, printer, pass);
        printer.printf(") goto ");
    }
    else if (jmpType == falseJmp) {
        printer.printf("if (!");
        expr.print(method, printer, pass);
        printer.printf(") goto ");
    }
    printer.printf("l__%d;", targetBlock->pos);
}

void CmpStmt::print(IRMethod *method, Printer& printer, int pass) {
    result.print(method, printer, pass);
    printer.printf("=");
    param1.print(method, printer, pass);
    printer.printf("<=>");
    param2.print(method, printer, pass);
    printer.printf(";");
}

void RetStmt::print(IRMethod *method, Printer& printer, int pass) {
    if (isVoid) {
        printer.printf("return;");
    } else {
        printer.printf("return ");
        retValue.print(method, printer, pass);
        printer.printf(";");
    }
}

void ExceptionStmt::print(IRMethod *method, Printer& printer, int pass) {
    switch (etype) {
        case TryStart:
            printer.printf("FR_TRY {");
            break;
        case TryEnd: {
            printer.println("} FR_CATCH {");
            printer.indent();
            bool hasCatchAll = false;
            for (int i=0; i<catchs.size(); ++i) {
                ExceptionStmt *itr = catchs[i];
                if (itr->catchType == -1) {
                    printer.println("goto l__%d;//catch all", handler);
                    hasCatchAll = true;
                    break;
                }
                
                if (i > 0) {
                    printer.printf("else ");
                }
                printer.println("if (fr_getErr(__env) is %d) {", itr->catchType);
                printer.printf("  Type ");
                itr->catchVar.print(method, printer, 0);
                printer.printf(" = getErr();");
                printer.println(" goto l__%d; }", handler);
            }
            if (!hasCatchAll) {
                printer.println("FR_THROW(fr_getErr(__env));");
            }
            printer.unindent();
            printer.println("}//end catch");
        }
            break;
        case CatchStart:
            //printer.printf("} catch(%d) {", catchType);
            break;
        case CatchEnd:
            //printer.printf("}//end catch");
            break;
        case FinallyStart:
            //printer.printf("finally {");
            break;
        case FinallyEnd:
            //printer.printf("}");
            break;
        default:
            break;
    }
}

void Block::print(IRMethod *method, Printer& printer, int pass) {
    if (pass == 0) {
        for (int i=0; i<locals.size(); ++i) {
            Var &v = locals[i];
            printer.printf("%s t__%d_%d; ", v.typeName.c_str(), index, v.index);
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
