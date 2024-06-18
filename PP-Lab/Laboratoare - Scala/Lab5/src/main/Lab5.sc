import scala.annotation.targetName
import scala.language.implicitConversions
// 5.1

class Animal(name: String) {
  override def toString: String = name
}
case class Cat(name: String) extends Animal(name)
case class Dog(name: String) extends Animal(name)

// 5.1.1
class Carrier[+T <: Animal](val content: T)

// 5.1.2
val catCarrier: Carrier[Cat] = new Carrier[Cat](Cat("Felix"))  // creeaza o instanta specifica petru Cat
val animalCarrier: Carrier[Animal] = catCarrier  // functioneaza datorita covariantei
// val dogCarrier: Carrier[Dog] = new Carrier[Dog](Cat("Merv")) -> nu merge, deoarece incearca sa creeze o instanta
// Carrier pentru Dog folosind o instanta Cat


class Vet[T <: Animal] {
  def treat(patient: T): String = {
    "Can treat " + patient.toString
  }
}

// 5.1.3
val generalVet: Vet[Animal] = new Vet[Animal]  // merge, deoarece generalVet este de tip Vet[Animal]
//val dogVet: Vet[Dog] = generalVet -> nu merge, deoarece incearca sa atribuie un Vet[Animal] unei variabile de tip Vet[Dog]
//dogVet.treat(Cat("Bob")) -> nu merge, deoarece incearca sa trateze o pisica (Cat) cu un veterinar pentru caini Vet[Dog]
//val catVet: Vet[Cat] = new Vet[Dog] -> nu merge, deoarece incearca sa atribuie un Vet[Dog] unei variabile de tip Vet[Cat]

// 5.1.4
object Ord extends Enumeration {
  type Ord = Value
  val LT, EQ, GT = Value
}

class Comparator[T <: Animal] {
  import Ord._
  def compare(o1: T, o2: T): Ord = {
    if (o1.toString < o2.toString) LT
    else if (o1.toString == o2.toString) EQ
    else GT
  }
}

// 5.1.5
def detFirst(lst: List[Animal]): Animal = {
  val comparator = new Comparator[Animal]
  lst.reduceLeft((a1, a2) => if (comparator.compare(a1, a2) == Ord.LT) a1 else a2)
}

// 5.1.6
def apply(g: List[Animal] => Animal)(lst: List[Animal]): Animal = {
  g(lst)
}
def getFirstAnimal(lst: List[Cat]): Cat = lst.head  //primeste o lista de pisici si returneaza prima pisica din lista

// 5.2.1
trait BoolExpr {
  def getVars: List[String]
  def eval(store: Map[String, Boolean]): Boolean
}

case object True extends BoolExpr {
  def getVars: List[String] = Nil
  def eval(store: Map[String, Boolean]): Boolean = true
}

case object False extends BoolExpr {
  def getVars: List[String] = Nil
  def eval(store: Map[String, Boolean]): Boolean = false
}

case class Symbol(s: String) extends BoolExpr {
  def getVars: List[String] = List(s)
  def eval(store: Map[String, Boolean]): Boolean = store.getOrElse(s, false)
}

case class And(e1: BoolExpr, e2: BoolExpr) extends BoolExpr {
  def getVars: List[String] = e1.getVars ++ e2.getVars
  def eval(store: Map[String, Boolean]): Boolean = e1.eval(store) && e2.eval(store)
}

case class Or(e1: BoolExpr, e2: BoolExpr) extends BoolExpr {
  def getVars: List[String] = e1.getVars ++ e2.getVars
  def eval(store: Map[String, Boolean]): Boolean = e1.eval(store) || e2.eval(store)
}

case class Not(e: BoolExpr) extends BoolExpr {
  def getVars: List[String] = e.getVars
  def eval(store: Map[String, Boolean]): Boolean = !e.eval(store)
}

// 5.2.2
implicit def boolToExpr(b: Boolean): BoolExpr = if (b) True else False
val expr = And(Not(Or(Symbol("x"), Symbol("y"))), And(true, Symbol("z")))

// 5.2.3
extension (e: BoolExpr) {
  @targetName("AND")
  def &&(other: BoolExpr): BoolExpr = And(e, other)
  @targetName("OR")
  def ||(other: BoolExpr): BoolExpr = Or(e, other)
  @targetName("UNARY")
  def unary_~ : BoolExpr = Not(e)
}

// 5.2.6
class Solver(formula: BoolExpr) {
  type Store = Map[String, Boolean]

  def interpretations: List[Store] = {
    def generateInterpretations(vars: List[String]): List[Store] = vars match {
      case Nil => List(Map.empty[String, Boolean])
      case v :: tail =>
        val tailInterpretations = generateInterpretations(tail)
        tailInterpretations.flatMap { store =>
          List(store + (v -> true), store + (v -> false))
        }
    }

    val variables = formula.getVars
    generateInterpretations(variables)
  }

  def solve: Option[Store] = {
    val allInterpretations = interpretations
    allInterpretations.find { store =>
      formula.eval(store)
    }
  }
}