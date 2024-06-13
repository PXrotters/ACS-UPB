/*
*	Created by Nan Mihai on 11.04.2023
*	Copyright (c) 2023 Nan Mihai. All rights reserved.
*	Laborator 7 - Structuri de date și algoritmi
*	Facultatea de Automatica si Calculatoare
*	Anul Universitar 2022-2023, Seria CD
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "avl.h"

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
		else \
			total_score += score; \
	} while (0)

int tests_run = 0;
float total_score = 0.0;

int test1[] = {10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
int test2[] = {22, 10, 12, 5, 90, 80, 70, 60, 50, 40, 41, 42, 43, 44, 45, 46, 47, 38, 37, 36, 35, 34, 33};
int test3[] = {10, 100, 90, 80, 70, 60, 50, 40, 30, 20, 10};

#define SIZE 	100

int abs(int x) {
	if (x >= 0)
		return x;
	return -x;
}

int isBalanced(Tree root) {
	if (root == NULL)
		return 1;
	int left, right;
	if (root->left)
		left = root->left->height;
	else
		left = 0;

	if (root->right)
		right = root->right->height;
	else
		right = 0;

	if (abs(left - right) <= 1)
		return isBalanced(root->left) && isBalanced(root->right);
	return 0;
}

int rec_height(Tree root) {
	if (root == NULL || (root->left == NULL && root->right == NULL))
		return 0;
	int left, right;
	left = rec_height(root->left);
	right = rec_height(root->right);
	if (left < right)
		return right + 1;
	return left + 1;
}

int checkHeight(Tree root) {
	if (root == NULL)
		return 1;
	if (root->height == rec_height(root))
		return checkHeight(root->left) && checkHeight(root->right);
	return 0;
}

int contains(Tree root, int value) {
	if (root == NULL)
		return 0;
	if (root->value == value)
		return 1;
	if (value < root->value)
		return contains(root->left, value);
	return contains(root->right, value);
}

void avl_print_dot_aux(Tree node, FILE* stream) {
    static int nullcount = 0;

    if (node->left) {
        fprintf(stream, "    %d -> %d;\n", node->value, node->left->value);
        avl_print_dot_aux(node->left, stream);
    }
    if (node->right) {
        fprintf(stream, "    %d -> %d;\n", node->value, node->right->value);
        avl_print_dot_aux(node->right, stream);
    }
}

void avl_print_dot(Tree tree, FILE* stream, int type) {
    fprintf(stream, "digraph BST {\n");
    if (type == 1)
    	fprintf(stream, "    node [fontname=\"Arial\", shape=circle, style=filled, fillcolor=green];\n");
    else
    	fprintf(stream, "    node [fontname=\"Arial\", shape=circle, style=filled, fillcolor=blue];\n");
    if (!tree)
        fprintf(stream, "\n");
    else if (!tree->right && !tree->left)
        fprintf(stream, "    %d;\n", tree->value);
    else
        avl_print_dot_aux(tree, stream);
    fprintf(stream, "}\n");
}

void avl_draw(Tree tree, char *filename) {
	FILE *f = fopen("test.dot", "w");
	char buffer[SIZE];
	avl_print_dot(tree, f, 1);
	fclose(f);
	sprintf(buffer, "dot test.dot | neato -n -Tpng -o %s", filename);
	system(buffer);
}

static char *test_rightRotation() {
	Tree root = createTree(8);
	sd_assert("Cerința3 - Test0 rightRotation picat", root != NULL);
	root->left = createTree(5);
	root->left->left = createTree(4);
	avl_draw(root, "rightRotation_test1_before.png");
	root = rightRotation(root);
	avl_draw(root, "rightRotation_test1_after.png");
	sd_assert("Cerința3 - Test1 rightRotation picat", root != NULL && root->value == 5);
	root = freeTree(root);

	root = createTree(20);
	root->left = createTree(15);
	root->left->left = createTree(14);
	root->left->left->left = createTree(13);
	root->left->left->left->left = createTree(10);
	avl_draw(root, "rightRotation_test2_before.png");
	root = rightRotation(root);
	avl_draw(root, "rightRotation_test2_after.png");
	sd_assert("Cerința3 - Test2 rightRotation picat", root != NULL && root->value == 15);
	
	avl_draw(root, "rightRotation_test3_after.png");
	root = rightRotation(root);
	avl_draw(root, "rightRotation_test3_after.png");
	sd_assert("Cerința3 - Test3 rightRotation picat", root != NULL && root->value == 14 && 
													   root->left != NULL && root->left->value == 13 &&
													   root->right != NULL && root->right->value == 15);
	root = freeTree(root);
	return 0;
}

static char *test_leftRotation() {
	Tree root = createTree(8);
	sd_assert("Cerința3 - Test0 leftRotation picat", root != NULL);
	root->right = createTree(10);
	root->right->right = createTree(12);
	avl_draw(root, "leftRotation_test1_before.png");
	root = leftRotation(root);
	avl_draw(root, "leftRotation_test1_after.png");
	sd_assert("Cerința3 - Test1 leftRotation picat", root != NULL && root->value == 10);
	root = freeTree(root);


	root = createTree(20);
	root->right = createTree(25);
	root->right->right = createTree(30);
	root->right->right->right = createTree(50);
	root->right->right->right->right = createTree(100);
	avl_draw(root, "leftRotation_test2_before.png");
	root = leftRotation(root);
	avl_draw(root, "leftRotation_test2_after.png");
	sd_assert("Cerința3 - Test2 leftRotation picat", root != NULL && root->value == 25);
	
	avl_draw(root, "leftRotation_test3_after.png");
	root = leftRotation(root);
	avl_draw(root, "leftRotation_test3_after.png");
	sd_assert("Cerința3 - Test3 leftRotation picat", root != NULL && root->value == 30 && 
													   root->left != NULL && root->left->value == 25 &&
													   root->right != NULL && root->right->value == 50);
	root = freeTree(root);
	return 0;
}

static char *test_insert() {
	Tree tree = NULL, pred;
	int i;

	int found = 1;
	for (i = 1; i <= test1[0]; i++) {
		tree = insert(tree, test1[i]);
		if (!contains(tree, test1[i]))
			found = 0;
	}
	avl_draw(tree, "avl_test1.png");
	sd_assert("Cerința3 - Test1 insert picat", found && tree != NULL && checkHeight(tree) && isBalanced(tree));
	tree = freeTree(tree);
	
	tree = NULL;
	found = 1;
	for (i = 1; i <= test2[0]; i++) {
		tree = insert(tree, test2[i]);
		if (!contains(tree, test2[i]))
			found = 0;
	}
	avl_draw(tree, "avl_test2.png");
	sd_assert("Cerința3 - Test2 insert picat", found && tree != NULL && checkHeight(tree) && isBalanced(tree));
	tree = freeTree(tree);


	tree = NULL;
	found = 1;
	for (i = 1; i <= test3[0]; i++) {
		tree = insert(tree, test3[i]);
		if (!contains(tree, test3[i]))
			found = 0;
	}
	avl_draw(tree, "avl_test3.png");
	sd_assert("Cerința3 - Test3 insert picat", found && tree != NULL && checkHeight(tree) && isBalanced(tree));
	tree = freeTree(tree);

	return 0;
}

static char *test_delete() {
	Tree tree = NULL, pred;
	int i;
	int found = 1;
	for (i = 1; i <= test1[0]; i++) {
		tree = insert(tree, test1[i]);
		if (!contains(tree, test1[i]))
			found = 0;
	}
	avl_draw(tree, "avl_delete1_before.png");
	tree = delete(tree, 6);
	avl_draw(tree, "avl_delete1_after.png");
	sd_assert("Cerința4 - Test1 delete picat", found && tree != NULL && !contains(tree, 6) && checkHeight(tree) && isBalanced(tree));
	tree = freeTree(tree);
	
	tree = NULL;
	found = 1;
	for (i = 1; i <= test2[0]; i++) {
		tree = insert(tree, test2[i]);
		if (!contains(tree, test2[i]))
			found = 0;
	}
	avl_draw(tree, "avl_delete2_before.png");
	tree = delete(tree, 36);
	avl_draw(tree, "avl_delete2_after.png");
	sd_assert("Cerința4 - Test2 delete picat", found && tree != NULL && !contains(tree, 36) && checkHeight(tree) && isBalanced(tree));
	tree = freeTree(tree);


	tree = NULL;
	found = 1;
	for (i = 1; i <= test3[0]; i++) {
		tree = insert(tree, test3[i]);
		if (!contains(tree, test3[i]))
			found = 0;
	}
	avl_draw(tree, "avl_delete3_before.png");
	tree = delete(tree, 80);
	avl_draw(tree, "avl_delete3_after.png");
	sd_assert("Cerința4 - Test3 delete picat", found && tree != NULL && !contains(tree, 80) && checkHeight(tree) && isBalanced(tree));
	tree = freeTree(tree);

	return 0;
}

static char *all_tests() {
	sd_run_test(test_leftRotation, 1);
	sd_run_test(test_rightRotation, 1);
	sd_run_test(test_insert, 4);
	sd_run_test(test_delete, 4);
	return 0;
}

static char *selective_tests(int argc, char **argv) {
	int i;
	int viz[4] = {0};
	for (i = 1; i < argc; i++) {
		if (viz[atoi(argv[i])]) {
			continue;
		}
		if (!strcmp(argv[i], "1")) {
			viz[1] = 1;
			sd_run_test(test_leftRotation, 2.5);
		} else if (!strcmp(argv[i], "2")) {
			viz[2] = 1;
			sd_run_test(test_rightRotation, 2.5);
		} else if (!strcmp(argv[i], "3")) {
			viz[3] = 1;
			sd_run_test(test_insert, 4);
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