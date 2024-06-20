#include "./utils.h"

#define SIZEOF_INFO 4*sizeof(unsigned char) + sizeof(unsigned int)

// Functie pentru marcarea obstacolelor pe harta
void markObstacles(char **matrix, int *obstacleX, int *obstacleY, int nr_obstacles) {
    for (int i = 0; i < nr_obstacles; i++) {
        matrix[obstacleX[i]][obstacleY[i]] = '@';
    }
}

// Functie pentru verificarea daca o pozitie (row, col) este sigura (nu este marcata cu '@' si este in interiorul matricei de dimensiune N x N)
int isSafe(char **matrix, int row, int col, int N) {
    return row >= 0 && row < N && col >= 0 && col < N && matrix[row][col] != '@';
}

// Functie pentru verificarea sigurantei avionului in functie de directie si tip
int checkSafety(char **matrix, int x, int y, unsigned char direction, unsigned char type, int N) {
    int search = 1;
    int row = 0, col = 0;

    if (type == '1') {
        if (direction == 'N') {
            for (row = x + 3; row >= x + 2 && search; row--) {
                for (col = y - 1; col <= y + 1 && search; col++) {
                    if (!isSafe(matrix, row, col, N)) search = 0;
                }
            }
            for (row = x + 1; row >= 0 && search; row--) {
                for (col = y - 2; col <= y + 2 && search; col++) {
                    if (!isSafe(matrix, row, col, N)) search = 0;
                }
            }
        } else if (direction == 'S') {
            for (row = x - 3; row <= x - 2 && search; row++) {
                for (col = y - 1; col <= y + 1 && search; col++) {
                    if (!isSafe(matrix, row, col, N)) search = 0;
                }
            }
            for (row = x - 1; row < N && search; row++) {
                for (col = y - 2; col <= y + 2 && search; col++) {
                    if (!isSafe(matrix, row, col, N)) search = 0;
                }
            }
        } else if (direction == 'E') {
            for (col = y - 3; col <= y - 2 && search; col++) {
                for (row = x - 1; row <= x + 1 && search; row++) {
                    if (!isSafe(matrix, row, col, N)) search = 0;
                }
            }
            for (col = y - 1; col < N && search; col++) {
                for (row = x - 2; row <= x + 2 && search; row++) {
                    if (!isSafe(matrix, row, col, N)) search = 0;
                }
            }
        } else { // direction == 'W'
            for (col = y + 3; col >= y + 2 && search; col--) {
                for (row = x - 1; row <= x + 1 && search; row++) {
                    if (!isSafe(matrix, row, col, N)) search = 0;
                }
            }
            for (col = y + 1; col >= 0 && search; col--) {
                for (row = x - 2; row <= x + 2 && search; row++) {
                    if (!isSafe(matrix, row, col, N)) search = 0;
                }
            }
        }
    } else {
        if (direction == 'N') {
            for (row = x + 4; row >= x + 3 && search; row--) {
                for (col = y - 2; col <= y + 2 && search; col++) {
                    if (!isSafe(matrix, row, col, N)) search = 0;
                }
            }
            for (row = x + 2; row >= 0 && search; row--) {
                for (col = y - 3; col <= y + 3 && search; col++) {
                    if (!isSafe(matrix, row, col, N)) search = 0;
                }
            }
        } else if (direction == 'S') {
            for (row = x - 4; row <= x - 3 && search; row++) {
                for (col = y - 2; col <= y + 2 && search; col++) {
                    if (!isSafe(matrix, row, col, N)) search = 0;
                }
            }
            for (row = x - 2; row < N && search; row++) {
                for (col = y - 3; col <= y + 3 && search; col++) {
                    if (!isSafe(matrix, row, col, N)) search = 0;
                }
            }
        } else if (direction == 'E') {
            for (col = y - 4; col <= y - 3 && search; col++) {
                for (row = x - 2; row <= x + 2 && search; row++) {
                    if (!isSafe(matrix, row, col, N)) search = 0;
                }
            }
            for (col = y - 2; col < N && search; col++) {
                for (row = x - 3; row <= x + 3 && search; row++) {
                    if (!isSafe(matrix, row, col, N)) search = 0;
                }
            }
        } else { // direction == 'W'
            for (col = y + 4; col >= y + 3 && search; col--) {
                for (row = x - 2; row <= x + 2 && search; row++) {
                    if (!isSafe(matrix, row, col, N)) search = 0;
                }
            }
            for (col = y + 2; col >= 0 && search; col--) {
                for (row = x - 3; row <= x + 3 && search; row++) {
                    if (!isSafe(matrix, row, col, N)) search = 0;
                }
            }
        }
    }

    return search;
}

void SolveTask4(void *info, int nr_avioane, int nr_obstacles, int *X, int *Y, int N) {
    char **matrix = init_mat(N);
    markObstacles(matrix, X, Y, nr_obstacles);

    void *idx = info;
    int safeCount = 0;

    for (int count = 1; count <= nr_avioane; count++) {
        unsigned short x = *((unsigned short *)idx);
        idx += sizeof(unsigned short);
        unsigned short y = *((unsigned short *)idx);
        idx += sizeof(unsigned short);
        unsigned char direction = *((unsigned char *)idx);
        idx += sizeof(unsigned char);
        unsigned char type = *((unsigned char *)idx);

        if (checkSafety(matrix, x, y, direction, type, N)) {
            safeCount++;
        }

        idx += SIZEOF_INFO;
    }

    printf("%i\n", safeCount);
    free_mat(matrix, N);
}
