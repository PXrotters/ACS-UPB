import scala.annotation.tailrec

// 4.1
trait Nat
case object Zero extends Nat
case class Successor(x: Nat) extends Nat

// 4.1.1
def add(x: Nat, y: Nat): Nat =
  (x, y) match {
    case (Zero, _) => y
    case (_, Zero) => x
    case (Successor(x), Successor(y)) => Successor(Successor(add(x, y)))
  }
add(Successor(Successor(Zero)), Successor(Successor(Successor(Zero))))

// 4.1.2
def multiply(x: Nat, y: Nat): Nat = {
  @tailrec
  def multiplyAcc(x: Nat, y: Nat, acc: Nat): Nat =
    (x, y) match {
      case (Zero, _) => Zero
      case (_, Zero) => Zero
      case (x, Successor(Zero)) => add(acc, x)
      case (x, Successor(y)) => multiplyAcc(x, y, add(acc, x))
    }
  multiplyAcc(x, y, Zero)
}
multiply(Successor(Successor(Zero)), Successor(Successor(Successor(Zero))))

// 4.1.3
def toNat(x: Int): Nat = {
  @tailrec
  def toNatAcc(x: Int, acc: Nat): Nat =
    if (x == 0) acc
    else toNatAcc(x - 1, Successor(acc))
  toNatAcc(x, Zero)
}
toNat(5)

// 4.2.1
def realrealtrycatch(t: => Option[Int], c: => Int): Int = {
  t match {
    case Some(value) => value
    case None => c
  }
}

// 4.2.2
def toNatOpt(x: Int): Option[Nat] = {
  if (x < 0) {
    None
  } else {
    def toNatAcc(x: Int): Nat = {
      if (x == 0) {
        Zero
      } else {
        Successor(toNatAcc(x - 1))
      }
    }
    Some(toNatAcc(x))
  }
}
toNatOpt(10)
toNatOpt(-10)

// 4.2.3
def addOpt(x: Option[Nat], y: Option[Nat]): Option[Nat] = {
  (x, y) match {
    case (Some(n1), Some(n2)) => Some(add(n1, n2))
    case (Some(_), None) => x
    case (None, Some(_)) => y
    case (None, None) => None
  }
}
addOpt(Some(Successor(Successor(Zero))), Some(Successor(Zero)))

// 4.3
trait BTree
case object EmptyTree extends BTree
case class Node(value: Int, left: BTree, right: BTree) extends BTree

// 4.3.1
def depth(tree: BTree): Int = {
  tree match {
    case EmptyTree => 0
    case Node(_, left, right) => 1 + Math.max(depth(left), depth(right))
  }
}
depth(Node(1, Node(2, EmptyTree, EmptyTree), Node(3, EmptyTree, EmptyTree)))

// 4.3.2
def subtree(tree: BTree): Int = {
  tree match {
    case EmptyTree => 0
    case Node(_, left, right) => 1 + subtree(left) + subtree(right)
  }
}
subtree(Node(1, Node(2, EmptyTree, EmptyTree), Node(3, EmptyTree, EmptyTree)))

// 4.3.3
def evenChildCount(tree: BTree): Int = {
  tree match {
    case EmptyTree => 0
    case Node(_, EmptyTree, EmptyTree) => 1
    case Node(_, EmptyTree, right) => evenChildCount(right)
    case Node(_, left, EmptyTree) => evenChildCount(left)
    case Node(_, left, right) => 1 + evenChildCount(left) + evenChildCount(right)
  }
}
evenChildCount(Node(1, Node(2, EmptyTree, EmptyTree), Node(3, EmptyTree, EmptyTree)))

// 4.3.4
def flatten(tree: BTree): List[Int] = {
  tree match {
    case EmptyTree => Nil
    case Node(value, left, right) => value :: flatten(left) ::: flatten(right)
  }
}
flatten(Node(1, Node(2, EmptyTree, EmptyTree), Node(3, EmptyTree, EmptyTree)))

