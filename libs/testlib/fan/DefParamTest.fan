
class DefParamTest
{
  static const Int i := 1

  static Int defParam(Int a, Int s := i) { s }

  static Int testIR3(Int s) {
    a := 2 * (s > 1 ? defParam(0) : defParam(0, 3))
    return a
  }

  static Void main() {
    p1 := DefParamTest()
    p2 := DefParamTest()
    echo(p1 <=> p2)
    echo(defParam(0))
  }
}


