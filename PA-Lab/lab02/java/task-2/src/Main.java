import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;

public class Main {
    static class Task {
        public final static String INPUT_FILE = "in";
        public final static String OUTPUT_FILE = "out";

        int n, m;
        int[] dist;

        public void solve() {
            readInput();
            writeOutput(getResult());
        }

        private void readInput() {
            try {
                Scanner sc = new Scanner(new File(INPUT_FILE));
                n = sc.nextInt();
                m = sc.nextInt();
                dist = new int[n];
                for (int i = 0; i < n; i++) {
                    dist[i] = sc.nextInt();
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
            int numarOpriri = 0; // numarul minim de opriri necesare
            int distantaParcursa = 0; // distanta parcursa intre opriri

            for (int i = 0; i < n - 1; i++) {
                int distantaIntreBenzinarii = dist[i + 1] - dist[i];

                // Verificam daca distanta parcursa intre benzinarii este mai mare sau egala cu capacitatea masinii
                if (distantaParcursa + distantaIntreBenzinarii >= m) {
                    // Dacă da, trebuie sa facem o oprire la benzinaria curenta
                    numarOpriri++;
                    // Resetam distanta parcursa pentru a porni de la benzinaria curenta
                    distantaParcursa = 0;
                } else {
                    // Altfel, continuam sa adaugam la distanta parcursa
                    distantaParcursa += distantaIntreBenzinarii;
                }
            }

            // Ultima benzinarie nu necesita o oprire în plus, deoarece este destinatia
            return numarOpriri;
        }


    }

    public static void main(String[] args) {
        new Task().solve();
    }
}
