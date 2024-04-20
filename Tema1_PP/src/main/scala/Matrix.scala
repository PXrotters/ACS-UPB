import scala.annotation.targetName

type Mat = List[List[Double]]

class Matrix(m: Option[List[List[Double]]]) {
  def transpose: Matrix = {
    val transposedMatrix = m match {
      case Some(data) =>
        val transposed = if (data.nonEmpty) {
          val numCols = data.head.length
          val numRows = data.length
          // Folosim tabulate pentru a crea o matrice de numCols x numRows
          Array.tabulate(numCols, numRows)((i, j) => data(j)(i)).toList.map(_.toList)
        } else {
          Nil
        }
        Some(transposed)
      case None =>
        None
    }
    new Matrix(transposedMatrix)
  }

  def map(f: Double => Double): Matrix = data match {
    case Some(matrixData) =>
      // Aplicam functia "f" pe fiecare element din matrice
      val newData = matrixData.map { row =>
        row.map { element =>
          f(element)
        }
      }
      new Matrix(Some(newData))
    case None => new Matrix(None)
  }

  @targetName("multiplication")
  def *(other: Matrix): Matrix = (m, other.data) match {
    case (Some(data1), Some(data2)) if data1.headOption.exists(_.length == data2.length) =>
      val resultData = data1.map(row1 =>
        data2.transpose.map(col2 =>
          row1.zip(col2).map { case (a, b) => a * b }.sum
        )
      )
      new Matrix(Some(resultData))
    case _ => new Matrix(None)
  }

  @targetName("addColumn")
  def ++(x: Double): Matrix = m match {
    case Some(data) => new Matrix(Some(data.map(row => row :+ x)))
    case None => new Matrix(None)
  }

  @targetName("subtraction")
  def -(other: Matrix): Matrix = (m, other.data) match {
    case (Some(data1), Some(data2)) if data1.length == data2.length && data1.headOption.exists(_.length == data2.headOption.map(_.length).getOrElse(0)) =>
      new Matrix(Some(data1.zip(data2).map { case (row1, row2) => row1.zip(row2).map { case (elem1, elem2) => elem1 - elem2 } }))
    case _ => new Matrix(None)
  }


  def data: Option[Mat] = m

  def height: Option[Int] = m.map(_.length)  // Returnam numarul de elemente al fiecarei subliste

  def width: Option[Int] = m.map(_.headOption.map(_.length).getOrElse(0))  // Returnam numarul de coloane (latimea)

  override def toString: String = m match {
    case Some(data) => data.map(_.mkString(", ")).mkString("\n")
    case None => "None"
  }
}

object Matrix {
  def apply(data: Mat): Matrix = new Matrix(Some(data))

  def apply(data: Option[Mat]): Matrix = new Matrix(data)

  def apply(dataset: Dataset): Matrix = {
    // Eliminam prima linie si aplicam dobule pe restul elementelor
    val matrixData = dataset.data.drop(1).map(_.map(_.toDouble))
    new Matrix(Some(matrixData))  // Returnam o noua instanta a lui Matrix
  }
}