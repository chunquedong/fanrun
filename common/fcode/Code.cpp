//
// Copyright (c) 2017, chunquedong
// Licensed under the Apache Licene 2.0
//
//  Created by chunquedong on 15/6/26.
//

#include "Code.h"
#include <stdlib.h>


FOpArg OpArgList[] =
{
    FOpArg::None,         //   0 Nop
    FOpArg::None,         //   1 LoadNull
    FOpArg::None,         //   2 LoadFalse
    FOpArg::None,         //   3 LoadTrue
    FOpArg::Int,      //   4 LoadInt
    FOpArg::Float,    //   5 LoadFloat
    FOpArg::Decimal,  //   6 LoadDecimal
    FOpArg::Str,      //   7 LoadStr
    FOpArg::Duration,      //   8 LoadDuration
    FOpArg::TypeRef,     //   9 LoadType
    FOpArg::Uri,      //  10 LoadUri
    FOpArg::Register,      //  11 LoadVar
    FOpArg::Register,      //  12 StoreVar
    FOpArg::FieldRef,    //  13 LoadInstance
    FOpArg::FieldRef,    //  14 StoreInstance
    FOpArg::FieldRef,    //  15 LoadStatic
    FOpArg::FieldRef,    //  16 StoreStatic
    FOpArg::FieldRef,    //  17 LoadMixinStatic
    FOpArg::FieldRef,    //  18 StoreMixinStatic
    FOpArg::MethodRef,   //  19 CallNew
    FOpArg::MethodRef,   //  20 CallCtor
    FOpArg::MethodRef,   //  21 CallStatic
    FOpArg::MethodRef,   //  22 CallVirtual
    FOpArg::MethodRef,   //  23 CallNonVirtual
    FOpArg::MethodRef,   //  24 CallMixinStatic
    FOpArg::MethodRef,   //  25 CallMixinVirtual
    FOpArg::MethodRef,   //  26 CallMixinNonVirtual
    FOpArg::JumpA,      //  27 Jump
    FOpArg::JumpA,      //  28 JumpTrue
    FOpArg::JumpA,      //  29 JumpFalse
    FOpArg::TypePair,  //  30 CompareEQ
    FOpArg::TypePair,  //  31 CompareNE
    FOpArg::TypePair,  //  32 Compare
    FOpArg::TypePair,  //  33 CompareLE
    FOpArg::TypePair,  //  34 CompareLT
    FOpArg::TypePair,  //  35 CompareGT
    FOpArg::TypePair,  //  36 CompareGE
    FOpArg::None,         //  37 CompareSame
    FOpArg::None,         //  38 CompareNotSame
    FOpArg::TypeRef,     //  39 CompareNull
    FOpArg::TypeRef,     //  40 CompareNotNull
    FOpArg::None,         //  41 Return
    FOpArg::TypeRef,     //  42 Pop
    FOpArg::TypeRef,     //  43 Dup
    FOpArg::TypeRef,     //  44 Is
    FOpArg::TypeRef,     //  45 As
    FOpArg::TypePair,  //  46 Coerce
    FOpArg::None,         //  47 Switch
    FOpArg::None,         //  48 Throw
    FOpArg::JumpA,      //  49 Leave
    FOpArg::JumpA,      //  50 JumpFinally
    FOpArg::None,         //  51 CatchAllStart
    FOpArg::TypeRef,     //  52 CatchErrStart
    FOpArg::None,         //  53 CatchEnd
    FOpArg::None,         //  54 FinallyStart
    FOpArg::None,         //  55 FinallyEnd
    FOpArg::MethodRef,   //  56 CallSuper
};

Code::Code() {
}

void Code::readSwitch(Buffer &buffer, FOpObj &op) {
    uint16_t count = buffer.readUInt16();
    uint16_t *table = (uint16_t*)malloc(sizeof(uint16_t)*count);
    for (int i=0; i<count; ++i) {
        table[i] = buffer.readUInt16();
    }
    op.table = table;
}

bool Code::read(Buffer &buffer) {
    buffer.readBuf(buf, true);
    return true;
}

bool Code::initOps() {
    bool ok = true;
    FOpObj op;
    buf.seek(0);
    while(!buf.isEof()) {
        ok = readOp(buf, op);
        if (!ok) {
            break;
        }
        ops.push_back(op);
    }
    return ok;
}

bool Code::readOp(Buffer &buffer, FOpObj &op) {
    int pos = (int)buffer.getPos();
    FOp opCode = (FOp)buffer.readUInt8();
    FOpArg arg = OpArgList[(int)opCode];
    op.opcode = opCode;
    op.arg = arg;
    op.i1 = 0;
    op.i2 = 0;
    op.table = NULL;
    op.pos = pos;
    
    if (opCode == FOp::Switch) {
        readSwitch(buffer, op);
    }
    else switch (arg)
    {
        case FOpArg::None:      //print();
            break;
        case FOpArg::Int:
            op.i1 = buffer.readUInt16();
            break;
        case FOpArg::Float:
            op.i1 = buffer.readUInt16();
            break;
        case FOpArg::Str:
            op.i1 = buffer.readUInt16();
            break;
        case FOpArg::Duration:
            op.i1 = buffer.readUInt16();
            break;
        case FOpArg::Uri:
            op.i1 = buffer.readUInt16();
            break;
        case FOpArg::Register:
            op.i1 = buffer.readUInt16();
            break;
        case FOpArg::TypeRef:
            op.i1 = buffer.readUInt16();
            break;
        case FOpArg::FieldRef:
            op.i1 = buffer.readUInt16();
            break;
        case FOpArg::MethodRef:
            op.i1 = buffer.readUInt16();
            break;
        case FOpArg::JumpA:
            op.i1 = buffer.readUInt16();
            break;
        case FOpArg::TypePair:
            op.i1 = buffer.readUInt16();
            op.i2 = buffer.readUInt16();
            break;
        default:
            return false;
    }
    return true;
}
