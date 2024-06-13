import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;
import java.util.ArrayList;

public class Main {
    static class Task {
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

        // parent[node] = parent of node in the DFS traversal
        int[] parent;

        // found[node] = the timestamp when node was found (when started to visit its subtree)
        // Note: The global timestamp is incremented everytime a node is found.
        int[] found;

        // the minimum accessible timestamp that node can see/access
        // low_link[node] = min { found[x] | x is node OR x in ancestors(node) OR x in descendants(node) };
        int[] low_link;

        // global timestamp
        int timestamp;

        public void solve() {
            readInput();
            writeOutput(getResult());
        }

        private void readInput() {
            try {
                Scanner sc = new Scanner(new BufferedReader(new FileReader(INPUT_FILE)));
                n = sc.nextInt();
                m = sc.nextInt();

                for (int i = 1; i <= n; i++) {
                    adj[i] = new ArrayList<>();
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

        private void writeOutput(ArrayList<Integer>  all_cvs) {
            try {
                PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter(OUTPUT_FILE)));
                for (Integer cv : all_cvs) {
                    pw.printf("%d ", cv);
                }
                pw.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private void dfs(int crtNode, int[] time, int[] disc, int[] firstAccessible, ArrayList<Integer> sol) {
            disc[crtNode] = time[0];
            firstAccessible[crtNode] = time[0]++;
            ArrayList<Integer> children = new ArrayList<>();

            for (int nextNode : adj[crtNode]) {
                if (disc[nextNode] == 0) {
                    children.add(nextNode);
                    dfs(nextNode, time, disc, firstAccessible, sol);
                    firstAccessible[crtNode] = Math.min(firstAccessible[nextNode], firstAccessible[crtNode]);
                } else {
                    firstAccessible[crtNode] = Math.min(disc[nextNode], firstAccessible[crtNode]);
                }
            }

            if (disc[crtNode] == firstAccessible[crtNode] && children.size() >= 2) {
                sol.add(crtNode);
            } else if (disc[crtNode] != firstAccessible[crtNode]) {
                for (int childNode : children) {
                    if (firstAccessible[childNode] >= disc[crtNode]) {
                        sol.add(crtNode);
                        break;
                    }
                }
            }
        }

        private ArrayList<Integer> getResult() {
            ArrayList<Integer> sol = new ArrayList<>();
            int[] disc = new int[n + 1];
            int[] firstAccessible = new int[n + 1];
            int[] startTime = {1};

            for (int i = 1; i <= n; ++i) {
                if (disc[i] == 0) {
                    dfs(i, startTime, disc, firstAccessible, sol);
                }
            }

            return sol;
        }
    }

    public static void main(String[] args) {
        new Task().solve();
    }
}