
class Main
{

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
}


