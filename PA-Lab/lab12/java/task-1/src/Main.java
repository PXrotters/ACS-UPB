import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.lang.Math;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;

public class Main {
    static class Task {
        public static final String INPUT_FILE = "in";
        public static final String OUTPUT_FILE = "out";

        // numarul maxim de noduri
        public static final int NMAX = 1005;

        // valoare mai mare decat maxFlow
        public static final int INF = (int) 10e9;

        // n = numar de noduri, m = numar de muchii
        int n, m;

        // adj[i] = lista de adiacenta a nodului i
        @SuppressWarnings("unchecked")
		ArrayList<Integer>[] adj = new ArrayList[NMAX];

        // cap[i][j] = capacitatea arcului i -> j
        int[][] c;

        public static class Edge {
            public int node;
            public int neigh;

            Edge(int _node, int _neigh) {
                node = _node;
                neigh = _neigh;
            }

        }

        // structura folosita pentru a stoca daca exista drum de ameliorare
        // si care este acesta.
        public static class AugmentedPath {
            boolean hasPath;
            ArrayList<Edge> path;

            AugmentedPath(boolean _hasPath, ArrayList<Edge> _path) {
                hasPath = _hasPath;
                path = _path;
            }
        }

        public void solve() {
            readInput();
            writeOutput(getResult());
        }

        private void readInput() {
            try {
                Scanner sc = new Scanner(new BufferedReader(new FileReader(
                        INPUT_FILE)));
                n = sc.nextInt();
                m = sc.nextInt();

                for (int i = 1; i <= n; i++) {
                    adj[i] = new ArrayList<>();
                }

                c = new int[n + 1][n + 1];

                for (int i = 1; i <= m; i++) {
                    // x -> y de capacitate c
                    int u, v, capacity;
                    u = sc.nextInt();
                    v = sc.nextInt();
                    capacity = sc.nextInt();
                    adj[u].add(v);
                    adj[v].add(u);

                    // Presupunem existenta mai multor arce x -> y cu capacitati c1, c2, ...
                    // Comprimam intr-un singur arc x -> y cu capacitate
                    // cap[x][y] = c1 + c2 + ...
                    c[u][v] += capacity;
                }
                sc.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private void writeOutput(int result) {
            try {
                PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter(
                        OUTPUT_FILE)));
                pw.printf("%d\n", result);
                pw.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private int getResult() {
            // Sursa este nodul 1, destinatia este nodul n
            int source = 1;
            int sink = n;

            // totalFlow va stoca fluxul maxim
            int totalFlow = 0;

            // rezidual va fi matricea de capacitati reziduale
            int[][] residual = new int[n + 1][n + 1];
            for (int i = 1; i <= n; i++) {
				System.arraycopy(c[i], 1, residual[i], 1, n);
            }

            // parinte va stoca drumul de ameliorare
            int[] parinte = new int[n + 1];

            // Implementare BFS pentru a gasi drumul de ameliorare
            while (bfs(residual, source, sink, parinte)) {
                // Determinăm capacitatea minimă pe drumul găsit de BFS
                int pathFlow = INF;
                for (int v = sink; v != source; v = parinte[v]) {
                    int u = parinte[v];
                    pathFlow = Math.min(pathFlow, residual[u][v]);
                }

                // Actualizam capacitatile reziduale ale arcelor si arcelor inverse
                for (int v = sink; v != source; v = parinte[v]) {
                    int u = parinte[v];
                    residual[u][v] -= pathFlow;
                    residual[v][u] += pathFlow;
                }

                // Adaugam fluxul acestui drum la fluxul total
                totalFlow += pathFlow;
            }

            return totalFlow;
        }

        private boolean bfs(int[][] residual, int source, int sink, int[] parinte) {
            boolean[] vizitat = new boolean[n + 1];
            Queue<Integer> queue = new LinkedList<>();

            queue.add(source);
            vizitat[source] = true;
            parinte[source] = -1;

            while (!queue.isEmpty()) {
                int u = queue.poll();

                for (int v : adj[u]) {
                    if (!vizitat[v] && residual[u][v] > 0) {
                        queue.add(v);
                        parinte[v] = u;
                        vizitat[v] = true;

                        if (v == sink) {
                            return true;
                        }
                    }
                }
            }

            return false;
        }

    }
    public static void main(String[] args) {
        new Task().solve();
    }
}
