import org.scalacheck.Prop.forAll
import org.scalacheck.Properties
import org.scalacheck.Gen
import org.scalacheck.Arbitrary
import org.scalacheck.Test

import scala.collection.immutable.ListMap
import Dataset._

import java.io.FileWriter
import scala.util.Random

object PropertiesDataset {

  class DatasetGenProperty(msg: String) extends Properties(msg) {
    val genDataset: Gen[Dataset] = for {
      n <- Gen.choose(2, 100)
      m <- Gen.choose(2, 100)
      data <- Gen.listOfN(n + 1, Gen.listOfN(m, Gen.double).map(_.map(_.toString)))
      // ^^ first line has column names :)
    } yield Dataset.apply(data)

    implicit val arbitraryDataset: Arbitrary[Dataset] = Arbitrary(genDataset)
  }

  object PropertiesReadCSV extends DatasetGenProperty("ReadCSV") {

    /* Aceasta proprietate citeste datseturile existente din folderul datasets.
      * Pentru fiecare dataset, se verifica daca:
      * - datasetul citit contine cel putin o virgula si un newline
      * - datasetul citit este acelasi cu cel citit din fisier
      *     -> verificarea se face prin scrierea datasetului citit
      *        intr-un fisier temporar si recitirea lui
      * - headerul datasetului citit este acelasi cu cel citit din fisier
      * - numarul de linii citite este acelasi cu cel citit din fisier
      * NOTA: Acesta nu e cod functional - NU faceti asta in tema :P */
    property("readCSV") = {
      var ok = true
      val files = new java.io.File("datasets").listFiles.filter(_.isFile).map(_.getPath)
      for f <- files do {
        val ds = Dataset.apply(f)
        val csvDS = ds.toString
        if !csvDS.contains(",") || !csvDS.contains("\n") then
          ok = false
        else {
          val fileName = "TEMPORARY.csv"
          val fw = new FileWriter(fileName)
          fw.write(csvDS)
          fw.close()
          val ds2 = Dataset.apply(fileName)
          val file = new java.io.File(fileName)
          file.delete()
          if ds2.toString != csvDS || ds.getHeader != ds2.getHeader || ds2.size != ds.size then
            ok = false
        }
      }
      ok
    }
  }

  object PropertiesSelectColumns extends DatasetGenProperty("SelectColumns") {

    /* Aceasta proprietate testeaza metoda selectColumn.
      * Se alege o coloana aleator din dataset.
      * Se creeaza un dataset nou cu acea coloana.
      * Se verifica daca selectColumn returneaza acelasi
      * dataset ca si selectColumns, cand aceasta din urma e
      * apelata cu o lista ce contine doar acea coloana.
     */
    property("selectColumn") = forAll { (ds: Dataset) =>
      val header = ds.getHeader
      val column = header(Random.nextInt(header.length))

      ds.selectColumn(column).getHeader == List(column) &&
        ds.selectColumn(column).data.zip(
          ds.selectColumns(List(column)).data).map((a, b) => a.sameElements(b)
        ).reduce(_ && _)
    }

    /* Aceasta proprietate testeaza metodele selectColumn si selectColumns.
      * Se alege un numar n aleator intre 1 si jumatatea dinnumarul de coloane din dataset.
      * Se alege cate o coloana la n pasi, incepand de la prima coloana.
      * Se creeaza un dataset nou cu acele coloane.
      * Se verifica daca datasetul nou are aceleasi coloane ca si datasetul initial,
      * comparandu-le reprezentarile sub forma de string. */
    property("selectColumns") = forAll { (ds: Dataset) =>
      val n = Random.nextInt(ds.data.head.length / 2) + 1
      val refCols = ds.data.map(_.zipWithIndex.collect { case (col, i) if i % n == 0 => col })
      val colNames = refCols.head
      val ref = Dataset(refCols).toString
      val rez = ds.selectColumns(colNames).toString
      ref == rez
    }
  }

  object PropertiesSplit extends DatasetGenProperty("Split") {

