import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.StringTokenizer;
import static java.lang.Integer.parseInt;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder out = new StringBuilder();
        StringTokenizer tokenizer;

        tokenizer = new StringTokenizer(in.readLine());
        int n = parseInt(tokenizer.nextToken());
        int k = parseInt(tokenizer.nextToken());
        tokenizer = new StringTokenizer(in.readLine());

        int [] a = new int[n];
        int [] b = new int[n];
        int [] c = new int[n];
        int total = 0;

        for (int i = 0; i < n; i++) {
            a[i] = parseInt(tokenizer.nextToken());
        }
        tokenizer = new StringTokenizer(in.readLine());
        for (int i = 0; i < n; i++) {
            b[i] = parseInt(tokenizer.nextToken());
            total += b[i];
            c[i] = a[i] - b[i];
        }

        Arrays.sort(c);

        int current = 0;
        for (int i = 0; i < n; i++) {
            if (current < k || c[i] < 0) {
                total += c[i];
                current++;
            }
        }

        System.out.println(total);
    }
}
