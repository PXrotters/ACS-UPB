import org.scalatest.BeforeAndAfterAll
import org.scalatest.funspec.AnyFunSpec

class TestTable extends AnyFunSpec with BeforeAndAfterAll {

  var PUNCTAJ: Double = 0

  override def afterAll(): Unit = {
    println(s"Total punctaj: $PUNCTAJ / 17")
  }

  describe("apply") {
    it("1") {
      assert(Table("People", Utils.peopleStr).tableData == Utils.people.tableData)
      assert(Table("Jobs", Utils.jobsStr).tableData == Utils.jobs.tableData)
      assert(Table("Hobbies", Utils.hobbiesStr).tableData == Utils.hobbies.tableData)
      PUNCTAJ += 1.5
    }
  }

  describe("toString") {
    it("1") {
      assert(Utils.people.toString == Utils.peopleStr)
      assert(Utils.jobs.toString == Utils.jobsStr)
      assert(Utils.hobbies.toString == Utils.hobbiesStr)

      PUNCTAJ += 0.5
    }
  }

  describe("filter") {
    it("1") {
      // PART 1
      val filter1: FilterCond = Field("id", _ == "1") || Field("age", a => a > "23" && a < "29")
      val result1: Table = Utils.people.filter(filter1)
      val expectedResult1: Table = Table("PeopleRef",
        "id,name,age,address\n" +
          "1,John,23,123 Main St\n" +
          "2,Jane,27,456 Elm St\n" +
          "4,Jill,25,101 Oak St\n" +
          "5,Jack,27,112 Pine St\n" +
          "6,Jen,24,131 Cedar St\n" +
          "7,Jim,26,141 Birch St\n" +
          "10,Jerry,28,171 Larch St")
      assert(result1.tableData == expectedResult1.tableData)

      // PART 2
      val filter2: FilterCond = Field("salary", a => a.toInt > 100000)
      val result2: Table = Utils.jobs.filter(filter2)
      val expectedResult2: Table = Table("JobsRef",
        "id,title,salary,person_name\n" +
          "2,Manager,200000,Jane\n" +
          "3,CEO,300000,Joe\n" +
          "4,Banker,150000,Mona\n" +
          "5,Doctor,200000,Jack\n" +
          "8,Engineer,120000,Mimi\n" +
          "9,Programmer,250000,Jenny\n" +
          "10,Teacher,400000,Jerry")
      assert(result2.tableData == expectedResult2.tableData)

      // PART 3
      val filter3: FilterCond = Field("hobby", _ != "Dancing")
      val result3: Table = Utils.hobbies.filter(filter3)
      val expectedResult3: Table = Table("HobbiesRef",
        "id,name,hobby\n" +
          "1,John,Basketball\n" +
          "2,Jane,Skiing\n" +
          "3,Joe,Football\n" +
          "4,Mona,Painting\n" +
          "5,Jack,Clay modeling\n" +
          "6,Jen,Film making\n" +
          "7,Maria,Skin care\n" +
          "8,Mimi,Music\n" +
          "9,Jenny,Makeup")
      assert(result3.tableData == expectedResult3.tableData)

      PUNCTAJ += 4.5
    }
  }

  describe("delete") {
    it("1") {
      // PART 1
      val row1: Map[String, String] = Map("id" -> "1", "name" -> "John", "age" -> "23", "address" -> "123 Main St")
      val result1: Table = Utils.people.delete(row1)
      val expectedResult1: Table = Table("PeopleRef",
        "id,name,age,address\n" +
          "2,Jane,27,456 Elm St\n" +
          "3,Joe,30,789 Maple St\n" +
          "4,Jill,25,101 Oak St\n" +
          "5,Jack,27,112 Pine St\n" +
          "6,Jen,24,131 Cedar St\n" +
          "7,Jim,26,141 Birch St\n" +
          "8,Jesse,29,151 Spruce St\n" +
          "9,Jenny,23,161 Fir St\n" +
          "10,Jerry,28,171 Larch St")
      assert(result1.tableData == expectedResult1.tableData)

      // PART 2
      val row2: Map[String, String] = Map("id" -> "3", "title" -> "CEO", "salary" -> "300000", "person_name" -> "Joe")
      val result2: Table = Utils.jobs.delete(row2)
      val expectedResult2: Table = Table("JobsRef",
        "id,title,salary,person_name\n" +
          "1,Engineer,100000,John\n" +
          "2,Manager,200000,Jane\n" +
          "4,Banker,150000,Mona\n" +
          "5,Doctor,200000,Jack\n" +
          "6,Nurse,100000,Jen\n" +
          "7,Teacher,80000,Maria\n" +
          "8,Engineer,120000,Mimi\n" +
          "9,Programmer,250000,Jenny\n" +
          "10,Teacher,400000,Jerry")
      assert(result2.tableData == expectedResult2.tableData)

      // PART 3
      val row3: Map[String, String] = Map("id" -> "10", "name" -> "Jerry", "hobby" -> "Dancing_not_existing")
      val result3: Table = Utils.hobbies.delete(row3)
      assert(result3.tableData == Utils.hobbies.tableData)

      PUNCTAJ += 1.5
    }
  }

