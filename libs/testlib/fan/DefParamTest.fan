
class DefParamTest
{
  static const Int i := 1

  static Int defParam(Int s := 0) { s }

  static Int testIR3(Int s) {
    a := 2 * (s > 1 ? defParam : defParam(3))
    return a
  }

  static Void main() {
    echo(defParam)
  }
}


