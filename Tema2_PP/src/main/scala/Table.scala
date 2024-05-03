type Row = Map[String, String]
type Tabular = List[Row]

case class Table (tableName: String, tableData: Tabular) {

  override def toString: String = {
    val headers = header.mkString(",") // Convertim lista de nume de coloane intr-un sir CSV
    val rows = tableData.map(_.values.mkString(",")) // Convertim fiecare rand intr-un sir CSV
    (headers :: rows).mkString("\n") // Concatenam numele coloanelor cu randurile si folosim "\n" pentru a separa liniile
  }

  def insert(row: Row): Table = {
    if (!tableData.contains(row)) {
      this.copy(tableData = tableData :+ row)  // Cream o noua instanta a obiectului Table (o copie) cu randul inserat
    } else {
      this  // Cazul cand exista returnam obiectul Table fara modificare
    }
  }

  def delete(row: Row): Table = {
    // Cream o copie a obiectului Table si eliminam orice rand din tableData care este egal cu row
    this.copy(tableData = tableData.filterNot(_ == row))
  }

  def sort(column: String): Table = {
    val sortedData = tableData.sortBy(_.getOrElse(column, "")) // Sortam lista de date in functie de valoarea din coloana specificata
    this.copy(tableData = sortedData) // Cream o noua instanta a tabelului cu lista de date sortata
  }

  def update(f: FilterCond, updates: Map[String, String]): Table = {
    Table(tableName, tableData.map { row =>  // Pentru fiecare rand din tableData aplicam logica de mai jos
      if (f.eval(row).getOrElse(false)) row ++ updates else row  // Daca row indeplineste conditia f folosind metoda eval a obiectului f
      // Si intoarce Some(true) atunci se aplica actualizarile din updates folosind ++
    })
  }

  def filter(f: FilterCond): Table = {
    // Pentru fiecare row din tableData se aplica functia eval a obiectului f si daca returneza Some(true) acesta va fi inclus in lista rezultata
    val filteredData = tableData.filter(row => f.eval(row).getOrElse(false))
    Table(tableName, filteredData)
  }

  def select(columns: List[String]): Table = {
    // Pentru fiecare row din tableData se apclica operatia de mapare pentru a crea o noua lista de perechi unde cheia e col si valoarea e row
    val selectedData = tableData.map(row => columns.map(col => col -> row.getOrElse(col, "")).toMap)
    Table(tableName, selectedData)
  }

  def header: List[String] = tableData.headOption.map(_.keys.toList).getOrElse(List.empty)
  def data: Tabular = tableData
  def name: String = tableName
}

object Table {
  def apply(name: String, s: String): Table = {
    val lines = s.split("\n")
    val headers = lines.head.split(",").toList
    val data = lines.tail.map(_.split(",").toList).map(row => headers.zip(row).toMap)
    val tabularData: Tabular = data.toList // Convertim datele în tipul Tabular
    new Table(name, tabularData)
  }
}

extension (table: Table) {
  def apply(i: Int): Table = {
    Table(table.tableName, List(table.tableData(i)))
  }
}
