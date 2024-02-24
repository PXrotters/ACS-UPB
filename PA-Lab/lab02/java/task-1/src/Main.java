import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.Comparator;
import java.util.Scanner;

public class Main {
    static class Obj {
        public int weight;
        public int price;

        public Obj() {
            weight = 0;
            price = 0;
        }

        public double getValueWeightRatio() {
            return (double) price / weight;
        }
    };

    static class Task {
        public final static String INPUT_FILE = "in";
        public final static String OUTPUT_FILE = "out";

        int n, w;
        Obj[] objs;

        public void solve() {
            readInput();
            writeOutput(getResult());
        }

        private void readInput() {
            try {
                Scanner sc = new Scanner(new File(INPUT_FILE));
                n = sc.nextInt();
                w = sc.nextInt();
                objs = new Obj[n];
                for (int i = 0; i < n; i++) {
                    objs[i] = new Obj();
                    objs[i].weight = sc.nextInt();
                    objs[i].price = sc.nextInt();
                }
                sc.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private void writeOutput(double result) {
            try {
                PrintWriter pw = new PrintWriter(new File(OUTPUT_FILE));
                pw.printf("%.4f\n", result);
                pw.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private double getResult() {
            // Sortam obiectele folosind un comparator personalizat
            Arrays.sort(objs, new Comparator<Obj>() {
                @Override
                public int compare(Obj o1, Obj o2) {
                    double ratio1 = (double) o1.price / o1.weight;
                    double ratio2 = (double) o2.price / o2.weight;
                    if (ratio1 > ratio2) {
                        return -1; // O1 are un raport valoare/greutate mai mare
                    } else if (ratio1 < ratio2) {
                        return 1; // O2 are un raport valoare/greutate mai mare
                    } else {
                        return 0; // Rapoartele sunt egale
                    }
                }
            });

            double profit = 0.0;
            int currentWeight = 0;

            // Adăugăm obiectele în rucsac în ordine greedy
            for (int i = 0; i < n && currentWeight < w; i++) {
                if (objs[i].weight <= w - currentWeight) {
                    // Daca obiectul poate fi adaugat complet în rucsac, il adaugam complet
                    profit += objs[i].price;
                    currentWeight += objs[i].weight;
                } else {
                    // Altfel, adaugam o parte din obiect in rucsac si actualizam profitul si greutatea
                    profit += (double) objs[i].price / objs[i].weight * (w - currentWeight);
                    currentWeight = w;
                }
            }

            return profit;
        }
    }

    public static void main(String[] args) {
        new Task().solve();
    }
}