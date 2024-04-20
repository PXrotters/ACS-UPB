import Dataset._
import Regression._

import munit.FunSuite

class TestRegression extends FunSuite {

    val eps = 0.2 // marja de eroare de 20%
    val split = 0.1

    /*
    Testele verifica daca functia de regresie intoarce un vector de ponderi
    care sa aproximeze cat mai bine datele de intrare.

    Se verifica daca raportul dintre fiecare element al vectorului de ponderi
    si valoarea asteptata este aproape de 1, cu o marja de eroare de 0.2.

    Valorile numerice prezente in testele de mai jos sunt calculate cu ajutorul
    solutiei de referinta a temei.
    */

    test("1") {
        val file = "datasets/mediumds_1.csv"
        val (w, loss) = Regression.regression(
            file, List("feature1"), "to_predict", split, 0.1, 10)
        println("\t" + "y = "
          + w.transpose.data.get(0)(0) + "x " +
          "+ " + w.transpose.data.get(0)(1))
        val ok = w.data.get(0)
          .zip(List(30.13768873362556, -1.2960102570320688))
          .map((a, b) => a / b < 1 + eps && a / b > 1 - eps)
        println("Loss: " + loss)
        assert(ok.reduce(_ && _))
    }

    test("2") {
        val file = "datasets/bigds_1.csv"
        val (w, loss) = Regression.regression(
            file, List("feature1"), "to_predict", split, 0.1, 10)
        println("\t" + "y = "
          + w.transpose.data.get(0)(0) + "x " +
          "+ " + w.transpose.data.get(0)(1))
        val ok = w.data.get(0)
          .zip(List(62.84123952393863, -0.23918131428069359))
          .map((a, b) => a / b < 1 + eps && a / b > 1 - eps)
        println("Loss: " + loss)
        assert(ok.reduce(_ && _))
    }

    test("3") {
        val file = "datasets/bigds_2.csv"
        val (w, loss) = Regression.regression(
            file, List("feature1", "feature2"), "to_predict", split, 0.1, 1)
        println("\t" + "y = "
          + w.transpose.data.get(0)(0) + "x1 " +
          "+ " + w.transpose.data.get(0)(1) + "x2 " +
          "+ " + w.transpose.data.get(0)(2))
        val ok = w.data.get(0)
          .zip(List(2.17621276701624, 6.794738067389389, 0.14722558471179611))
          .map((a, b) => a / b < 1 + eps && a / b > 1 - eps)
        println("Loss: " + loss)
        assert(ok.reduce(_ && _))
    }

    test("4") {
        val file = "datasets/houseds.csv"
        val (w, loss) = Regression.regression(
            file, List("GrLivArea", "YearBuilt"), "SalePrice", split, 0.01, 1)
        println("\t" + "y = "
          + w.transpose.data.get(0)(0) + "x1 " +
          "+ " + w.transpose.data.get(0)(1) + "x2 " +
          "+ " + w.transpose.data.get(0)(2))
        val ok = w.data.get(0)
          .zip(List(3016079.195045662, 3564264.170022831, 1801.9062785388128))
          .map((a, b) => a / b < 1 + eps && a / b > 1 - eps)
        println("Loss: " + loss)
        assert(ok.reduce(_ && _))
    }

    test("5") {
        val file = "datasets/houseds.csv"
        val (w, loss) = Regression.regression(
            file, List("GrLivArea"), "SalePrice", split, 0.01, 1)
        println("\t" + "y = "
          + w.transpose.data.get(0)(0) + "x1 " +
          "+ " + w.transpose.data.get(0)(1))
        val ok = w.data.get(0)
          .zip(List(3020389.0442313547, 1802.6816438356163))
          .map((a, b) => a / b < 1 + eps && a / b > 1 - eps)
        println("Loss: " + loss)
        assert(ok.reduce(_ && _))
    }

    test("6") {
        val file = "datasets/mediumds_1.csv"
        val (w, loss) = Regression.regression(
            file, List("feature1"), "to_predict", split, 0.1, 5)
        println("\t" + "y = "
          + w.transpose.data.get(0)(0) + "x " +
          "+ " + w.transpose.data.get(0)(1))
        val ok = w.data.get(0)
          .zip(List(18.15636490729292, -1.0355229938376973))
          .map((a, b) => a / b < 1 + eps && a / b > 1 - eps)
        println("Loss: " + loss)
        assert(ok.reduce(_ && _))
    }

    test("7") {
        val file = "datasets/bigds_1.csv"
        val (w, loss) = Regression.regression(
            file, List("feature1"), "to_predict", split, 0.01, 5)
        println("\t" + "y = "
          + w.transpose.data.get(0)(0) + "x " +
          "+ " + w.transpose.data.get(0)(1))
        val ok = w.data.get(0)
          .zip(List(4.877868348580691, -0.03016982434403231))
          .map((a, b) => a / b < 1 + eps && a / b > 1 - eps)
        println("Loss: " + loss)
        assert(ok.reduce(_ && _))
    }

    test("8") {
        val file = "datasets/bigds_2.csv"
        val (w, loss) = Regression.regression(
            file, List("feature1", "feature2"), "to_predict", split, 0.001, 5)
        println("\t" + "y = "
          + w.transpose.data.get(0)(0) + "x1 " +
          "+ " + w.transpose.data.get(0)(1) + "x2 " +
          "+ " + w.transpose.data.get(0)(2))
        val ok = w.data.get(0)
          .zip(List(0.10850027614878494, 0.33897039511907456, 0.007331630833966705))
          .map((a, b) => a / b < 1 + eps && a / b > 1 - eps)
        println("Loss: " + loss)
        assert(ok.reduce(_ && _))
    }

    test("9") {
        val file = "datasets/houseds.csv"
        val (w, loss) = Regression.regression(
            file, List("GrLivArea", "YearBuilt"), "SalePrice", split, 0.001, 5)
        println("\t" + "y = "
          + w.transpose.data.get(0)(0) + "x1 " +
          "+ " + w.transpose.data.get(0)(1) + "x2 " +
          "+ " + w.transpose.data.get(0)(2))
        val ok = w.data.get(0)
          .zip(List(4.532065772931244E20, 5.6503657069136924E20, 2.86489323160482368E17))
          .map((a, b) => a / b < 1 + eps && a / b > 1 - eps)
        println("Loss: " + loss)
        assert(ok.reduce(_ && _))
    }

    test("10") {
        val file = "datasets/houseds.csv"
        val (w, loss) = Regression.regression(
            file, List("GrLivArea"), "SalePrice", split, 1e-7, 500)
        println("\t" + "y = "
          + w.transpose.data.get(0)(0) + "x1 " +
          "+ " + w.transpose.data.get(0)(1))
        val ok = w.data.get(0)
          .zip(List(117.68190794119705, 0.1827095147039086))
          .map((a, b) => a / b < 1 + eps && a / b > 1 - eps)
        println("Loss: " + loss)
        assert(ok.reduce(_ && _))
    }

}