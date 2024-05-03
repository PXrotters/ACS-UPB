import org.scalatest.BeforeAndAfterAll
import org.scalatest.funspec.AnyFunSpec

class TestFilter extends AnyFunSpec with BeforeAndAfterAll {

  var PUNCTAJ: Double = 0

  override def afterAll(): Unit = {
    println(s"Total punctaj: $PUNCTAJ / 22")
  }

  describe("implicit") {
    it("1") {
      // PART 1
      val field1: Field = Field("id", _ == "John")
      val touple1: Field = ("id", (_: String) == "John")
      assert(field1.eval(Map("id" -> "John")) == touple1.eval(Map("id" -> "John")))
      assert(field1.eval(Map("id" -> "John")).get)

      // PART 2
      val field2: Field = Field("hobby", _ == "Football")
      val touple2: Field = ("hobby", (_: String) == "Football")
      assert(field2.eval(Map("hobby" -> "Football", "id" -> "John")) == touple2.eval(Map("hobby" -> "Football", "id" -> "John")))
      assert(field2.eval(Map("hobby" -> "Football", "id" -> "John")).get)

      PUNCTAJ += 1
    }
  }

  describe("syntactic sugars") {
    it("1") {
      val and: FilterCond = And(Field("id", _ == "John"), Field("hobby", _ == "Football"))
      val touple: FilterCond = ("id", (_: String) == "John") && ("hobby", (_: String) == "Football")
      assert(and.eval(Map("id" -> "John", "hobby" -> "Football")) == touple.eval(Map("id" -> "John", "hobby" -> "Football")))
      assert(and.eval(Map("id" -> "John", "hobby" -> "Football")).get)
      PUNCTAJ += 0.5
    }
    it("2") {
      val or: FilterCond = Or(Field("id", _ == "John"), Field("hobby", _ == "Football"))
      val touple: FilterCond = ("id", (_: String) == "John") || ("hobby", (_: String) == "Football")
      assert(or.eval(Map("id" -> "John", "hobby" -> "Football")) == touple.eval(Map("id" -> "John", "hobby" -> "Football")))
      assert(or.eval(Map("id" -> "John", "hobby" -> "Football")).get)
      PUNCTAJ += 0.5
    }
    it("3") {
      val not: FilterCond = Not(Field("id", _ == "John"))
      val touple: FilterCond = !!("id", (_: String) == "John")
      assert(not.eval(Map("id" -> "John")) == touple.eval(Map("id" -> "John")))
      assert(!not.eval(Map("id" -> "John")).get)
      PUNCTAJ += 0.5
    }
    it("4") {
      val equal: FilterCond = Equal(Field("id", _ == "John"), Field("hobby", _ == "Football"))
      val touple: FilterCond = ("id", (_: String) == "John") === ("hobby", (_: String) == "Football")
      assert(equal.eval(Map("id" -> "John", "hobby" -> "Football")) == touple.eval(Map("id" -> "John", "hobby" -> "Football")))
      assert(equal.eval(Map("id" -> "John", "hobby" -> "Football")).get)
      assert(!equal.eval(Map("id" -> "John", "hobby" -> "Basketball")).get)
      PUNCTAJ += 0.5
    }
  }

  describe("eval") {
    it("1") {
      val field: FilterCond = Field("id", _ == "John")
      assert(field.eval(Map("id" -> "John")).get)
      assert(!field.eval(Map("id" -> "Jack")).get)
      PUNCTAJ += 4
    }
    it("2") {
      val compound: FilterCond = Compound(
        _ && _,
        List(
          Field("id", _ == "1"),
          Field("hobby", _ == "Football"),
          Field("name", _.startsWith("J")),
          Field("name", _.endsWith("n"))
        )
      )
      assert(compound.eval(Map("id" -> "1", "hobby" -> "Football", "name" -> "John")).get)
      assert(!compound.eval(Map("id" -> "1", "hobby" -> "Football", "name" -> "Jack")).get)
      PUNCTAJ += 3
    }
    it("3") {
      val not: FilterCond = Not(Field("id", _ == "John"))
      assert(not.eval(Map("id" -> "Jack")).get)
      assert(!not.eval(Map("id" -> "John")).get)
      PUNCTAJ += 2
    }
    it("4") {
      val equal: FilterCond = Equal(Field("id", _ == "John"), Field("hobby", _ == "Football"))
      assert(equal.eval(Map("id" -> "John", "hobby" -> "Football")).get)
      assert(!equal.eval(Map("id" -> "John", "hobby" -> "Basketball")).get)
      PUNCTAJ += 2
    }
    it("5") {
      val and: FilterCond = And(Field("id", _ == "John"), Field("hobby", _ == "Football"))
      assert(and.eval(Map("id" -> "John", "hobby" -> "Football")).get)
      assert(!and.eval(Map("id" -> "John", "hobby" -> "Basketball")).get)
      PUNCTAJ += 2
    }
    it("6") {
      val or: FilterCond = Or(Field("id", _ == "John"), Field("hobby", _ == "Football"))
      assert(or.eval(Map("id" -> "John", "hobby" -> "Football")).get)
      assert(or.eval(Map("id" -> "Jack", "hobby" -> "Football")).get)
      assert(!or.eval(Map("id" -> "Jack", "hobby" -> "Basketball")).get)
      PUNCTAJ += 2
    }
    it("7") {
      val any: FilterCond = Any(List(
          Field("id", _ == "John"),
          Field("hobby", _ == "Football"),
          Field("name", _.startsWith("J")),
          Field("name", _.endsWith("n"))
        ))
      assert(any.eval(Map("id" -> "John", "hobby" -> "Football", "name" -> "John")).get)
      assert(any.eval(Map("id" -> "1", "hobby" -> "Football", "name" -> "John")).get)
      assert(any.eval(Map("id" -> "1", "hobby" -> "Football", "name" -> "Jack")).get)
      assert(!any.eval(Map("id" -> "8", "hobby" -> "Basketball", "name" -> "Dodo")).get)
      PUNCTAJ += 2
    }
    it("8") {
      val all: FilterCond = All(List(
        Field("id", _ == "John"),
        Field("hobby", _ == "Football"),
        Field("name", _.startsWith("J")),
        Field("name", _.endsWith("n"))
      ))
      assert(all.eval(Map("id" -> "John", "hobby" -> "Football", "name" -> "John")).get)
      assert(!all.eval(Map("id" -> "1", "hobby" -> "Football", "name" -> "John")).get)
      assert(!all.eval(Map("id" -> "1", "hobby" -> "Football", "name" -> "Jack")).get)
      assert(!all.eval(Map("id" -> "8", "hobby" -> "Basketball", "name" -> "Dodo")).get)
      PUNCTAJ += 2
    }
  }
}