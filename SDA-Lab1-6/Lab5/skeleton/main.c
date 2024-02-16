/*
*	Created by Nan Mihai on 28.03.2021
*	Copyright (c) 2021 Nan Mihai. All rights reserved.
*	Laborator 5 - Structuri de date
*	Facultatea de Automatica si Calculatoare
*	Anul Universitar 2020-2021, Seria CD
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "tree.h"

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
float total_score = 0;

int test1[] = {9, 7, 5, 9, 4, 10, 6, 8, -8, 12};
int test2[] = {11, 9, 7, 25, 12, 29, 27, 8, 5, 1, 35, 26};
int test3[] = {26, 50, 150, 35, 175, 155, 100, 95, 9, 15, 45, 40, 4, 47, 98, \
	97, 99, 90, 200, 50, 68, 35, 39, 37, 44, 43, 46};

int checkBST(Tree node) { 
	if (node == NULL) 
		return 1;
	if (node->left != NULL && node->left->value > node->value)
		return 0; 
	if (node->right != NULL && node->right->value < node->value) 
		return 0; 
	if (!checkBST(node->left) || !checkBST(node->right)) 
		return 0; 
	return 1; 
}

void bst_print_dot_aux(Tree node, FILE* stream) {
    if (node->left) {
        fprintf(stream, "    %d -> %d;\n", node->value, node->left->value);
        bst_print_dot_aux(node->left, stream);
    }
    if (node->right) {
        fprintf(stream, "    %d -> %d;\n", node->value, node->right->value);
        bst_print_dot_aux(node->right, stream);
    }
}

void bst_print_dot(Tree tree, FILE* stream, int type) {
    fprintf(stream, "digraph BST {\n");
    if (type == 1)
    	fprintf(stream, "    node [fontname=\"Arial\", shape=circle, style=filled, fillcolor=green];\n");
    else
    	fprintf(stream, "    node [fontname=\"Arial\", shape=circle, style=filled, fillcolor=red];\n");
    if (!tree)
        fprintf(stream, "\n");
    else if (!tree->right && !tree->left)
        fprintf(stream, "    %d;\n", tree->value);
    else
        bst_print_dot_aux(tree, stream);
    fprintf(stream, "}\n");
}

static char *test_insert() {
	Tree tree = NULL;
	FILE *f;
	int i;

	for (i = 1; i <= test1[0]; i++) {
		tree = insert(tree, test1[i]);
	}
	f = fopen("test.dot", "w");
	bst_print_dot(tree, f, 1);
	fclose(f);
	system("dot test.dot | neato -n -Tpng -o out_tree1.png");
	sd_assert("Cerința 1 - Test1 insert picat", checkBST(tree) && tree != NULL);
	freeTree(&tree);

	tree = NULL;
	for (i = 1; i <= test2[0]; i++) {
		tree = insert(tree, test2[i]);
	}
	f = fopen("test.dot", "w");
	bst_print_dot(tree, f, 1);
	fclose(f);
	system("dot test.dot | neato -n -Tpng -o out_tree2.png");
	sd_assert("Cerința 1 - Test2 insert picat", checkBST(tree) && tree != NULL);
	freeTree(&tree);
	
	tree = NULL;
	for (i = 1; i <= test3[0]; i++) {
		tree = insert(tree, test3[i]);
	}
	f = fopen("test.dot", "w");
	bst_print_dot(tree, f, 1);
	fclose(f);
	system("dot test.dot | neato -n -Tpng -o out_tree3.png");
	sd_assert("Cerința 1 - Test3 insert picat", checkBST(tree) && tree != NULL);
	freeTree(&tree);
	printf("insert \t\t- Toate testele au trecut!\n");
	return 0;
}

static char *test_preorder() {
	printf("preorder \t- Testele sunt verificate manual!\n");
	Tree tree = NULL;
	int i;

	for (i = 1; i <= test1[0]; i++) {
		tree = insert(tree, test1[i]);
	}
	printf("\tpreorder \t- Testul 1: [7 5 4 -8 6 9 8 10 12]\n\t\t");
	printPreorder(tree);
	printf("\n");
	freeTree(&tree);

	tree = NULL;
	for (i = 1; i <= test2[0]; i++) {
		tree = insert(tree, test2[i]);
	}
	printf("\tpreorder \t- Testul 2: [9 7 5 1 8 25 12 29 27 26 35]\n\t\t");
	printPreorder(tree);
	printf("\n");
	freeTree(&tree);
	
	tree = NULL;
	for (i = 1; i <= test3[0]; i++) {
		tree = insert(tree, test3[i]);
	}
	printf("\tpreorder \t- Testul 3: [50 35 9 4 15 45 40 39 37 44 43 47 46 150 100 95 90 68 98 97 99 175 155 200]\n\t\t");
	printPreorder(tree);
	printf("\n");
	freeTree(&tree);
	return 0;
}

static char *test_postorder() {
	printf("postorder \t- Testele sunt verificate manual!\n");
	Tree tree = NULL;
	int i;

	for (i = 1; i <= test1[0]; i++) {
		tree = insert(tree, test1[i]);
	}
	printf("\tpostorder \t- Testul 1: [-8 4 6 5 8 12 10 9 7]\n\t\t");
	printPostorder(tree);
	printf("\n");
	freeTree(&tree);

	tree = NULL;
	for (i = 1; i <= test2[0]; i++) {
		tree = insert(tree, test2[i]);
	}
	printf("\tpostorder \t- Testul 2: [1 5 8 7 12 26 27 35 29 25 9]\n\t\t");
	printPostorder(tree);
	printf("\n");
	freeTree(&tree);
	
	tree = NULL;
	for (i = 1; i <= test3[0]; i++) {
		tree = insert(tree, test3[i]);
	}
	printf("\tpostorder \t- Testul 3: [4 15 9 37 39 43 44 40 46 47 45 35 68 90 97 99 98 95 100 155 200 175 150 50]\n\t\t");
	printPostorder(tree);
	printf("\n");
	freeTree(&tree);
	return 0;
}

static char *test_inorder() {
	printf("inorder \t- Testele sunt verificate manual!\n");
	Tree tree = NULL;
	int i;

	for (i = 1; i <= test1[0]; i++) {
		tree = insert(tree, test1[i]);
	}
	printf("\tinorder \t- Testul 1: [-8 4 5 6 7 8 9 10 12]\n\t\t");
	printInorder(tree);
	printf("\n");
	freeTree(&tree);

	tree = NULL;
	for (i = 1; i <= test2[0]; i++) {
		tree = insert(tree, test2[i]);
	}
	printf("\tinorder \t- Testul 2: [1 5 7 8 9 12 25 26 27 29 35]\n\t\t");
	printInorder(tree);
	printf("\n");
	freeTree(&tree);
	
	tree = NULL;
	for (i = 1; i <= test3[0]; i++) {
		tree = insert(tree, test3[i]);
	}
	printf("\tinorder \t- Testul 3: [4 9 15 35 37 39 40 43 44 45 46 47 50 68 90 95 97 98 99 100 150 155 175 200]\n\t\t");
	printInorder(tree);
	printf("\n");
	freeTree(&tree);
	return 0;
}

static char *test_maxDepth() {
	Tree tree = NULL;
	int i;

	for (i = 1; i <= test1[0]; i++) {
		tree = insert(tree, test1[i]);
	}
	sd_assert("Cerința 1 - Test1 maxDepth picat", maxDepth(tree) == 3);
	freeTree(&tree);

	tree = NULL;
	for (i = 1; i <= test2[0]; i++) {
		tree = insert(tree, test2[i]);
	}
	sd_assert("Cerința 1 - Test2 maxDepth picat", maxDepth(tree) == 4);
	freeTree(&tree);

	tree = NULL;
	for (i = 1; i <= test3[0]; i++) {
		tree = insert(tree, test3[i]);
	}
	sd_assert("Cerința 1 - Test3 maxDepth picat", maxDepth(tree) == 5);
	freeTree(&tree);
	printf("maxDepth \t- Toate testele au trecut!\n");
	return 0;
}

static char *test_size() {
	Tree tree = NULL;
	int i;

	for (i = 1; i <= test1[0]; i++) {
		tree = insert(tree, test1[i]);
	}
	sd_assert("Cerința 1 - Test1 size picat", size(tree) == test1[0]);
	freeTree(&tree);

	tree = NULL;
	for (i = 1; i <= test2[0]; i++) {
		tree = insert(tree, test2[i]);
	}
	sd_assert("Cerința 1 - Test2 size picat", size(tree) == test2[0]);
	freeTree(&tree);

	tree = NULL;
	for (i = 1; i <= test3[0]; i++) {
		tree = insert(tree, test3[i]);
	}
	sd_assert("Cerința 1 - Test3 size picat", size(tree) == test3[0] - 2);
	freeTree(&tree);
	printf("size \t\t- Toate testele au trecut!\n");

	return 0;
}

static char *test_free() {
	Tree tree = NULL;
	int i;

	for (i = 1; i <= test1[0]; i++) {
		tree = insert(tree, test1[i]);
	}
	freeTree(&tree);
	sd_assert("Cerința 1 - Test1 free picat", tree == NULL);
	

	tree = NULL;
	for (i = 1; i <= test2[0]; i++) {
		tree = insert(tree, test2[i]);
	}
	freeTree(&tree);
	sd_assert("Cerința 1 - Test2 free picat", tree == NULL);
	
	tree = NULL;
	for (i = 1; i <= test3[0]; i++) {
		tree = insert(tree, test3[i]);
	}
	freeTree(&tree);
	sd_assert("Cerința 1 - Test3 free picat", tree == NULL);
	printf("free \t\t- Testele sunt verificate manual!\n");

	return 0;
}

int areMirrorTrees(Tree root1, Tree root2) {
	if (root1 == NULL && root2 == NULL)
		return 1;
	if (root1 == NULL || root2 == NULL)
		return 0;
	if (root1->value != root2->value)
		return 1;
	int res1, res2;
	res1 = areMirrorTrees(root1->left, root2->right);
	res2 = areMirrorTrees(root2->right, root1->left);
	return res1 && res2;
}

static char *test_mirror() {
	Tree tree = NULL, result = NULL;
	int i;
	FILE *f;

	for (i = 1; i <= test1[0]; i++) {
		tree = insert(tree, test1[i]);
		result = insert(result, test1[i]);
	}
	mirror(tree);
	f = fopen("test.dot", "w");
	bst_print_dot(tree, f, 3);
	fclose(f);
	system("dot test.dot | neato -n -Tpng -o out_mirror1.png");
	sd_assert("Cerința 2 - Test1 mirror picat", tree != NULL && areMirrorTrees(tree, result));
	freeTree(&tree);
	freeTree(&result);

	tree = NULL;
	result = NULL;
	for (i = 1; i <= test2[0]; i++) {
		tree = insert(tree, test2[i]);
		result = insert(result, test2[i]);
	}
	mirror(tree);
	f = fopen("test.dot", "w");
	bst_print_dot(tree, f, 3);
	fclose(f);
	system("dot test.dot | neato -n -Tpng -o out_mirror2.png");
	sd_assert("Cerința 2 - Test2 mirror picat", tree != NULL && areMirrorTrees(tree, result));
	freeTree(&tree);
	freeTree(&result);

	tree = NULL;
	result = NULL;
	for (i = 1; i <= test3[0]; i++) {
		tree = insert(tree, test3[i]);
		result = insert(result, test3[i]);
	}
	mirror(tree);
	f = fopen("test.dot", "w");
	bst_print_dot(tree, f, 3);
	fclose(f);
	system("dot test.dot | neato -n -Tpng -o out_mirror3.png");
	sd_assert("Cerința 2 - Test3 mirror picat", tree != NULL && areMirrorTrees(tree, result));
	freeTree(&tree);
	freeTree(&result);
	printf("mirror \t\t- Toate testele au trecut!\n");

	return 0;
}

static char *test_sameTree() {
	Tree tree = NULL, result = NULL;
	int i;

	for (i = 1; i <= test1[0]; i++) {
		tree = insert(tree, test1[i]);
		result = insert(result, test1[i]);
	}
	sd_assert("Cerința 3 - Test1 sameTree picat", sameTree(tree, result));
	freeTree(&tree);
	freeTree(&result);

	tree = NULL;
	result = NULL;
	for (i = 1; i <= test2[0]; i++) {
		tree = insert(tree, test2[i]);
		result = insert(result, test2[i]);
	}
	sd_assert("Cerința 3 - Test2 sameTree picat", sameTree(tree, result));
	freeTree(&tree);
	freeTree(&result);

	tree = NULL;
	result = NULL;
	for (i = 1; i <= test3[0]; i++) {
		tree = insert(tree, test3[i]);
		result = insert(result, test3[i]);
	}
	sd_assert("Cerința 3 - Test3 sameTree picat", sameTree(tree, result));
	freeTree(&tree);
	freeTree(&result);
	printf("sameTree \t- Toate testele au trecut!\n");

	return 0;
}

static char *all_tests() {
	sd_run_test(test_insert, 1.5);
	sd_run_test(test_postorder, 0.75);
	sd_run_test(test_preorder, 0.75);
	sd_run_test(test_inorder, 0.75);
	sd_run_test(test_free, 0.75);
	sd_run_test(test_size, 0.75);
	sd_run_test(test_maxDepth, 0.75);
	sd_run_test(test_mirror, 2);
	sd_run_test(test_sameTree, 2);
	return 0;
}

static char *selective_tests(int argc, char **argv) {
	int i;
	int viz[10] = {0};
	for (i = 1; i < argc; i++) {
		if (viz[atoi(argv[i])]) {
			continue;
		}
		if (!strcmp(argv[i], "1")) {
			viz[1] = 1;
			sd_run_test(test_insert, 1.5);
		} else if (!strcmp(argv[i], "2")) {
			viz[2] = 1;
			sd_run_test(test_postorder, 0.75);
		} else if (!strcmp(argv[i], "3")) {
			viz[3] = 1;
			sd_run_test(test_preorder, 0.75);
		} else if (!strcmp(argv[i], "4")) {
			viz[4] = 1;
			sd_run_test(test_inorder, 0.75);
		} else if (!strcmp(argv[i], "5")) {
			viz[5] = 1;
			sd_run_test(test_free, 0.75);
		} else if (!strcmp(argv[i], "6")) {
			viz[6] = 1;
			sd_run_test(test_size, 0.75);
		} else if (!strcmp(argv[i], "7")) {
			viz[7] = 1;
			sd_run_test(test_maxDepth, 0.75);
		} else if (!strcmp(argv[i], "8")) {
			viz[8] = 1;
			sd_run_test(test_mirror, 2);
		} else if (!strcmp(argv[i], "9")) {
			viz[9] = 1;
			sd_run_test(test_sameTree, 2);
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
