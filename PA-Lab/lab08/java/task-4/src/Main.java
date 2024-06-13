import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.Stack;

public class Main {
    static class Task {
        class Edge {
            int x, y;

            public Edge(int x, int y) {
                this.x = x;
                this.y = y;
            }

            public boolean equals(Object o) {
                if (o == this) {
                    return true;
                }
                if (!(o instanceof Edge)) {
                    return false;
                }
                Edge other = (Edge)(o);
                return (x == other.x && y == other.y);
            }
        }

        public static final String INPUT_FILE = "in";
        public static final String OUTPUT_FILE = "out";

        // numarul maxim de noduri
        public static final int NMAX = (int) 1e5 + 5; // 10^5 + 5 = 100.005

        // n = numar de noduri, m = numar de muchii/arce
        int n, m, timp;

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
        private void writeOutput(ArrayList<ArrayList<Integer>> all_bccs) {
            try {
                PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter(OUTPUT_FILE)));
                pw.printf("%d\n", all_bccs.size());
                for (ArrayList<Integer> bcc : all_bccs) {
                    for (Integer node : bcc) {
                        pw.printf("%d ", node);
                    }
                    pw.printf("\n");
                }
                pw.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private ArrayList<ArrayList<Integer>> getResult() {
            ArrayList<ArrayList<Integer>> allBCCs = new ArrayList<>();
            Stack<Integer> stack = new Stack<>();
            int[] depth = new int[NMAX];
            int[] low = new int[NMAX];
            boolean[] inStack = new boolean[NMAX];

            timp = 0;

            for (int i = 1; i <= n; i++) {
                if (depth[i] == 0) {
                    tarjan(i, -1, stack, depth, low, inStack, allBCCs);
                }
            }

            return allBCCs;
        }

        private void tarjan(int node, int parent, Stack<Integer> stack, int[] depth, int[] low, boolean[] inStack, ArrayList<ArrayList<Integer>> allBCCs) {
            depth[node] = low[node] = ++timp;
            stack.push(node);
            inStack[node] = true;

            for (int nextNode : adj[node]) {
                if (nextNode == parent) continue;

                if (depth[nextNode] == 0) {
                    tarjan(nextNode, node, stack, depth, low, inStack, allBCCs);
                    low[node] = Math.min(low[node], low[nextNode]);

                    if (low[nextNode] >= depth[node]) {
                        ArrayList<Integer> bcc = new ArrayList<>();
                        while (true) {
                            int x = stack.pop();
                            bcc.add(x);
                            inStack[x] = false;
                            if (x == nextNode) break;
                        }
                        bcc.add(node);
                        allBCCs.add(bcc);
                    }
                } else if (inStack[nextNode]) {
                    low[node] = Math.min(low[node], depth[nextNode]);
                }
            }
        }
    }

    public static void main(String[] args) {
        new Task().solve();
    }
}