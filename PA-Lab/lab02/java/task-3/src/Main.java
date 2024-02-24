import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.Scanner;

public class Main {
    static class Homework {
        public int deadline;
        public int score;

        public Homework() {
            deadline = 0;
            score = 0;
        }
    }

    static class Task {
        public final static String INPUT_FILE = "in";
        public final static String OUTPUT_FILE = "out";

        int n;
        Homework[] hws;

        public void solve() {
            readInput();
            writeOutput(getResult());
        }

        private void readInput() {
            try {
                Scanner sc = new Scanner(new File(INPUT_FILE));
                n = sc.nextInt();
                hws = new Homework[n];
                for (int i = 0; i < n; i++) {
                    hws[i] = new Homework();
                    hws[i].deadline = sc.nextInt();
                    hws[i].score = sc.nextInt();
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
            // Sortam temele in functie de punctajul lor in ordine descrescatoare
            Arrays.sort(hws, (a, b) -> Integer.compare(b.score, a.score));

            // Inițializam matricea de deadline-uri cu -1 (insemnand ca nu exista nicio tema la acel termen)
            int maxDeadline = Arrays.stream(hws).mapToInt(hw -> hw.deadline).max().orElse(0);
            int[] deadlines = new int[maxDeadline + 1];
            Arrays.fill(deadlines, -1);

            // Parcurgem temele si le alocam în ordine
            int totalScore = 0;
            for (int i = 0; i < n; i++) {
                // Cautam prima locatie disponibila inainte de deadline-ul temei
                int j = hws[i].deadline;
                while (j > 0 && deadlines[j] != -1) {
                    j--;
                }
                // Daca gasim o locatie disponibila, o ocupam si adaugam punctajul temei la total
                if (j > 0) {
                    deadlines[j] = i;
                    totalScore += hws[i].score;
                }
            }

            return totalScore;
        }

    }

    public static void main(String[] args) {
        new Task().solve();
    }
}
