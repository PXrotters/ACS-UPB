import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.List;
import java.util.PriorityQueue;
import java.util.Scanner;

/**
 * Clasa Drumuri calculeaza o submultime de muchii a caror suma este minima astfel incat sa existe
 * cel putin un drum care pleaca dintru-un nod x si unui care pleaca dintr-un nod y, ambele ajungand
 * in nodul z
 */
public class Drumuri {

	/**
	 * Structura pentru a reprezenta o muchie a grafului
	 */
	public static class Edge {
		int node;
		long cost;

		/**
		 * Constructor pentru clasa Edge
		 *
		 * @param node nodul destinatie
		 * @param cost costul muchiei
		 */
		Edge(int node, long cost) {
			this.node = node;
			this.cost = cost;
		}
	}

	/**
	 * Metoda principala care initiaza executia programului
	 *
	 * @param args 		   argumentele liniei de comanda (nu sunt folosite)
	 * @throws IOException daca fisierul de intrare nu este gasit
	 */
	public static void main(String[] args) throws IOException {
		Drumuri drumuri = new Drumuri();
		drumuri.execute();
	}

	/**
	 * Citeste datele de intrare, calculeaza costul minim al drumului
	 * si scrie rezultatul in fisierul de iesire
	 *
	 * @throws IOException daca nu se poate gasi fisierul de intrare sau crea fisierul de iesire
	 */
	public void execute() throws IOException {
		int N, M, x, y, z;
		List<List<Edge>> graph, reversedGraph;
		try (Scanner scanner = new Scanner(new File("drumuri.in"))) {
			N = scanner.nextInt();
			M = scanner.nextInt();

			graph = new ArrayList<>();
			reversedGraph = new ArrayList<>();

			for (int i = 0; i <= N; i++) {
				graph.add(new ArrayList<>());
				reversedGraph.add(new ArrayList<>());
			}

			readEdges(scanner, M, graph, reversedGraph);

			x = scanner.nextInt();
			y = scanner.nextInt();
			z = scanner.nextInt();
		}

		// Calcularea distantelor folosind Dijkstra
		long[] distanceFromX = dijkstra(graph, x, N);
		long[] distanceFromY = dijkstra(graph, y, N);
		long[] distanceToZ = dijkstra(reversedGraph, z, N);

		// Calcularea costului minim
		long minCost = calculateMinCost(N, distanceFromX, distanceFromY, distanceToZ);

		// Afisarea rezultatului in fisier
		writeResult(minCost);
	}

	/**
	 * Citeste muchiile grafului si le adauga in listele de adiacenta ale grafurilor
	 *
	 * @param scanner       scannerul utilizat pentru citirea datelor de intrare
	 * @param M             numarul total de muchii din graf
	 * @param graph         graful reprezentat ca o lista de adiacenta
	 * @param reversedGraph graful inversat reprezentat ca o lista de adiacenta
	 */
	private void readEdges(
			Scanner scanner,
			int M,
			List<List<Edge>> graph,
			List<List<Edge>> reversedGraph
	) {
		for (int i = 0; i < M; i++) {
			int a = scanner.nextInt();
			int b = scanner.nextInt();
			long c = scanner.nextLong();
			graph.get(a).add(new Edge(b, c));
			reversedGraph.get(b).add(new Edge(a, c));
		}
	}

	/**
	 * Scrie rezultatul in fisierul de iesire
	 *
	 * @param result 	   rezultatul de scris in fisier
	 * @throws IOException daca fisierul de iesire nu poate fi creat
	 */
	private static void writeResult(long result) throws IOException {
		try (PrintWriter pw = new PrintWriter("drumuri.out")) {
			pw.println(result);
		}
	}

	/**
	 * Calculeaza distantele minime folosind algoritmul Dijkstra
	 *
	 * @param graph graful reprezentat ca o lista de adiacenta
	 * @param start nodul de start
	 * @param N     numarul de noduri din graf
	 * @return un array de lungime N+1, cu distantele minime de la start la nodul i
	 */
	public static long[] dijkstra(List<List<Edge>> graph, int start, int N) {
		PriorityQueue<Edge> pq = new PriorityQueue<>(Comparator.comparingLong(e -> e.cost));
		long[] dist = new long[N + 1];
		Arrays.fill(dist, Long.MAX_VALUE);
		dist[start] = 0;

		pq.add(new Edge(start, 0));

		while (!pq.isEmpty()) {
			Edge current = pq.poll();
			int u = current.node;
			long currentCost = current.cost;

			if (currentCost > dist[u]) {
				continue;
			}

			for (Edge edge : graph.get(u)) {
				int v = edge.node;
				long newDist = dist[u] + edge.cost;

				if (newDist < dist[v]) {
					dist[v] = newDist;
					pq.add(new Edge(v, newDist));
				}
			}
		}

		return dist;
	}

	/**
	 * Calculeaza costul minim al drumului
	 *
	 * @param N             numarul de noduri din graf
	 * @param distanceFromX distantele de la nodul x la toate celelalte noduri
	 * @param distanceFromY distantele de la nodul y la toate celelalte noduri
	 * @param distanceToZ   distantele de la toate nodurile la nodul z
	 * @return costul minim al drumului
	 */
	private static long calculateMinCost(
			int N,
			long[] distanceFromX,
			long[] distanceFromY,
			long[] distanceToZ
	) {
		long minCost = Long.MAX_VALUE;

		for (int node = 1; node <= N; node++) {
			if (distanceFromX[node] != Long.MAX_VALUE
					&& distanceFromY[node] != Long.MAX_VALUE
					&& distanceToZ[node] != Long.MAX_VALUE) {
				long cost = distanceFromX[node] + distanceFromY[node] + distanceToZ[node];
				if (cost < minCost) {
					minCost = cost;
				}
			}
		}

		return minCost;
	}
}
