import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Scanner;

public class Main {
    static class Result {
        int len; // rezultat pentru cerinta 1
        ArrayList<Integer> subsequence; // rezultat pentru cerinta 2

        public Result() {
            len = 0;
            subsequence = new ArrayList<>();
        }
    }

    static class Task {
        public final static String INPUT_FILE = "in";
        public final static String OUTPUT_FILE = "out";

        int n, m;
        int[] v;
        int[] w;

        public void solve() {
            readInput();
            writeOutput(getResult());
        }

        private void readInput() {
            try {
                Scanner sc = new Scanner(new File(INPUT_FILE));
                n = sc.nextInt();
                m = sc.nextInt();

                v = new int[n + 1]; // Adaugare element fictiv - indexare de la 1
                for (int i = 1; i <= n; i++) {
                    v[i] = sc.nextInt();
                }

                w = new int[m + 1]; // Adaugare element fictiv - indexare de la 1
                for (int i = 1; i <= m; i++) {
                    w[i] = sc.nextInt();
                }
                sc.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private void writeOutput(Result result) {
            try {
                PrintWriter pw = new PrintWriter(new File(OUTPUT_FILE));
                pw.printf("%d\n", result.len);
                for (Integer x : result.subsequence) {
                    pw.printf("%d ", x);
                }
                pw.printf("\n");
                pw.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private Result getResult() {
            Result result = new Result();

            // Matricea pentru stocarea rezultatelor parțiale ale lungimii CMLSC
            int[][] dp = new int[n + 1][m + 1];

            // Calcularea lungimii CMLSC
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= m; j++) {
                    if (v[i] == w[j]) {
                        dp[i][j] = dp[i - 1][j - 1] + 1;
                    } else {
                        dp[i][j] = Math.max(dp[i - 1][j], dp[i][j - 1]);
                    }
                }
            }

            // Lungimea celui mai lung subsir comun
            result.len = dp[n][m];

            // Reconstituirea subsirului comun
            int i = n, j = m;
            while (i > 0 && j > 0) {
                if (v[i] == w[j]) {
                    result.subsequence.add(v[i]);
                    i--;
                    j--;
                } else if (dp[i - 1][j] > dp[i][j - 1]) {
                    i--;
                } else {
                    j--;
                }
            }

            // Inversăm rezultatul pentru a-l afișa în ordinea corectă
            Collections.reverse(result.subsequence);

            return result;
        }
    }

    public static void main(String[] args) {
        new Task().solve();
    }
}
