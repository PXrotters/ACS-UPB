import scala.annotation.tailrec
import scala.math.abs

// 1.1.1
def fact(n: Int): Int = {
  @tailrec
  def aux_fact(n: Int, acc: Int): Int =
    if (n <= 1) acc
    else aux_fact(n - 1, n * acc)

  aux_fact(n, 1)
}

fact(5)

//  1.1.2
@tailrec
def gcd(a: Int, b: Int): Int = {
  if (b == 0) a
  else gcd(b, a % b)
}

gcd(20,16)

// 1.1.3
def sumSquares(n: Int): Int = {
  @tailrec
  def aux_sumSquares(n: Int, acc: Int): Int =
    if (n <= 0) acc
    else aux_sumSquares(n - 1, acc + n * n)

  aux_sumSquares(n, 0)
}

sumSquares(3)

// 1.1.4
def sumNats(start: Int, stop: Int): Int = {
  if (start > stop) 0
  else start + sumNats(start + 1, stop)
}

def tailSumNats(start: Int, stop: Int): Int = {
  @tailrec
  def aux_sumNats(start: Int, stop: Int, acc: Int): Int =
    if (start > stop) acc
    else aux_sumNats(start + 1, stop, acc + start)

  aux_sumNats(start, stop, 0)
}

// 1.1.5
def isPrime(n: Int): Boolean = {
  if (n <= 1) false
  else !(2 until n).exists(i => n % i == 0)
}

def sumPrimes(start: Int, stop: Int): Int = {
  @tailrec
  def aux_sumPrimes(start: Int, stop: Int, acc: Int): Int =
    if (start > stop) acc
    else if (isPrime(start)) aux_sumPrimes(start + 1, stop, acc + start)
    else aux_sumPrimes(start + 1, stop, acc)

  aux_sumPrimes(start, stop, 0)
}

// 1.1.6
def subtractRange(x: Int, start: Int, stop: Int): Int = {
  @tailrec
  def aux_subtractRange(current: Int, start: Int, stop: Int): Int =
    if (start > stop) current
    else aux_subtractRange(current - start, start + 1, stop)

  aux_subtractRange(x, start, stop)
}

// 1.1.7
def nestedSubtractRange(x: Int, start: Int, stop: Int): Int = {
  def aux_nestedSubtractRange(start: Int, stop: Int): Int =
    if (start > stop) x
    else start - aux_nestedSubtractRange(start + 1, stop)

  aux_nestedSubtractRange(start, stop)
}

// 1.2.1
def improve(xn: Double, a: Double): Double = {
  0.5 * (xn + a / xn)
}

// 1.2.2
def nth_guess(n: Int, a: Double): Double = {
  @tailrec
  def iterate(guess: Double, count: Int): Double = {
    if (count == 0) guess
    else iterate(improve(guess, a), count - 1)
  }

  iterate(1.0, n)
}

// 1.2.3
def acceptable(xn: Double, a: Double): Boolean = {
  abs(xn * xn - a) <= 0.001
}

// 1.2.4 - 1.2.5
def mySqrt(a: Double): Double = {
  def improve(xn: Double): Double = {
    0.5 * (xn + a / xn)
  }

  def acceptable(xn: Double): Boolean = {
    abs(xn * xn - a) / a <= 0.001
  }

  @tailrec
  def tailSqrt(estimate: Double): Double = {
    if (acceptable(estimate)) estimate
    else tailSqrt(improve(estimate))
  }

  tailSqrt(1.0)
}
