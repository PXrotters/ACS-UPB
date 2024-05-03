import scala.annotation.targetName
import scala.language.implicitConversions

trait FilterCond {def eval(r: Row): Option[Boolean]}

case class Field(colName: String, predicate: String => Boolean) extends FilterCond {
  override def eval(r: Row): Option[Boolean] = {
    r.get(colName).map(predicate)
  }
}

case class Compound(op: (Boolean, Boolean) => Boolean, conditions: List[FilterCond]) extends FilterCond {
  override def eval(r: Row): Option[Boolean] = {
    val results = conditions.map(_.eval(r))
    // Daca cel putin una din conditii nu a putut fi evaluata pentru randul dat intoarem None
    if (results.exists(_.isEmpty)) None
      // Altfel aplicam operatia de op pe rezultatele evaluarii folisind reduce
    else Some(results.map(_.get).reduce(op))
  }
}

case class Not(f: FilterCond) extends FilterCond {
  override def eval(r: Row): Option[Boolean] = f.eval(r).map(!_)
}

def And(f1: FilterCond, f2: FilterCond): FilterCond = Compound(_ && _, List(f1, f2))
def Or(f1: FilterCond, f2: FilterCond): FilterCond = Compound(_ || _, List(f1, f2))
def Equal(f1: FilterCond, f2: FilterCond): FilterCond = Compound(_ == _, List(f1, f2))

case class Any(fs: List[FilterCond]) extends FilterCond {
  override def eval(r: Row): Option[Boolean] = {
    val results = fs.map(_.eval(r))
    if (results.exists(_.isEmpty)) None
    else Some(results.exists(_.get))
  }
}

case class All(fs: List[FilterCond]) extends FilterCond {
  override def eval(r: Row): Option[Boolean] = {
    val results = fs.map(_.eval(r))
    if (results.exists(_.isEmpty)) None
    else Some(results.forall(_.get))
  }
}

implicit def tuple2Field(t: (String, String => Boolean)): Field = Field(t._1, t._2)

extension (f: FilterCond) {
  @targetName("equality")
  def ===(other: FilterCond): FilterCond = Equal(f, other)
  @targetName("conjunction")
  def &&(other: FilterCond): FilterCond = And(f, other)
  @targetName("disjunction")
  def ||(other: FilterCond): FilterCond = Or(f, other)
  @targetName("negation")
  def !! : FilterCond = Not(f)
}