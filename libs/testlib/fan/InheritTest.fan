
class Base {
  Int i
  new make(Int x) {
    i = x
  }

  virtual Str say() { "hi" }
}

mixin Bar {
  virtual Str foo() { "bar" }
}

class Sub : Base, Bar {
  Int j
  new make(Int j) : super(0) {
    this.j = j
  }

  override Str say() { "hello" }

  override Str foo() { "sub" }

  static Void main() {
    m := Sub(1)
    echo(m.say)
    echo(m.foo)
  }
}