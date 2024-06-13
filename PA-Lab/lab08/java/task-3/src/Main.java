import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Scanner;

public class Main {
    static class Task {
        class Edge {
            int x, y;

            public Edge(int x, int y) {
                this.x = x;
                this.y = y;
            }
        }

        public static final String INPUT_FILE = "in";
        public static final String OUTPUT_FILE = "out";

        // numarul maxim de noduri
        public static final int NMAX = (int) 1e5 + 5; // 10^5 + 5 = 100.005

        // n = numar de noduri, m = numar de muchii/arce
        int n, m;

        // adj[node] = lista de adiacenta a nodului node
        // exemplu: daca adj[node] = {..., neigh, ...} => exista arcul (node, neigh)
        @SuppressWarnings("unchecked")
        ArrayList<Integer> adj[] = new ArrayList[NMAX];

        boolean[] visited;
        int[] parent;
        int[] low;
        int[] disc;
        ArrayList<Edge> all_ces;

        public void solve() {
            readInput();
            all_ces = getResult();
            writeOutput(all_ces);
        }

        private void readInput() {
            try {
                Scanner sc = new Scanner(new BufferedReader(new FileReader(INPUT_FILE)));
                n = sc.nextInt();
                m = sc.nextInt();

                visited = new boolean[n + 1];
                parent = new int[n + 1];
                low = new int[n + 1];
                disc = new int[n + 1];
                all_ces = new ArrayList<>();

                for (int i = 1; i <= n; i++) {
                    adj[i] = new ArrayList<>();
                    visited[i] = false;
                    parent[i] = -1;
                }

                for (int i = 1; i <= m; i++) {
                    int x, y;
                    x = sc.nextInt();
                    y = sc.nextInt();
                    // muchie (x, y)
                    adj[x].add(y);
                    adj[y].add(x);
                }
                sc.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private void writeOutput(ArrayList<Edge> all_ces) {
            try {
                PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter(OUTPUT_FILE)));
                pw.printf("%d\n", all_ces.size());
                for (Edge ce : all_ces) {
                    pw.printf("%d %d\n", ce.x, ce.y);
                }
                pw.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private void dfs(int crtNode, int[] time, int crtDad, int[] disc, int[] firstAccessible, ArrayList<Edge> sol) {
            disc[crtNode] = firstAccessible[crtNode] = time[0]++;

            for (int nextNode : adj[crtNode]) {
                if (disc[nextNode] == 0) {
                    dfs(nextNode, time, crtNode, disc, firstAccessible, sol);
                    firstAccessible[crtNode] = Math.min(firstAccessible[nextNode], firstAccessible[crtNode]);

                    if (firstAccessible[nextNode] > disc[crtNode]) {
                        sol.add(new Edge(crtNode, nextNode));
                    }
                } else if (nextNode != crtDad) {
                    firstAccessible[crtNode] = Math.min(disc[nextNode], firstAccessible[crtNode]);
                }
            }
        }

        private ArrayList<Edge> getResult() {
            ArrayList<Edge> sol = new ArrayList<>();
            int[] disc = new int[n + 1];
            int[] firstAccessible = new int[n + 1];
            int[] startTime = {1};

            for (int i = 1; i <= n; ++i) {
                if (disc[i] == 0) {
                    dfs(i, startTime, 0, disc, firstAccessible, sol);
                }
            }

            return sol;
        }
    }

    public static void main(String[] args) {
        new Task().solve();
    }
}