  describe("insert") {
    it("1") {
      // PART 1
      val row1: Map[String, String] = Map("id" -> "11", "name" -> "Jill", "age" -> "25", "address" -> "101 Oak St")
      val result1: Table = Utils.people.insert(row1)
      val expectedResult1: Table = Table("PeopleRef",
        "id,name,age,address\n" +
          "1,John,23,123 Main St\n" +
          "2,Jane,27,456 Elm St\n" +
          "3,Joe,30,789 Maple St\n" +
          "4,Jill,25,101 Oak St\n" +
          "5,Jack,27,112 Pine St\n" +
          "6,Jen,24,131 Cedar St\n" +
          "7,Jim,26,141 Birch St\n" +
          "8,Jesse,29,151 Spruce St\n" +
          "9,Jenny,23,161 Fir St\n" +
          "10,Jerry,28,171 Larch St\n" +
          "11,Jill,25,101 Oak St")
      assert(result1.tableData == expectedResult1.tableData)

      // PART 2
      val row2: Map[String, String] = Map("id" -> "11", "title" -> "Teacher", "salary" -> "400000", "person_name" -> "Jerry")
      val result2: Table = Utils.jobs.insert(row2)
      val expectedResult2: Table = Table("JobsRef",
        "id,title,salary,person_name\n" +
          "1,Engineer,100000,John\n" +
          "2,Manager,200000,Jane\n" +
          "3,CEO,300000,Joe\n" +
          "4,Banker,150000,Mona\n" +
          "5,Doctor,200000,Jack\n" +
          "6,Nurse,100000,Jen\n" +
          "7,Teacher,80000,Maria\n" +
          "8,Engineer,120000,Mimi\n" +
          "9,Programmer,250000,Jenny\n" +
          "10,Teacher,400000,Jerry\n" +
          "11,Teacher,400000,Jerry")
      assert(result2.tableData == expectedResult2.tableData)

      // PART 3
      val row3: Map[String, String] = Map("id" -> "3", "name" -> "Joe", "hobby" -> "Football")
      val result3: Table = Utils.hobbies.insert(row3)
      assert(result3.tableData == Utils.hobbies.tableData)

      PUNCTAJ += 1.5
    }
  }

  describe("sort") {
    it("1") {
      // PART 1
      val result1: Table = Utils.people.sort("name")
      val expectedResult1: Table = Table("PeopleRef",
        """id,name,age,address
          |5,Jack,27,112 Pine St
          |2,Jane,27,456 Elm St
          |6,Jen,24,131 Cedar St
          |9,Jenny,23,161 Fir St
          |10,Jerry,28,171 Larch St
          |8,Jesse,29,151 Spruce St
          |4,Jill,25,101 Oak St
          |7,Jim,26,141 Birch St
          |3,Joe,30,789 Maple St
          |1,John,23,123 Main St""".stripMargin)
      assert(result1.tableData == expectedResult1.tableData)

      // PART 2
      val result2: Table = Utils.jobs.sort("title")
      val expectedResult2: Table = Table("JobsRef",
        """id,title,salary,person_name
          |4,Banker,150000,Mona
          |3,CEO,300000,Joe
          |5,Doctor,200000,Jack
          |1,Engineer,100000,John
          |8,Engineer,120000,Mimi
          |2,Manager,200000,Jane
          |6,Nurse,100000,Jen
          |9,Programmer,250000,Jenny
          |7,Teacher,80000,Maria
          |10,Teacher,400000,Jerry""".stripMargin)

      assert(result2.tableData == expectedResult2.tableData)

      // PART 3
      val result3: Table = Utils.hobbies.sort("hobby")
      val expectedResult3: Table = Table("HobbiesRef",
        "id,name,hobby\n" +
          "1,John,Basketball\n" +
          "5,Jack,Clay modeling\n" +
          "10,Jerry,Dancing\n" +
          "6,Jen,Film making\n" +
          "3,Joe,Football\n" +
          "9,Jenny,Makeup\n" +
          "8,Mimi,Music\n" +
          "4,Mona,Painting\n" +
          "2,Jane,Skiing\n" +
          "7,Maria,Skin care\n")
      assert(result3.tableData == expectedResult3.tableData)

      PUNCTAJ += 1.5
    }
  }

