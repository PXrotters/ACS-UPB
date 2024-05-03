import org.scalatest.BeforeAndAfterAll
import org.scalatest.funspec.AnyFunSpec

class TestSQL extends AnyFunSpec with BeforeAndAfterAll {

  var PUNCTAJ: Double = 0

  override def afterAll(): Unit = {
    println(s"Total punctaj: $PUNCTAJ / 45")
  }

  describe("TDA DB") {
    it("1") {
      val create: PP_SQL_DB = CreateTable(Utils.db1, "Rampapapam")
      val res = Utils.db1.create("Rampapapam")
      assert(create.eval.get.tables.map(_.name) == res.tables.map(_.name))
      PUNCTAJ += 2
    }
    it("2") {
      val drop: PP_SQL_DB = DropTable(Utils.db2, "7")
      val res = Utils.db2.drop("7")
      assert(drop.eval.get.tables.map(_.name) == res.tables.map(_.name))
      PUNCTAJ += 2
    }
    it("3") {
      val selectT: PP_SQL_DB = SelectTables(Utils.db2, List("1", "2", "3"))
      val res: Database = Utils.db2.selectTables(List("1", "2", "3")).get
      assert(selectT.eval.get.tables.map(_.name) == res.tables.map(_.name))
      PUNCTAJ += 2
    }
    it("4") {
      val t1: Table = Table("Sweet Brands",
        List(
          Map("name" -> "Hershey's", "type" -> "Chocolate", "country" -> "USA", "rating" -> "5"),
          Map("name" -> "M&M's", "type" -> "Chocolate", "country" -> "USA", "rating" -> "4"),
          Map("name" -> "Sour Patch Kids", "type" -> "Sour", "country" -> "USA", "rating" -> "3"),
          Map("name" -> "Skittles", "type" -> "Fruity", "country" -> "USA", "rating" -> "4"),
          Map("name" -> "Twix", "type" -> "Chocolate", "country" -> "USA", "rating" -> "4"),
          Map("name" -> "Haribo", "type" -> "Gummy", "country" -> "Germany", "rating" -> "5"),
          Map("name" -> "Lindt", "type" -> "Chocolate", "country" -> "Switzerland", "rating" -> "5"),
          Map("name" -> "Trolli", "type" -> "Gummy", "country" -> "Germany", "rating" -> "4"),
          Map("name" -> "Ferrero Rocher", "type" -> "Chocolate", "country" -> "Italy", "rating" -> "5")
        ))
      val t2: Table = Table("Sweets Prices",
        List(
          Map("name1" -> "Hershey's", "price" -> "1.50", "rating" -> "1"),
          Map("name1" -> "M&M's", "price" -> "1.25", "rating" -> "2"),
          Map("name1" -> "Prince Polo", "price" -> "1.00", "rating" -> "4"),
          Map("name1" -> "Unicorn Bar", "price" -> "2.00", "rating" -> "4"),
          Map("name1" -> "Twix", "price" -> "1.50", "rating" -> "1"),
          Map("name1" -> "Haribo", "price" -> "1.25", "rating" -> "5"),
          Map("name1" -> "Oreo", "price" -> "1.00", "rating" -> "2")
        ))

      val db: Database = Database(List(t1, t2))
      val join: PP_SQL_DB = JoinTables(db, "Sweet Brands", "name", "Sweets Prices", "name1")
      val res: String = """name,price,country,rating,type
                          |Hershey's,1.50,USA,5;1,Chocolate
                          |M&M's,1.25,USA,4;2,Chocolate
                          |Twix,1.50,USA,4;1,Chocolate
                          |Haribo,1.25,Germany,5,Gummy
                          |Sour Patch Kids,,USA,3,Sour
                          |Skittles,,USA,4,Fruity
                          |Lindt,,Switzerland,5,Chocolate
                          |Trolli,,Germany,4,Gummy
                          |Ferrero Rocher,,Italy,5,Chocolate
                          |Prince Polo,1.00,,4,
                          |Unicorn Bar,2.00,,4,
                          |Oreo,1.00,,2,""".stripMargin
      assert(join.eval.get.tables.head.toString == res)
      PUNCTAJ += 2
    }
  }

