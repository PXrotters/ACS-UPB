import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.*;

public class Main {
    static class Task {
        public static final String INPUT_FILE = "in";
        public static final String OUTPUT_FILE = "out";

        // numarul maxim de noduri
        public static final int NMAX = (int)1e5 + 5; // 10^5 + 5 = 100.005

        // n = numar de noduri, m = numar de muchii/arce
        int n, m;

        // adj[node] = lista de adiacenta a nodului node
        // exemplu: daca adj[node] = {..., neigh, ...} => exista arcul (node, neigh)
        @SuppressWarnings("unchecked")
        ArrayList<Integer> adj[] = new ArrayList[NMAX];

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

                for (int node = 1; node <= n; node++) {
                    adj[node] = new ArrayList<>();
                }

                for (int i = 1, x, y; i <= m; i++) {
                    // arc (x, y)
                    x = sc.nextInt();
                    y = sc.nextInt();
                    adj[x].add(y);
                }

                sc.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private void writeOutput(ArrayList<Integer> topsort) {
            try {
                PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter(
                                OUTPUT_FILE)));
                for (Integer node : topsort) {
                    pw.printf("%d ", node);
                }
                pw.printf("\n");
                pw.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        // Kahn's algorithm
        private ArrayList<Integer> getResult() {
            int[] internDegree = new int[n + 1];
            Queue<Integer> queue = new ArrayDeque<>();
            ArrayList<Integer> topsort = new ArrayList<>();

            // Calculam gradul intern al fiecarui nod
            for (int node = 1; node <= n; node++) {
                for (int neigh : adj[node]) {
                    internDegree[neigh]++;
                }
            }

            // Initializam coada de la BFS cu nodurile care au grad intern 0
            for (int node = 1; node <= n; node++) {
                if (internDegree[node] == 0) {
                    queue.add(node);
                }
            }

            // BFS
            while (!queue.isEmpty()) {
                int node = queue.poll();
                topsort.add(node);

                // Stergem muchiile catre vecinii nodului curent si actualizam gradul intern al vecinilor
                for (int neigh : adj[node]) {
                    internDegree[neigh]--;
                    if (internDegree[neigh] == 0) {
                        queue.add(neigh);
                    }
                }
            }

            // Verificam daca mai sunt muchii nesterse (cicluri)
            for (int node = 1; node <= n; node++) {
                if (internDegree[node] > 0) {
                    // Graful contine cel putin un ciclu
                    return new ArrayList<>(); // Returnam o lista goala pentru sortare topologica invalida
                }
            }
            return topsort;
        }
    }

    public static void main(String[] args) {
        new Task().solve();
    }
}
