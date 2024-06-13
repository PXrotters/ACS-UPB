import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayDeque;
import java.util.Queue;
import java.util.Scanner;
import java.util.ArrayList;

public class Main {
    static class Task {
        public static final String INPUT_FILE = "in";
        public static final String OUTPUT_FILE = "out";

        // numarul maxim de noduri
        public static final int NMAX = (int)1e5 + 5; // 10^5 + 5 = 100.005

        // n = numar de noduri, m = numar de muchii/arce
        int n, m;

        // adj[node] = lista de adiacenta a nodului node
        // exemplu: daca adj[node] = {..., neigh, ...} => exista muchia (node, neigh)
        @SuppressWarnings("unchecked")
        ArrayList<Integer> adj[] = new ArrayList[NMAX];

        // nodul sursa in parcurgerea BFS
        int source;

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
                source = sc.nextInt();

                for (int node = 1; node <= n; node++) {
                    adj[node] = new ArrayList<>();
                }

                for (int i = 1, x, y; i <= m; i++) {
                    // muchie (x, y)
                    x = sc.nextInt();
                    y = sc.nextInt();
                    adj[x].add(y);
                    adj[y].add(x);
                }

                sc.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private void writeOutput(int[] d) {
            try {
                PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter(
                                OUTPUT_FILE)));
                for (int node = 1; node <= n; node++) {
                    pw.printf("%d%c", d[node], node == n ? '\n' : ' ');
                }
                pw.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private int[] getResult() {
            int[] d = new int[n + 1];
            boolean[] visited = new boolean[n + 1];
            Queue<Integer> queue = new ArrayDeque<>();

            for (int node = 1; node <= n; node++) {
                d[node] = -1; // Initializam distantele cu -1
            }

            d[source] = 0;
            visited[source] = true;
            queue.add(source);

            while (!queue.isEmpty()) {
                int node = queue.poll();
                for (int neigh : adj[node]) {
                    if (!visited[neigh]) {
                        visited[neigh] = true;
                        d[neigh] = d[node] + 1;
                        queue.add(neigh);
                    }
                }
            }

            return d;
        }
    }

    public static void main(String[] args) {
        new Task().solve();
    }
}
