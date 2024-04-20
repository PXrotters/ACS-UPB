import scala.annotation.tailrec

object Regression {

  def regression(dataset_file: String,
                 attribute_columns: List[String],
                 value_column: String,
                 test_percentage: Double,
                 alpha: Double,
                 gradient_descent_steps: Int): (Matrix, Double) = {
    // Citim setul de date din fișier
    val dataset = Dataset(dataset_file)

    // Impartim setul de date intr-un set de antrenare si unul de validare
    val (trainingDataset, validationDataset) = dataset.split(test_percentage)

    // Selectam coloanele de interes din setul de date
    val attributeTrainingDataset = trainingDataset.selectColumns(attribute_columns)
    val attributeValidationDataset = validationDataset.selectColumns(attribute_columns)
    val valueTrainingDataset = trainingDataset.selectColumn(value_column)
    val valueValidationDataset = validationDataset.selectColumn(value_column)

    // Cream matricea cu date de intrare
    val xMatrix = Matrix(attributeTrainingDataset)
    val Y = Matrix(valueTrainingDataset)  // Pretul real al locuintelor
    val X = xMatrix ++ 1.0  // Adaugam coloana aditionala cu valoarea 1 la finalul matricii X

    // Extragem numarul de linii si de coloane a matricii X -> fara coloana aditionala
    val m = xMatrix.height.getOrElse(0)
    val n = xMatrix.width.getOrElse(0)

    // Cream vectorul W (matrice cu n + 1 coloane si 1 linie)
    val W: Matrix = Matrix(List.fill(n + 1)(List.fill(1)(0.0)))

    // Algoritmul Gradient Descent
    def gradientDescent(wMatrix: Matrix): Matrix = {
      val estimations: Matrix = X * wMatrix
      val errors: Matrix = estimations - Y
      val gradient: Matrix = X.transpose * errors
      val gradientMatrix: Matrix = gradient.map(_ / m)
      val alphaProduct: Matrix = gradientMatrix.map(_ * alpha)
      wMatrix - alphaProduct
    }

    // Aplicam algoritmul Gradient Descent pentru un numar prestabilit de pasi
    @tailrec
    def gradientDescentSteps(step: Int, wMatrix: Matrix): Matrix = {
      if (step > gradient_descent_steps) wMatrix
      else gradientDescentSteps(step + 1, gradientDescent(wMatrix))
    }

    // Retinem matricea W actualizata dupa aplicarea algoritmului Gradient Descent
    val updatedW = gradientDescentSteps(1, W)

    // Cream matricea din datele de evaluare
    val xValidation = Matrix(attributeValidationDataset) ++ 1
    val yValidation = Matrix(valueValidationDataset)

    val predictions = xValidation * updatedW

    val absoluteDifference = (predictions - yValidation).map(_.abs)
    val sumError = absoluteDifference.data.get.flatten.sum
    val totalError = sumError / m

    (updatedW, totalError)
  }

  def main(args: Array[String]): Unit = {
    // Exemplu de utilizare
    print(regression("datasets/houseds.csv", List("GrLivArea", "YearBuilt"), "SalePrice", 0.1, 1e-7, 10000))
  }
}