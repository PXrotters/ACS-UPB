import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;

public class Main {
    static class Task {
        public final static String INPUT_FILE = "in";
        public final static String OUTPUT_FILE = "out";

        int n, x, y;

        public void solve() {
            readInput();
            writeOutput(getResult(n, x, y));
        }

        private void readInput() {
            try {
                Scanner sc = new Scanner(new File(INPUT_FILE));
                n = sc.nextInt();
                x = sc.nextInt();
                y = sc.nextInt();
                sc.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private void writeOutput(int answer) {
            try {
                PrintWriter pw = new PrintWriter(new File(OUTPUT_FILE));
                pw.printf("%d\n", answer);
                pw.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private int getResult(int n, int x, int y) {
            int order = 0;
            int size = (int) Math.pow(2, n);  //size = 1 << n

            x--; // Coordonatele pleaca de la 0
            y--;

            while (n > 0) {
                size /= 2;
                n--;

                int quadrantX;
                if (x >= size) {
                    quadrantX = 1;
                } else {
                    quadrantX = 0;
                }
                int quadrantY;
                if (y >= size) {
                    quadrantY = 1;
                } else {
                    quadrantY = 0;
                }
                int quadrant = 2 * quadrantX + quadrantY;

                order += quadrant * size * size;

                // Ajustam coordonatele pentru urmatorul cadran
                if (quadrantX == 1) {
                    x -= size; // Se misca catre urmatorul cadran in directia x
                }
                if (quadrantY == 1) {
                    y -= size; // Se misca catre urmatorul cadran in directia y
                }
                x = Math.max(x, 0); // Ne asiguram ca x e pozitiv
                y = Math.max(y, 0); // Ne asiguram ca y e pozitiv
            }

            return order + 1;
        }
    }

    public static void main(String[] args) {
        new Task().solve();
    }
}
