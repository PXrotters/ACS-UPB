/*
*	Created by Nan Mihai on 08.03.2021
*	Copyright (c) 2021 Nan Mihai. All rights reserved.
*	Laborator 2 - Structuri de date
*	Facultatea de Automatica si Calculatoare
*	Anul Universitar 2020-2021, Seria CD
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef int T;
#include "SortedList.h"

#define sd_assert(message, test) \
	do { \
		if (!(test)) \
			return message; \
	} while (0)

#define sd_run_test(test, score) \
	do { \
		char *message = test(); \
		tests_run++; \
		if (message) \
			return message; \
		else { \
			total_score += score; \
			printf("\tPuncte: %.2lf\n", 1.0 * score); \
		} \
	} while (0)

int tests_run = 0;
float total_score = 0;

int check(TSortedList l, int *vector, int size) {
	if(l == NULL && size == 0) {
		return 1;
	} else {
		int i = 0;
		while(l != NULL && i < size) {
			if(l->value != vector[i++]) {
				printf("1) %d si 2) %d\n", l->value, vector[i-1]);
				return 0;
			}
			l = l->next;
		}
		if(l == NULL && i == size) {
			return 1;
		} else {
			return 0;
		}
	}
}

static char *test_create() {
	int *v, size;
	size = 1;
	v = (int*) malloc(size*sizeof(int));
	v[0] = 5;
	TSortedList l = NULL;
	l = create(5);
	sd_assert("create - Test 1 picat", check(l, v, size));
	if(l != NULL) {
		free(l);
	}
	l = create(10);
	v[0] = 10;
	sd_assert("create - Test 2 picat", check(l, v, size));
	if(l != NULL) {
		free(l);
	}
	free(v);
	printf("create \t\t- Toate testele au trecut!");
	return 0;
}

static char *test_isEmpty() {
	int size = 1, *v;
	TSortedList l = NULL;
	sd_assert("isEmpty - Test 1 picat", isEmpty(l));
	l = create(10);
	v = malloc(sizeof(int));
	v[0] = 10;
	sd_assert("isEmpty - Test 2 picat", check(l, v, size));
	if(l != NULL) {
		free(l);
	}
	free(v);
	printf("isEmpty \t- Toate testele au trecut!");
	return 0;
}

int cmp(const void *a, const void *b) {
	int pa, pb;
	pa = *(int*) a;
	pb = *(int*) b;
	return pa - pb;
}

static char *test_insert() {
	int *v, size, i;
	TSortedList l = NULL;
	size = 5;
	v = (int*) malloc(size*sizeof(int));
	for(i = 0; i < size; i++) {
		v[i] = rand() % 100;
		l = insert(l, v[i]);
	}
	qsort(v, size, sizeof(int), cmp);
	sd_assert("insert - Test 1 picat", check(l, v, size));
	if(l != NULL) {
		l = freeTSortedList(l);
	}
	free(v);
	l = NULL;
	size = 15;
	v = (int*) malloc(size*sizeof(int));
	for(i = 0; i < size; i++) {
		v[i] = rand() % 100;
		l = insert(l, v[i]);
	}
	qsort(v, size, sizeof(int), cmp);
	sd_assert("insert - Test 2 picat", check(l, v, size));
	if(l != NULL) {
		l = freeTSortedList(l);
	}
	free(v);
	l = NULL;
	size = 50;
	v = (int*) malloc(size*sizeof(int));
	for(i = 0; i < size; i++) {
		v[i] = rand() % 100;
		l = insert(l, v[i]);
	}
	qsort(v, size, sizeof(int), cmp);
	sd_assert("insert - Test 3 picat", check(l, v, size));
	if(l != NULL) {
		l = freeTSortedList(l);
	}
	free(v);
	printf("insert \t\t- Toate testele au trecut!");
	return 0;
}

static char *test_contains() {
	int *v, size, i;
	TSortedList l = NULL;
	size = 5;
	v = (int*) malloc(size*sizeof(int));
	for(i = 0; i < size; i++) {
		v[i] = rand() % 100;
		l = insert(l, v[i]);
	}
	qsort(v, size, sizeof(int), cmp);
	sd_assert("contains - Test 1 picat", check(l, v, size) && contains(l, v[1]));
	if(l != NULL) {
		l = freeTSortedList(l);
	}
	free(v);
	l = NULL;
	size = 15;
	v = (int*) malloc(size*sizeof(int));
	for(i = 0; i < size; i++) {
		v[i] = rand() % 100;
		l = insert(l, v[i]);
	}
	qsort(v, size, sizeof(int), cmp);
	sd_assert("contains - Test 2 picat", check(l, v, size) && !contains(l, -100));
	if(l != NULL) {
		l = freeTSortedList(l);
	}
	free(v);
	l = NULL;
	size = 50;
	v = (int*) malloc(size*sizeof(int));
	for(i = 0; i < size; i++) {
		v[i] = rand() % 100;
		l = insert(l, v[i]);
	}
	qsort(v, size, sizeof(int), cmp);
	sd_assert("contains - Test 3 picat", check(l, v, size) && contains(l, v[22]));
	if(l != NULL) {
		l = freeTSortedList(l);
	}
	free(v);
	printf("contains \t- Toate testele au trecut!");
	return 0;
}

static char *test_deleteOnce() {
	int *v, size, i, x;
	TSortedList l = NULL;
	size = 5;
	v = (int*) malloc(size*sizeof(int));
	for(i = 0; i < size; i++) {
		v[i] = rand() % 100;
		l = insert(l, v[i]);
	}
	x = rand() % 100;
	l = insert(l, x);
	l = deleteOnce(l, x);
	qsort(v, size, sizeof(int), cmp);
	sd_assert("deleteOnce - Test 1 picat", check(l, v, size));
	if(l != NULL) {
		l = freeTSortedList(l);
	}
	free(v);
	l = NULL;
	size = 15;
	v = (int*) malloc(size*sizeof(int));
	for(i = 0; i < size; i++) {
		v[i] = rand() % 100;
		l = insert(l, v[i]);
	}
	x = rand() % 100;
	l = insert(l, x);
	l = insert(l, x);
	l = deleteOnce(l, x);
	l = deleteOnce(l, x);
	qsort(v, size, sizeof(int), cmp);
	sd_assert("deleteOnce - Test 2 picat", check(l, v, size));
	if(l != NULL) {
		l = freeTSortedList(l);
	}
	free(v);
	l = NULL;
	size = 50;
	v = (int*) malloc(size*sizeof(int));
	for(i = 0; i < size; i++) {
		v[i] = rand() % 100;
		l = insert(l, v[i]);
		x = rand() % 1000;
		l = insert(l, x);
		l = deleteOnce(l, x);
	}
	qsort(v, size, sizeof(int), cmp);
	sd_assert("deleteOnce - Test 3 picat", check(l, v, size));
	if(l != NULL) {
		l = freeTSortedList(l);
	}
	free(v);
	printf("deleteOnce \t- Toate testele au trecut!");
	return 0;
}

static char *test_length() {
	int size, i, x;
	TSortedList l = NULL;
	size = 5;
	for(i = 0; i < size; i++) {
		l = insert(l, rand() % 100);
	}
	sd_assert("length - Test 1 picat", length(l) == size);
	if(l != NULL) {
		l = freeTSortedList(l);
	}

	l = NULL;
	size = 15;
	for(i = 0; i < size; i++) {
		l = insert(l, rand() % 1000);
	}
	sd_assert("length - Test 2 picat", length(l) == size);
	if(l != NULL) {
		l = freeTSortedList(l);
	}
	l = NULL;
	size = 50;
	for(i = 0; i < size; i++) {
		x = rand() % 1000;
		l = insert(l, x);
	}
	l = deleteOnce(l, x);
	sd_assert("length - Test 3 picat", length(l) == size - 1);
	if(l != NULL) {
		l = freeTSortedList(l);
	}
	printf("length \t\t- Toate testele au trecut!");
	return 0;
}

static char *test_getNth() {
	int *v, size, i;
	TSortedList l = NULL;
	size = 5;
	v = (int*) malloc(size*sizeof(int));
	for(i = 0; i < size; i++) {
		v[i] = rand() % 100;
		l = insert(l, v[i]);
	}
	qsort(v, size, sizeof(int), cmp);
	sd_assert("getNth - Test 1 picat", getNth(l, 1) == v[0] && getNth(l, size) == v[size-1]);
	if(l != NULL) {
		l = freeTSortedList(l);
	}
	free(v);
	l = NULL;
	size = 15;
	v = (int*) malloc(size*sizeof(int));
	for(i = 0; i < size; i++) {
		v[i] = rand() % 100;
		l = insert(l, v[i]);
	}
	qsort(v, size, sizeof(int), cmp);
	sd_assert("getNth - Test 2 picat", getNth(l, 3) == v[2] && getNth(l, size - 1) == v[size-2]);
	if(l != NULL) {
		l = freeTSortedList(l);
	}
	free(v);
	l = NULL;
	size = 50;
	v = (int*) malloc(size*sizeof(int));
	for(i = 0; i < size; i++) {
		v[i] = rand() % 100;
		l = insert(l, v[i]);
	}
	qsort(v, size, sizeof(int), cmp);
	sd_assert("getNth - Test 3 picat", getNth(l, 6) == v[5] && getNth(l, size-9) == v[size-10]);
	if(l != NULL) {
		l = freeTSortedList(l);
	}
	free(v);
	printf("getNth \t\t- Toate testele au trecut!");
	return 0;
}


static char *all_tests() {
	sd_run_test(test_create, 0.25);
	sd_run_test(test_isEmpty, 0.25);
	sd_run_test(test_insert, 2);
	sd_run_test(test_length, 0.5);
	sd_run_test(test_contains, 0.5);
	sd_run_test(test_deleteOnce, 2);
	sd_run_test(test_getNth, 0.5);
	return 0;
}

static char *selective_tests(int argc, char **argv) {
	int i;
	int viz[8] = {0};
	for (i = 1; i < argc; i++) {
		if (viz[atoi(argv[i])]) {
			continue;
		}
		if (!strcmp(argv[i], "1")) {
			viz[1] = 1;
			sd_run_test(test_create, 0.25);
		} else if (!strcmp(argv[i], "2")) {
			viz[2] = 1;
			sd_run_test(test_isEmpty, 0.25);
		} else if (!strcmp(argv[i], "3")) {
			viz[3] = 1;
			sd_run_test(test_insert, 2);
		} else if (!strcmp(argv[i], "4")) {
			viz[4] = 1;
			sd_run_test(test_length, 0.5);
		} else if (!strcmp(argv[i], "5")) {
			viz[5] = 1;
			sd_run_test(test_contains, 0.5);
		} else if (!strcmp(argv[i], "6")) {
			viz[6] = 1;
			sd_run_test(test_deleteOnce, 2);
		} else if (!strcmp(argv[i], "7")) {
			viz[7] = 1;
			sd_run_test(test_getNth, 0.5);
		}
	}
	return 0;
}

int main(int argc, char **argv) {
	srand(time(NULL));
	char *result;
	if (argc == 1) {
		result = all_tests();
		if (result != 0) {
			printf("%s\n", result);
		} else {
			printf("*Programul se va verifica cu valgrind!*\t\tPuncte: 1.00\n");
			printf("Toate testele au trecut! Felicitari!\n");
		}
	} else {
		result = selective_tests(argc, argv);
		if (result != 0) {
			printf("%s\n", result);
		} else {
			printf("Toate testele selectate au trecut!\n");
		}
	}
	printf("Punctajul obtinut este: %.2lf\n", total_score);
	printf("Teste rulate: %d\n", tests_run);
	return result != 0;
}
