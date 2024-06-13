import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;

public class Main {
    static int n;
    static int[][] a;
    static int[][] d;
    static int[] fr;

    static void Citire(BufferedReader fin) throws IOException {
        n = Integer.parseInt(fin.readLine());
        a = new int[n + 1][n + 1];
        d = new int[n + 1][n + 1];
        fr = new int[10003];

        for (int i = 1; i <= n; i++) {
            String[] tokens = fin.readLine().split(" ");
            for (int j = 1; j <= n; j++) {
                a[i][j] = Integer.parseInt(tokens[j - 1]);
            }
        }
    }

    static void Afisare(PrintWriter fout) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (a[i][j] == 0) d[i][j] = 0;
                else d[i][j] = 1 + Math.min(Math.min(d[i - 1][j], d[i][j - 1]), d[i - 1][j - 1]);
                fr[d[i][j]]++;
            }
        }

        for (int i = n - 1; i >= 1; i--)
            fr[i] += fr[i + 1];

        for (int i = 1; i <= n; i++)
            fout.println(fr[i]);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("custi.in"));
        PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("custi.out")));

        Citire(fin);
        Afisare(fout);

        fin.close();
        fout.close();
    }
}
