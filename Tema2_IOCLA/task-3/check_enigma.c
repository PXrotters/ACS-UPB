#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define UPPER_CHAR_TO_INT(c) (int)c - 65
#define RIGHT_SHIFT 1
#define LEFT_SHIFT 0

int len_plain;

void rotate_x_positions(int x, int rotor, char config[10][26], int forward);

void enigma(char *plain, char key[3], char notches[3], char config[10][26], char *enc);

void readInput(char *filename, char *plain, char *key, char config[10][26], char ovf[3], char offset[3]) {
    int i, j;
    FILE *f = fopen(filename, "r");

    fscanf(f, "%d", &len_plain);
    fgetc(f);
    fread(plain, sizeof(char), len_plain, f);
    fgetc(f);
    fread(key, sizeof(char), 3, f);
    fgetc(f);
    for (i = 0; i < 3; i++) {
        fscanf(f, "%c", &ovf[i]);
        fgetc(f);
        fscanf(f, "%c", &offset[i]);
        fgetc(f);
        for (j = 0; j < 26; j++) {
            fscanf(f, "%c", &config[2 * i + 0][j]);
            fgetc(f);
        }
        for (j = 0; j < 26; j++) {
            fscanf(f, "%c", &config[2 * i + 1][j]);
            fgetc(f);
        }
    }
    for (i; i < 5; i++) {
        for (j = 0; j < 26; j++) {
            fscanf(f, "%c", &config[2 * i + 0][j]);
            fgetc(f);
        }
        for (j = 0; j < 26; j++) {
            fscanf(f, "%c", &config[2 * i + 1][j]);
            fgetc(f);
        }
    }
    
    fclose(f);
}

void readRefA(char *filename, char ref_config[6][26]) {
    FILE *f = fopen(filename, "r");
    
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 26; j++) {
            fscanf(f, "%c", &ref_config[i][j]);
            fgetc(f);
        }
    }

    fclose(f);
}

void readRefB(char *filename, char *ref_string) {
    FILE *f = fopen(filename, "r");

    /* read the encrypted text */
    fscanf(f, "%s", ref_string);

    fclose(f);
}

void printOutputA(char *filename, char config[10][26]) {
    FILE *f = fopen(filename, "w");

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 26; j++) {
            fprintf(f, "%c ", config[i][j]);
        }
        fprintf(f, "\n");
    }

    fclose(f);
}

void printOutputB(char *filename, char *string) {
    FILE *f = fopen(filename, "w");

    fprintf(f, "%s", string);

    fclose(f);
}

int main(int argc, char **argv) {
    int i = 0, j = 0;
    float score = 0;
    char plain[10001];
    char key[3];
    char config[10][26];
    char ref_config[6][26];
    char ovf[3];
    char offset[3];
    char enc_string[10001];
    char ref_string[10001];
    char input_file[30], output_file[30], ref_file[30];

    printf("--------------TASK 3--------------\n");
    for (i = 0; i < 10; i++) {
        sprintf(input_file, "input/enigma-%d.in", i);
        readInput(input_file, plain, key, config, ovf, offset);

        for (j = 0; j < 3; j++) {
            rotate_x_positions(UPPER_CHAR_TO_INT(key[j]), j, config, LEFT_SHIFT);
        }

        for (j = 0; j < 3; j++) {
            rotate_x_positions(UPPER_CHAR_TO_INT(offset[j]), j, config, RIGHT_SHIFT);
        }

        memset(ref_string, 0, 10001);
        sprintf(ref_file, "ref/enigma-%d.ref", i);
        if (i < 2) {
            readRefA(ref_file, ref_config);
            sprintf(output_file, "output/enigma-%d.out", i);
            printOutputA(output_file, config);
            int correct = 1;
            for (int j = 0; j < 6 && correct; j++) {
                for (int k = 0; k < 26; k++) {
                    if (config[j][k] != ref_config[j][k]) {
                        printf("TEST %d..................FAILED: 0.00p\n", i);
                        correct = 0;
                        break;
                    }
                }
            }
            if (correct == 1) {
                score += 2.5;
                printf("TEST %d..................PASSED: 2.50p\n", i);
            }
        } else {
            readRefB(ref_file, ref_string);
            memset(enc_string, 0, 10001);
            enigma(plain, key, ovf, config, enc_string);

            sprintf(output_file, "output/enigma-%d.out", i);
            printOutputB(output_file, enc_string);

            if (strcmp(enc_string, ref_string)) {
                printf("TEST %d..................FAILED: 0.00p\n", i);
            } else {
                score += 2.5;
                printf("TEST %d..................PASSED: 2.50p\n", i);
            }
        }
    }
    printf("\nTASK 3 SCORE: %.2f / 25.00\n\n", score);

    return 0;
}