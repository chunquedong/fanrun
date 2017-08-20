//
// Copyright (c) 2010, chunquedong
// Licensed under the Academic Free License version 3.0
//
// History:
//   2011-4-2  Jed Young  Creation
//

native class ByteArray {
   new make(Int size)

   @Operator Int get(Int pos)

   @Operator Int set(Int pos, Int val)

   Int size()

   Bool realloc(Int newSize)

   This copyFrom(ByteArray that, Int thatOffset, Int thisOffset, Int length)

   protected Void finalize()
}

