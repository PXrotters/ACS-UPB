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
            ArrayList<Integer> subset = new ArrayList<>();
            generateSubsets(1, subset, all);
            return all;
        }

        private void generateSubsets(int index, ArrayList<Integer> subset, ArrayList<ArrayList<Integer>> all) {
            if (index > n) {
                all.add(new ArrayList<>(subset));
                return;
            }

            // Nu adaugam elementul curent in subset
            generateSubsets(index + 1, subset, all);

            // Adaugam elementul curent in subset si continuam cu urmatoarele elemente
            subset.add(index);
            generateSubsets(index + 1, subset, all);

            // Eliminam ultimul element adaugat pentru a genera toate combinatiile posibile
            subset.remove(subset.size() - 1);
        }
    }

    public static void main(String[] args) {
        new Task().solve();
    }
}
