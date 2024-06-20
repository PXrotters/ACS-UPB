#include <stdio.h>

#define N 35
#define SIZE_OF_VECTOR 32
#define LOOP_LIMIT 15
#define HALFWAY 31

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
    for (int i = 0; i <= LOOP_LIMIT; i++) {
        aux = v[i];
        v[i] = v[HALFWAY - i];
        v[HALFWAY - i] = aux;
    }
}

// Functie pentru determinarea numarului de instructiuni si afisarea acestuia
unsigned int determine_instructions(unsigned int v[]) {
    unsigned int nr = 0;
    nr = 2 * 2 * v[0] + 2 * v[1] + v[2] + 1;
    printf("%u", nr);
    return nr;
}

// Functie pentru afisarea operatiilor bazate pe vectorul de biti
void display_operations(unsigned int v[], unsigned int nr) {
    for (int i = 0; i < nr; i++) {
        unsigned int bit1 = v[3 + i * 2];
        unsigned int bit2 = v[3 + 1 + i * 2];
        if (bit1 == 0 && bit2 == 0)
            printf(" +");
        else if (bit1 == 0 && bit2 == 1)
            printf(" -");
        else if (bit1 == 1 && bit2 == 0)
            printf(" *");
        else
            printf(" /");
    }
}

// Functie pentru determinarea dimensiunii si afisarea acesteia
unsigned int determine_size(unsigned int v[], unsigned int nr) {
    nr *= 2;
    nr += 3;
    unsigned int dim = 2 * 2 * 2 * v[nr] + 2 * 2 * v[nr + 1] + 2 * v[nr + 2] + v[nr + 3] + 1;
    printf(" %u\n", dim);
    return dim;
}

int main() {
    unsigned int inst = 0, v[N] = {0};

    scanf("%u", &inst);

    // Transformam numarul in binar
    transform_to_binary(inst, v);

    // Inversam o parte din vectorul de biti
    reverse_bits(v);

    // Determinam si afisam numarul de instructiuni
    unsigned int nr = determine_instructions(v);

    // Afisam operatiile bazate pe vectorul de biti
    display_operations(v, nr);

    // Determinam si afisam dimensiunea
    unsigned int dim = determine_size(v, nr);

    return 0;
}