    property("split - 20 entries") = {
      val ds = Dataset.apply(List("col1", "col2")::((0 until 20).toList.map(e => List(e.toString, e.toString))))
      val factor = 0.2
      val (ds1, ds2) = ds.split(factor)

      ds2.data == List(List("col1", "col2"), List("12", "12"), List("17", "17"), List("4", "4"), List("9", "9")) &&
        ds1.data == List(List("col1", "col2"), List("0", "0"), List("1", "1"), List("10", "10"), List("11", "11"), List("13", "13"),
          List("14", "14"), List("15", "15"), List("16", "16"), List("18", "18"), List("19", "19"), List("2", "2"),
          List("3", "3"), List("5", "5"), List("6", "6"), List("7", "7"), List("8", "8"))
    }

    property("split - 120 entries") = {
      val ds = Dataset.apply(List("col1", "col2")::((0 until 120).toList.map(e => List(e.toString, e.toString))))
      val factor = 0.3
      val (ds1, ds2) = ds.split(factor)

      ds1.data == List(List("col1", "col2"), List("0", "0"), List("1", "1"), List("10", "10"),
        List("101", "101"), List("102", "102"), List("103", "103"), List("105", "105"),
        List("106", "106"), List("107", "107"), List("109", "109"), List("11", "11"),
        List("110", "110"), List("112", "112"), List("113", "113"), List("114", "114"),
        List("116", "116"), List("117", "117"), List("118", "118"), List("12", "12"),
        List("13", "13"), List("14", "14"), List("16", "16"), List("17", "17"), List("18", "18"),
        List("2", "2"), List("20", "20"), List("21", "21"), List("23", "23"), List("24", "24"),
        List("25", "25"), List("27", "27"), List("28", "28"), List("29", "29"), List("30", "30"),
        List("31", "31"), List("32", "32"), List("34", "34"), List("35", "35"), List("36", "36"),
        List("38", "38"), List("39", "39"), List("4", "4"), List("41", "41"), List("42", "42"),
        List("43", "43"), List("45", "45"), List("46", "46"), List("47", "47"), List("49", "49"),
        List("5", "5"), List("50", "50"), List("52", "52"), List("53", "53"), List("54", "54"),
        List("56", "56"), List("57", "57"), List("58", "58"), List("6", "6"), List("60", "60"),
        List("61", "61"), List("63", "63"), List("64", "64"), List("65", "65"), List("67", "67"),
        List("68", "68"), List("69", "69"), List("70", "70"), List("71", "71"), List("72", "72"),
        List("74", "74"), List("75", "75"), List("76", "76"), List("78", "78"), List("79", "79"),
        List("8", "8"), List("81", "81"), List("82", "82"), List("83", "83"), List("85", "85"),
        List("86", "86"), List("87", "87"), List("89", "89"), List("9", "9"), List("90", "90"),
        List("92", "92"), List("93", "93"), List("94", "94"), List("96", "96"), List("97", "97"),
        List("98", "98")) &&
        ds2.data == List(List("col1", "col2"), List("100", "100"), List("104", "104"),
          List("108", "108"), List("111", "111"), List("115", "115"), List("119", "119"),
          List("15", "15"), List("19", "19"), List("22", "22"), List("26", "26"), List("3", "3"),
          List("33", "33"), List("37", "37"), List("40", "40"), List("44", "44"), List("48", "48"),
          List("51", "51"), List("55", "55"), List("59", "59"), List("62", "62"), List("66", "66"),
          List("7", "7"), List("73", "73"), List("77", "77"), List("80", "80"), List("84", "84"),
          List("88", "88"), List("91", "91"), List("95", "95"), List("99", "99"))
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
      if runProperties(PropertiesReadCSV) then 15 else 0,
      if runProperties(PropertiesSelectColumns) then 15 else 0,
      if runProperties(PropertiesSplit) then 10 else 0
    )
    print("Punctaj: " + points.sum + " / 40")
  }


}