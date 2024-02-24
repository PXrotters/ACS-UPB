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
        char[] caractere;
        int[] freq;

        public void solve() {
            readInput();
            writeOutput(getResult());
        }

        private void readInput() {
            try {
                Scanner sc = new Scanner(new File(INPUT_FILE));
                n = sc.nextInt();
                k = sc.nextInt();
                String s = sc.next().trim();
                s = " " + s;
                caractere = s.toCharArray();
                freq = new int[n + 1];
                for (int i = 1; i <= n; i++) {
                    freq[i] = sc.nextInt();
                }
                sc.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private void writeOutput(ArrayList<ArrayList<Character>> result) {
            try {
                PrintWriter pw = new PrintWriter(new File(OUTPUT_FILE));
                pw.printf("%d\n", result.size());
                for (ArrayList<Character> arr : result) {
                    for (int i = 0; i < arr.size(); i++) {
                        pw.printf("%c", arr.get(i));
                    }
                    pw.printf("\n");
                }
                pw.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

         private ArrayList<ArrayList<Character>> getResult() {
            ArrayList<ArrayList<Character>> all = new ArrayList<>();
            generateStrings(new ArrayList<>(), 0, all);
            return all;
        }

        private void generateStrings(ArrayList<Character> current, int consecutiveCount, ArrayList<ArrayList<Character>> result) {
            if (current.size() == n) {
                result.add(new ArrayList<>(current));
                return;
            }

            for (int i = 0; i < n; i++) {
                if (freq[i] > 0 && (current.isEmpty() || current.get(current.size() - 1) != caractere[i] || consecutiveCount < k)) {
                    current.add(caractere[i]);
                    int newConsecutiveCount = (current.size() > 1 && current.get(current.size() - 1) == current.get(current.size() - 2)) ? consecutiveCount + 1 : 1;
                    freq[i]--; // Scadem frecventa caracterului folosit
                    generateStrings(current, newConsecutiveCount, result);
                    freq[i]++; // Restauram frecventa caracterului dupa ce am terminat de utilizat in aceasta ramura a recursivitatii
                    current.remove(current.size() - 1);
                }
            }
        }

    }

    public static void main(String[] args) {
        new Task().solve();
    }
}
