#include <stdio.h>
#include <string.h>

void bonus(int x, int y, int board[2]);

void readRef(char *filename, char matrix[8][8]) {
    FILE *fp;
    int i, j;
    int tmp;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    for (i = 7; i >= 0; i--) {
        for (j = 0; j < 8; j++) {
            fscanf(fp, "%d", &tmp);
            if(tmp == 0)
                matrix[i][j] = 0;
            else
                matrix[i][j] = 1;
        }
    }

    fclose(fp);
}

void readInput(char *filename, int *x, int *y) {
    FILE *fp;
    int i, j;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    fscanf(fp, "%d", x);
    fscanf(fp, "%d", y);

    fclose(fp);
}

void printOutput(char *filename, int board[2]) {
    FILE *f = fopen(filename, "w");
    unsigned long long bitboard = ((unsigned long long) board[0] << 32) | (unsigned long long) board[1];

    for (int row = 7; row >= 0; row--) {
        for (int col = 0; col < 8; col++) {

            if (bitboard & (1ULL << (row*8 + col))) {
                fprintf(f, "%d ", 1);
            } else {
                fprintf(f, "%d ", 0);
            }
        }
        fprintf(f, "\n");
    }

    fclose(f);
}

int check_board(int board[2], char ref[8][8]) {
    int i, j;
    unsigned long long bitboard = ((unsigned long long) board[0] << 32) | (unsigned long long) board[1];

    for (int row = 7; row >= 0; row--) {
        for (int col = 0; col < 8; col++) {

            unsigned long long tmp = bitboard & (1ULL << (row*8 + col));

            if ((ref[row][col] == 1 && tmp == 0) || ref[row][col] == 0 && tmp != 0) {
                return 0;
            }
        }
    }

    return 1;
}

int main() {
    int i, j, z;
    char tmp[8][8];
    int board[2];
    int x, y;
    char ref_file[30];
    char input_file[30];
    char output_file[30];
    float score = 0;

    printf("--------------BONUS--------------\n");
    for(i = 1; i <= 15; i++) {
        
        memset(board, 0, sizeof(board));

        sprintf(ref_file, "ref/%d.txt", i);
        readRef(ref_file, tmp);

        sprintf(input_file, "input/%d.txt", i);
        readInput(input_file, &x, &y);

        bonus(x, y, board);

        sprintf(output_file, "output/%d.txt", i);
        printOutput(output_file, board);

        if(check_board(board, tmp) == 0) {
            printf("TEST %d..................FAILED: 0.00p\n", i);
        } else {
            score += 1.33;
            printf("TEST %d..................PASSED: 1.33p\n", i);
        }

    }
    
    if(score >= 19.95)
        score = 20.00;
    printf("\nBONUS SCORE: %.2f / 20.00\n\n", score);

    return 0;
}