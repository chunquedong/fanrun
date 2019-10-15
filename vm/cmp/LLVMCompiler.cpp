//
//  LLVMCompiler.cpp
//  cmp
//
//  Created by yangjiandong on 2019/10/5.
//  Copyright © 2019 yangjiandong. All rights reserved.
//

#include "LLVMCompiler.hpp"
#include "LLVMCodeGen.hpp"
#include "llvm/Bitcode/BitcodeWriter.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"

#include "MBuilder.hpp"
#include "FCodeUtil.hpp"

LLVMCompiler::LLVMCompiler() {
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();
}

LLVMCompiler::~LLVMCompiler() {
    llvm_shutdown();
}

bool LLVMCompiler::complie(FPod *fpod) {
    
    for (FType &ftype : fpod->types) {
        for (FMethod &method : ftype.methods) {
            IRMethod ir(fpod, &method);
            MBuilder builder(method.code, ir);
            builder.buildMethod(&method);
            
            LLVMCodeGen code(&ctx, &ir, method.c_mangledName);
            code.gen(ctx.module);
        }
    }
    
    if (true) {
      ctx.module->print(dbgs(), nullptr,
                      /*ShouldPreserveUseListOrder=*/false, /*IsForDebug=*/true);
    }
    
    llvm::verifyModule(*ctx.module, &llvm::errs());
    
    // Output the bitcode file to stdout
    //llvm::WriteBitcodeToFile(*ctx.module, outs());
    return true;
}


