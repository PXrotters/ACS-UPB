import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;

/**
 * Clasa Colorare realizeaza numarul de posibilitati de colorare a unui tablou
 */
public class Colorare {
	public static final long MOD = 1000000007;

	/**
	 * Calculeaza rapid (base^exp) % mod
	 *
	 * @param base   baza
	 * @param exp    exponentul
	 * @return       rezultatul exponentierii rapide
	 */
	public static long fastExp(long base, long exp) {
		if (exp == 0) {
			return 1;
		}
		long recursiveExp = fastExp(base, exp / 2) % MOD;
		long result = (recursiveExp * recursiveExp) % MOD;
		if (exp % 2 == 1) {
			result = (result * base) % MOD;
		}
		return result;
	}

	/**
	 * Citeste datele de intrare, realizeaza colorarea si scrie rezultatul intr-un fisier de iesire
	 *
	 * @param args  argumentele liniei de comanda (nu sunt folosite)
	 * @throws FileNotFoundException daca fisierul de intrare nu este gasit
	 */
	public static void main(String[] args) throws FileNotFoundException {
		Scanner scanner = new Scanner(new File("colorare.in"));
		int K = scanner.nextInt();
		scanner.nextLine();
		long sum;
		int X = scanner.nextInt();
		char T = scanner.next().charAt(0);
		long exp = (X - 1) % (MOD - 1);
		if (T == 'H') {
			sum = (6 * fastExp(3, exp)) % MOD;
		} else {
			sum = (3 * fastExp(2, exp)) % MOD;
		}
		char prev_T = T;

		for (int i = 0; i < K - 1; i++) {
			X = scanner.nextInt();
			T = scanner.next().charAt(0);
			exp = (X - 1) % (MOD - 1);

			if (T == 'H' && prev_T == 'H') {
				sum = (((3 * sum) % MOD) * fastExp(3, exp)) % MOD;
			} else if (T == 'H' && prev_T == 'V') {
				sum = (((2 * sum) % MOD) * fastExp(3, exp)) % MOD;
			} else if (T == 'V' && prev_T == 'H') {
				sum = (sum * fastExp(2, exp)) % MOD;
			} else {
				sum = (((2 * sum) % MOD) * fastExp(2, exp)) % MOD;
			}
			prev_T = T;
		}

		try {
			PrintWriter writer = new PrintWriter("colorare.out");
			writer.printf("%d", sum);
			writer.close();
		} catch (IOException e) {
			System.err.println("Eroare la scrierea in fisier" + e.getMessage());
		}
	}
}