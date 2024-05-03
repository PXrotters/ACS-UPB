case class Database(tables: List[Table]) {
  override def toString: String = {
    tables.map(_.toString).mkString("\n\n")
  }

  def create(tableName: String): Database = {
    if (!tables.exists(_.tableName == tableName)) {
      val newTable = Table(tableName, List.empty)
      Database(tables :+ newTable) // Adaugam tabela nou creata la sfarsitul listei de tabele
    } else {
      this // Returnam baza de date nemodificata daca tabela exista deja
    }
  }

  def drop(tableName: String): Database = {
    // Cream o lista filtrata care elimina toate elementele care au acelasi nume ca si tableName
    val updatedTables = tables.filterNot(_.tableName == tableName)
    Database(updatedTables)
  }

  def selectTables(tableNames: List[String]): Option[Database] = {
    // Filtram daca numele fiecarei tabele din tables se gaseste in lista tableNames
    val selectedTables = tables.filter(table => tableNames.contains(table.tableName))
    if (selectedTables.length == tableNames.length) {
      /* Daca numarul de tabele selectate este egal cu numarul de tabele specificate in tableNames atunci intoarcem
      Some care contine o noua instanta a bazei de data Database */
      Some(Database(selectedTables))
    } else {
      None
    }
  }

  def join(table1Name: String, column1Name: String, table2Name: String, column2Name: String): Option[Table] = {
    // Cautam tabelele cu numele respective in tables
    val table1Option = tables.find(_.tableName == table1Name)
    val table2Option = tables.find(_.tableName == table2Name)

    // Verificam daca una dintre tabele nu a fost gasita
    if (table1Option.isEmpty || table2Option.isEmpty) return None

    // Obtinem lista de date tableData a tabelelor gasite si le stocam separat
    val table1Data = table1Option.get.tableData
    val table2Data = table2Option.get.tableData

    // Retinem numele coloanelor pe care le folosim in unirea datelor
    val joinColumn1 = column1Name
    val joinColumn2 = column2Name

    val joinedData = for {
      // Retinem cate un rand din fiecare tabela
      row1 <- table1Data
      row2 <- table2Data
      if row1(joinColumn1) == row2(joinColumn2) || (row1(joinColumn1) == "" && row2(joinColumn2) == "")
    } yield {
      val joinedRow = row1 ++ row2.view.filterKeys(_ != joinColumn2)
        .map { case (k, v2) =>
          val v1 = row1.getOrElse(k, "")
          val newValue = if (v1.isEmpty) v2 else if (v1 != v2) s"$v1;$v2" else v1
          k -> newValue
        }.toMap
      joinedRow
    }

    val additionalRowsTable1 = table1Data.view.filterNot(row1 => joinedData.exists(joinedRow => joinedRow(joinColumn1) == row1(joinColumn1)))
      .map(row1 => {
        val newRow = row1 ++ table2Data.head.view.filterKeys(_ != joinColumn2).map { case (k, _) => k -> row1.getOrElse(k, "") }
        newRow
      })

    val table1Opt = tables.find(_.name == table1Name)
    val table2Opt = tables.find(_.name == table2Name)

    (table1Opt, table2Opt) match {
      case (Some(table1), Some(table2)) =>
        // Extragem coloanele specificate pentru join
        val columnIndex1 = table1.header.indexOf(column1Name)
        val columnIndex2 = table2.header.indexOf(column2Name)

        // Realizam unirea randurilor din tabele
        val joinedData1 = for {
          row1 <- table1.data
          row2 <- table2.data
          if row1(column1Name) == row2(column2Name) || (row1(column1Name).isEmpty && row2(column2Name).isEmpty)
        } yield {
          val newRow = row1 ++ row2
          val updatedValue = if (row1(column1Name).isEmpty) row2(column2Name) else row1(column1Name)
          val updatedRow = newRow.updated(column1Name, updatedValue)
          updatedRow
        }

        val table1Data = table1Opt.get.tableData
        val table2Data = table2Opt.get.tableData

        val missingRowsTable2 = for {
          row2 <- table2.data
          if !joinedData1.exists(row => row(column2Name) == row2(column2Name))
        } yield {
          val newRow = (table1.header.map(_ -> "").toMap + (column1Name -> row2(column2Name))) ++ row2.view.filterKeys(k => k != column2Name && k != column2Name)
          newRow
        }

        val newTableData = joinedData ++ additionalRowsTable1 ++ missingRowsTable2
        val newTableName = s"$table1Name$table2Name"
        val newTable = Table(newTableName, newTableData.map(_.toMap))
        Some(newTable)

      case _ =>
        None
    }
  }

  def apply(i: Int): Table = {
      tables(i)
    }
}
