import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;

public class Main {
    static class Task {
        public final static String INPUT_FILE = "in";
        public final static String OUTPUT_FILE = "out";

        int n, S;
        int[] v;

        public void solve() {
            readInput();
            writeOutput(getResult());
        }

        private void readInput() {
            try {
                Scanner sc = new Scanner(new File(INPUT_FILE));
                n = sc.nextInt();
                S = sc.nextInt();
                v = new int[n + 1];
                for (int i = 1; i <= n; i++) {
                    v[i] = sc.nextInt();
                }
                sc.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private void writeOutput(int result) {
            try {
                PrintWriter pw = new PrintWriter(new File(OUTPUT_FILE));
                pw.printf("%d\n", result);
                pw.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private int getResult() {
            int[] dp = new int[S + 1]; // Initializam un vector pentru a stoca rezultatele partiale
            dp[0] = 0; // Numarul minim de monede pentru a obtine suma 0 este 0

            // Initializam restul valorilor cu o valoare mare, pentru a le putea actualiza ulterior
            for (int i = 1; i <= S; i++) {
                dp[i] = Integer.MAX_VALUE;
            }

            // Calculăm numarul minim de monede pentru fiecare suma de la 1 la S
            for (int i = 1; i <= S; i++) {
                // Pentru fiecare tip de moneda disponibila
                for (int j = 1; j <= n; j++) {
                    // Verificam daca moneda j poate fi folosita pentru a obține suma i
                    if (v[j] <= i && dp[i - v[j]] != Integer.MAX_VALUE) {
                        // Actualizam numarul minim de monede necesare pentru suma i
                        dp[i] = Math.min(dp[i], dp[i - v[j]] + 1);
                    }
                }
            }

            // Verificam daca solutia exista sau nu pentru suma S
            if (dp[S] == Integer.MAX_VALUE) {
                return -1; // Nu exista solutie
            } else {
                return dp[S]; // Returnam numarul minim de monede necesare
            }
        }
    }

    public static void main(String[] args) {
        new Task().solve();
    }
}
