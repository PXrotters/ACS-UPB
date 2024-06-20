#include "./utils.h"

#define SIZEOF_VECTOR 13
#define CODE_LENGTH 4

void SolveTask1(void *info, int numPlanes) {
    for (int i = 0; i < numPlanes; i++) {
        short planeLine = 0, planeColumn = 0;
        char planeDirection = '\0';
        char planeCode[CODE_LENGTH + 1]; // +1 for null-terminator
        int planeSpeed = 0;

        // Calcularea offset-ului pentru fiecare avion
        void *planePtr = info + i * SIZEOF_VECTOR;

        // Extrage linia si coloana
        memcpy(&planeLine, planePtr, sizeof(short));
        memcpy(&planeColumn, (char *)planePtr + sizeof(short), sizeof(short));

        // Extrage directia
        memcpy(&planeDirection, (char *)planePtr + 2 * sizeof(short), sizeof(char));

        // Extrage codul avionului
        memcpy(planeCode, (char *)planePtr + 2 * sizeof(short) + sizeof(char), CODE_LENGTH);
        planeCode[CODE_LENGTH] = '\0';  // Adaugam null-terminator

        // Extrage viteza
        memcpy(&planeSpeed, (char *)planePtr + 2 * sizeof(short) + sizeof(char) + CODE_LENGTH, sizeof(int));

        // Afiseaza informatiile despre avion
        printf("(%d, %d)\n%c\n%s\n%d\n\n", planeLine, planeColumn, planeDirection, planeCode, planeSpeed);
    }
}
