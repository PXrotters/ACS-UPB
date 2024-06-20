#include "./utils.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define SIZEOF_VECTOR 13
#define OFFSET_DIRECTION 4
#define OFFSET_TYPE 5
#define OFFSET_AIRPORT_CODE 6
#define OFFSET_SPEED 9
#define LENGTH_AIRPORT_CODE 3

typedef struct {
    short line;
    short column;
    char direction;
    char type;
    char airport_code[LENGTH_AIRPORT_CODE + 1];
    int speed;
} Plane;

// Functie de comparare pentru qsort
int comparePlanes(const void *a, const void *b) {
    const Plane *plane1 = (const Plane *)a;
    const Plane *plane2 = (const Plane *)b;

    // Compara tipurile de avioane
    if (plane1->type != plane2->type) {
        return plane1->type - plane2->type;
    }

    // Compara codurile aeroporturilor in ordine descrescatoare
    int airportComparison = strcmp(plane2->airport_code, plane1->airport_code);
    if (airportComparison != 0) {
        return airportComparison;
    }

    // Compara vitezele de deplasare
    return plane1->speed - plane2->speed;
}

void SolveTask3(void *info, int nr_planes) {
    // Aloca dinamic vectorul de avioane
    Plane *planes = (Plane *)malloc(nr_planes * sizeof(Plane));

    for (int i = 0; i < nr_planes; i++) {
        void *ptr = info + i * SIZEOF_VECTOR;

        // Extrage datele avionului din vectorul info
        memcpy(&planes[i].line, ptr, sizeof(short));
        memcpy(&planes[i].column, ptr + sizeof(short), sizeof(short));
        memcpy(&planes[i].direction, ptr + OFFSET_DIRECTION, sizeof(char));
        memcpy(&planes[i].type, ptr + OFFSET_TYPE, sizeof(char));
        memcpy(planes[i].airport_code, ptr + OFFSET_AIRPORT_CODE, LENGTH_AIRPORT_CODE);
        planes[i].airport_code[LENGTH_AIRPORT_CODE] = '\0';  // Adauga terminatorul de sir
        memcpy(&planes[i].speed, ptr + OFFSET_SPEED, sizeof(int));
    }

    // Sorteaza vectorul de avioane folosind functia de comparare
    qsort(planes, nr_planes, sizeof(Plane), comparePlanes);

    // Afiseaza informatiile fiecarui avion
    for (int i = 0; i < nr_planes; i++) {
        printf("(%d, %d)\n%c\n%c%s\n%d\n\n", planes[i].line, planes[i].column, planes[i].direction, planes[i].type, planes[i].airport_code, planes[i].speed);
    }

    // Elibereaza memoria alocata pentru vectorul de avioane
    free(planes);
}
