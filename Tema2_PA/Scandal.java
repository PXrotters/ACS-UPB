import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.Scanner;

/**
 * Clasa Scandal calculeaza lista posibila de invitati care pot fi chemati la petrecere fara sa
 * se incalce niciuna dintre reguli
 */
public class Scandal {

	/**
	 * Metoda principala care initiaza executia programului
	 *
	 * @param args 		   argumentele liniei de comanda (nu sunt folosite)
	 * @throws IOException daca fisierul de intrare nu este gasit
	 */
	public static void main(String[] args) throws IOException {
		Scandal scandal = new Scandal();
		scandal.execute();
	}

	/**
	 * Citeste datele de intrare, calculeaza lista de invitati si scrie rezultatul
	 * in fisierul de iesire
	 *
	 * @throws IOException daca fisierul de intrare nu este gasit
	 */
	public void execute() throws IOException {
		InputData inputData = readInput();
		boolean[] invitations = calculateInvitations(inputData);
		writeResult(invitations);
	}

	/**
	 * Clasa interna pentru a reprezenta datele de intrare ale problemei
	 */
	static class InputData {
		int N;
		int M;
		List<Rule> rules;

		InputData(int N, int M, List<Rule> rules) {
			this.N = N;
			this.M = M;
			this.rules = rules;
		}
	}

	/**
	 * Clasa interna pentru a reprezenta o regula specifica
	 */
	static class Rule {
		int x;
		int y;
		int c;

		Rule(int x, int y, int c) {
			this.x = x;
			this.y = y;
			this.c = c;
		}
	}

	/**
	 * Citeste datele de intrare din fisierul de intrare
	 *
	 * @return datele de intrare ale problemei
	 * @throws IOException exceptie in caz de erori la citirea fisierului de intrare
	 */
	private InputData readInput() throws IOException {
		Scanner scanner = new Scanner(new File("scandal.in"));
		int N = scanner.nextInt();
		int M = scanner.nextInt();

		List<Rule> rules = new ArrayList<>();
		for (int i = 0; i < M; i++) {
			int x = scanner.nextInt();
			int y = scanner.nextInt();
			int c = scanner.nextInt();
			rules.add(new Rule(x, y, c));
		}

		scanner.close();
		return new InputData(N, M, rules);
	}

	/**
	 * Scrie rezultatul in fisierul de iesire
	 *
	 * @param invitations  lista de invitati
	 * @throws IOException daca fisierul de iesire nu poate fi creat
	 */
	private void writeResult(boolean[] invitations) throws IOException {
		PrintWriter pw = new PrintWriter(new FileWriter("scandal.out"));
		List<Integer> invitedFriends = new ArrayList<>();

		for (int i = 1; i < invitations.length; i++) {
			if (invitations[i]) {
				invitedFriends.add(i);
			}
		}

		pw.println(invitedFriends.size());
		for (int friend : invitedFriends) {
			pw.println(friend);
		}

		pw.close();
	}

	/**
	 * Calculeaza lista de invitati conform regulilor date
	 *
	 * @param inputData datele de intrare ale problemei
	 * @return lista de invitati
	 */
	private boolean[] calculateInvitations(InputData inputData) {
		boolean[] invitationStatus = new boolean[inputData.N + 1];
		Random rand = new Random();

		while (true) {
			boolean rulesSatisfied = true;
			for (Rule rule : inputData.rules) {
				int x = rule.x;
				int y = rule.y;
				int c = rule.c;

				if (!isConditionSatisfied(invitationStatus, x, y, c)) {
					if (rand.nextBoolean()) {
						invitationStatus[x] = !invitationStatus[x];
					} else {
						invitationStatus[y] = !invitationStatus[y];
					}
					rulesSatisfied = false;
					break;
				}
			}
			if (rulesSatisfied) {
				break;
			}
		}

		return invitationStatus;
	}

	/**
	 * Verifica daca o anumita conditie specifica este indeplinita pentru invitati
	 *
	 * @param invitationStatus starea actuala a invitatilor
	 * @param x                primul prieten implicat
	 * @param y                al doilea prieten implicat
	 * @param c                tipul de conditie specifica regulii
	 * @return true daca conditia este indeplinita, false altfel
	 */
	private boolean isConditionSatisfied(boolean[] invitationStatus, int x, int y, int c) {
		boolean satisfied;
		switch (c) {
			case 0:
				satisfied = invitationStatus[x] || invitationStatus[y];
				break;
			case 1:
				satisfied = invitationStatus[x] || !invitationStatus[y];
				break;
			case 2:
				satisfied = !invitationStatus[x] || invitationStatus[y];
				break;
			case 3:
				satisfied = !invitationStatus[x] || !invitationStatus[y];
				break;
			default:
				satisfied = false;
				break;
		}
		return satisfied;
	}
}
