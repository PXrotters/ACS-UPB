object Utils {
  val people : Table = Table(
    "People",
    List(
      Map("id" -> "1", "name" -> "John", "age" -> "23", "address" -> "123 Main St"),
      Map("id" -> "2", "name" -> "Jane", "age" -> "27", "address" -> "456 Elm St"),
      Map("id" -> "3", "name" -> "Joe", "age" -> "30", "address" -> "789 Maple St"),
      Map("id" -> "4", "name" -> "Jill", "age" -> "25", "address" -> "101 Oak St"),
      Map("id" -> "5", "name" -> "Jack", "age" -> "27", "address" -> "112 Pine St"),
      Map("id" -> "6", "name" -> "Jen", "age" -> "24", "address" -> "131 Cedar St"),
      Map("id" -> "7", "name" -> "Jim", "age" -> "26", "address" -> "141 Birch St"),
      Map("id" -> "8", "name" -> "Jesse", "age" -> "29", "address" -> "151 Spruce St"),
      Map("id" -> "9", "name" -> "Jenny", "age" -> "23", "address" -> "161 Fir St"),
      Map("id" -> "10", "name" -> "Jerry", "age" -> "28", "address" -> "171 Larch St")
    )
  )

  val peopleStr: String =
    """|id,name,age,address
       |1,John,23,123 Main St
       |2,Jane,27,456 Elm St
       |3,Joe,30,789 Maple St
       |4,Jill,25,101 Oak St
       |5,Jack,27,112 Pine St
       |6,Jen,24,131 Cedar St
       |7,Jim,26,141 Birch St
       |8,Jesse,29,151 Spruce St
       |9,Jenny,23,161 Fir St
       |10,Jerry,28,171 Larch St""".stripMargin

  val jobs : Table = Table(
    "Jobs",
    List(
      Map("id" -> "1", "title" -> "Engineer", "salary" -> "100000", "person_name" -> "John"),
      Map("id" -> "2", "title" -> "Manager", "salary" -> "200000", "person_name" -> "Jane"),
      Map("id" -> "3", "title" -> "CEO", "salary" -> "300000", "person_name" -> "Joe"),
      Map("id" -> "4", "title" -> "Banker", "salary" -> "150000", "person_name" -> "Mona"),
      Map("id" -> "5", "title" -> "Doctor", "salary" -> "200000", "person_name" -> "Jack"),
      Map("id" -> "6", "title" -> "Nurse", "salary" -> "100000", "person_name" -> "Jen"),
      Map("id" -> "7", "title" -> "Teacher", "salary" -> "80000", "person_name" -> "Maria"),
      Map("id" -> "8", "title" -> "Engineer", "salary" -> "120000", "person_name" -> "Mimi"),
      Map("id" -> "9", "title" -> "Programmer", "salary" -> "250000", "person_name" -> "Jenny"),
      Map("id" -> "10", "title" -> "Teacher", "salary" -> "400000", "person_name" -> "Jerry")
    )
  )

  val jobsStr: String =
    """|id,title,salary,person_name
       |1,Engineer,100000,John
       |2,Manager,200000,Jane
       |3,CEO,300000,Joe
       |4,Banker,150000,Mona
       |5,Doctor,200000,Jack
       |6,Nurse,100000,Jen
       |7,Teacher,80000,Maria
       |8,Engineer,120000,Mimi
       |9,Programmer,250000,Jenny
       |10,Teacher,400000,Jerry""".stripMargin

  val hobbies: Table = Table(
    "Hobbies",
    List(
      Map("id" -> "1", "name" -> "John", "hobby" -> "Basketball"),
      Map("id" -> "2", "name" -> "Jane", "hobby" -> "Skiing"),
      Map("id" -> "3", "name" -> "Joe", "hobby" -> "Football"),
      Map("id" -> "4", "name" -> "Mona", "hobby" -> "Painting"),
      Map("id" -> "5", "name" -> "Jack", "hobby" -> "Clay modeling"),
      Map("id" -> "6", "name" -> "Jen", "hobby" -> "Film making"),
      Map("id" -> "7", "name" -> "Maria", "hobby" -> "Skin care"),
      Map("id" -> "8", "name" -> "Mimi", "hobby" -> "Music"),
      Map("id" -> "9", "name" -> "Jenny", "hobby" -> "Makeup"),
      Map("id" -> "10", "name" -> "Jerry", "hobby" -> "Dancing")
    )

  )

  val hobbiesStr: String =
    """|id,name,hobby
       |1,John,Basketball
       |2,Jane,Skiing
       |3,Joe,Football
       |4,Mona,Painting
       |5,Jack,Clay modeling
       |6,Jen,Film making
       |7,Maria,Skin care
       |8,Mimi,Music
       |9,Jenny,Makeup
       |10,Jerry,Dancing""".stripMargin

  val db1 = Database(
    List(people, jobs, hobbies)
  )

  val db2 = Database(
    List(
      Table("1", List()),
      Table("2", List()),
      Table("3", List()),
      Table("4", List()),
      Table("5", List()),
      Table("6", List()),
      Table("7", List()),
      Table("8", List()),
      Table("9", List()),
      Table("10", List())
    ))
}