#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct proc {
    short pid;
    char prio;
    short time; 
} __attribute__((packed));

typedef struct avg {
    short quo;
    short remain;
} __attribute__((packed));

int tests_num, types_num;
float *type_score;

void sort_procs(struct proc *procs, int len);
void run_procs(struct proc* procs, int len, struct avg *avg_out);

void readConfig(char *filename)
{
    FILE *config = fopen(filename, "r");

    fscanf(config, "tests_num: %d\n", &tests_num);
    fscanf(config, "types: %d\n", &types_num);
    type_score = malloc(types_num * sizeof(float));

    char *test_string = malloc(40);

    for (int i = 0; i < types_num; i++) {
        sprintf(test_string, "type %d: ", i + 1);
        fscanf(config, strcat(test_string, "%f\n"), &type_score[i]);
    }
}

int readInput(char *filename, struct proc **procsArr)
{
    FILE *input = fopen(filename, "r");
    int len;

    /* read procs */
    fscanf(input, "%d\n", &len);
    *procsArr = malloc(len * sizeof(struct proc));
    for(int i = 0 ; i < len ; i++) {
        fscanf(input, "%hd %hhd %hd\n", &(*procsArr)[i].pid,
                                        &(*procsArr)[i].prio,
                                        &(*procsArr)[i].time);
    }
    fclose(input);

    return len;
}

void readRef(char *filename, int len, struct proc *ref_procs, struct avg *avg_ref)
{
    FILE *ref = fopen(filename, "r");

    for(int i = 0 ; i < len; i++) {
        fscanf(ref, "%hd %hhd %hd\n", &ref_procs[i].pid,
                                      &ref_procs[i].prio,
                                      &ref_procs[i].time);
    }

    for (int i = 0; i < 5; i++) {
        fscanf(ref, "%hd %hd\n", &avg_ref[i].quo, &avg_ref[i].remain);
    }
    fclose(ref);
}

void printOutput(char *filename, int len, struct proc *out_procs, struct avg *avg_out)
{
    FILE *output = fopen(filename, "w");

    for (int i = 0; i < len; i++) {
        fprintf(output, "%hd %hhd %hd\n", out_procs[i].pid,
                                          out_procs[i].prio,
                                          out_procs[i].time);
    }

    for (int i = 0; i < 5; i++) {
        fprintf(output, "%hd %hd\n", avg_out[i].quo, avg_out[i].remain);
    }
    
    fclose(output);
}

void printScore(float *sort_tests_score, float *run_tests_score)
{
    float score = 0.0;

    printf("-------------SORT TESTS-------------\n\n");
    for (int i = 0; i < tests_num; i++) {
        if (sort_tests_score[i]) {
            if (i + 1 < 10) {
                printf("Test %d..................PASSED: %.2fp\n", i + 1, sort_tests_score[i]);
            } else {
                printf("Test %d.................PASSED: %.2fp\n", i + 1, sort_tests_score[i]);
            }
            score += sort_tests_score[i];
        } else {
            if (i + 1 < 10) {
                printf("Test %d..................FAILED: %.2fp\n", i + 1, 0.0);
            } else {
                printf("Test %d.................FAILED: %.2fp\n", i + 1, 0.0);
            }
        }
    }
    printf("\n");

    printf("--------------RUN TESTS-------------\n\n");
    for (int i = 0; i < tests_num; i++) {
        if (run_tests_score[i]) {
            if (i + 1 < 10) {
                printf("Test %d..................PASSED: %.2fp\n", i + 1, run_tests_score[i]);
            } else {
                printf("Test %d.................PASSED: %.2fp\n", i + 1, run_tests_score[i]);
            }
            score += run_tests_score[i];
        } else {
            if (i + 1 < 10) {
                printf("Test %d..................FAILED: %.2fp\n", i + 1, 0.0);
            } else {
                printf("Test %d.................FAILED: %.2fp\n", i + 1, 0.0);
            }
        }
    }

    printf("\nTASK 2 SCORE: %.2f / 25.00\n", score);
}

int main(int argc, char **argv)
{
    int len = 0;
    float score = 0;

    readConfig(".config");
    float sort_tests_score[tests_num], run_tests_score[tests_num];

    struct proc *procs = NULL, *ref_procs = NULL;
    struct avg avg_out[5], avg_ref[5];
    char input_file[30], output_file[30], ref_file[30];

    printf("---------------TASK 2---------------\n\n");
    for (int i = 0; i < tests_num; i++) {
        for (int j = 0; j < 5; j++) {
            avg_out[j].quo = 0;
            avg_out[j].remain = 0;
        }

        /* read input */
        sprintf(input_file, "./input/procs_%d.in", i + 1);
        len = readInput(input_file, &procs);

        /* read ref */
        sprintf(ref_file, "./ref/procs_%d.ref", i + 1);
        ref_procs = malloc(len * sizeof(struct proc));
        readRef(ref_file, len, ref_procs, avg_ref);

        sort_procs(procs, len);
        run_procs(procs, len, avg_out);

        int sort_ok = 1, run_ok = 1;

        for (int j = 0; j < len; j++) {
            if (procs[j].pid != ref_procs[j].pid ||
                procs[j].prio != ref_procs[j].prio ||
                procs[j].time != ref_procs[j].time) {
                sort_ok = 0;
            }
        }

        sort_tests_score[i] = sort_ok ? type_score[0] : 0;

        for (int j = 0; j < 5; j++) {
            if (avg_out[j].quo != avg_ref[j].quo ||
                avg_out[j].remain != avg_ref[j].remain) {
                run_ok = 0;
            }
        }

        run_tests_score[i] = run_ok ? type_score[1] : 0;

        sprintf(output_file, "./output/procs_%d.out", i + 1);
        printOutput(output_file, len, procs, avg_out);
    }

    printScore(sort_tests_score, run_tests_score);

    return 0;
}