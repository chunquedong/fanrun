//
// Copyright (c) 2017, chunquedong
// Licensed under the Apache Licene 2.0
//
//  Created by yangjiandong on 16/9/10.
//

#include "Stmt.hpp"
#include "IRMethod.h"
#include "FCodeUtil.hpp"

Expr Var::asRef() {
    if (block == NULL || index == -1) {
        printf("ERROR\n");
    }
    Expr expr;
    expr.index = index;
    expr.block = block;
    return expr;
}

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

std::string Expr::getName() {
    Var &var = block->locals[index];
    return var.name;
}

std::string Expr::getTypeName() {
    Var &var = block->locals[index];
    return var.typeName;
}

bool Expr::isValueType() {
    return FCodeUtil::isValType(getTypeName());
}

void ConstStmt::print(Printer& printer) {
    printer.printf("%s = ", dst.getName().c_str());
    printValue(printer, curPod, opObj);
    printer.printf(";");
}

std::string ConstStmt::getTypeName() {
    std::string res;
    switch (opObj.opcode) {
        case FOp::LoadNull: {
            res = "sys_Obj_ref";
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

void StoreStmt::print(Printer& printer) {
    printer.printf("%s = %s;", dst.getName().c_str(), src.getName().c_str());
}

void CallStmt::print(Printer& printer) {
    if (!isVoid) {
        printer.printf("%s = ", retValue.getName().c_str());
    }
    
    if (!isVirtual) {
        printer.printf("%s_%s(__env", typeName.c_str(), mthName.c_str());
    } else if (isMixin) {
        printer.printf("FR_ICALL(%s, %s", typeName.c_str(), mthName.c_str());
    } else {
        if (params.size() > 0 && params.at(0).isValueType()) {
            printer.printf("%s_%s_val(__env", typeName.c_str(), mthName.c_str());
        } else {
            printer.printf("FR_VCALL(%s, %s", typeName.c_str(), mthName.c_str());
        }
    }
    
    for (int i=0; i<params.size(); ++i) {
        if (!isStatic && i == 0) {
            printer.printf(", (%s)%s"
                           , typeName.c_str(), params[i].getName().c_str());
        } else {
            printer.printf(", %s", params[i].getName().c_str());
        }
    }
    printer.printf(");");
}

void FieldStmt::print(Printer& printer) {
    std::string typeName = FCodeUtil::getTypeRefName(curPod, fieldRef->parent, false);
    std::string name = FCodeUtil::getIdentifierName(curPod, fieldRef->name);
    
    if (isLoad) {
        printer.printf("%s = ", value.getName().c_str());
        if (isStatic) {
            printer.printf("%s_%s", typeName.c_str(), name.c_str());
        } else {
            printer.printf("%s->%s", instance.getName().c_str(), name.c_str());
        }
    } else {
        if (isStatic) {
            printer.printf("%s_%s", typeName.c_str(), name.c_str());
        } else {
            printer.printf("%s->%s", instance.getName().c_str(), name.c_str());
        }
        printer.printf("= %s", value.getName().c_str());
    }
    
    printer.printf(";");
    if (!isLoad && !isStatic) {
        printer.printf("FR_SET_DIRTY(%s)", instance.getName().c_str());
    }
}

void JmpStmt::print(Printer& printer) {
    switch (jmpType) {
        case trueJmp:{
            if (targetPos < selfPos) {
                printer.println("FR_CHECK_POINT");
            }
            printer.printf("if (%s) goto ", expr.getName().c_str());
        }
            break;
        case falseJmp: {
            if (targetPos < selfPos) {
                printer.println("FR_CHECK_POINT");
            }
            printer.printf("if (!%s) goto ", expr.getName().c_str());
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

void AllocStmt::print(Printer& printer) {
    std::string typeName = FCodeUtil::getTypeRefName(curPod, type, false);
    printer.printf("%s = FR_ALLOC(%s);", obj.getName().c_str(), typeName.c_str());
}

void CmpStmt::print(Printer& printer) {
    int cmpType = 0;
    bool isVal1 = false;
    bool isVal2 = false;
    switch (opObj.opcode) {
        case FOp::CompareNull: {
            printer.printf("%s = %s == NULL;"
                           , result.getName().c_str(), param1.getName().c_str());
            return;
        }
        case FOp::CompareNotNull: {
            printer.printf("%s = %s != NULL;"
                           , result.getName().c_str(), param1.getName().c_str());
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
        std::string name1 = param1.getTypeName();
        std::string name2 = param2.getTypeName();
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
    
    //value type
    if (isVal1 && isVal2) {
        printer.printf("%s = %s %s %s;", result.getName().c_str()
                       , param1.getName().c_str(), op, param2.getName().c_str());
    }
    else if (!isVal1 && !isVal2) {
        cmpType = -1;
    }
    else {
        if (!isVal1) {
            printer.printf("if (%s == NULL) fr_throwNPE(__env);", param1.getName().c_str());
            printer.printf("if (!FR_TYPE_IS(%s, %s) )"
                           , param1.getName().c_str(), param2.getTypeName().c_str());
            if (opObj.opcode == FOp::Compare) {
                printer.printf("%s = -1;", result.getName().c_str());
            } else {
                printer.printf("%s = false;", result.getName().c_str());
            }
            
            printer.printf("else %s = FR_UNBOXING(%s, %s) %s %s;", result.getName().c_str()
                           , param1.getName().c_str(), param2.getTypeName().c_str()
                           , op, param2.getName().c_str());
        }
        else if (!isVal2) {
            printer.printf("if (%s == NULL) fr_throwNPE(__env);", param2.getName().c_str());
            printer.printf("if (!FR_TYPE_IS(%s, %s) )"
                           , param2.getName().c_str(), param1.getTypeName().c_str());
            if (opObj.opcode == FOp::Compare) {
                printer.printf("%s = -1;", result.getName().c_str());
            } else {
                printer.printf("%s = false;", result.getName().c_str());
            }
            
            printer.printf("else %s = %s %s FR_UNBOXING(%s, %s);", result.getName().c_str()
                           , param1.getName().c_str(), op
                           , param2.getName().c_str(), param1.getTypeName().c_str());
        }
    }
    
    //pointer object
    if (cmpType == -1) {
        switch (opObj.opcode) {
            case FOp::Compare: {
                printer.printf("%s = FR_VCALL(sys_Obj, compare1, (sys_Obj)%s, (sys_Obj)%s);"
                                , result.getName().c_str()
                                , param1.getName().c_str(), param2.getName().c_str());
                break;
            }
            case FOp::CompareEQ: {
                printer.printf("%s = FR_VCALL(sys_Obj, equals1, (sys_Obj)%s, (sys_Obj)%s);"
                               , result.getName().c_str()
                               , param1.getName().c_str(), param2.getName().c_str());
                break;
            }
            case FOp::CompareNE: {
                printer.printf("%s = !FR_VCALL(sys_Obj, equals1, (sys_Obj)%s, (sys_Obj)%s);"
                               , result.getName().c_str()
                               , param1.getName().c_str(), param2.getName().c_str());
                break;
            }
            case FOp::CompareLT: {
                printer.printf("%s = FR_VCALL(sys_Obj, compare1, (sys_Obj)%s, (sys_Obj)%s) < 0;"
                               , result.getName().c_str()
                               , param1.getName().c_str(), param2.getName().c_str());
                break;
            }
            case FOp::CompareLE: {
                printer.printf("%s = FR_VCALL(sys_Obj, compare1, (sys_Obj)%s, (sys_Obj)%s) <= 0;"
                               , result.getName().c_str()
                               , param1.getName().c_str(), param2.getName().c_str());
                break;
            }
            case FOp::CompareGE: {
                printer.printf("%s = FR_VCALL(sys_Obj, compare1, (sys_Obj)%s, (sys_Obj)%s) >= 0;"
                               , result.getName().c_str()
                               , param1.getName().c_str(), param2.getName().c_str());
                break;
            }
            case FOp::CompareGT: {
                printer.printf("%s = FR_VCALL(sys_Obj, compare1, (sys_Obj)%s, (sys_Obj)%s) > 0;"
                               , result.getName().c_str()
                               , param1.getName().c_str(), param2.getName().c_str());
                break;
            }
            case FOp::CompareSame: {
                printer.printf("%s = FR_VCALL(sys_Obj, compare1, (sys_Obj)%s, (sys_Obj)%s) == 0;"
                               , result.getName().c_str()
                               , param1.getName().c_str(), param2.getName().c_str());
                break;
            }
            case FOp::CompareNotSame: {
                printer.printf("%s = (sys_Obj)%s == (sys_Obj)%s;"
                               , result.getName().c_str()
                               , param1.getName().c_str(), param2.getName().c_str());
                break;
            }
            default:
                printf("ERROR:unknow cmp opcode:%d", opObj.opcode);
        }
    }
}

void RetStmt::print(Printer& printer) {
    if (isVoid) {
        printer.printf("return;");
    } else {
        printer.printf("return %s;", retValue.getName().c_str());
    }
}

void ThrowStmt::print(Printer& printer) {
    printer.printf("FR_THROW(%s);", var.getName().c_str());
}

void ExceptionStmt::print(Printer& printer) {
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
                        printer.printf("if (FR_ERR_TYPE(%s)) { "
                                       "%s = (%s)fr_getErr(__env); "
                                       "fr_clearErr(__env); goto l__%d;}"
                                ,typeName.c_str(), itr->catchVar.getName().c_str()
                                , typeName.c_str(), handler);
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

void CoerceStmt::print(Printer& printer) {
    std::string typeName1 = from.getTypeName();
    std::string typeName2 = to.getTypeName();
    
    if (typeName1 == typeName2) return;
    
    bool isVal1 = FCodeUtil::isValType(typeName1);
    bool isVal2 = FCodeUtil::isValType(typeName2);
    bool isNull1 = FCodeUtil::isNullableType(typeName1);
    bool isNull2 = FCodeUtil::isNullableType(typeName2);
    
    if (!isVal1 && !isVal2) {
        if (isNull1 && !isNull2) {
            printer.printf("%s = FR_NOT_NULL(%s, %s);", to.getName().c_str()
                           , from.getName().c_str(), typeName2.c_str());
            return;
        }
    }
    else if (!isVal1 && isVal2) {
        printer.printf("%s = FR_UNBOXING(%s, %s);"
                       , to.getName().c_str(), from.getName().c_str(), typeName2.c_str());
        return;
    }
    else if (isVal1 && !isVal2) {
        if (typeName1 == "sys_Int") {
            printer.printf("%s = (%s)FR_BOX_INT(%s);"
                           , to.getName().c_str(), typeName2.c_str(), from.getName().c_str());
        }
        else if (typeName1 == "sys_Float") {
            printer.printf("%s = (%s)FR_BOX_FLOAT(%s);"
                           , to.getName().c_str(), typeName2.c_str(), from.getName().c_str());
        }
        else if (typeName1 == "sys_Bool") {
            printer.printf("%s = (%s)FR_BOX_BOOL(%s);"
                           , to.getName().c_str(), typeName2.c_str(), from.getName().c_str());
        }
        else {
            printer.printf("FR_BOXING(%s, %s, %s, %s);"
                           , to.getName().c_str(), from.getName().c_str()
                           , typeName1.c_str(), typeName2.c_str());
        }
        return;
    }
    
    //cast
    if (safe) {
        printer.printf("%s = (%s)(%s);", to.getName().c_str()
                   , typeName2.c_str(), from.getName().c_str());
    } else {
        std::string toTypeName = FCodeUtil::getTypeRefName(curPod, toType, false);
        printer.printf("%s = FR_SAFE_CAST(%s, %s, %s);", to.getName().c_str()
                       , from.getName().c_str() , toTypeName.c_str(), typeName2.c_str());
    }
}

void TypeCheckStmt::print(Printer& printer) {
    std::string typeName = FCodeUtil::getTypeRefName(curPod, type, false);
    if (isOrAs) {
        printer.printf("%s = FR_TYPE_IS(%s, %s);"
                       , result.getName().c_str(), obj.getName().c_str(), typeName.c_str());
    } else {
        printer.printf("%s = FR_TYPE_AS(%s, %s);"
                       , result.getName().c_str(), obj.getName().c_str(), typeName.c_str());
    }
}
