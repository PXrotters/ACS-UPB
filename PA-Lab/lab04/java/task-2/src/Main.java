import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;

public class Main {
    static class Task {
        public final static String INPUT_FILE = "in";
        public final static String OUTPUT_FILE = "out";

        private final static int MOD = 1000000007;

        int n;
        char[] expr;

        public void solve() {
            readInput();
            writeOutput(getResult());
        }

        private void readInput() {
            try {
                Scanner sc = new Scanner(new File(INPUT_FILE));
                n = sc.nextInt();
                String s = sc.next().trim();
                s = " " + s;
                expr = s.toCharArray();
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
            long[][] dpTrue = new long[n + 1][n + 1];
            long[][] dpFalse = new long[n + 1][n + 1];

            for (int i = 1; i <= n; i++) {
                if (expr[i] == 'T' || expr[i] == 'F') {
                    if (expr[i] == 'T') {
                        dpTrue[i][i] = 1;
                        dpFalse[i][i] = 0;
                    } else {
                        dpTrue[i][i] = 0;
                        dpFalse[i][i] = 1;
                    }
                }
            }

            for (int len = 3; len <= n; len += 2) {
                for (int i = 1; i <= n - len + 1; i += 2) {
                    int j = i + len - 1;
                    for (int k = i + 1; k <= j - 1; k += 2) {
                        if (expr[k] == '&') {
                            dpTrue[i][j] += (dpTrue[i][k - 1] * dpTrue[k + 1][j]) % MOD;
                            dpFalse[i][j] += ((dpFalse[i][k - 1] * dpTrue[k + 1][j]) % MOD +
                                    (dpTrue[i][k - 1] * dpFalse[k + 1][j]) % MOD +
                                    (dpFalse[i][k - 1] * dpFalse[k + 1][j]) % MOD) % MOD;
                        } else if (expr[k] == '|') {
                            dpTrue[i][j] += ((dpTrue[i][k - 1] * dpFalse[k + 1][j]) % MOD +
                                    (dpFalse[i][k - 1] * dpTrue[k + 1][j]) % MOD +
                                    (dpTrue[i][k - 1] * dpTrue[k + 1][j]) % MOD) % MOD;
                            dpFalse[i][j] += (dpFalse[i][k - 1] * dpFalse[k + 1][j]) % MOD;
                        } else if (expr[k] == '^') {
                            dpTrue[i][j] += ((dpTrue[i][k - 1] * dpFalse[k + 1][j]) % MOD +
                                    (dpFalse[i][k - 1] * dpTrue[k + 1][j]) % MOD) % MOD;
                            dpFalse[i][j] += ((dpTrue[i][k - 1] * dpTrue[k + 1][j]) % MOD +
                                    (dpFalse[i][k - 1] * dpFalse[k + 1][j]) % MOD) % MOD;
                        }
                    }
                }
            }

            return (int) (dpTrue[1][n] % MOD);
        }
    }

    public static void main(String[] args) {
        new Task().solve();
    }
}