  describe("TDA Table") {
    it("1") {
      val insertRow: PP_SQL_Table = InsertRow(Utils.people,
        List(Map("id" -> "11", "name" -> "Jack", "age" -> "33", "address" -> "181 Pine St")))
      val res: Table = Utils.people.insert(
        Map("id" -> "11", "name" -> "Jack", "age" -> "33", "address" -> "181 Pine St"))
      assert(insertRow.eval.get.toString == res.toString)
      PUNCTAJ += 2
    }
    it("2") {
      val row: Row = Map("id" -> "4000", "name" -> "Julia123", "age" -> "125", "address" -> "101 Oak St")
      val updateRow: PP_SQL_Table = UpdateRow(Utils.people, Field("name", _ == "Jill"), row)
      val res: Table = Utils.people.update(Field("name", _ == "Jill"), row)
      assert(updateRow.eval.get.toString == res.toString)
      PUNCTAJ += 2
    }
    it("3") {
      val row: Row = Map("id" -> "5", "name" -> "Jack", "hobby" -> "Clay modeling")
      val deleteRow: PP_SQL_Table = DeleteRow(Utils.hobbies, row)
      val res: Table = Utils.hobbies.delete(row)
      assert(deleteRow.eval.get.toString == res.toString)
      PUNCTAJ += 2
    }
    it("4") {
      val sortTable: PP_SQL_Table = SortTable(Utils.people, "name")
      val res: Table = Utils.people.sort("name")
      assert(sortTable.eval.get.toString == res.toString)
      PUNCTAJ += 2
    }
    it("5") {
      val selectColumns = SelectTables(Utils.db1, List("People", "Hobbies"))
      val res: Database = Utils.db1.selectTables(List("People", "Hobbies")).get
      assert(selectColumns.eval.get.tables.map(_.name) == res.tables.map(_.name))
      PUNCTAJ += 2
    }
    it("6") {
      val filter: FilterCond = Not(Field("id", _ == "9"))
      val filterTable: PP_SQL_Table = FilterRows(Utils.people, filter)
      val res: Table = Utils.people.filter(filter)
      assert(filterTable.eval.get.toString == res.toString)
      PUNCTAJ += 2
    }
  }

  describe("implicits") {
    it("1") {
      val sql1 : Option[Table] = queryT((Some(Utils.people), "EXTRACT", List("id", "name")))
      val sql2 = PP_SQL_Table_Select((Some(Utils.people), "EXTRACT", List("id", "name")))
      assert(sql1.get.toString == sql2.get.eval.get.toString)
      PUNCTAJ += 1
    }
    it("2") {
      val sql1 : Option[Database] = queryDB((Some(Utils.db1), "SELECT", List("People", "Hobbies")))
      val sql2 = PP_SQL_DB_Select((Some(Utils.db1), "SELECT", List("People", "Hobbies")))
      assert(sql1.get.toString == sql2.get.eval.get.toString)
      PUNCTAJ += 1
    }
  }

