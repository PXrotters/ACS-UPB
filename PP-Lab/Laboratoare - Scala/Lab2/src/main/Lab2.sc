import scala.annotation.tailrec

// 2.1.1
def apply(n: Int, f: Int => Int): Int = {
  f(n)
}

// 2.1.2
def doubler(): Int => Int = {
  x => x * 2
}

// 2.1.3
def trycatch(t: Int => Int, c: Int => Int)(x: Int): Int = {
  val result = t(x)
  if (result == 0) c(x) else result
}

// 2.1.4
def realtrycatch(t: => Int, c: => Int): Int = {
  val result = t
  if (result == 0) c else result
}

// 2.2.1
def foldWith(op: (Int, Int) => Int)(start: Int, stop: Int): Int = {
  @tailrec
  def tail_fold(crt: Int, acc: Int): Int = {
    if (crt > stop) acc
    else tail_fold(crt + 1, op(acc, crt))
  }
  tail_fold(start, 0)
}

// 2.2.2
def foldConditional(op: (Int, Int) => Int, p: Int => Boolean)(start: Int, stop: Int): Int = {
  @tailrec
  def tail_fold(crt: Int, acc: Int): Int = {
    if (crt > stop) acc
    else if (p(crt)) tail_fold(crt + 1, op(acc, crt))
    else tail_fold(crt + 1, acc)
  }
  tail_fold(start, 0)
}

// 2.2.3
def foldMap(op: (Int, Int) => Int, f: Int => Int)(start: Int, stop: Int): Int = {
  def map_and_fold(acc: Int, x: Int): Int = {
    op(acc, f(x))
  }
  foldWith(map_and_fold)(start, stop)
}

// 2.3.1
def multiply(x: Int)(y: Int): Int = x * y

val result = multiply(5)(3)
println(result)

// 2.3.2
def compare(x: Int)(y: Int)(z: Int): Int = {
  if (x > y && x > z) x
  else if (y > x && y > z) y
  else z
}

val rez = compare(3)(5)(1)
println(rez)

// 2.4.1
def shiftOY(line: Double => Double, delta_y: Double): Double => Double = {
  x => line(x) + delta_y
}

// 2.4.2
def shiftOX(line: Double => Double, delta_x: Double): Double => Double = {
  x => line(x - delta_x)
}

// 2.4.3
def intersect(line1: Double => Double, line2: Double => Double)(start: Int, stop: Int): Boolean = {
  (start to stop).exists(x => line1(x) == line2(x))
}
