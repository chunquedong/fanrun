//
// Copyright (c) 2017, chunquedong
// Licensed under the Apache Licene 2.0
//
//  Created by yangjiandong on 16/9/10.
//

#include "Stmt.hpp"
#include "IRMethod.h"
#include "escape.h"


std::string getTypeRefName(FPod *pod, uint16_t tid, bool checkNullable);

void printValue(Printer& printer, FPod *curPod, FOpObj &opObj) {
    switch (opObj.opcode) {
        case FOp::LoadNull: {
            printer.printf("null");
            break;
        }
        case FOp::LoadFalse: {
            printer.printf("false");
            break;
        }
        case FOp::LoadTrue: {
            printer.printf("true");
            break;
        }
        case FOp::LoadInt: {
            int64_t i = curPod->constantas.ints[opObj.i1];
            printer.printf("%lld", i);
            break;
        }
        case FOp::LoadFloat: {
            double i = curPod->constantas.reals[opObj.i1];
            printer.printf("%g", i);
            break;
        }
        case FOp::LoadDecimal: {
            break;
        }
        case FOp::LoadStr: {
            std::string &i = curPod->constantas.strings[opObj.i1];
            printer.printf("\"%s\"", i.c_str());
            break;
        }
        case FOp::LoadDuration: {
            //TODO
            break;
        }
        case FOp::LoadUri: {
            std::string &i = curPod->constantas.uris[opObj.i1];
            printer.printf("\"%s\"", i.c_str());
            break;
        }
        case FOp::LoadType: {
            break;
        }
        default: {
            printer.printf("other");
            break;
        }
    }
}

std::string Expr::getConstantType() {
    std::string res;
    switch (opObj.opcode) {
        case FOp::LoadNull: {
            res = "sys_Obj";
            break;
        }
        case FOp::LoadFalse: {
            res = "sys_Bool";
            break;
        }
        case FOp::LoadTrue: {
            res = "sys_Bool";
            break;
        }
        case FOp::LoadInt: {
            res = "sys_Int";
            break;
        }
        case FOp::LoadFloat: {
            res = "sys_Float";
            break;
        }
        case FOp::LoadDecimal: {
            res = "sys_Decimal";
            break;
        }
        case FOp::LoadStr: {
            res = "sys_Str";
            break;
        }
        case FOp::LoadDuration: {
            res = "sys_Duration";
            break;
        }
        case FOp::LoadUri: {
            res = "sys_Uri";
            break;
        }
        case FOp::LoadType: {
            res = "sys_Type";
            break;
        }
        default: {
            res = "sys_Obj";
            break;
        }
    }
    return res;
}

void Expr::print(IRMethod *method, Printer& printer, int pass) {
    switch (type) {
        case ExprType::constant: {
            printValue(printer, method->curPod, opObj);
            break;
        }
        case ExprType::localVar: {
            if (varRef.block == -1) {
                Var &var = method->locals[varRef.index];
                printer.printf("%s", var.name.c_str());
            } else {
                printf("ERROR: block is %d\n", varRef.block);
            }
            break;
        }
        case ExprType::tempVar: {
            Block *block = method->blocks[varRef.block];
            Var &var = block->locals[varRef.index];
            printer.printf("%s", var.name.c_str());
            break;
        }
        default:
            break;
    }
}

void StoreStmt::print(IRMethod *method, Printer& printer, int pass) {
    dst.print(method, printer, pass);
    printer.printf(" = ");
    src.print(method, printer, pass);
    printer.printf(";");
}

void CallStmt::print(IRMethod *method, Printer& printer, int pass) {
    if (!isVoid) {
        retValue.print(method, printer, pass);
        printer.printf(" = ");
    }
    
    std::string typeName = getTypeRefName(curPod, methodRef->parent, false);
    std::string mthName = curPod->names[methodRef->name];
    escape(mthName);
    
    mthName += std::to_string(methodRef->paramCount);
    
    if (!isVirtual) {
        std::string tname = getTypeRefName(curPod, methodRef->parent, false);
        printer.printf("%s_%s(__env", typeName.c_str(), mthName.c_str());
    } else if (isMixin) {
        printer.printf("FR_ICALL(%s, %s", typeName.c_str(), mthName.c_str());
    } else {
        printer.printf("FR_VCALL(%s, %s", typeName.c_str(), mthName.c_str());
    }
    
    for (int i=0; i<params.size(); ++i) {
        printer.printf(",");
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
    printer.printf(" = ");
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
    if (jmpType == trueJmp) {
        printer.printf("if (");
        expr.print(method, printer, pass);
        printer.printf(") goto ");
    }
    else if (jmpType == falseJmp) {
        printer.printf("if (!");
        expr.print(method, printer, pass);
        printer.printf(") goto ");
    } else {
        printer.printf("goto ");
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

void CoerceStmt::print(IRMethod *method, Printer& printer, int pass) {
    std::string typeName1 = getTypeRefName(curPod, fromType, true);
    std::string typeName2 = getTypeRefName(curPod, toType, true);
    to.print(method, printer, pass);
    switch (coerceType) {
        case cast: {
            printer.printf(" = FR_CAST(");
            break;
        }
        case boxing: {
            printer.printf(" = FR_BOX(");
            break;
        }
        case unboxing: {
            printer.printf(" = FR_UNBOX(");
            break;
        }
        default:
            break;
    }
    from.print(method, printer, pass);
    printer.printf(",%s,%s", typeName1.c_str(), typeName2.c_str());
    printer.printf(");");
}

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
