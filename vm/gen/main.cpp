//
// Copyright (c) 2017, chunquedong
// Licensed under the Apache Licene 2.0
//
//  Created by yangjiandong on 2017/8/20.
//

#include "PodLoader.h"
#include "PodGen.hpp"

int main(int argc, const char * argv[]) {
    
    std::string libPath = "/Users/yangjiandong/workspace/code/fanCore/devEnv";
    std::string pod = "baseTest";
    std::string outPath = "/Users/yangjiandong/workspace/code/fanrun/vm/temp/";
  
    PodLoader podMgr;
    libPath += "/lib/fan/";
    podMgr.load(libPath, pod);
    
    PodGen gen(&podMgr, "sys");
    gen.gen(outPath);
    
    //PodGen gen1(&podMgr, "std");
    //gen1.gen(outPath);
    
    PodGen gen2(&podMgr, "baseTest");
    gen2.gen(outPath);
    
    puts("DONE!");
    return 0;
}
