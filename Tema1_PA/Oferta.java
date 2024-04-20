import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.Scanner;


/**
 * Clasa Oferta realizeaza generarea pretului minim obtinut prin gruparea produselor,
 * avand in vedere doua oferte
 */
public class Oferta {
	/**
	 * Calculeaza pretul obtinut prin aplicarea reducerii de 50% asupra produsului mai ieftin
	 *
	 * @param product1 Pretul primului produs
	 * @param product2 Pretul celui de-al doilea produs
	 * @return Pretul obtinut dupa aplicarea reducerii
	 */
	public static double halfPrice(double product1, double product2) {
		double cheaperProduct = Math.min(product1, product2);
		double discount = cheaperProduct / 2;
		return product1 + product2 - discount;
	}

	/**
	 * Calculeaza pretul obtinut prin aplicarea reducerii de 100% asupra celui mai ieftin produs
	 *
	 * @param product1 Pretul primului produs
	 * @param product2 Pretul celui de-al doilea produs
	 * @param product3 Pretul celui de-al treilea produs
	 * @return Pretul obtinut dupa aplicarea reducerii
	 */
	public static double fullPrice(double product1, double product2, double product3) {
		double cheapestProduct = Math.min(product1, Math.min(product2, product3));
		return product1 + product2 + product3 - cheapestProduct;
	}

	/**
	 * Determina indexul minim al unei liste
	 *
	 * @param list Lista de numere duble in care se cauta valoarea minima
	 * @return Indexul elementului cu valoarea minima sau -1 daca lista este goala
	 */
	private static int minIndex(List<Double> list) {
		double min = Double.MAX_VALUE;
		int minIndex = -1;
		for (int i = 0; i < list.size(); i++) {
			if (list.get(i) < min) {
				min = list.get(i);
				minIndex = i;
			}
		}
		return minIndex;
	}

	/**
	 * Genereaza toate combinatiile posibile ale produselor pentru a obtine pretul minim
	 *
	 * @param dp Matricea in care sunt stocate preturile intermediare
	 * @param currentIndex Indexul curent in lista de preturi a produselor
	 * @param nextIndex Indexul urmator in lista de preturi a produselor
	 * @param K Numarul sumei dorite
	 * @param products Lista de preturi a produselor
	 */
	private static void generateCombinations(
			List<List<Double>> dp,
			int currentIndex, int nextIndex,
			int K, double[] products
	) {
		// Initializam lista de indici cu 0
		List<Integer> indices = new ArrayList<>(Arrays.asList(0, 0, 0));

		while (dp.get(nextIndex).size() < K
				&& (indices.get(0) < dp.get(currentIndex).size()
				|| indices.get(1) < dp.get(currentIndex - 1).size()
				|| indices.get(2) < dp.get(currentIndex - 2).size())) {


			// Initializam o lista pentru stocarea sumelor preturilor pentru diferite combinatii
			List<Double> combinationSum = new ArrayList<>(Collections.nCopies(3, Double.MAX_VALUE));

			/* Calculam suma preturilor pentru combinatia de produse curenta
			si o adaugam in lista combinationSum */
			if (indices.get(0) < dp.get(currentIndex).size()) {
				combinationSum.set(0,
						dp.get(currentIndex).get(indices.get(0)) + products[currentIndex]);

			}
			/* Calculam suma preturilor pentru combinatia de produse
			cu un produs anterior si o adaugam in lista combinationSum */
			if (indices.get(1) < dp.get(currentIndex - 1).size()) {
				combinationSum.set(1, dp.get(currentIndex - 1).get(indices.get(1))
						+ halfPrice(products[currentIndex], products[currentIndex - 1]));
			}
			/* Calculam suma preturilor pentru combinatia de produse
			cu cele doua produse anterioare si o adaugam in lista combinationSum */

			if (indices.get(2) < dp.get(currentIndex - 2).size()) {
				combinationSum.set(2, dp.get(currentIndex - 2).get(indices.get(2)) + fullPrice(
						products[currentIndex],
						products[currentIndex - 1],
						products[currentIndex - 2]
				));
			}

			int minIndex = minIndex(combinationSum);

			// Incrementam indicele corespunzator combinatiei de preturi cu suma minima
			indices.set(minIndex, indices.get(minIndex) + 1);

			if (dp.get(nextIndex).isEmpty() || !combinationSum.get(minIndex).equals(
							dp.get(nextIndex).get(dp.get(nextIndex).size() - 1)
					)
			) {
				dp.get(nextIndex).add(combinationSum.get(minIndex));
			}
		}
	}

	/**
	 * Citeste datele din fisier si calculeaza pretul ofertei
	 *
	 * @param inputFile Numele fisierului de intrare
	 * @return Pretul ofertei sau -1 in caz de eroare
	 * @throws FileNotFoundException daca fisierul de intrare nu este gasit
	 */
	public static double calculateOfferPrice(String inputFile) throws FileNotFoundException {
		Scanner scanner = new Scanner(new File(inputFile));
		int N = scanner.nextInt();
		int K = scanner.nextInt();
		double[] products = new double[N];

		for (int i = 0; i < N; i++) {
			products[i] = scanner.nextDouble();
		}

		if (N == 1 && K == N) {
			return products[0];
		} else if (N == 1 && K > N) {
			return -1;
		}

		// Initializam lista pentru stocarea tuturor combinatiilor de produse
		List<List<Double>> dp = new ArrayList<>();
		// Adaugam o lista goala pentru cazul cand nu se cumpara niciun produs
		dp.add(new ArrayList<>(Collections.singletonList(0.0)));
		// Adaugam o lista cu pretul primului produs pentru cazul cand se cumpara doar un produs
		dp.add(new ArrayList<>(Collections.singletonList(products[0])));
		// Adaugam o lista cu pretul minim pentru doua produse folosind reducerea de 50%
		dp.add(new ArrayList<>(Collections.singletonList(halfPrice(products[0], products[1]))));

		if (K != 1) {
			dp.get(2).add(products[0] + products[1]);
		}

		for (int i = 2; i < N; i++) {
			dp.add(new ArrayList<>());
			generateCombinations(dp, i, i + 1, K, products);
		}

		if (dp.get(N).size() < K) {
			return -1;
		} else {
			return dp.get(N).get(K - 1);
		}
	}

	/**
	 * Scrie rezultatul intr-un fisier de iesire
	 *
	 * @param args argumentele liniei de comanda (nu sunt folosite)
	 * @throws FileNotFoundException daca fisierul de intrare nu este gasit
	 */
	public static void main(String[] args) throws FileNotFoundException {
		double result = calculateOfferPrice("oferta.in");
		try {
			PrintWriter writer = new PrintWriter(new FileWriter("oferta.out"));
			if (result == -1) {
				writer.printf("%d", -1);
			} else {
				writer.printf("%.1f", result);
			}
			writer.close();
		} catch (IOException e) {
			System.err.println("Eroare la scrierea in fisier" + e.getMessage());
		}
	}
}
