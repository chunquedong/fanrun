//
// Copyright (c) 2017, chunquedong
// Licensed under the Apache Licene 2.0
//
//  Created by yangjiandong on 2017/8/20.
//

#include "PodLoader.h"
#include "Generator.hpp"

int main(int argc, const char * argv[]) {
    
    std::string libPath = "/Users/yangjiandong/workspace/soft/fantom-1.0.68";
    std::string pod = "sys";
    std::string outPath = "/Users/yangjiandong/workspace/code/fanrun/temp/";
  
    PodLoader podMgr;
    libPath += "/lib/fan/";
    podMgr.load(libPath, pod);
    
    Generator gen;
    gen.path = outPath;
    gen.podMgr = &podMgr;
    gen.gen("sys");
    
    puts("DONE!");
    return 0;
}
