import Dataset._
import org.scalacheck.Prop.forAll
import org.scalacheck.Properties
import org.scalacheck.Gen
import org.scalacheck.Arbitrary
import org.scalacheck.Test
import scala.collection.immutable.ListMap

object PropertiesMatrix {

  def compare_floats(a: Double, b: Double): Boolean = {
    val epsilon = 1e-5
    Math.abs(a - b) < epsilon
  }

  class MatrixGenProperty(msg: String) extends Properties(msg) {
    val genMat: Gen[Mat] = for {
      rows <- Gen.choose(1, 5)
      cols <- Gen.choose(1, 2)
      matrix <- Gen.listOfN(rows, Gen.listOfN(cols, Gen.double))
    } yield matrix

    implicit val arbMatrix: Arbitrary[Matrix] = Arbitrary {
      genMat.map(mat => Matrix(mat))
    }
  }

  object PropertiesTranspose extends MatrixGenProperty("Transpose") {

    /* Aceasta proprietate verifica daca matricea transpusa are
     * dimensiunile corecte - invers fata de matricea initiala */
    property("transpose - width & height") = forAll { (m: Matrix) =>
      val t = m.transpose
      t.width == m.height && t.height == m.width
    }

    /* Aceasta proprietate verifica daca aplicarea functiei de transpusa
     * de doua ori pe aceeasi matrice duce la matricea initiala */
    property("transpose - applied twice") = forAll { (m: Matrix) =>
      val t = m.transpose.transpose
      val t_elems = t.data.get
      val m_elems = m.data.get
      val rows = m.height
      val cols = m.width
      val res = for {
        i <- 0 until rows.get
        j <- 0 until cols.get
      } yield compare_floats(t_elems(i)(j), m_elems(i)(j))
      res.reduce(_ && _)
    }

    /* Aceasta proprietate verifica daca elementele matricei transpuse
     * sunt corecte in raport cu elementele matricei initiale.
     * Adica verific ca transpunerea este corect realizata si liniile
     * devin coloane si invers. */
    property("transpose - elems") = forAll { (m: Matrix) =>
      val t = m.transpose
      val rows = m.height
      val cols = m.width
      val t_elems = t.data.get
      val m_elems = m.data.get
      val res = for {
        i <- 0 until rows.get
        j <- 0 until cols.get
      } yield (t_elems(j)(i), m_elems(i)(j))

      res.map(pair => compare_floats(pair._1, pair._2)).reduce(_ && _)
    }

    /* Aceasta proprietate verifica daca aplic functia de transpusa
     * pe o matrice nula duce la o matrice nula */
    property("transpose - None") = {
      val emptyMatrix = Matrix(None)
      val transposedMatrix = emptyMatrix.transpose
      transposedMatrix.data.isEmpty
    }
  }

  object PropertiesMap extends MatrixGenProperty("Map") {
    /* Aceasta proprietate verifica daca aplicarea functiei map pe o matrice
     * nula duce la o matrice nula */
    property("map - None") = {
      val emptyMatrix = Matrix(None)
      val mappedMatrix = emptyMatrix.map(x => x)
      mappedMatrix.data.isEmpty
    }

    /* Aceasta proprietate verifica daca aplicarea functiei map pe o matrice
     * ii schimba elementele aplicand functia data. Fac verificarea pentru
     * fiecare element al matricei */
    property("map - function apply") = forAll { (m: Matrix) =>
      val mappedMatrix = m.map(x => x)
      val m_elems = m.data.get
      val mappedMatrix_elems = mappedMatrix.data.get
      val rows = m.height
      val cols = m.width
      val res = for {
        i <- 0 until rows.get
        j <- 0 until cols.get
      } yield compare_floats(m_elems(i)(j), mappedMatrix_elems(i)(j))
      res.reduce(_ && _)
    }
  }

  object PropertiesMinus extends MatrixGenProperty("Minus") {
    /* Aceasta proprietate verifica daca aplicarea functiei minus pe o matrice
      * nula duce la o matrice nula */
      property("minus - matrix is None") = forAll { (m: Matrix) =>
        val emptyMatrix = Matrix(None)
        val minusMatrix_1 = m - emptyMatrix
        val minusMatrix_2 = emptyMatrix - m
        minusMatrix_1.data.isEmpty && minusMatrix_2.data.isEmpty
      }

      /* Aceasta proprietate verifica daca aplicarea functiei minus pe doua matrici
       * cu dimensiuni diferite duce la o matrice nula - eroare de dimensionalitate */
      property("minus - different dimensions") = forAll { (m1: Matrix, m2: Matrix) =>
        val minusMatrix = m1 - m2
        if m1.height != m2.height || m1.width != m2.width then
          minusMatrix.data.isEmpty
        else
          minusMatrix.data.nonEmpty
      }

      /* Aceasta proprietate verifica daca aplicarea functiei minus intre 2 matrici
       * cu aceeasi dimensiune le scade pe acestea element cu element */
      property("minus - function apply") = forAll { (m: Matrix) =>
        val m2 = Matrix(List.fill(m.height.get)(List.fill(m.width.get)(Math.random())))
        val minusMatrix = m - m2
        val m_elems = m.data.get
        val m2_elems = m2.data.get
        val minusMatrix_elems = minusMatrix.data.get
        val rows = m.height
        val cols = m.width
        val res = for {
          i <- 0 until rows.get
          j <- 0 until cols.get
        } yield compare_floats(m_elems(i)(j) - m2_elems(i)(j), minusMatrix_elems(i)(j))
        res.reduce(_ && _)
      }
  }

