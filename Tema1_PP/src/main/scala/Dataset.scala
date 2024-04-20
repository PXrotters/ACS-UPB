import scala.collection.mutable.ListBuffer
import scala.io.Source

class Dataset(m: List[List[String]]) {
  val data: List[List[String]] = m  // Pointam cu data la adresa lui m

  override def toString: String = {
    data.map(_.mkString(",")).mkString("\n")  // Transformam listele din interiorul listei data in siruri de caractere
  }

  def selectColumn(col: String): Dataset = {
    // Cautam prima aparitie a numelui "col" in antet (prima linie din data) si retinem indexul specific
    val colIdx = data.head.indexOf(col)
    val column = data.map(row => List(row(colIdx)))  // Coloana selectata din setul de date
    new Dataset(column)  // Cream o noua instanta a lui Dataset cu lista de liste facuta anterior
  }

  def selectColumns(cols: List[String]): Dataset = {
    // Obtine indexurile coloanelor specifice
    val colIdxes = cols.flatMap(col => data.head.indexOf(col) match {
      case -1 => None // Ignora coloanele care nu se gasesc in setul de date
      case idx => Some(idx)
    })

    // Selecteaza doar coloanele in ordinea specificata
    val columns = data.map(row => colIdxes.map(idx => row(idx)))
    new Dataset(columns)
  }

  def split(percentage: Double): (Dataset, Dataset) = {
    // Sortam setul de date crescator dupa prima coloana
    val sortedData = data.tail.sortBy(row => row.head)

    // Calculam cate intrari trebuie sa fie in setul de validare
    val validationSize = math.ceil(1 / percentage).toInt - 1

    // Functie auxiliara pentru distribuirea datelor in seturile de validare si antrenament
    def distributeData(data: List[List[String]], validationSize: Int): (List[List[String]], List[List[String]]) = {
      val (training, validation) = data.zipWithIndex.partition { case (_, index) => index % (validationSize + 1) < validationSize }
      (training.map(_._1), validation.map(_._1))
    }

    // Distribuim datele in seturile de validare si antrenament
    val (trainingData, validationData) = distributeData(sortedData, validationSize)

    // Construim seturile de date corespunzatoare
    val trainingDataset = new Dataset(data.head :: trainingData)
    val validationDataset = new Dataset(data.head :: validationData)

    // Returnam perechea de dataset-uri
    (trainingDataset, validationDataset)
  }

  def size: Int = data.length  // Retinem lungimea "matricii"

  // Intoarcem randurile matricii (matricea in sine) mai putin primul rand care este header-ul
  def getRows: List[List[String]] = data.tail
  def getHeader: List[String] = data.head  // Intoarcem prima linie a "matricii" (header-ul)
}

object Dataset {
  def apply(csv_filename: String): Dataset = {
    val fin = Source.fromFile(csv_filename)  // Deschidem fisierul
    val readLines = fin.getLines().toList  // Citim liniile din fisier pe care le vom converti intr-o lista
    fin.close()  // Inchidem fisierul - oprim citirea din acesta
    val data = readLines.map(_.split(",").toList)  // Parcurgem nodurile din lines si le transformam in liste (formam matricea)
    new Dataset(data)  // Creeam o noua instanta a clasei Dataset
  }

  def apply(ds: List[List[String]]): Dataset = {
    new Dataset(ds)  // Creeam o noua instanta a clasei Dataset (o lista de liste)
  }
}
