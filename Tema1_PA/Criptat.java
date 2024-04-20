import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Collections;
import java.util.List;
import java.util.Scanner;

/**
 * Clasa Criptat realizeaza generarea unei parole de lungime maxima pe baza unei liste de cuvinte
 */
public class Criptat {
	/**
	 * Genereaza parola criptata utilizand lista de cuvinte si caracterul curent ca litera dominanta
	 *
	 * @param wordsList      lista de cuvinte din care se construieste parola
	 * @param current        caracterul curent care este litera dominanta
	 * @return lungimea maxima a parolei criptate
	 */
	public static int generateEncryptedPassword(List<String> wordsList, char current) {
		int maxPossiblePasswordLength = 10000; // Valoarea maxima posibila a parolei (10^4)
		List<Integer> dp = new ArrayList<>(Collections.nCopies(maxPossiblePasswordLength + 1, 0));
		int encryptedPasswordLength = 0;

		for (String word : wordsList) {
			int charCount = 0;

			for (char ch : word.toCharArray()) {
				if (ch == current) {
					charCount++;
				}
			}

			// Calcului lungimii maxime a parolei
			int potentialLength = maxPossiblePasswordLength;
			while (potentialLength >= 0) {
				// Daca putem adauga cuvantul curent la aceasta pozitie
				if (dp.get(potentialLength) > 0 || potentialLength == 0) {
					int newLength = potentialLength + word.length();
					// Actualizam valoarea maxima
					dp.set(newLength, Math.max(dp.get(newLength),
							dp.get(potentialLength) + charCount));
					if (dp.get(newLength) > (newLength / 2)
							&& encryptedPasswordLength < newLength) {
						encryptedPasswordLength = newLength;
					}
				}
				potentialLength--;
			}
		}
		return encryptedPasswordLength;
	}


	/**
	 * Citeste datele de intrare, genereaza parolele si scrie rezultatul intr-un fisier de iesire
	 *
	 * @param args argumentele liniei de comanda (nu sunt folosite)
	 * @throws FileNotFoundException daca fisierul de intrare nu este gasit
	 */
	public static void main(String[] args) throws FileNotFoundException {
		Scanner scanner = new Scanner(new File("criptat.in"));
		int N = scanner.nextInt();
		scanner.nextLine();

		HashMap<Character, Integer> charFreq = new HashMap<>();
		List<String> wordsList = new ArrayList<>();

		// Retinem apritiile caracterelor
		for (int i = 0; i < N; i++) {
			String word = scanner.nextLine();
			wordsList.add(word);
			for (char ch : word.toCharArray()) {
				charFreq.put(ch, charFreq.getOrDefault(ch, 0) + 1);
			}
		}

		// Retinem toate caracterele gasite
		ArrayList<Character> characters = new ArrayList<>(charFreq.keySet());

		int maxPasswordLength = Integer.MIN_VALUE;
		for (char character : characters) {
			int passwordLength = generateEncryptedPassword(wordsList, character);
			if (maxPasswordLength < passwordLength) {
				maxPasswordLength = passwordLength;
			}
		}

		try {
			PrintWriter writer = new PrintWriter("criptat.out");
			writer.printf("%d", maxPasswordLength);
			writer.close();
		} catch (IOException e) {
			System.err.println("Eroare la scrierea in fisier" + e.getMessage());
		}
	}
}