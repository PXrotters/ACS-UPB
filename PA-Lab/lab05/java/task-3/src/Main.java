import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Scanner;

public class Main {
    static class Task {
        public final static String INPUT_FILE = "in";
        public final static String OUTPUT_FILE = "out";

        int n;

        public void solve() {
            readInput();
            writeOutput(getResult());
        }

        private void readInput() {
            try {
                Scanner sc = new Scanner(new File(INPUT_FILE));
                n = sc.nextInt();
                sc.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private void writeOutput(ArrayList<Integer> result) {
            try {
                PrintWriter pw = new PrintWriter(new File(OUTPUT_FILE));
                for (int i = 1; i <= n; i++) {
                    pw.printf("%d%c", result.get(i), i == n ? '\n' : ' ');
                }
                pw.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private ArrayList<Integer> getResult() {
            ArrayList<Integer> sol = new ArrayList<>();
            for (int i = 0; i <= n; i++)
                sol.add(0);

            if (solveNQueens(1, sol))
                return sol;
            else
                return new ArrayList<>(); // Nu exista solutie
        }

        private boolean solveNQueens(int row, ArrayList<Integer> sol) {
            if (row == n + 1)
                return true;

            for (int col = 1; col <= n; col++) {
                if (isValid(row, col, sol)) {
                    sol.set(row, col);
                    if (solveNQueens(row + 1, sol))
                        return true;
                    sol.set(row, 0);
                }
            }

            return false;
        }

        private boolean isValid(int row, int col, ArrayList<Integer> sol) {
            for (int i = 1; i < row; i++) {
                if (sol.get(i) == col || Math.abs(i - row) == Math.abs(sol.get(i) - col))
                    return false;
            }
            return true;
        }
    }

    public static void main(String[] args) {
        new Task().solve();
    }
}
