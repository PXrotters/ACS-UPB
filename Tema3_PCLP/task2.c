#include <stdio.h>
#include <math.h>

#define N 35
#define SIZE_OF_VECTOR 32
#define HALFWAY 31
#define MASK_SIZE 16
#define MASK_BITS 15
#define EGH 8

// Functie pentru transformarea unui numar in binar si stocarea intr-un vector
void transform_to_binary(unsigned int inst, unsigned int v[]) {
    int i = 0;
    while (inst > 0) {
        v[i++] = inst % 2;
        inst /= 2;
    }
    for (; i < SIZE_OF_VECTOR; i++)
        v[i] = 0;
}

// Functie pentru inversarea unei parti a vectorului de biti
void reverse_bits(unsigned int v[]) {
    unsigned int aux = 0;
    for (int i = 0; i <= MASK_BITS; i++) {
        aux = v[i];
        v[i] = v[HALFWAY - i];
        v[HALFWAY - i] = aux;
    }
}

// Functie pentru determinarea numarului de instructiuni si afisarea acestuia
unsigned int determine_instructions(unsigned int v[]) {
    unsigned int nr = 0;
    nr = 2 * 2 * v[0] + 2 * v[1] + v[2] + 1;
    return nr;
}

// Functie pentru afisarea operatiilor bazate pe vectorul de biti
void display_operations(unsigned int v[], unsigned int nr, char semn[]) {
    int nrop = 0;
    for (int i = 0; i < nr; i++) {
        unsigned int bit1 = v[3 + i * 2];
        unsigned int bit2 = v[4 + i * 2];
        if (bit1 == 0 && bit2 == 0)
            semn[++nrop] = '+';
        else if (bit1 == 0 && bit2 == 1)
            semn[++nrop] = '-';
        else if (bit1 == 1 && bit2 == 0)
            semn[++nrop] = '*';
        else
            semn[++nrop] = '/';
    }
}

// Functie pentru determinarea dimensiunii si afisarea acesteia
unsigned int determine_size(unsigned int v[], unsigned int nr) {
    unsigned int nrb = nr * 2 + 3;
    unsigned int dim = EGH * v[nrb] + 4 * v[nrb + 1] + 2 * v[nrb + 2] + v[nrb + 3] + 1;
    return dim;
}

// Functie pentru introducerea numerelor si calcularea valorilor corespunzatoare
void input_numbers(int op[], int *nrop, unsigned int nr, unsigned int dim, char semn[]) {
    unsigned short x = 0;
    unsigned int mask = 0;
    unsigned int nec = ((nr + 1) * dim) / MASK_SIZE;
    if (((nr + 1) * dim) % MASK_SIZE != 0)
        nec++;

    *nrop = 0;
    for (int i = 1; i <= nec; i++) {
        scanf("%hu", &x);
        mask = (unsigned int) pow(2, MASK_BITS);

        for (int j = 1; j <= MASK_SIZE / dim; j++) {
            if (*nrop < nr + 1) {
                (*nrop)++;
                for (int k = 0; k <= dim - 1; k++) {
                    if ((mask & x) == mask) {
                        op[*nrop] = op[*nrop] + (int) pow(2, dim - 1 - k);
                    }
                    mask = mask >> 1;
                }
            }
        }
    }
}

// Functie pentru calcularea rezultatului final bazat pe operatiile si valorile stocate
int calculate_result(int op[], char semn[], unsigned int nrop) {
    int rezultat = op[1];
    for (int i = 1; i < nrop; i++) {
        switch (semn[i]) {
            case '+':
                rezultat += op[i + 1];
                break;
            case '-':
                rezultat -= op[i + 1];
                break;
            case '*':
                rezultat *= op[i + 1];
                break;
            case '/':
                rezultat /= op[i + 1];
                break;
        }
    }
    return rezultat;
}

int main() {
    unsigned int inst = 0, v[N] = {0};
    unsigned int nec = 0;
    int op[N] = {0}, nrop = 0;
    char semn[N];

    scanf("%u", &inst);

    // Transformam numarul in binar
    transform_to_binary(inst, v);

    // Inversam o parte din vectorul de biti
    reverse_bits(v);

    // Determinam numarul de instructiuni
    unsigned int nr = determine_instructions(v);

    // Afisam operatiile bazate pe vectorul de biti si le salvam în semn[]
    display_operations(v, nr, semn);

    // Determinăm dimensiunea
    unsigned int dim = determine_size(v, nr);

    // Introducem numerele si calculam valorile corespunzatoare
    nec = ((nr + 1) * dim) / MASK_SIZE;
    if (((nr + 1) * dim) % MASK_SIZE != 0)
        nec++;

    input_numbers(op, &nrop, nr, dim, semn);
    
    // Calculam rezultatul final si il afisam
    int rezultat = calculate_result(op, semn, nrop);
    printf("%d\n", rezultat);
    return 0;
}