  describe("prettier language") {
    it("1") {
      val err: Option[Database] = queryDB(Some(Utils.db1), "CREATE", "People")
      assert(err.contains(Utils.db1.create("People")))
      val ok: Option[Database] = queryDB(Some(Utils.db1), "CREATE", "People8")
      assert(ok.get.tables.map(_.name) == Utils.db1.create("People8").tables.map(_.name))
      PUNCTAJ += 1
      val ok2: Option[Database] = queryDB(ok, "DROP", "People8")
      assert(ok2.get.tables.map(_.name) == Utils.db1.tables.map(_.name))
      PUNCTAJ += 1
    }
    it("2") {
      val ok: Option[Database] = queryDB((Some(Utils.db1), "SELECT", List("People")))
      assert(ok.get(0).toString == Utils.people.toString)
      PUNCTAJ += 1
    }
    it("3") {
      val t1: Table = Table("Sweet Brands",
        List(
          Map("name" -> "Hershey's", "type" -> "Chocolate", "country" -> "USA", "rating" -> "5"),
          Map("name" -> "M&M's", "type" -> "Chocolate", "country" -> "USA", "rating" -> "4"),
          Map("name" -> "Sour Patch Kids", "type" -> "Sour", "country" -> "USA", "rating" -> "3"),
          Map("name" -> "Skittles", "type" -> "Fruity", "country" -> "USA", "rating" -> "4"),
          Map("name" -> "Twix", "type" -> "Chocolate", "country" -> "USA", "rating" -> "4"),
          Map("name" -> "Haribo", "type" -> "Gummy", "country" -> "Germany", "rating" -> "5"),
          Map("name" -> "Lindt", "type" -> "Chocolate", "country" -> "Switzerland", "rating" -> "5"),
          Map("name" -> "Trolli", "type" -> "Gummy", "country" -> "Germany", "rating" -> "4"),
          Map("name" -> "Ferrero Rocher", "type" -> "Chocolate", "country" -> "Italy", "rating" -> "5")
        ))
      val t2: Table = Table("Sweets Prices",
        List(
          Map("name1" -> "Hershey's", "price" -> "1.50", "rating" -> "1"),
          Map("name1" -> "M&M's", "price" -> "1.25", "rating" -> "2"),
          Map("name1" -> "Prince Polo", "price" -> "1.00", "rating" -> "4"),
          Map("name1" -> "Unicorn Bar", "price" -> "2.00", "rating" -> "4"),
          Map("name1" -> "Twix", "price" -> "1.50", "rating" -> "1"),
          Map("name1" -> "Haribo", "price" -> "1.25", "rating" -> "5"),
          Map("name1" -> "Oreo", "price" -> "1.00", "rating" -> "2")
        ))
      val db: Database = Database(List(t1, t2))
      val ok: Option[Database] = queryDB((Some(db), "JOIN", "Sweet Brands", "name", "Sweets Prices", "name1"))
      val tab: Table = ok.get(0)
      val ref: String = """name,price,country,rating,type
                          |Hershey's,1.50,USA,5;1,Chocolate
                          |M&M's,1.25,USA,4;2,Chocolate
                          |Twix,1.50,USA,4;1,Chocolate
                          |Haribo,1.25,Germany,5,Gummy
                          |Sour Patch Kids,,USA,3,Sour
                          |Skittles,,USA,4,Fruity
                          |Lindt,,Switzerland,5,Chocolate
                          |Trolli,,Germany,4,Gummy
                          |Ferrero Rocher,,Italy,5,Chocolate
                          |Prince Polo,1.00,,4,
                          |Unicorn Bar,2.00,,4,
                          |Oreo,1.00,,2,""".stripMargin
      assert(tab.toString == ref)
      PUNCTAJ += 1
    }
    it("4") {
      val sql: Option[Table] = queryT((Some(Utils.people), "INSERT",
        List(Map(
            "id" -> "10",
            "name" -> "Johnnatan",
            "age" -> "93",
            "address" -> "123 Main St"))))
      val ref: String = """id,name,age,address
                          |1,John,23,123 Main St
                          |2,Jane,27,456 Elm St
                          |3,Joe,30,789 Maple St
                          |4,Jill,25,101 Oak St
                          |5,Jack,27,112 Pine St
                          |6,Jen,24,131 Cedar St
                          |7,Jim,26,141 Birch St
                          |8,Jesse,29,151 Spruce St
                          |9,Jenny,23,161 Fir St
                          |10,Jerry,28,171 Larch St
                          |10,Johnnatan,93,123 Main St""".stripMargin
      assert(sql.get.toString == ref)
      PUNCTAJ += 1
    }
    it("5") {
      val sql: Option[Table] =  queryT((Some(Utils.hobbies), "SORT", "hobby"))
      val ref: String = """id,name,hobby
                          |1,John,Basketball
                          |5,Jack,Clay modeling
                          |10,Jerry,Dancing
                          |6,Jen,Film making
                          |3,Joe,Football
                          |9,Jenny,Makeup
                          |8,Mimi,Music
                          |4,Mona,Painting
                          |2,Jane,Skiing
                          |7,Maria,Skin care""".stripMargin
      assert(sql.get.toString == ref)
      PUNCTAJ += 1
    }
    it("6") {
      val sql: Option[Table] = queryT((Some(Utils.people), "DELETE",
        Map("id" -> "6", "name" -> "Jen", "age" -> "24", "address" -> "131 Cedar St")))
      val ref: String = """id,name,age,address
          |1,John,23,123 Main St
          |2,Jane,27,456 Elm St
          |3,Joe,30,789 Maple St
          |4,Jill,25,101 Oak St
          |5,Jack,27,112 Pine St
          |7,Jim,26,141 Birch St
          |8,Jesse,29,151 Spruce St
          |9,Jenny,23,161 Fir St
          |10,Jerry,28,171 Larch St""".stripMargin
      assert(sql.get.toString == ref)
      PUNCTAJ += 1
    }
    it("7") {
      val sql: Option[Table] =
        queryT((Some(Utils.people), "UPDATE",
          Field("name", _ == "Jenny"),
          Map("name" -> "weeeeeee")
        ))
      val ref: String = """id,name,age,address
                          |1,John,23,123 Main St
                          |2,Jane,27,456 Elm St
                          |3,Joe,30,789 Maple St
                          |4,Jill,25,101 Oak St
                          |5,Jack,27,112 Pine St
                          |6,Jen,24,131 Cedar St
                          |7,Jim,26,141 Birch St
                          |8,Jesse,29,151 Spruce St
                          |9,weeeeeee,23,161 Fir St
                          |10,Jerry,28,171 Larch St""".stripMargin
      assert(sql.get.toString == ref)
      PUNCTAJ += 1
    }
    it("8") {
      val sql: Option[Table] = queryT((Some(Utils.people), "EXTRACT", List("id", "name")))
      val ref: String = """id,name
                          |1,John
                          |2,Jane
                          |3,Joe
                          |4,Jill
                          |5,Jack
                          |6,Jen
                          |7,Jim
                          |8,Jesse
                          |9,Jenny
                          |10,Jerry""".stripMargin
      assert(sql.get.toString == ref)
      PUNCTAJ += 0
    }
    it("9") {
      val sql: Option[Table] = queryT((Some(Utils.people), "FILTER", Not(Field("id", _ == "9"))))
      val ref: String = """id,name,age,address
                          |1,John,23,123 Main St
                          |2,Jane,27,456 Elm St
                          |3,Joe,30,789 Maple St
                          |4,Jill,25,101 Oak St
                          |5,Jack,27,112 Pine St
                          |6,Jen,24,131 Cedar St
                          |7,Jim,26,141 Birch St
                          |8,Jesse,29,151 Spruce St
                          |10,Jerry,28,171 Larch St""".stripMargin
      assert(sql.get.toString == ref)
      PUNCTAJ += 0
    }
  }