  describe("select") {
    it("1") {
      // PART 1
      val result1: Table = Utils.people.select(List("name", "age"))
      val expectedResult1: Table = Table("PeopleRef",
        "name,age\n" +
          "John,23\n" +
          "Jane,27\n" +
          "Joe,30\n" +
          "Jill,25\n" +
          "Jack,27\n" +
          "Jen,24\n" +
          "Jim,26\n" +
          "Jesse,29\n" +
          "Jenny,23\n" +
          "Jerry,28")
      assert(result1.tableData == expectedResult1.tableData)

      // PART 2
      val result2: Table = Utils.jobs.select(List("title", "salary"))
      val expectedResult2: Table = Table("JobsRef",
        "title,salary\n" +
          "Engineer,100000\n" +
          "Manager,200000\n" +
          "CEO,300000\n" +
          "Banker,150000\n" +
          "Doctor,200000\n" +
          "Nurse,100000\n" +
          "Teacher,80000\n" +
          "Engineer,120000\n" +
          "Programmer,250000\n" +
          "Teacher,400000")
      assert(result2.tableData == expectedResult2.tableData)

      // PART 3
      val result3: Table = Utils.hobbies.select(List("name", "hobby"))
      val expectedResult3: Table = Table("HobbiesRef",
        "name,hobby\n" +
          "John,Basketball\n" +
          "Jane,Skiing\n" +
          "Joe,Football\n" +
          "Mona,Painting\n" +
          "Jack,Clay modeling\n" +
          "Jen,Film making\n" +
          "Maria,Skin care\n" +
          "Mimi,Music\n" +
          "Jenny,Makeup\n" +
          "Jerry,Dancing")
      assert(result3.tableData == expectedResult3.tableData)

      PUNCTAJ += 1.5
    }

  }

  describe("update") {
    it("1") {
      // PART 1
      val update1: Map[String, String] = Map("name" -> "John", "age" -> "74", "address" -> "123 Main St")
      val result1: Table = Utils.people.update(Field("name", _ == "John"), update1)
      val expectedResult: Table = Table("PeopleRef",
        "id,name,age,address\n" +
          "1,John,74,123 Main St\n" +
          "2,Jane,27,456 Elm St\n" +
          "3,Joe,30,789 Maple St\n" +
          "4,Jill,25,101 Oak St\n" +
          "5,Jack,27,112 Pine St\n" +
          "6,Jen,24,131 Cedar St\n" +
          "7,Jim,26,141 Birch St\n" +
          "8,Jesse,29,151 Spruce St\n" +
          "9,Jenny,23,161 Fir St\n" +
          "10,Jerry,28,171 Larch St")
      assert(result1.tableData == expectedResult.tableData)

      // PART 2
      val update2: Map[String, String] = Map("title" -> "Drug Dealer", "salary" -> "8000000000")
      val result2: Table = Utils.jobs.update(Field("title", _ == "Engineer"), update2)
      val expectedResult2: Table = Table("JobsRef",
        "id,title,salary,person_name\n" +
          "1,Drug Dealer,8000000000,John\n" +
          "2,Manager,200000,Jane\n" +
          "3,CEO,300000,Joe\n" +
          "4,Banker,150000,Mona\n" +
          "5,Doctor,200000,Jack\n" +
          "6,Nurse,100000,Jen\n" +
          "7,Teacher,80000,Maria\n" +
          "8,Drug Dealer,8000000000,Mimi\n" +
          "9,Programmer,250000,Jenny\n" +
          "10,Teacher,400000,Jerry")
      assert(result2.tableData == expectedResult2.tableData)

      // PART 3
      val update3: Map[String, String] = Map("name" -> "Jerry", "hobby" -> "Dancing")
      val result3: Table = Utils.hobbies.update(Field("name", _ == "Jerry"), update3)
      assert(result3.tableData == Utils.hobbies.tableData)

      PUNCTAJ += 4.5
    }
  }
}