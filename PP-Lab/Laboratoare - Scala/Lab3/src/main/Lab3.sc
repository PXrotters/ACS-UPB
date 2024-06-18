import scala.annotation.tailrec

// 3.1.1
@tailrec
def atLeastk(k: Int, l: List[Int]): Boolean = {
  if (k == 0) true
  else l match {
    case Nil => false
    case _ :: tail => atLeastk(k - 1, tail)
  }
}

@tailrec
def atLeastkPred(pred: Int => Boolean)(k: Int, l: List[Int]): Boolean = {
  if (k == 0) true
  else l match {
    case Nil => false
    case head :: tail =>
      if (pred(head)) atLeastkPred(pred)(k - 1, tail)
      else atLeastkPred(pred)(k, tail)
  }
}

// 3.1.2
def take(n: Int, l: List[Int]): List[Int] = {
  (n, l) match {
    case (0, _) => Nil
    case (_, Nil) => Nil
    case (_, head :: tail) => head :: take(n - 1, tail)
  }
}

take(3, List(1, 2, 3, 4, 5))

// 3.1.3
@tailrec
def drop(n: Int, l: List[Int]): List[Int] = {
  (n, l) match {
    case (0, _) => l
    case (_, Nil) => Nil
    case (_, _ :: tail) => drop(n - 1, tail)
  }
}
drop(3, List(1, 2, 3, 4, 5))

// 3.1.4
def takeP(p: Int => Boolean)(l: List[Int]): List[Int] = {
  l.filter(p)
}
takeP(_ % 2 == 0)(List(1, 2, 3, 4, 5, 6))

// 3.1.5
def part(p: Int => Boolean)(l: List[Int]): (List[Int], List[Int]) = {
  l.partition(p)
}
part(_ % 2 == 0)(List(1, 2, 3, 4, 5, 6))

// 3.1.6
def rev(l: List[Int]): List[Int] = {
  l.foldLeft(List[Int]())((acc, elem) => elem :: acc)
}
rev(List(1, 2, 3, 4, 5, 6))

// 3.2
type Str = List[Char]
val l: List[Str] = List("matei@gmail.com", "mihai@gmail.com", "tEst@mail.com", "email@email.com", "short@ax.ro").map(x => x.toList)

// 3.2.1
def remUpper(list: List[Str]): List[Str] = {
  list.map(_.filter(_.isLower))
}
remUpper(l)

// 3.2.2
def longer(k: Int, list: List[Str]): List[Str] = {
  list.filter(_.length <= k)
}
longer(14, List("matei@gmail.com".toList, "tEst@mail.com".toList))


// 3.2.3
def howMany(k: Int)(list: List[Str]): Int = {
  list.foldRight(0)((str, count) => if (str.length > k) count + 1 else count)
}
howMany(10)(List("matei@gmail.com".toList, "tEst@mail.com".toList))

// 3.2.4
def mySplit(l: Str, sep: Char): List[Str] = {
  l.foldRight(List[Str](Nil)) { (ch, acc) =>
    if (ch == sep) Nil :: acc
    else (ch :: acc.head) :: acc.tail
  }
}
mySplit("a,b,c".toList, ',')

// 3.2.5
def domains(list: List[Str]): List[Str] = {
  list.map { email =>
    val domain = email.dropWhile(_ != '@').drop(1).dropWhile(_ != '.').drop(1)
    domain.takeWhile(_ != '.')
  }
}
domains(List("matei@gmail.com".toList, "mihai@gmail.com".toList))

// 3.3
val l2 = List(1,2,3,4,5,6,7,8,9)
l2.take(3)
l2.drop(3)
l2.partition(_%2 == 0)

val gradebook: List[(Str, Int)] = List((List('G'),3), (List('F'), 10), (List('M'),6), (List('P'),4))

type Gradebook = List[(Str,Int)] //the type Gradebook now refers to a list of pairs of String and Int

// 3.3.1
def increment(g: Gradebook, p: (Str, Int) => Boolean): Gradebook = {
  g.map { case (name, grade) =>
    if (p(name, grade)) (name, grade + 1)
    else (name, grade)
  }
}
increment(gradebook, (_, grade) => grade >= 5)

// 3.3.2
def average(g: Gradebook): Double = {
  val (sum, count) = g.foldRight((0, 0)) { case ((_, grade), (accSum, accCount)) =>
    (accSum + grade, accCount + 1)
  }
  sum.toDouble / count
}
average(gradebook)

// 3.3.3
def pass(g: Gradebook): List[Str] = {
  g.filter(_._2 >= 5).map(_._1)
}
pass(gradebook)

// 3.3.4
def mergeSort(l: Gradebook): Gradebook = {
  def merge(u: Gradebook, v: Gradebook): Gradebook = (u, v) match {
    case (Nil, _) => v
    case (_, Nil) => u
    case ((name1, grade1) :: tail1, (name2, grade2) :: tail2) =>
      if (grade1 < grade2) (name1, grade1) :: merge(tail1, v)
      else (name2, grade2) :: merge(u, tail2)
  }

  val n = l.length / 2
  if (n == 0) l
  else {
    val (left, right) = l.splitAt(n)
    merge(mergeSort(left), mergeSort(right))
  }
}
mergeSort(gradebook)

// 3.3.5
def honorsList(g: Gradebook): List[Str] = {
  mergeSort(g).filter(_._2 >= 5).map(_._1).reverse
}
honorsList(gradebook)
