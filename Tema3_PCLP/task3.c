#include <stdio.h>
#include <math.h>

#define N 35
#define SIZE_OF_VECTOR 32
#define HALFWAY 31
#define MASK_SIZE 16
#define MASK_BITS 15
#define EGH 8

// Transformare numar in binar si stocare in vector
void transform_to_binary(unsigned int inst, unsigned int v[]) {
    int i = 0;
    while (inst > 0) {
        v[i++] = inst % 2;
        inst /= 2;
    }
    for (; i < SIZE_OF_VECTOR; i++)
        v[i] = 0;
}

// Rearanjare vector de biti
void rearrange_bits(unsigned int v[]) {
    unsigned int aux = 0;
    for (int i = 0; i <= MASK_BITS; i++) {
        aux = v[i];
        v[i] = v[HALFWAY - i];
        v[HALFWAY - i] = aux;
    }
}

// Calcul numar de instructiuni
unsigned int determine_instructions(unsigned int v[]) {
    unsigned int nr = 0;
    nr = 2 * 2 * v[0] + 2 * v[1] + v[2] + 1;
    return nr;
}

// Determinare operatii si salvare in sir
void determine_operations(unsigned int v[], unsigned int nr, char semn[]) {
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

// Determinare dimensiune
unsigned int determine_size(unsigned int v[], unsigned int nr) {
    unsigned int nrb = nr * 2 + 3;
    unsigned int dim = EGH * v[nrb] + 4 * v[nrb + 1] + 2 * v[nrb + 2] + v[nrb + 3] + 1;
    return dim;
}

// Functie pentru introducerea numerelor si calcularea valorilor corespunzatoare
void input_numbers(int op[], int *nrop, unsigned int nr, unsigned int dim) {
    unsigned short x = 0;
    unsigned short mask = (unsigned short) pow(2, MASK_BITS);
    unsigned int nec = ((nr + 1) * dim) / MASK_SIZE;
    if (((nr + 1) * dim) % MASK_SIZE != 0)
        nec++;

    *nrop = 0;
    unsigned int dim2 = 0;
    for (int i = 1; i <= nec; i++) {
        scanf("%hu", &x);
        mask = (unsigned short) pow(2, MASK_BITS);

        while (mask > 0 && *nrop < nr + 1) {
            if (dim2 == 0)
                dim2 = dim;
            (*nrop)++;
            while (dim2 > 0) {
                if ((mask & x) == mask)
                    op[*nrop] = op[*nrop] + (int) pow(2, dim2 - 1);
                mask = mask >> 1;
                dim2--;
                if (mask == 0) {
                    (*nrop)--;
                    break;
                }
            }
        }
    }
}

// Calcul rezultat final
int calculate_result(int op[], char semn[], int nrop) {
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
    unsigned int nr = 0;
    int op[N] = {0}, nrop = 0, rezultat = 0;
    unsigned int dim = 0;
    char semn[N];

    // Citirea instructiunii si conversia in binar
    scanf("%u", &inst);
    transform_to_binary(inst, v);

    // Rearanjarea vectorului cu biti
    rearrange_bits(v);

    // Calculul numarului de instructiuni
    nr = determine_instructions(v);

    // Determinarea operatiilor si salvarea in semn[]
    determine_operations(v, nr, semn);

    // Determinarea dimensiunii
    dim = determine_size(v, nr);

    // Introducerea numerelor si calculul valorilor corespunzatoare utilizand functia definita
    input_numbers(op, &nrop, nr, dim);

    // Calculul rezultatului final si afisarea acestuia
    rezultat = calculate_result(op, semn, nrop);
    printf("%d\n", rezultat);
}