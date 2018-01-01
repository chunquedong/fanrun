
class ExceptionTest
{
  static Int testSimple() {
    res := 100
    try {
      if (res > 50) return res
      res *= 2
    }
    catch (Err e) {
      e.trace
    }
    return res
  }

  static Int testNest() {
    res := 100
    try {
      if (res > 50) return res
      try {
        res *= 2
      }
      catch {
      }
      finally {
        res = 200
      }
      if (res > 50) return res
    }
    catch (Err e) {
      e.trace
    }
    return res
  }


  static Int test(Int a) {
    Int res := 100
    try
    {
      if (a > 5) { throw Err() }
      if (a < 5) { return -1 }
      res = 10
    }
    catch (sys::ArgErr e)
    {
      if (a > 6) { throw e }
      if (a < 7) { return -1 }
      res = 20
    }
    catch {
      if (a > 7) { throw Err() }
      if (a < 7) { return -1 }
      res = 30
    }
    finally {
      if (a > 8) { throw Err() }
      //if (a < 0) { return -1 }
      res = 40
    }
    return res
  }

  static Void main() {
    r := test(6)
    echo(r)
  }
}


