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

std::string Expr::getTypeName(IRMethod *method) {
    switch (type) {
        case ExprType::constant: {
            return "";
        }
        case ExprType::localVar: {
            if (varRef.block == -1) {
                Var &var = method->locals[varRef.index];
                return var.typeName;
            } else {
                printf("ERROR: block is %d\n", varRef.block);
            }
            break;
        }
        case ExprType::tempVar: {
            Block *block = method->blocks[varRef.block];
            Var &var = block->locals[varRef.index];
            return var.typeName;
            break;
        }
        default:
            break;
    }
    return "";
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

bool Expr::isValueType(IRMethod *method) {
    switch (type) {
        case ExprType::constant: {
            std::string ctype = getConstantType();
            return FCodeUtil::isValType(ctype);
            break;
        }
        case ExprType::localVar: {
            if (varRef.block == -1) {
                Var &var = method->locals[varRef.index];
                return FCodeUtil::isValType(var.typeName);
            } else {
                printf("ERROR: block is %d\n", varRef.block);
            }
            break;
        }
        case ExprType::tempVar: {
            Block *block = method->blocks[varRef.block];
            Var &var = block->locals[varRef.index];
            return FCodeUtil::isValType(var.typeName);
            break;
        }
        default:
            break;
    }
    return false;
}

void StoreStmt::print(IRMethod *method, Printer& printer, int pass) {
    dst.print(method, printer, pass);
    printer.printf(" = ");
    std::string desType = dst.getTypeName(method);
    if (desType.empty()) {
        printf("ERROR");
    }
    printer.printf("(%s)", desType.c_str());
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
        if (params.size() > 0 && params.at(0).isValueType(method)) {
            printer.printf("%s_%s_val(__env", typeName.c_str(), mthName.c_str());
        } else {
            printer.printf("FR_VCALL(%s, %s", typeName.c_str(), mthName.c_str());
        }
    }
    
    for (int i=0; i<params.size(); ++i) {
        printer.printf(",");
        std::string varTypeName;
        int j = -1;
        if (isStatic) {
            j = i;
        }
        else if (i > 0) {
            j = i - 1;
        }
        else if (methodRef) {
            varTypeName = FCodeUtil::getTypeRefName(curPod, methodRef->parent, true);
        }
        
        if (j >= 0) {
            if (methodRef) {
                uint16_t var = methodRef->params.at(j);
                //FTypeRef vart = curPod->typeRefs[var];
                varTypeName = FCodeUtil::getTypeRefName(curPod, var, true);
            } else if (argsType.size() > 0) {
                varTypeName = argsType.at(j);
            }
        }
        if (varTypeName.size() > 0) {
            printer.printf("(%s)", varTypeName.c_str());
        }
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
            if (targetPos < selfPos) {
                printer.println("FR_CHECK_POINT");
            }
            printer.printf("if (");
            expr.print(method, printer, pass);
            printer.printf(") goto ");
        }
            break;
        case falseJmp: {
            if (targetPos < selfPos) {
                printer.println("FR_CHECK_POINT");
            }
            printer.printf("if (!");
            expr.print(method, printer, pass);
            printer.printf(") goto ");
        }
            break;
        case finallyJmp: {
            //printer.println("fr_clearErr(__env);");
            //printer.println("FR_LEAVE");
            printer.printf("goto ");
        }
            break;
        case leaveJmp : {
            //printer.println("FR_LEAVE");
            printer.printf("goto ");
        }
            break;
        default: {
            if (targetPos < selfPos) {
                printer.println("FR_CHECK_POINT");
            }
            printer.printf("goto ");
        }
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
    int cmpType = 0;
    bool isVal1 = false;
    bool isVal2 = false;
    switch (opObj.opcode) {
        case FOp::CompareNull: {
            result.print(method, printer, pass);
            printer.printf("=");
            param1.print(method, printer, pass);
            printer.printf(" == NULL;");
            return;
        }
        case FOp::CompareNotNull: {
            result.print(method, printer, pass);
            printer.printf("=");
            param1.print(method, printer, pass);
            printer.printf(" != NULL;");
            return;
        }
        default:
            break;
    }
    
    if (opObj.i1 > 0 || opObj.i2 > 0) {
        FTypeRef &typeRef1 = curPod->typeRefs[opObj.i1];
        FTypeRef &typeRef2 = curPod->typeRefs[opObj.i2];
        bool isNullable1 = false, isNullable2 = false;
        FCodeUtil::getTypeInfo(curPod, typeRef1, isVal1, isNullable1);
        FCodeUtil::getTypeInfo(curPod, typeRef2, isVal2, isNullable2);
        if (isNullable1) isVal1 = false;
        if (isNullable2) isVal2 = false;
    }
    else {
        std::string name1 = param1.getTypeName(method);
        std::string name2 = param2.getTypeName(method);
        isVal1 = FCodeUtil::isValType(name1);
        isVal2 = FCodeUtil::isValType(name2);
    }
    
    const char *op = "==";
    switch (opObj.opcode) {
        case FOp::Compare: {
            op = "-";
            break;
        }
        case FOp::CompareEQ: {
            op = "==";
            break;
        }
        case FOp::CompareNE: {
            op = "!=";
            break;
        }
        case FOp::CompareLT: {
            op = "<";
            break;
        }
        case FOp::CompareLE: {
            op = "<=";
            break;
        }
        case FOp::CompareGE: {
            op = ">=";
            break;
        }
        case FOp::CompareGT: {
            op = ">";
            break;
        }
        case FOp::CompareSame: {
            op = "==";
            break;
        }
        case FOp::CompareNotSame: {
            op = "!=";
            break;
        }
        case FOp::CompareNull: {
            op = "==";
            break;
        }
        case FOp::CompareNotNull: {
            op = "!=";
            break;
        }
        default:
            printf("ERROR:unknow cmp opcode:%d", opObj.opcode);
    }
    
    if (isVal1 && isVal2) {
        result.print(method, printer, pass);
        printer.printf("=");
        param1.print(method, printer, pass);
        printer.printf(" %s ", op);
        param2.print(method, printer, pass);
        printer.printf(";");
    }
    else if (!isVal1 && !isVal2) {
        cmpType = -1;
    }
    else {
        if (!isVal1) {
            printer.printf("if (");
            param1.print(method, printer, pass);
            printer.println(" == NULL) fr_throwNPE(__env);");
            
            printer.printf("if (!FR_TYPE_IS(");
            param1.print(method, printer, pass);
            printer.printf(",%s) ) ", param2.getTypeName(method).c_str());
            if (opObj.opcode == FOp::Compare) {
                result.print(method, printer, pass);
                printer.printf("=");
                printer.println("-1;");
            } else {
                result.print(method, printer, pass);
                printer.printf("=");
                printer.println("false;");
            }
            printer.printf("else ");
            result.print(method, printer, pass);
            printer.printf("=FR_UNBOXING(");
            param1.print(method, printer, pass);
            printer.printf(",X, %s) %s ", param2.getTypeName(method).c_str(), op);
            param2.print(method, printer, pass);
            printer.printf(";");
        }
        else if (!isVal2) {
            printer.printf("if (");
            param2.print(method, printer, pass);
            printer.println(" == NULL) fr_throwNPE(__env);");
            
            printer.printf("if (!FR_TYPE_IS(");
            param2.print(method, printer, pass);
            printer.printf(",%s) ) ", param1.getTypeName(method).c_str());
            if (opObj.opcode == FOp::Compare) {
                result.print(method, printer, pass);
                printer.printf("=");
                printer.println("-1;");
            } else {
                result.print(method, printer, pass);
                printer.printf("=");
                printer.println("false;");
            }
            printer.printf("else ");
            result.print(method, printer, pass);
            printer.printf("=");
            param1.print(method, printer, pass);
            printer.printf(" %s FR_UNBOXING(", op);
            param2.print(method, printer, pass);
            printer.printf(",X, %s)", param1.getTypeName(method).c_str());
            printer.printf(";");
        }
    }
    
    if (cmpType == -1) {
        result.print(method, printer, pass);
        printer.printf("=");
        
        switch (opObj.opcode) {
            case FOp::Compare: {
                printer.printf("FR_VCALL(sys_Obj, compare1, (sys_Obj)");
                param1.print(method, printer, pass);
                printer.printf(", (sys_Obj)");
                param2.print(method, printer, pass);
                printer.printf(");");
                break;
            }
            case FOp::CompareEQ: {
                printer.printf("FR_VCALL(sys_Obj, equals1, (sys_Obj)");
                param1.print(method, printer, pass);
                printer.printf(", (sys_Obj)");
                param2.print(method, printer, pass);
                printer.printf(");");
                break;
            }
            case FOp::CompareNE: {
                printer.printf("!(FR_VCALL(sys_Obj, equals1, (sys_Obj)");
                param1.print(method, printer, pass);
                printer.printf(", (sys_Obj)");
                param2.print(method, printer, pass);
                printer.printf("));");
                break;
            }
            case FOp::CompareLT: {
                printer.printf("(FR_VCALL(sys_Obj, compare1, (sys_Obj)");
                param1.print(method, printer, pass);
                printer.printf(", (sys_Obj)");
                param2.print(method, printer, pass);
                printer.printf(")) < 0;");
                break;
            }
            case FOp::CompareLE: {
                printer.printf("(FR_VCALL(sys_Obj, compare1, (sys_Obj)");
                param1.print(method, printer, pass);
                printer.printf(", (sys_Obj)");
                param2.print(method, printer, pass);
                printer.printf(")) <= 0;");
                break;
            }
            case FOp::CompareGE: {
                printer.printf("(FR_VCALL(sys_Obj, compare1, (sys_Obj)");
                param1.print(method, printer, pass);
                printer.printf(", (sys_Obj)");
                param2.print(method, printer, pass);
                printer.printf(")) >= 0;");
                break;
            }
            case FOp::CompareGT: {
                printer.printf("(FR_VCALL(sys_Obj, compare1, (sys_Obj)");
                param1.print(method, printer, pass);
                printer.printf(", (sys_Obj)");
                param2.print(method, printer, pass);
                printer.printf(")) > 0;");
                break;
            }
            case FOp::CompareSame: {
                printer.printf("(sys_Obj)");
                param1.print(method, printer, pass);
                printer.printf("==");
                printer.printf("(sys_Obj)");
                param2.print(method, printer, pass);
                printer.printf(";");
                break;
            }
            case FOp::CompareNotSame: {
                printer.printf("(sys_Obj)");
                param1.print(method, printer, pass);
                printer.printf("!=");
                printer.printf("(sys_Obj)");
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
            printer.println("} FR_CATCH {");
            printer.indent();
            for (int i=0; i<handlerStmt.size(); ++i) {
                ExceptionStmt *itr = handlerStmt[i];
                if (itr->etype == CatchStart) {
                    if (itr->catchType > 0) {
                        std::string typeName = FCodeUtil::getTypeRefName(curPod, itr->catchType, false);
                        printer.printf("if (FR_ERR_TYPE(%s)) {", typeName.c_str());
                        itr->catchVar.print(method, printer, 0);
                        printer.println(" = (%s)fr_getErr(__env); fr_clearErr(__env); goto l__%d;}"
                                        ,typeName.c_str(), handler);
                    } else {
                        printer.println("fr_clearErr(__env); goto l__%d;", handler);
                    }
                }
                else if (itr->etype == FinallyStart) {
                    printer.println("goto l__%d;//goto finally", handler);
                }
            }
            printer.unindent();
            printer.println("}//ce");
        }
            break;
        case CatchStart:
            printer.println("//catch start");
            /*
            printer.println(";");
            if (catchType == -1) {
                printer.println("} catch(...) {");
            } else {
                std::string typeName = FCodeUtil::getTypeRefName(curPod, catchType, false);
                printer.printf("} catch(%s ", typeName.c_str());
                catchVar.print(method, printer, 0);
                printer.println(") {");
            }
             */
            break;
        case CatchEnd:
            printer.println("//catch end");
            /*
            printer.println(";");
            printer.println("}//end catch");
             */
            break;
        case FinallyStart:
            printer.println("//finally start");
            /*
            printer.println("} catch(...) {");
             */
            break;
        case FinallyEnd:
            printer.println("//finally end");
            
            printer.println("if (fr_getErr(__env)) { FR_THROW(fr_getErr(__env)); }");
            
            break;
        default:
            break;
    }
}

void CoerceStmt::print(IRMethod *method, Printer& printer, int pass) {
    std::string typeName1 = FCodeUtil::getTypeRefName(curPod, fromType, true);
    std::string typeName2 = FCodeUtil::getTypeRefName(curPod, toType, true);
    
    const char *name = "";
    bool isPrefix = false;
    switch (coerceType) {
        case nonNull: {
            name = "FR_NNULL(";
            break;
        }
        case boxing: {
            if (typeName1 == "sys_Int") {
                name =("FR_BOX_INT(");
            }
            else if (typeName1 == "sys_Float") {
                name = ("FR_BOX_FLOAT(");
            }
            else if (typeName1 == "sys_Bool") {
                name = ("FR_BOX_BOOL(");
            }
            else {
                name = ("FR_BOXING(");
                isPrefix = true;
            }
            break;
        }
        case unboxing: {
            name = ("FR_UNBOXING(");
            break;
        }
        default:
            break;
    }
    if (isPrefix) {
        printer.printf("%s", name);
        to.print(method, printer, pass);
        printer.printf(", ");
    } else {
        to.print(method, printer, pass);
        printer.printf(" = ");
        printer.printf("%s", name);
    }
    from.print(method, printer, pass);
    printer.printf(", %s ,%s", typeName1.c_str(), typeName2.c_str());
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
