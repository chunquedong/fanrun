//
// Copyright (c) 2017, chunquedong
// Licensed under the Apache Licene 2.0
//
//  Created by yangjiandong on 2017/8/20.
//

#include "PodLoader.h"
#include "PodGen.hpp"

// /Users/yangjiandong/workspace/code/fanx/env/ baseTest /Users/yangjiandong/workspace/code/fanrun/gen/temp/
int main(int argc, const char * argv[]) {
    std::string libPath;
    std::string pod;
    std::string outPath;
    if (argc == 4) {
        libPath = argv[1];
        pod = argv[2];
        outPath = argv[3];
    }
    else {
        printf("Usage: <envPath> <podName> <outputPath>");
        return -1;
    }
  
    PodLoader podMgr;
    libPath += "lib/fan/";
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
