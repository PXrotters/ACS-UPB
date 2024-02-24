import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;

public class Main {
    static class Task {
        public final static String INPUT_FILE = "in";
        public final static String OUTPUT_FILE = "out";
        public final static double EPSILON = 0.001;

        double n;

        public void solve() {
            readInput();
            writeOutput(getResult());
        }

        private void readInput() {
            try {
                Scanner sc = new Scanner(new File(INPUT_FILE));
                n = sc.nextDouble();
                sc.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private void writeOutput(double x) {
            try {
                PrintWriter pw = new PrintWriter(new File(OUTPUT_FILE));
                pw.printf("%.4f\n", x);
                pw.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private double getResult() {
            double left = 0;
            double right = Math.max(1, n); // Ajustăm intervalul pe baza valorii lui n

            while (right - left > EPSILON) {
                double mid = (left + right) / 2;
                double square = mid * mid;
                if (square > n) {
                    right = mid;
                } else {
                    left = mid;
                }
            }

            return (left + right) / 2; // Întoarce media din intervalul rezultat.
        }
    }

    public static void main(String[] args) {
        new Task().solve();
    }
}