import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;

/**
 * Clasa Compresie realizeaza compresia a doua siruri de numere si determina
 * lungimea maxima a sirului rezultat
 */
public class Compresie {
	/**
	 * Realizeaza compresia a doua siruri si determina sirul rezultat
	 *
	 * @param sirA      primul sir de numere
	 * @param sirB      al doilea sir de numere
	 * @param sirFinal  sirul rezultat al compresiei
	 */
	public static void compression(int[] sirA, int[] sirB, ArrayList<Integer> sirFinal) {
		int currentSumA = sirA[0];
		int currentSumB = sirB[0];
		int i = 0, j = 0;
		while (i < sirA.length && j < sirB.length) {
			if (currentSumA < currentSumB) {
				i++;
				if (i < sirA.length) {
					currentSumA += sirA[i];
				}
			} else if (currentSumA > currentSumB) {
				j++;
				if (j < sirB.length) {
					currentSumB += sirB[j];
				}
			} else {
				sirFinal.add(currentSumA);
				i++;
				if (i < sirA.length) {
					currentSumA = sirA[i];
				}
				j++;
				if (j < sirB.length) {
					currentSumB = sirB[j];
				}
			}
		}
	}

	/**
	 * Citeste datele de intrare, realizeaza compresia si
	 * scrie rezultatul intr-un fisier de iesire
	 *
	 * @param args                argumentele liniei de comanda (nu sunt folosite)
	 * @throws FileNotFoundException daca fisierul de intrare nu este gasit
	 */
	public static void main(String[] args) throws FileNotFoundException {
		Scanner scanner = new Scanner(new File("compresie.in"));

		int n = scanner.nextInt();
		int[] sirA = new int[n];
		for (int i = 0; i < n; i++) {
			sirA[i] = scanner.nextInt();
		}

		int m = scanner.nextInt();
		int[] sirB = new int[m];
		for (int i = 0; i < m; i++) {
			sirB[i] = scanner.nextInt();
		}

		try {
			PrintWriter writer = new PrintWriter("compresie.out");
			ArrayList<Integer> sirFinal = new ArrayList<>();

			// Verificam daca sirurile initiale au suma egala
			if (Arrays.stream(sirA).sum() == Arrays.stream(sirB).sum()) {
				compression(sirA, sirB, sirFinal);
				writer.printf("%d", sirFinal.size());
			} else {
				writer.printf("%d", -1);
			}
			writer.close();
		} catch (FileNotFoundException e) {
			System.err.println("Eroare la scrierea in fisier" + e.getMessage());
		}
	}
}