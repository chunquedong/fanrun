#! /usr/bin/env fan
//
// Copyright (c) 2010, chunquedong
// Licensed under the Academic Free License version 3.0
//
// History:
//   2011-4-3  Jed Young  Creation
//

using build

class Build : BuildPod
{
  new make()
  {
    podName = "syslib"
    summary = "system lib"
    depends =
    [
        "sys 1.0"
    ]
    srcDirs = [`fan/native/`, `fan/lang/`, `fan/err/`, `fan/primary/`
               , `fan/reflect/`, `fan/collection/`, `fan/utils/`]
  }
}