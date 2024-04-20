import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.Scanner;

/**
 * Clasa Servere realizeaza efectuarea puterii de calcul maxima bazata pe un factor optim
 */
public class Servere {

	/**
	 * Calculeaza puterea de calcul maxima bazata pe factorul optim
	 *
	 * @param power     un vector care reprezinta puterea de calcul a fiecarui server
	 * @param capacity  un vector care reprezinta capacitatea fiecarui server
	 * @param factor    factorul optim
	 * @return          puterea de calcul maxima
	 */
	public static double optimalMaxPower(int[] power, int[] capacity, double factor) {
		double maximumPower = Double.MAX_VALUE;
		for (int i = 0; i < power.length; i++) {
			maximumPower = Math.min(maximumPower, power[i] - Math.abs(factor - capacity[i]));
		}
		return maximumPower;
	}

	/**
	 * Realizeaza cautarea binara pentru a gasi puterea de calcul maxima
	 *
	 * @param power     un vector care reprezinta puterea de calcul a fiecarui server
	 * @param capacity  un vector care reprezinta capacitatea fiecarui server
	 * @return          puterea de calcul maxima
	 */
	public static double binarySearch(int[] power, int[] capacity) {
		// Setam capetele intervalului de cautare
		double left = Integer.MAX_VALUE;
		for (int cap : capacity) {
			left = Math.min(left, cap);
		}
		double right = Integer.MIN_VALUE;
		for (int cap : capacity) {
			right = Math.max(right, cap);
		}

		double optimalMaxPower = Integer.MIN_VALUE;

		while (left < right) {
			double middle = (left + right) / 2;  // Ajustam mijlocul
			// Calculam puterea de calcul maxima pentru factorul curent
			double powerOfMiddlePoint = optimalMaxPower(power, capacity, middle);
			optimalMaxPower = Math.max(optimalMaxPower, powerOfMiddlePoint);

			// Verificam puterea pentru vecinii mijlocului incluzand si cazul jumatatii de unitate
			double leftMidPower = optimalMaxPower(power, capacity, middle - 1);
			optimalMaxPower = Math.max(optimalMaxPower, leftMidPower);
			double rightMidPower = optimalMaxPower(power, capacity, middle + 1);
			optimalMaxPower = Math.max(optimalMaxPower, rightMidPower);
			double leftMidPowerLow = optimalMaxPower(power, capacity, middle - 0.5);
			optimalMaxPower = Math.max(optimalMaxPower, leftMidPowerLow);
			double rightMidPowerLow = optimalMaxPower(power, capacity, middle + 0.5);
			optimalMaxPower = Math.max(optimalMaxPower, rightMidPowerLow);

			if (Math.floor(middle) == middle) {  // Cazul cand mijlocul nostru este rotunjit
				if (rightMidPower > powerOfMiddlePoint) {
					left = middle + 1;
				} else if (leftMidPower > powerOfMiddlePoint) {
					right = middle - 1;
				} else {
					return optimalMaxPower;
				}
			} else {  // Cazul cand mijlocul nostru nu e rotunjit
				if (rightMidPower > powerOfMiddlePoint) {
					left = middle + 0.5;
				} else if (leftMidPower > powerOfMiddlePoint) {
					right = middle - 0.5;
				} else {
					return optimalMaxPower;
				}
			}
		}
		return optimalMaxPower;
	}

	/**
	 * Citeste datele de intrare dintr-un fisier, efectueaza cautarea binara
	 * si scrie rezultatul intr-un fisier de iesire
	 *
	 * @param args  argumentele liniei de comanda (nu sunt folosite)
	 * @throws FileNotFoundException daca fisierul de intrare nu este gasit
	 */
	public static void main(String[] args) throws FileNotFoundException {
		Scanner scanner = new Scanner(new File("servere.in"));
		int N = scanner.nextInt();
		int[] power = new int[N];
		int[] capacity = new int[N];

		// Citirea datelor de intrare din fisier
		for (int i = 0; i < 2 * N; i++) {
			if (i < N) {
				power[i] = scanner.nextInt();
			} else {
				capacity[i - N] = scanner.nextInt();
			}
		}

		try {
			PrintWriter writer = new PrintWriter("servere.out");
			double optimalMaxPower = binarySearch(power, capacity);
			writer.printf("%.1f", optimalMaxPower);
			writer.close();
		} catch (FileNotFoundException e) {
			System.err.println("Eroare la scrierea in fisier" + e.getMessage());
		}
	}
}