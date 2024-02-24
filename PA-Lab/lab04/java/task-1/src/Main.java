import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;

public class Main {
    static class Task {
        public final static String INPUT_FILE = "in";
        public final static String OUTPUT_FILE = "out";

        int n;
        int[] v;

        private final static int MOD = 1000000007;

        public void solve() {
            readInput();
            writeOutput(getResult());
        }

        private void readInput() {
            try {
                Scanner sc = new Scanner(new File(INPUT_FILE));
                n = sc.nextInt();
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
            int sum = 0;
            for (int num : v) {
                sum += num;
            }

            int[][] dp = new int[n + 1][sum + 1];
            dp[0][0] = 1;

            for (int i = 1; i <= n; i++) {
                for (int j = 0; j <= sum; j++) {
                    dp[i][j] = dp[i - 1][j];
                    if (j >= v[i]) {
                        dp[i][j] += dp[i - 1][j - v[i]];
                        dp[i][j] %= MOD;
                    }
                }
            }

            int result = -1;
            for (int j = 0; j <= sum; j++) {
                if (j % 2 == 0) {
                    result += dp[n][j];
                    result %= MOD;
                }
            }

            return result;
        }
    }

    public static void main(String[] args) {
        new Task().solve();
    }
}
