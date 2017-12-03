//
// Copyright (c) 2017, chunquedong
// Licensed under the Apache Licene 2.0
//
//  Created by yangjiandong on 16/9/10.
//

#include "Stmt.hpp"
#include "IRMethod.h"
#include "FCodeUtil.hpp"

void printValue(Printer& printer, FPod *curPod, FOpObj &opObj) {
    switch (opObj.opcode) {
        case FOp::LoadNull: {
            printer.printf("NULL");
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
            double i = curPod->constantas.reals[opObj.i1];
            printer.printf("%g", i);
            break;
        }
        case FOp::LoadStr: {
            std::string str = curPod->constantas.strings[opObj.i1];
            long pos = 0;
            while (pos < str.length()) {
                if (str[pos] == '"') {
                    str.replace(pos, 2, "\\\"");
                    ++pos;
                }
                ++pos;
            }
            printer.printf("(sys_Str)fr_newStrUtf8(__env, \"%s\")", str.c_str());
            break;
        }
        case FOp::LoadDuration: {
            int64_t i = curPod->constantas.ints[opObj.i1];
            printer.printf("%lld", i);
            break;
            break;
        }
        case FOp::LoadUri: {
            std::string &i = curPod->constantas.uris[opObj.i1];
            printer.printf("\"%s\"", i.c_str());
            break;
        }
        case FOp::LoadType: {
            std::string typeName = FCodeUtil::getTypeRefName(curPod
                                                             , opObj.i1, false);
            printer.printf("FR_TYPE(%s)", typeName.c_str());
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
    
    if (!isVirtual) {
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
    std::string typeName = FCodeUtil::getTypeRefName(curPod, fieldRef->parent, false);
    std::string name = FCodeUtil::getIdentifierName(curPod, fieldRef->name);
    
    if (isLoad) {
        value.print(method, printer, pass);
    } else {
        if (isStatic) {
            printer.printf("%s_%s", typeName.c_str(), name.c_str());
        } else {
            instance.print(method, printer, pass);
            printer.printf("->%s", name.c_str());
        }
    }
    printer.printf(" = ");
    if (isLoad) {
        if (isStatic) {
            printer.printf("%s_%s", typeName.c_str(), name.c_str());
        } else {
            instance.print(method, printer, pass);
            printer.printf("->%s", name.c_str());
        }
    } else {
        value.print(method, printer, pass);
    }
    printer.printf(";");
}

void JmpStmt::print(IRMethod *method, Printer& printer, int pass) {
    switch (jmpType) {
        case trueJmp:{
            printer.printf("if (");
            expr.print(method, printer, pass);
            printer.printf(") goto ");
        }
            break;
        case falseJmp: {
            printer.printf("if (!");
            expr.print(method, printer, pass);
            printer.printf(") goto ");
        }
            break;
        case finallyJmp:
        case leaveJmp : {
            printer.println("fr_clearErr(__env);");
            printer.printf("goto ");
        }
            break;
        default:
            printer.printf("goto ");
            break;
    }
    printer.printf("l__%d;", targetBlock->pos);
}

void AllocStmt::print(IRMethod *method, Printer& printer, int pass) {
    obj.print(method, printer, pass);
    printer.printf(" = FR_ALLOC(");
    std::string typeName = FCodeUtil::getTypeRefName(curPod, type, false);
    printer.printf("%s);", typeName.c_str());
}

void CmpStmt::print(IRMethod *method, Printer& printer, int pass) {
    FTypeRef &typeRef1 = curPod->typeRefs[opObj.i1];
    FTypeRef &typeRef2 = curPod->typeRefs[opObj.i2];
    bool isVal1, isVal2, isNullable1, isNullable2;
    FCodeUtil::getTypeInfo(curPod, typeRef1, isVal1, isNullable1);
    FCodeUtil::getTypeInfo(curPod, typeRef2, isVal2, isNullable2);
    
    bool direct = false;
    if (isVal1 && !isNullable1 && isVal2 && !isNullable2) {
        direct = true;
    }
    
    result.print(method, printer, pass);
    printer.printf("=");
    
    if (direct) {
        switch (opObj.opcode) {
            case FOp::CompareEQ: {
                param1.print(method, printer, pass);
                printer.printf(" == ");
                param2.print(method, printer, pass);
                printer.printf(";");
                break;
            }
            case FOp::CompareNE: {
                param1.print(method, printer, pass);
                printer.printf(" != ");
                param2.print(method, printer, pass);
                printer.printf(";");
                break;
            }
            case FOp::CompareLT: {
                param1.print(method, printer, pass);
                printer.printf(" < ");
                param2.print(method, printer, pass);
                printer.printf(";");
                break;
            }
            case FOp::CompareLE: {
                param1.print(method, printer, pass);
                printer.printf(" <= ");
                param2.print(method, printer, pass);
                printer.printf(";");
                break;
            }
            case FOp::CompareGE: {
                param1.print(method, printer, pass);
                printer.printf(" >= ");
                param2.print(method, printer, pass);
                printer.printf(";");
                break;
            }
            case FOp::CompareGT: {
                param1.print(method, printer, pass);
                printer.printf(" > ");
                param2.print(method, printer, pass);
                printer.printf(";");
                break;
            }
            case FOp::CompareSame: {
                param1.print(method, printer, pass);
                printer.printf(" == ");
                param2.print(method, printer, pass);
                printer.printf(";");
                break;
            }
            case FOp::CompareNotSame: {
                param1.print(method, printer, pass);
                printer.printf(" != ");
                param2.print(method, printer, pass);
                printer.printf(";");
                break;
            }
            case FOp::CompareNull: {
                param1.print(method, printer, pass);
                printer.printf(" == NULL;");
                break;
            }
            case FOp::CompareNotNull: {
                param1.print(method, printer, pass);
                printer.printf(" != NULL;");
                break;
            }
            default:
                printf("ERROR:unknow cmp opcode:%d", opObj.opcode);
        }
    } else {
        switch (opObj.opcode) {
            case FOp::CompareEQ: {
                printer.printf("FR_VCALL(sys_Obj, equals1, ");
                param1.print(method, printer, pass);
                printer.printf(",");
                param2.print(method, printer, pass);
                printer.printf(");");
                break;
            }
            case FOp::CompareNE: {
                printer.printf("!(FR_VCALL(sys_Obj, equals1, ");
                param1.print(method, printer, pass);
                printer.printf(",");
                param2.print(method, printer, pass);
                printer.printf("));");
                break;
            }
            case FOp::CompareLT: {
                printer.printf("(FR_VCALL(sys_Obj, compare1, ");
                param1.print(method, printer, pass);
                printer.printf(",");
                param2.print(method, printer, pass);
                printer.printf(")) < 0;");
                break;
            }
            case FOp::CompareLE: {
                printer.printf("(FR_VCALL(sys_Obj, compare1, ");
                param1.print(method, printer, pass);
                printer.printf(",");
                param2.print(method, printer, pass);
                printer.printf(")) <= 0;");
                break;
            }
            case FOp::CompareGE: {
                printer.printf("(FR_VCALL(sys_Obj, compare1, ");
                param1.print(method, printer, pass);
                printer.printf(",");
                param2.print(method, printer, pass);
                printer.printf(")) >= 0;");
                break;
            }
            case FOp::CompareGT: {
                printer.printf("(FR_VCALL(sys_Obj, compare1, ");
                param1.print(method, printer, pass);
                printer.printf(",");
                param2.print(method, printer, pass);
                printer.printf(")) > 0;");
                break;
            }
            case FOp::CompareSame: {
                param1.print(method, printer, pass);
                printer.printf("==");
                param2.print(method, printer, pass);
                printer.printf(";");
                break;
            }
            case FOp::CompareNotSame: {
                param1.print(method, printer, pass);
                printer.printf("!=");
                param2.print(method, printer, pass);
                printer.printf(";");
                break;
            }
            case FOp::CompareNull: {
                param1.print(method, printer, pass);
                printer.printf("== NULL;");
                break;
            }
            case FOp::CompareNotNull: {
                param1.print(method, printer, pass);
                printer.printf("!= NULL;");
                break;
            }
            default:
                printf("ERROR:unknow cmp opcode:%d", opObj.opcode);
        }
    }
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

void ThrowStmt::print(IRMethod *method, Printer& printer, int pass) {
    printer.printf("FR_THROW(");
    var.print(method, printer, pass);
    printer.printf(");");
}

void ExceptionStmt::print(IRMethod *method, Printer& printer, int pass) {
    switch (etype) {
        case TryStart:
            printer.printf("FR_TRY {");
            break;
        case TryEnd: {
            printer.println(";");//print NOP(no operation)
            
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
                std::string typeName = FCodeUtil::getTypeRefName(curPod, itr->catchType, false);
                printer.println("if (FR_ERR_TYPE(%s)) {", typeName.c_str());
                itr->catchVar.print(method, printer, 0);
                printer.printf(" = (%s)fr_getErr(__env);", typeName.c_str());
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
    std::string typeName1 = FCodeUtil::getTypeRefName(curPod, fromType, true);
    std::string typeName2 = FCodeUtil::getTypeRefName(curPod, toType, true);
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

void TypeCheckStmt::print(IRMethod *method, Printer& printer, int pass) {
    result.print(method, printer, pass);
    if (isOrAs) {
        printer.printf(" = FR_TYPE_IS(");
    } else {
        printer.printf(" = FR_TYPE_AS(");
    }
    obj.print(method, printer, pass);
    std::string typeName = FCodeUtil::getTypeRefName(curPod, type, false);
    printer.printf(", %s);", typeName.c_str());
}
