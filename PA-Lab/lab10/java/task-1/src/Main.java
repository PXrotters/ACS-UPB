import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class Main {
    static class Task {
        public static final String INPUT_FILE = "in";
        public static final String OUTPUT_FILE = "out";

        // numarul maxim de noduri
        public static final int NMAX = 105;

        // n = numar de noduri
        int n;

        // w[x]y] = constul muchiei de la x la y: (x, y, w[x][y])
        // (w[x][y] = 0 - muchia lipseste)
        //
        // In aceasta problema, costurile sunt strict pozitive.
        int w[][];

        // structura folosita pentru a stoca matricea de distante, matricea
        // de parinti folosind algoritmul RoyFloyd.
        public class RoyFloydResult {
            int d[][];
            int p[][];

            RoyFloydResult(int _d[][], int _p[][]) {
                d = _d;
                p = _p;
            }
        };

        public void solve() {
            readInput();
            writeOutput(getResult());
        }

        private void readInput() {
            try {
                Scanner sc = new Scanner(new BufferedReader(new FileReader(
                                INPUT_FILE)));
                n = sc.nextInt();
                w = new int[n + 1][n + 1];
                for (int i = 1; i <= n; i++) {
                    for (int j = 1; j <= n; j++) {
                        w[i][j] = sc.nextInt();
                    }
                }
                sc.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private void writeOutput(RoyFloydResult res) {
            try {
                BufferedWriter bw = new BufferedWriter(new FileWriter(
                                OUTPUT_FILE));
                StringBuilder sb = new StringBuilder();
                for (int x = 1; x <= n; x++) {
                    for (int y = 1; y <= n; y++) {
                        sb.append(res.d[x][y]).append(' ');
                    }
                    sb.append('\n');
                }
                bw.write(sb.toString());
                bw.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private RoyFloydResult getResult() {
            int[][] d = new int[n + 1][n + 1];
            int[][] p = new int[n + 1][n + 1];

            // Initialize the distance matrix d[][] with the given weights
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= n; j++) {
                    d[i][j] = w[i][j];
                    // If there's no edge between nodes i and j, set distance to 0
                    if (i != j && d[i][j] == 0) {
                        d[i][j] = Integer.MAX_VALUE; // Assuming Integer.MAX_VALUE represents infinity
                    }
                    // If there's an edge from i to j, set the parent matrix p[i][j] to i
                    if (d[i][j] != Integer.MAX_VALUE) {
                        p[i][j] = i;
                    }
                }
            }

            // Roy-Floyd algorithm
            for (int k = 1; k <= n; k++) {
                for (int i = 1; i <= n; i++) {
                    for (int j = 1; j <= n; j++) {
                        // Check if going through node k shortens the distance from i to j
                        if (d[i][k] != Integer.MAX_VALUE && d[k][j] != Integer.MAX_VALUE &&
                                d[i][k] + d[k][j] < d[i][j]) {
                            d[i][j] = d[i][k] + d[k][j];
                            p[i][j] = p[k][j]; // Update the parent of j to be the parent of k
                        }
                    }
                }
            }

            // If there's no path between nodes i and j, set distance to 0
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= n; j++) {
                    if (d[i][j] == Integer.MAX_VALUE) {
                        d[i][j] = 0;
                    }
                }
            }

            return new RoyFloydResult(d, p);
        }

    }

    public static void main(String[] args) {
        new Task().solve();
    }
}
