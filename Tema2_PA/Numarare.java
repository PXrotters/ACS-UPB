import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Collections;
import java.util.LinkedList;
import java.util.List;
import java.util.Objects;
import java.util.Queue;
import java.util.Scanner;
import java.util.stream.IntStream;

/**
 * Clasa Numarare efectueaza numararea lanturilor elementare comune din doua grafuri date.
 * Un lant elementar este un "drum" intr-un graf in care toate nodurile sunt distincte
 */
public class Numarare {

	static final int MOD = 1000000007;

	/**
	 * Metoda principala care initiaza executia programului
	 *
	 * @param args 		   argumentele liniei de comanda (nu sunt folosite)
	 * @throws IOException daca fisierul de intrare nu este gasit
	 */
	public static void main(String[] args) throws IOException {
		Numarare numarare = new Numarare();
		numarare.execute();
	}

	/**
	 * Citeste datele de intrare, calculeaza numarul de lanturi elementare comune
	 * si scrie rezultatul in fisierul de iesire
	 *
	 * @throws IOException daca nu se poate gasi fisierul de intrare sau crea fisierul de iesire
	 */
	public void execute() throws IOException {
		Scanner scanner = new Scanner(new File("numarare.in"));

		int N = scanner.nextInt();
		int M = scanner.nextInt();

		List<List<Integer>> firstGraph = readGraph(N, M, scanner);
		List<List<Integer>> secondGraph = readGraph(N, M, scanner);

		List<List<Integer>> fullGraph = commonElementaryChainsGraph(N, firstGraph, secondGraph);

		List<Long> commonPaths = countElementaryChains(
				fullGraph,
				Objects.requireNonNull(topologicalSort(fullGraph, N)),
				N
		);

		writeResult(commonPaths.get(N));
		scanner.close();
	}

	/**
	 * Citeste un graf de dimensiune N si M si il returneaza
	 *
	 * @param N       numarul de noduri din graf
	 * @param M       numarul de muchii din graf
	 * @param scanner scannerul utilizat pentru citirea datelor
	 * @return reprezentarea sub forma de lista de adiacenta a grafului citit
	 */
	static List<List<Integer>> readGraph(int N, int M, Scanner scanner) {
		List<List<Integer>> graph = new ArrayList<>();

		// Initializam graful cu listele de adiacenta
		for (int i = 0; i <= N; i++) {
			graph.add(new ArrayList<>());
		}

		// Citim muchiile si le adaugam in listele de adiacenta corespunzatoare
		for (int i = 0; i < M; i++) {
			int x = scanner.nextInt();
			int y = scanner.nextInt();
			graph.get(x).add(y);
		}

		return graph;
	}

	/**
	 * Scrie rezultatul in fisierul de iesire
	 *
	 * @param result 	   rezultatul de scris in fisier
	 * @throws IOException daca fisierul de iesire nu poate fi creat
	 */
	static void writeResult(long result) throws IOException {
		PrintWriter writer = new PrintWriter("numarare.out");
		writer.println(result);
		writer.close();
	}

	/**
	 * Realizeaza sortarea topologica a unui graf dat si returneaza rezultatul sub forma de lista
	 *
	 * @param graph graful reprezentat ca o lista de adiacenta
	 * @param N     numarul total de noduri din graf
	 * @return sortarea topologica a grafului sau null daca exista un ciclu in graf
	 */
	static List<Integer> topologicalSort(List<List<Integer>> graph, int N) {
		List<Integer> topSort = new ArrayList<>();
		List<Integer> inDegrees = calculateInDegrees(graph, N);

		Queue<Integer> zeroInDegreeNodes = new LinkedList<>();

		// Adaugam toate nodurile cu gradul intern 0 in coada
		for (int node = 1; node <= N; node++) {
			if (inDegrees.get(node) == 0) {
				zeroInDegreeNodes.add(node);
			}
		}

		while (!zeroInDegreeNodes.isEmpty()) {
			int currentNode = zeroInDegreeNodes.poll();
			topSort.add(currentNode);

			/* Reducem gradul intern al fiecarui vecin si daca acesta devine 0, inseamna ca
			acel vecin nu are niciun alt vecin care sa depinda de el, asadar il adaugam in coada */
			graph.get(currentNode).forEach(neigh -> {
				int newDegree = inDegrees.get(neigh) - 1;
				inDegrees.set(neigh, newDegree);
				if (newDegree == 0) {
					zeroInDegreeNodes.add(neigh);
				}
			});
		}

		// Verificam daca sortarea topologica este posibila (daca nu exista cicluri)
		if (topSort.size() != N) {
			/* Daca dimensiunea sortarii topologice nu este egala cu numarul total de noduri,
			atunci exista un ciclu in graf si nu se poate face sortarea topologica */
			return null;
		}

		return topSort;
	}

	/**
	 * Calculeaza gradele interne ale fiecarui nod din graf
	 *
	 * @param graph graful reprezentat ca o lista de adiacenta
	 * @param N     numarul total de noduri din graf
	 * @return un vector care contine gradele interne ale fiecarui nod din graf
	 */
	static List<Integer> calculateInDegrees(List<List<Integer>> graph, int N) {
		List<Integer> inDegrees = new ArrayList<>(Collections.nCopies(N + 1, 0));

		// Calculam gradele interne pentru fiecare nod
		for (List<Integer> adjacencyList : graph) {
			for (int neigh : adjacencyList) {
				inDegrees.set(neigh, inDegrees.get(neigh) + 1);
			}
		}

		return inDegrees;
	}

	/**
	 * Calculeaza numarul de lanturi elementare pentru fiecare nod din graf,
	 * folosind sortarea topologica
	 *
	 * @param graph            graful reprezentat ca o lista de adiacenta
	 * @param topologicalOrder sortarea topologica a grafului
	 * @param N                numarul total de noduri din graf
	 * @return o lista care contine numarul de lanturi elementare pentru fiecare nod din graf
	 */
	static List<Long> countElementaryChains(
			List<List<Integer>> graph,
			List<Integer> topologicalOrder,
			int N
	) {
		List<Long> chainsCount = new ArrayList<>(Collections.nCopies(N + 1, 0L));
		chainsCount.set(1, 1L);
		for (int u : topologicalOrder) {
			for (int v : graph.get(u)) {
				long newValue = (chainsCount.get(v) + chainsCount.get(u)) % MOD;
				chainsCount.set(v, newValue);
			}
		}
		return chainsCount;
	}

	/**
	 * Construieste un graf care reprezinta lanturile elementare comune din doua grafuri date
	 *
	 * @param N           numarul total de noduri din grafuri
	 * @param firstGraph  reprezentarea sub forma de lista de adiacenta a primului graf
	 * @param secondGraph reprezentarea sub forma de lista de adiacenta a celui de-al doilea graf
	 * @return reprezentarea sub forma de lista de adiacenta a grafului construit
	 */
	static List<List<Integer>> commonElementaryChainsGraph(
			int N,
			List<List<Integer>> firstGraph,
			List<List<Integer>> secondGraph
	) {
		List<List<Integer>> commonGraph = new ArrayList<>();

		// Initializam graful comun
		for (int i = 0; i <= N; i++) {
			commonGraph.add(new ArrayList<>());
		}

		// Adaugam nodurile si muchiile comune in noul graf
		IntStream.rangeClosed(1, N)
				.forEach(u -> firstGraph.get(u).stream()
						.filter(v -> secondGraph.get(u).contains(v))
						.forEach(v -> commonGraph.get(u).add(v)));

		return commonGraph;
	}
}