  object PropertiesMultiply extends MatrixGenProperty("Multiply") {
    /* Aceasta proprietate verifica daca aplicarea functiei de multiply pe o matrice
      * nula duce la o matrice nula, indiferent de cealalta matrice */
    property ("multiply - matrix is None") = forAll { (m: Matrix) =>
      val emptyMatrix = Matrix(None)
      val multiplyMatrix_1 = m * emptyMatrix
      val multiplyMatrix_2 = emptyMatrix * m
      multiplyMatrix_1.data.isEmpty && multiplyMatrix_2.data.isEmpty
    }

    /* Aceasta proprietate verifica daca aplicarea functiei de multiply pe doua matrice
     * cu dimensiuni incompatibile duce la o matrice nula - eroare de dimensionalitate
     * Dimensiuni compatibile sunt daca numarul de coloane al primei matrici este egal cu
      * numarul de linii al celei de-a doua matrice */
    property("multiply - different dimensions") = forAll { (m1: Matrix, m2: Matrix) =>
      val multiplyMatrix = m1 * m2
      if m1.width != m2.height then
        multiplyMatrix.data.isEmpty
      else
        multiplyMatrix.data.nonEmpty
    }

    /* Aceasta proprietate verifica daca implementarea voastra FUNCTIONALA de inmultire
      * a matricilor este corecta. Se compara rezultatul obtinut cu o implementare procedurala
      * a inmultirii matricilor. */
    property("multiply :)") = forAll { (m1: Matrix) =>
      // YOU ARE NOT ALLOWED TO USE THIS MULTIPLICATION VERSION IN YOUR SOLUTION !!!
      // YOURS SHOULD BE WRITTEN IN A FUNCTIONAL STYLE
      def multiplyMatrices(A: List[List[Double]], B: List[List[Double]]): List[List[Double]] = {
        require(A(0).length == B.length, "Number of columns in Matrix A must be equal to number of rows in Matrix B")
        var result = List.fill(A.length)(List.fill(B(0).length)(0.0))
        for (i <- A.indices) // Loop over the rows of Matrix A
          for (j <- B(0).indices) // Loop over the columns of Matrix B
            for (k <- A(0).indices) // Loop over the columns of Matrix A / rows of Matrix B
              result = result.updated(i, result(i).updated(j, result(i)(j) + A(i)(k) * B(k)(j)))
        result
      }

      val m2 = Matrix(List.fill(m1.width.get)(List.fill(m1.width.get)(Math.random())))

      val m_elems = m1.data.get
      val t_elems = m2.data.get
      val multiplyMatrix = m1 * m2
      val multiplyMatrix_ref = Matrix(Some(multiplyMatrices(m_elems, t_elems)))
      val rows = multiplyMatrix_ref.height
      val cols = multiplyMatrix_ref.width

      val res = for {
        i <- 0 until rows.get
        j <- 0 until cols.get
      } yield compare_floats(multiplyMatrix.data.get(i)(j), multiplyMatrix_ref.data.get(i)(j))

      res.reduce(_ && _)
    }
  }

  object PropertiesColConcat extends MatrixGenProperty("Column_Concat") {
    /* Aceasta proprietate verifica daca aplicarea functiei de concatenare a unei
     * valori constante la fiecare linie pe o matrice nula duce la o matrice nula */
    property("col_concat - matrix is None") = forAll { (c: Double) =>
      val emptyMatrix = Matrix(None)
      val colConcatMatrix = emptyMatrix ++ c
      colConcatMatrix.data.isEmpty
    }

    /* Aceasta proprietate verifica daca aplicarea functiei de concatenare a unei
     * valori constante la fiecare linie pe o matrice duce la o matrice cu dimensiuni
     * corecte si verifica daca ultima coloana contine doar valoarea constanta */
    property("col_concat - last row is constant") = forAll { (m: Matrix, c: Double) =>
      val colConcatMatrix = m ++ c
      val last_col = colConcatMatrix.data.get.map(_.last)
      last_col.map(compare_floats(_, c)).reduce(_ && _) && colConcatMatrix.width.get == m.width.get + 1
    }
  }

  def runProperties(properties: Properties): Boolean = {
    var ok = true
    properties.properties.foreach { case (name, prop) =>
      println(s"Running property: $name")
      val result = Test.check(Test.Parameters.default, prop)
      println(result.status)
      ok &&= result.passed
    }
    ok
  }

  def main(args: Array[String]): Unit = {
    val points = List(
      if runProperties(PropertiesTranspose) then 5 else 0,
      if runProperties(PropertiesMap) then 5 else 0,
      if runProperties(PropertiesMinus) then 5 else 0,
      if runProperties(PropertiesMultiply) then 5 else 0,
      if runProperties(PropertiesColConcat) then 5 else 0
    )
    print("Punctaj: " + points.sum + " / 25")
  }


}