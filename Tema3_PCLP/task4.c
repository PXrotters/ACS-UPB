#include <stdio.h>

#define N 35
#define SIZE_OF_VECTOR 32
#define HALFWAY 31
#define MASK_SIZE 16
#define MASK_BITS 15
#define EGH 8

// Functie pentru calculul unei puteri
long power(int base, int exponent) {
    long result = 1;
    for (int i = 0; i < exponent; i++) {
        result *= base;
    }
    return result;
}

// Functie pentru calculul rezultatului operatiei
int calculate(int a, int b, char op) {
    switch (op) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            return a / b;
        default:
            return 0; // Tratare cazuri de eroare
    }
}

// Functie pentru extragerea si decodificarea instructiunii
void decodeInstruction(int nr) {
    // Extragem numarul de operatii
    int n = 0;
    int i = HALFWAY;
    for (int j = 0, p = 4; j < 3; j++, p /= 2) {
        int k = nr >> i;
        n += p * (k & 1);
        i--;
    }
    n += 1;

    // Extragem operatiile
    char op[n];
    for (int j = 0; j < n; j++) {
        int a = nr >> i;
        i--;
        int b = nr >> i;
        i--;

        int temp = (a & 1) * 2 + (b & 1);

        switch (temp) {
            case 0:
                op[j] = '+';
                break;
            case 1:
                op[j] = '-';
                break;
            case 2:
                op[j] = '*';
                break;
            case 3:
                op[j] = '/';
                break;
            default:
                op[j] = '+'; // Default, ar trebui tratat cazul de eroare
                break;
        }
    }

    // Extragem dimensiunea
    int dim = 0;
    for (int j = 0, p = EGH; j < 4; j++, p /= 2) {
        int k = nr >> i;
        dim += p * (k & 1);
        i--;
    }
    dim += 1;

    // Determinam cate numere trebuie sa citim
    int numbers = 0;
    if (((n + 1) * dim) % MASK_SIZE != 0)
        numbers = ((n + 1) * dim) / MASK_SIZE + 1;
    else
        numbers = ((n + 1) * dim) / MASK_SIZE;

    // Citim numerele
    int v[numbers];
    for (int i = 0; i < numbers; i++) {
        scanf("%d", &v[i]);
    }

    // Formam operanzii
    int operands[numbers * MASK_SIZE / dim];
    int operandsIndex = 0;
    int bitIndex = MASK_BITS;
    int numbersIndex = 0;
    for (int i = 0; i < numbers * (MASK_SIZE / dim); i++) {
        long value = 0;
        for (int j = 0; j < dim; j++) {
            long p = power(2, dim - 1 - j);
            int bit = v[numbersIndex] >> bitIndex;
            value += p * (bit & 1);
             bitIndex--;

            if (bitIndex < 0) {
                numbersIndex++;
                bitIndex = MASK_BITS;
            }
        }
        operands[operandsIndex] = value;
        operandsIndex++;
    }

    // Efectuam operatiile * si /
    for (int i = 0; i < n; i++) {
        if (op[i] == '*' || op[i] == '/') {
            operands[i] = calculate(operands[i], operands[i + 1], op[i]);

            for (int j = i + 1; j < n; j++)
                operands[j] = operands[j + 1];

            for (int j = i; j < n - 1; j++)
                op[j] = op[j + 1];
            n--;
            i--;
        }
    }

    // Calculam rezultatul final
    int result = operands[0];
    for (int i = 1; i < n + 1; i++) {
        result = calculate(result, operands[i], op[i - 1]);
    }

    // Afisam rezultatul final
    printf("%d\n", result);
}

int main() {
    int nr = 0;
    scanf("%d", &nr);

    // Apelam functia pentru decodificarea si calculul instructiunii
    decodeInstruction(nr);

    return 0;
}
