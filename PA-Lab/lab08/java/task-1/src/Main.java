import java.io.*;
import java.util.ArrayList;
import java.util.Scanner;
import java.util.Stack;

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

        // lista de componente tare-conexe
        ArrayList<ArrayList<Integer>> all_sccs = new ArrayList<>();

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
                    adj[x].add(y); // arc (x, y)
                }
                sc.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private void writeOutput(ArrayList<ArrayList<Integer>> all_sccs) {
            try {
                PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter(OUTPUT_FILE)));
                pw.printf("%d\n", all_sccs.size());
                for (ArrayList<Integer> scc : all_sccs) {
                    for (Integer node : scc) {
                        pw.printf("%d ", node);
                    }
                    pw.printf("\n");
                }
                pw.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private void dfs(int crtNode, int[] time, int[] disc, int[] firstAccessible, Stack<Integer> stack,
                         ArrayList<ArrayList<Integer>> sol, boolean[] inStack) {
            disc[crtNode] = time[0];
            firstAccessible[crtNode] = time[0]++;
            stack.push(crtNode);
            inStack[crtNode] = true;

            for (int nextNode : adj[crtNode]) {
                if (disc[nextNode] == 0) {
                    dfs(nextNode, time, disc, firstAccessible, stack, sol, inStack);
                    firstAccessible[crtNode] = Math.min(firstAccessible[nextNode], firstAccessible[crtNode]);
                } else if (inStack[nextNode]) {
                    firstAccessible[crtNode] = Math.min(disc[nextNode], firstAccessible[crtNode]);
                }
            }

            if (disc[crtNode] == firstAccessible[crtNode]) {
                ArrayList<Integer> crtSol = new ArrayList<>();
                int x;
                do {
                    x = stack.pop();
                    crtSol.add(x);
                    inStack[x] = false;
                } while (crtNode != x);
                sol.add(crtSol);
            }
        }

        private ArrayList<ArrayList<Integer>> getResult() {
            ArrayList<ArrayList<Integer>> sol = new ArrayList<>();
            int[] disc = new int[n + 1];
            int[] firstAccessible = new int[n + 1];
            boolean[] isInStack = new boolean[n + 1];
            Stack<Integer> s = new Stack<>();
            int[] startTime = {1};

            for (int i = 1; i <= n; ++i) {
                if (disc[i] == 0) {
                    dfs(i, startTime, disc, firstAccessible, s, sol, isInStack);
                }
            }

            return sol;
        }
    }

    public static void main(String[] args) {
        new Task().solve();
    }
}