import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;

public class Main {
    static class Task {
        public final static String INPUT_FILE = "in";
        public final static String OUTPUT_FILE = "out";

        int base;
        int exponent;
        int mod;

        public void solve() {
            readInput();
            writeOutput(getResult());
        }

        private void readInput() {
            try {
                Scanner sc = new Scanner(new File(INPUT_FILE));
                base = sc.nextInt();
                exponent = sc.nextInt();
                mod = sc.nextInt();
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

        private int fastPow(int base, int exponent, int mod) {
            if (exponent == 0)
                return 1;

            long result = 1;
            long baseLong = base % mod; // ne asiguram ca baza este mai mica decât modul pentru a evita overflow-ul

            while (exponent > 0) {
                // Daca exponentul este impar, inmultim rezultatul cu baza (mod mod)
                if (exponent % 2 == 1)
                    result = (result * baseLong) % mod;

                // Ridicam baza la patrat si reducem exponentul la jumatate
                baseLong = (baseLong * baseLong) % mod;
                exponent /= 2;
            }

            return (int) result;
        }

        private int getResult() {
            return fastPow(base, exponent, mod);
        }
    }

    public static void main(String[] args) {
        new Task().solve();
    }
}