// 4.3.5
def countNodes(tree: BTree, cond: Int => Boolean): Int = {
  tree match {
    case EmptyTree => 0
    case Node(value, left, right) => (if (cond(value)) 1 else 0) + countNodes(left, cond) + countNodes(right, cond)
  }
}
countNodes(Node(1, Node(2, EmptyTree, EmptyTree), Node(3, EmptyTree, EmptyTree)), _ % 2 == 0)

// 4.3.6
def mirror(tree: BTree): BTree= {
  tree match {
    case EmptyTree => EmptyTree
    case Node(value, left, right) => Node(value, mirror(right), mirror(left))
  }
}
mirror(Node(1, Node(2, EmptyTree, EmptyTree), Node(3, EmptyTree, EmptyTree)))

// 4.4
trait Expr
case class Atom(a: Int) extends Expr
case class Add(e1: Expr, e2: Expr) extends Expr
case class Mult(e1: Expr, e2: Expr) extends Expr

// 4.4.1
def evaluate(e: Expr): Int = e match {
  case Atom(a) => a
  case Add(e1, e2) => evaluate(e1) + evaluate(e2)
  case Mult(e1, e2) => evaluate(e1) * evaluate(e2)
}

// 4.4.2
def simplify(e: Expr): Expr = e match {
  case Atom(_) => e
  case Add(e1, e2) =>
    val simplifiedE1 = simplify(e1)
    val simplifiedE2 = simplify(e2)
    (simplifiedE1, simplifiedE2) match {
      case (Atom(a), Atom(b)) => Atom(a + b)
      case (_, Atom(0)) => simplifiedE1
      case (Atom(0), _) => simplifiedE2
      case _ => Add(simplifiedE1, simplifiedE2)
    }
  case Mult(e1, e2) =>
    val simplifiedE1 = simplify(e1)
    val simplifiedE2 = simplify(e2)
    (simplifiedE1, simplifiedE2) match {
      case (Atom(a), Atom(b)) => Atom(a * b)
      case (_, Atom(0)) => Atom(0)
      case (Atom(0), _) => Atom(0)
      case (_, Atom(1)) => simplifiedE1
      case (Atom(1), _) => simplifiedE2
      case _ => Mult(simplifiedE1, simplifiedE2)
    }
}

// 4.4.3
def optimize(e: Expr): Expr = e match {
  case Atom(_) => e
  case Add(e1, e2) =>
    val optimizedE1 = optimize(e1)
    val optimizedE2 = optimize(e2)
    (optimizedE1, optimizedE2) match {
      case (_, Atom(0)) => optimizedE1
      case (Atom(0), _) => optimizedE2
      case _ => Add(optimizedE1, optimizedE2)
    }
  case Mult(e1, e2) =>
    val optimizedE1 = optimize(e1)
    val optimizedE2 = optimize(e2)
    (optimizedE1, optimizedE2) match {
      case (_, Atom(0)) => Atom(0)
      case (Atom(0), _) => Atom(0)
      case (_, Atom(1)) => optimizedE1
      case (Atom(1), _) => optimizedE2
      case _ => Mult(optimizedE1, optimizedE2)
    }
}

// 4.5
type Matrix = List[List[Int]]

// 4.5.1
def scalarProd(m: Matrix)(v: Int): Matrix = {
  m.map(row => row.map(_ * v))
}
scalarProd(List(List(1, 2), List(3, 4)))(2)

// 4.5.2
def hJoin(m1: Matrix, m2: Matrix): Matrix = {
  m1 zip m2 map { case (l1, l2) => l1 ::: l2 }
}
hJoin(List(List(1, 2), List(3, 4)), List(List(5, 6), List(7, 8)))

// 4.5.3
def vJoin(m1: Matrix, m2: Matrix): Matrix = {
  m1 ::: m2
}
vJoin(List(List(1, 2), List(3, 4)), List(List(5, 6), List(7, 8)))

// 4.5.4
def matSum(m1: Matrix, m2: Matrix): Matrix = {
  m1 zip m2 map { case (l1, l2) => l1 zip l2 map { case (x, y) => x + y } }
}
matSum(List(List(1, 2), List(3, 4)), List(List(5, 6), List(7, 8)))