  describe("killJackSparrow") {
    it("1") {
      val res: Table = Queries.killJackSparrow(Utils.people).get
      assert(res.toString ==
        """id,name,age,address
          |1,John,23,123 Main St
          |2,Jane,27,456 Elm St
          |3,Joe,30,789 Maple St
          |4,Jill,25,101 Oak St
          |6,Jen,24,131 Cedar St
          |7,Jim,26,141 Birch St
          |8,Jesse,29,151 Spruce St
          |9,Jenny,23,161 Fir St
          |10,Jerry,28,171 Larch St""".stripMargin)
      PUNCTAJ += 5
    }
  }

  describe("insertLinesThenSort") {
    it("1") {
      val res: Option[Table] = Queries.insertLinesThenSort(Utils.db1)
      val ref: String= """name,age,CNP
                         |Rosmaria,12,855532172
                         |Diana,33,255532142
                         |Tatiana,55,655532132
                         |Ana,93,455550555""".stripMargin
      assert(res.get.toString == ref)
      assert(res.get.name == "Inserted Fellas")
      PUNCTAJ += 5
    }
  }

  describe("youngAdultHobbiesJ") {
    it("1") {
      val res: Option[Table] = Queries.youngAdultHobbiesJ(Utils.db1)
      val ref: String = """name,hobby
                          |John,Basketball
                          |Jen,Film making
                          |Jenny,Makeup""".stripMargin
      assert(res.get.toString == ref)
      PUNCTAJ += 5
    }
  }



}