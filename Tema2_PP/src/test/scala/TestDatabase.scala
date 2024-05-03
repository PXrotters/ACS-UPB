import org.scalatest.BeforeAndAfterAll
import org.scalatest.funspec.AnyFunSpec

class TestDatabase extends AnyFunSpec with BeforeAndAfterAll {

  var PUNCTAJ: Double = 0

  override def afterAll(): Unit = {
    println(s"Total punctaj: $PUNCTAJ / 16")
  }

  describe("create") {
    it("1") {
      // PART 1
      val db1 : Database = Database(List()).create("a")
      assert(db1.tables.size == 1)
      assert(db1.tables.head.name == "a")
      assert(db1.tables.head.tableData.isEmpty)

      // PART 2
      val db2: Database = Database(List()).create("a").create("b")
      assert(db2.tables.size == 2)
      assert(db2.tables.head.name == "a")
      assert(db2.tables.head.tableData.isEmpty)
      assert(db2.tables(1).name == "b")
      assert(db2.tables(1).tableData.isEmpty)

      // PART 3
      val db3: Database = Database(List(Utils.people, Utils.hobbies))
        .create("a")
        .create("b")
        .create("c")
      assert(db3.tables.size == 5)
      assert(db3.tables.head.name == "People")
      assert(db3.tables(1).name == "Hobbies")
      assert(db3.tables(2).name == "a")
      assert(db3.tables(3).name == "b")
      assert(db3.tables(4).name == "c")
      PUNCTAJ += 1.5
    }
  }

  describe("select") {
    it("1") {
      // PART 1
      val result1: Database = Utils.db1.selectTables(List("People")).get
      assert(result1.tables.size == 1)
      assert(result1.tables.head.name == "People")

      // PART 2
      val names2: List[String] = List("1", "3", "6", "8")
      val result2: Database = Utils.db2.selectTables(names2).get
      assert(result2.tables.size == 4)
      assert(result2.tables.map(_.name) == names2)

      // PART 3
      val names3: List[String] = List("2", "4", "6", "10")
      val result3: Database = Utils.db2.selectTables(names3).get
      assert(result3.tables.size == 4)
      assert(result3.tables.map(_.name) == names3)

      PUNCTAJ += 1.5
    }
  }

  describe("drop") {
    it("1") {
      // PART 1
      val result1: Database = Utils.db1.drop("People")
      assert(result1.tables.size == 2)

      // PART 2
      val names2: List[String] = List("1", "3", "6", "8")
      val result2: Database = names2.foldLeft(Utils.db2)((acc, name) => acc.drop(name))
      assert(result2.tables.size == 6)
      assert(result2.tables.map(_.name) == List("2", "4", "5", "7", "9", "10"))

      // PART 3
      val names3: List[String] = List("2", "4", "6", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20")
      val result3: Database = names3.foldLeft(Utils.db2)((acc, name) => acc.drop(name))
      assert(result3.tables.size == 6)
      assert(result3.tables.map(_.name) == List("1", "3", "5", "7", "8", "9"))

      PUNCTAJ += 1.5
    }
  }

  describe("indexing") {
    it("1"){
      // PART 1
      val t1: Table = Utils.db1(0)
      val t2: Table = Utils.db1(1)
      val t3: Table = Utils.db1(2)
      assert(t1.name == "People")
      assert(t2.name == "Jobs")
      assert(t3.name == "Hobbies")

      // PART 2
      val tables = (1 to 10).map(i => Utils.db2(i - 1))
      assert(tables.map(_.name) == List("1", "2", "3", "4", "5", "6", "7", "8", "9", "10"))

      PUNCTAJ += 1.5
    }

  }

  describe("join") {
    it("1") {
      val people : Table = Table(
        "People",
        List(
          Map("name" -> "John", "age" -> "23", "address" -> "123 Main St"),
          Map("name" -> "Jane", "age" -> "27", "address" -> "456 Elm St"),
          Map("name" -> "Joe", "age" -> "30", "address" -> "789 Maple St"),
          Map("name" -> "Jill", "age" -> "25", "address" -> "101 Oak St"),
          Map("name" -> "Jack", "age" -> "27", "address" -> "112 Pine St"),
          Map("name" -> "Jen", "age" -> "24", "address" -> "131 Cedar St"),
          Map("name" -> "Jim", "age" -> "26", "address" -> "141 Birch St"),
          Map("name" -> "Jesse", "age" -> "29", "address" -> "151 Spruce St"),
          Map("name" -> "Jenny", "age" -> "23", "address" -> "161 Fir St"),
          Map("name" -> "Jerry", "age" -> "28", "address" -> "171 Larch St")
        )
      )

      val jobs: Table = Table(
        "Jobs",
        List(
          Map("title" -> "Engineer", "salary" -> "100000", "person_name" -> "John", "address" -> "654 Oak St"),
          Map("title" -> "Manager", "salary" -> "200000", "person_name" -> "Jane", "address" -> "123 Main St"),
          Map("title" -> "CEO", "salary" -> "300000", "person_name" -> "Joe", "address" -> "789 Maple St"),
          Map("title" -> "Banker", "salary" -> "150000", "person_name" -> "Mona", "address" -> "789 Maple St"),
          Map("title" -> "Doctor", "salary" -> "200000", "person_name" -> "Jack", "address" -> "112 Pine St"),
          Map("title" -> "Nurse", "salary" -> "100000", "person_name" -> "Jen", "address" -> "132 Cedar St"),
          Map("title" -> "Teacher", "salary" -> "80000", "person_name" -> "Jill", "address" -> "888 Elm St"),
          Map("title" -> "Engineer", "salary" -> "120000", "person_name" -> "Mimi", "address" -> "141 Birch St"),
          Map("title" -> "Programmer", "salary" -> "250000", "person_name" -> "Jenny", "address" -> "161 Fir St"),
          Map("title" -> "Teacher", "salary" -> "400000", "person_name" -> "Jerry", "address" -> "171 Larch St")
        )
      )

      val db: Database = Database(List(people, jobs))
      val result: Option[Table] = db.join("People", "name", "Jobs", "person_name")

      val expected: String = """name,age,salary,address,title
                               |John,23,100000,123 Main St;654 Oak St,Engineer
                               |Jane,27,200000,456 Elm St;123 Main St,Manager
                               |Joe,30,300000,789 Maple St,CEO
                               |Jill,25,80000,101 Oak St;888 Elm St,Teacher
                               |Jack,27,200000,112 Pine St,Doctor
                               |Jen,24,100000,131 Cedar St;132 Cedar St,Nurse
                               |Jenny,23,250000,161 Fir St,Programmer
                               |Jerry,28,400000,171 Larch St,Teacher
                               |Jim,26,,141 Birch St,
                               |Jesse,29,,151 Spruce St,
                               |Mona,,150000,789 Maple St,Banker
                               |Mimi,,120000,141 Birch St,Engineer""".stripMargin

      assert(result.get.toString == expected)
      PUNCTAJ += 10
    }
  }
}