//
// Copyright (c) 2006, Brian Frank and Andy Frank
// Licensed under the Academic Free License version 3.0
//
// History:
//   16 Apr 06  Brian Frank  Creation
//

**
** Enum is the base class for enum classes defined using the 'enum'
** keyword.  An enum models a fixed range of discrete values.  Each
** value has an Int ordinal and a Str name.
**
** Every enum class implicitly has the following slots auto-generated
** by the compiler:
**   - a static const field for each name in the enum's range.
**   - a static field called "vals" which contains the list of
**     discrete values indexed by ordinal.
**   - a static method called "fromStr" which maps an enum name
**     to an enum instance
**
** See `docLang::Enums` for details.
**
abstract const class FanEnum
{

//////////////////////////////////////////////////////////////////////////
// Constructor
//////////////////////////////////////////////////////////////////////////

  **
  ** Protected constructor - for compiler use only.
  **
  protected new make(sys::Int ordinal, sys::Str name) {
    this.name = name
    this.ordinal = ordinal
  }

  **
  ** Protected fromStr implementation - for compiler use only.
  ** A public static fromStr method is always auto-generated
  ** by the compiler for each enum.
  **
  protected static sys::Enum? doFromStr(sys::Type t, sys::Str name, sys::Bool checked) {
    slot := t.slot(name, false);
    //TODO
    if (slot != null)// && (slot.flags & FConst.Enum) != 0)
    {
      try
      {
        return (sys::Enum)((Field)slot).get(null)
      }
      catch (sys::Err e)
      {
      }
    }
    if (!checked) return null
    throw sys::ParseErr(t.qname +","+ name)
  }

//////////////////////////////////////////////////////////////////////////
// Obj Overrides
//////////////////////////////////////////////////////////////////////////

  **
  ** Enums are only equal if same instance using ===.
  **
  override sys::Bool equals(sys::Obj? obj) { this === obj }

  **
  ** Compare based on ordinal value.
  **
  override sys::Int compare(sys::Obj obj) {
    //TODO
    if (obj isnot sys::Enum) return 0
    return ordinal.compare((obj as sys::Enum).ordinal)
  }

  **
  ** Always returns name().
  **
  override sys::Str toStr() { name }

/////////////////////////////////////////////////////////////////////////
// Access
//////////////////////////////////////////////////////////////////////////

  **
  ** Get the programatic name for this enum.
  **
  abstract sys::Str name

  **
  ** Return ordinal value which is a zero based index into values.
  **
  abstract sys::Int ordinal

}