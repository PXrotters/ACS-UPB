#include "./utils.h"

#define SIZEOF_VECTOR 13
#define PLANE_TYPE_1_ROWS 4
#define PLANE_TYPE_1_COLS 7
#define PLANE_TYPE_2_ROWS 5
#define PLANE_TYPE_2_COLS 9

// Functie pentru afisarea unei matrice de caractere
void printMatrix(char **matrix, int numRows, int numCols) {
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Functie pentru interschimbarea a doua valori intregi
void swapIntegers(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Functie pentru rotirea matricei in sensul acelor de ceasornic
char **rotateMatrixClockwise(char **matrix, int *numRows, int *numCols) {
    char **rotatedMatrix = (char **)malloc((*numCols) * sizeof(char *));
    for (int i = 0; i < (*numCols); i++) {
        rotatedMatrix[i] = (char *)malloc((*numRows) * sizeof(char));
    }

    for (int i = 0; i < *numRows; i++) {
        for (int j = 0; j < *numCols; j++) {
            rotatedMatrix[j][*numRows - i - 1] = matrix[i][j];
        }
    }

    free_mat(matrix, *numRows);
    swapIntegers(numRows, numCols);
    return rotatedMatrix;
}

// Functie pentru construirea layout-ului unui avion in functie de tip
char **buildPlaneLayout(char type) {
    if (type == '1') {
        char **planeType1 = (char **)malloc(PLANE_TYPE_1_ROWS * sizeof(char *));
        for (int i = 0; i < PLANE_TYPE_1_ROWS; i++) {
            planeType1[i] = (char *)malloc(PLANE_TYPE_1_COLS * sizeof(char));
        }

        strcpy(planeType1[0], "...*...");
        strcpy(planeType1[1], ".*****.");
        strcpy(planeType1[2], "...*...");
        strcpy(planeType1[3], "..***..");
        return planeType1;
    } else {
        char **planeType2 = (char **)malloc(PLANE_TYPE_2_ROWS * sizeof(char *));
        for (int i = 0; i < PLANE_TYPE_2_ROWS; i++) {
            planeType2[i] = (char *)malloc(PLANE_TYPE_2_COLS * sizeof(char));
        }
        strcpy(planeType2[0], "....*....");
        strcpy(planeType2[1], "...***...");
        strcpy(planeType2[2], ".*******.");
        strcpy(planeType2[3], "....*....");
        strcpy(planeType2[4], "..*****..");
        return planeType2;
    }
}

// Functie pentru obtinerea numarului de randuri ale unui avion in functie de tip si directie
int getPlaneRowsByTypeAndDirection(char type, char direction) {
    if (type == '1') {
        return (direction == 'N' || direction == 'S') ? PLANE_TYPE_1_ROWS : PLANE_TYPE_1_COLS;
    }
    return (direction == 'N' || direction == 'S') ? PLANE_TYPE_2_ROWS : PLANE_TYPE_2_COLS;
}

// Functie pentru obtinerea numarului de coloane ale unui avion in functie de tip si directie
int getPlaneColsByTypeAndDirection(char type, char direction) {
    if (type == '1') {
        return (direction == 'N' || direction == 'S') ? PLANE_TYPE_1_COLS : PLANE_TYPE_1_ROWS;
    }
    return (direction == 'N' || direction == 'S') ? PLANE_TYPE_2_COLS : PLANE_TYPE_2_ROWS;
}

// Functie pentru obtinerea coloanei de start a avionului in functie de coloana, tip si directie
int getStartingColumn(int column, char type, char direction) {
    switch (type) {
        case '1':
            switch (direction) {
                case 'N': case 'E': case 'S': return column - 3;
                case 'W': return column;
            }
        case '2':
            switch (direction) {
                case 'N': case 'E': case 'S': return column - 4;
                case 'W': return column;
            }
    }
    return -1; // Invalid case
}

// Functie pentru obtinerea randului de start a avionului in functie de rand, tip si directie
int getStartingRow(int row, char type, char direction) {
    switch (type) {
        case '1':
            switch (direction) {
                case 'N': return row;
                case 'E': case 'W': case 'S': return row - 3;
            }
        case '2':
            switch (direction) {
                case 'N': return row;
                case 'E': case 'W': case 'S': return row - 4;
            }
    }
    return -1; // Invalid case
}

// Functie pentru rotirea layout-ului avionului intr-o anumita directie
char **rotatePlaneToDirection(char **planeLayout, int *numRows, int *numCols, char direction) {
    char directions[] = {'N', 'E', 'S', 'W'};
    int numRotations = 0;

    for (int i = 0; directions[i] != '\0'; i++) {
        if (directions[i] == direction) {
            numRotations = i;
            break;
        }
    }

    for (int i = 0; i < numRotations; i++) {
        planeLayout = rotateMatrixClockwise(planeLayout, numRows, numCols);
    }

    return planeLayout;
}

void SolveTask2(void *info, int numPlanes, int matrixSize, char **matrix) {
    for (int i = 0; i < numPlanes; i++) {
        char **planeLayout = NULL;
        short planeRow = 0, planeCol = 0;
        char planeDirection = '\0', planeType = '\0';

        // Extrage informatiile despre avion din vectorul info
        memcpy(&planeRow, (info + i * SIZEOF_VECTOR), sizeof(planeRow));
        memcpy(&planeCol, (info + i * SIZEOF_VECTOR) + sizeof(planeRow), sizeof(planeCol));
        memcpy(&planeDirection, (info + i * SIZEOF_VECTOR) + sizeof(planeRow) + sizeof(planeCol), sizeof(planeDirection));
        memcpy(&planeType, (info + i * SIZEOF_VECTOR) + sizeof(planeRow) + sizeof(planeCol) + sizeof(planeDirection), sizeof(planeType));

        // Construieste layout-ul avionului
        planeLayout = buildPlaneLayout(planeType);
        int numRows = getPlaneRowsByTypeAndDirection(planeType, 'N');
        int numCols = getPlaneColsByTypeAndDirection(planeType, 'N');

        // Roteste layout-ul in directia specificata
        planeLayout = rotatePlaneToDirection(planeLayout, &numRows, &numCols, planeDirection);

        // Plaseaza avionul pe matricea mare in pozitia corecta
        for (int row = getStartingRow(planeRow, planeType, planeDirection), a = 0; a < numRows; row++, a++) {
            for (int col = getStartingColumn(planeCol, planeType, planeDirection), b = 0; b < numCols; col++, b++) {
                if (planeLayout[a][b] == '*') {
                    matrix[row][col] = planeLayout[a][b];
                }
            }
        }

        // Elibereaza memoria layout-ului avionului
        free_mat(planeLayout, numRows);
    }

    // Afiseaza matricea finala cu avioanele
    printMatrix(matrix, matrixSize, matrixSize);
}
