import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Scanner;

public class Main {
    static class Task {
        public final static String INPUT_FILE = "in";
        public final static String OUTPUT_FILE = "out";

        int n, k;

        public void solve() {
            readInput();
            writeOutput(getResult());
        }

        private void readInput() {
            try {
                Scanner sc = new Scanner(new File(INPUT_FILE));
                n = sc.nextInt();
                k = sc.nextInt();
                sc.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private void writeOutput(ArrayList<ArrayList<Integer>> result) {
            try {
                PrintWriter pw = new PrintWriter(new File(OUTPUT_FILE));
                pw.printf("%d\n", result.size());
                for (ArrayList<Integer> arr : result) {
                    for (int i = 0; i < arr.size(); i++) {
                        pw.printf("%d%c", arr.get(i), i + 1 == arr.size() ?
                                '\n' : ' ');
                    }
                }
                pw.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private ArrayList<ArrayList<Integer>> getResult() {
            ArrayList<ArrayList<Integer>> all = new ArrayList<>();
            ArrayList<Integer> currentArrangement = new ArrayList<>();
            boolean[] used = new boolean[n + 1]; // Vector de marcaje pentru elementele folosite

            generateArrangements(all, currentArrangement, used, 1);

            return all;
        }

        private void generateArrangements(ArrayList<ArrayList<Integer>> all, ArrayList<Integer> currentArrangement,
                                          boolean[] used, int position) {
            if (position > k) { // Verificam daca am ajuns la dimensiunea dorita a aranjamentului
                all.add(new ArrayList<>(currentArrangement)); // Adaugam aranjamentul curent la lista de rezultate
                return;
            }

            // Iteram prin toate elementele posibile pentru pozitia curenta
            for (int i = 1; i <= n; i++) {
                if (!used[i]) { // Daca elementul nu a fost deja folosit
                    used[i] = true; // Marcam elementul ca fiind folosit
                    currentArrangement.add(i); // Adaugam elementul in aranjamentul curent
                    // Generam aranjamentele pentru pozitia urmatoare
                    generateArrangements(all, currentArrangement, used, position + 1);
                    currentArrangement.remove(currentArrangement.size() - 1); // Eliminam ultimul element adaugat
                    used[i] = false; // Demarcam elementul pentru a-l putea folosi in alte aranjamente
                }
            }
        }
    }

    public static void main(String[] args) {
        new Task().solve();
    }
}
