
class Main
{
  static Int testIR(Int s) {
    a := 2 * (s > 1 ? 10 : 11)
    return a
  }

  static Int testIR2(Int s) {
    b := 0
    if (s > 2) {
      a := 10
      b = a * b
    } else {
      a := "11"
      b = a.size * b
    }
    return b
  }
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
/*
  static Void testExpr(Int a) {
    i := a + 1 + (a>0?3:4)
    echo("" + i)
  }

  static Void testFor() {
    Int a := 0
    Int sum := 0
    for (i := a; i < 1000000; ++i) {
      sum += i
    }
    echo(sum)
  }

  static Void testBranch() {
    Str s := "Hello"
    if (s.size > 0) {
      echo(s)
    } else {
      echo("empty")
    }
  }

  Int i
  new make(Int x) {
    i = x
  }

  Void testDefaultParam(Int x := i) {
    echo(x)
  }

  Void print() {
    echo("Hello")
  }

  static Void main() {
    m := Main(2)
    m.print
    m.testDefaultParam

    testBranch
    //testExpr(1) StrBuf
    testFor
  }
  */
}


