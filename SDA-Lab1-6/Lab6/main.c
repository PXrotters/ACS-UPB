/*
*	Created by Nan Mihai on 05.05.2021
*	Copyright (c) 2020 Nan Mihai. All rights reserved.
*	Laborator 6 - Structuri de date
*	Grupa 314CD
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
float total_score = 1;

int test1[] = {9, 7, 5, 9, 4, 10, 6, 8, -8, 12};
int test2[] = {11, 9, 7, 25, 12, 29, 27, 8, 5, 1, 35, 26};
int test3[] = {26, 50, 150, 35, 175, 155, 100, 95, 9, 15, 45, 40, 4, 47, 98, \
	97, 99, 90, 200, 50, 68, 35, 39, 37, 44, 43, 46};

int height(Tree root) {
	if (root == NULL)
		return 0;
	int left = height(root->left);
	int right = height(root->right);
	if (left > right)
		return left + 1;
	return right + 1;
}

int checkBST(Tree node) { 
	if (node == NULL) 
		return 1;
	if (node->left != NULL && node->left->value > node->value && node->left->parent != node)
		return 0; 
	if (node->right != NULL && node->right->value < node->value && node->right->parent != node) 
		return 0; 
	if (!checkBST(node->left) || !checkBST(node->right)) 
		return 0; 
	return 1; 
}

void bst_print_dot_aux(Tree node, FILE* stream) {
    static int nullcount = 0;

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
    	fprintf(stream, "    node [fontname=\"Arial\", shape=circle, style=filled, fillcolor=blue];\n");
    if (!tree)
        fprintf(stream, "\n");
    else if (!tree->right && !tree->left)
        fprintf(stream, "    %d;\n", tree->value);
    else
        bst_print_dot_aux(tree, stream);
    fprintf(stream, "}\n");
}

void bst_print_dot_aux_min(Tree node, FILE* stream) {
    static int nullcount = 0;

    if (!node)
    	return;
    if (node->left) {
        bst_print_dot_aux_min(node->left, stream);
    } else {
    	fprintf(stream, "    %d [fontname=\"Arial\", shape=circle, style=filled, fillcolor=yellow];\n", node->value);
    }
    
}

void bst_print_dot_aux_max(Tree node, FILE* stream) {
    static int nullcount = 0;

    if (!node)
    	return;
    if (node->right) {
        bst_print_dot_aux_max(node->right, stream);
    } else {
    	fprintf(stream, "    %d [fontname=\"Arial\", shape=circle, style=filled, fillcolor=green];\n", node->value);
    }
    
}

void bst_print_dot_minmax(Tree tree, FILE* stream, int type) {
    fprintf(stream, "digraph BST {\n");
    if (type == 1)
    	fprintf(stream, "    node [fontname=\"Arial\", shape=circle, style=filled, fillcolor=red];\n");
    else
    	fprintf(stream, "    node [fontname=\"Arial\", shape=circle, style=filled, fillcolor=blue];\n");
    if (!tree)
        fprintf(stream, "\n");
    else if (!tree->right && !tree->left)
        fprintf(stream, "    %d;\n", tree->value);
    else {
        bst_print_dot_aux(tree, stream);
    	bst_print_dot_aux_min(tree, stream);
    	bst_print_dot_aux_max(tree, stream);
    }
    fprintf(stream, "}\n");
}

void bst_print_dot_values(Tree tree, FILE* stream, int type, int min, int max) {
    fprintf(stream, "digraph BST {\n");
    if (type == 1)
    	fprintf(stream, "    node [fontname=\"Arial\", shape=circle, style=filled, fillcolor=red];\n");
    else
    	fprintf(stream, "    node [fontname=\"Arial\", shape=circle, style=filled, fillcolor=blue];\n");
    if (!tree)
        fprintf(stream, "\n");
    else if (!tree->right && !tree->left)
        fprintf(stream, "    %d;\n", tree->value);
    else {
        bst_print_dot_aux(tree, stream);
    	fprintf(stream, "    %d [fontname=\"Arial\", shape=circle, style=filled, fillcolor=yellow];\n", min);
    	if (max != -1)
    		fprintf(stream, "    %d [fontname=\"Arial\", shape=circle, style=filled, fillcolor=green];\n", max);
    }
    fprintf(stream, "}\n");
}

void bst_print_dot_lca(Tree tree, FILE* stream, int type, int value1, int value2, int lca) {
    fprintf(stream, "digraph BST {\n");
    if (type == 1)
    	fprintf(stream, "    node [fontname=\"Arial\", shape=circle, style=filled, fillcolor=red];\n");
    else
    	fprintf(stream, "    node [fontname=\"Arial\", shape=circle, style=filled, fillcolor=blue];\n");
    if (!tree)
        fprintf(stream, "\n");
    else if (!tree->right && !tree->left)
        fprintf(stream, "    %d;\n", tree->value);
    else {
        bst_print_dot_aux(tree, stream);
    	fprintf(stream, "    %d [fontname=\"Arial\", shape=circle, style=filled, fillcolor=yellow];\n", value1);
    	fprintf(stream, "    %d [fontname=\"Arial\", shape=circle, style=filled, fillcolor=yellow];\n", value2);
    	fprintf(stream, "    %d [fontname=\"Arial\", shape=circle, style=filled, fillcolor=green];\n", lca);
    }
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
	system("dot test.dot | neato -n -Tpng -o out_insert_tree1.png");
	sd_assert("Cerința 1 - Test1 insert picat", height(tree) == 4 && checkBST(tree) && tree != NULL && tree->value == 7 &&
												tree->left != NULL && tree->left->parent == tree);
	destroyTree(&tree);

	tree = NULL;
	for (i = 1; i <= test2[0]; i++) {
		tree = insert(tree, test2[i]);
	}
	f = fopen("test.dot", "w");
	bst_print_dot(tree, f, 1);
	fclose(f);
	system("dot test.dot | neato -n -Tpng -o out_insert_tree2.png");
	sd_assert("Cerința 1 - Test2 insert picat", height(tree) == 5 && checkBST(tree) && tree != NULL && tree->value == 9 &&
												tree->right != NULL && tree->right->parent == tree);
	destroyTree(&tree);
	
	tree = NULL;
	for (i = 1; i <= test3[0]; i++) {
		tree = insert(tree, test3[i]);
	}
	f = fopen("test.dot", "w");
	bst_print_dot(tree, f, 1);
	fclose(f);
	system("dot test.dot | neato -n -Tpng -o out_insert_tree3.png");
	sd_assert("Cerința 1 - Test3 insert picat", height(tree) == 6 && checkBST(tree) && tree != NULL && tree->value == 50 &&
												tree->right != NULL && tree->left != NULL && tree->left->parent == tree->right->parent);
	destroyTree(&tree);
	printf("insert \t\t- Toate testele au trecut!\n");
	return 0;
}

static char *test_isEmpty() {
	Tree tree = NULL;
	FILE *f;
	int i;

	for (i = 1; i <= test1[0]; i++) {
		tree = insert(tree, test1[i]);
	}
	f = fopen("test.dot", "w");
	bst_print_dot(tree, f, 1);
	fclose(f);
	system("dot test.dot | neato -n -Tpng -o insert_out_tree1.png");
	sd_assert("Cerința 1 - Test1 isEmpty picat", isEmpty(tree) == 0);
	destroyTree(&tree);

	tree = NULL;
	for (i = 1; i <= test2[0]; i++) {
		tree = insert(tree, test2[i]);
	}
	f = fopen("test.dot", "w");
	bst_print_dot(tree, f, 1);
	fclose(f);
	system("dot test.dot | neato -n -Tpng -o insert_out_tree2.png");
	sd_assert("Cerința 1 - Test2 isEmpty picat", isEmpty(tree) == 0);
	destroyTree(&tree);
	
	tree = NULL;
	for (i = 1; i <= test3[0]; i++) {
		tree = insert(tree, test3[i]);
	}
	f = fopen("test.dot", "w");
	bst_print_dot(tree, f, 1);
	fclose(f);
	system("dot test.dot | neato -n -Tpng -o insert_out_tree3.png");
	sd_assert("Cerința 1 - Test3 isEmpty picat", isEmpty(tree) == 0);
	destroyTree(&tree);
	sd_assert("Cerința 1 - Test4 isEmpty picat", isEmpty(NULL) == 1);

	printf("isEmpty \t- Toate testele au trecut!\n");
	return 0;
}

static char *test_minmax() {
	Tree tree = NULL;
	int i;
	Tree min = NULL, max = NULL;
	FILE *f;

	for (i = 1; i <= test1[0]; i++) {
		tree = insert(tree, test1[i]);
	}
	min = minimum(tree);
	max = maximum(tree);
	f = fopen("test.dot", "w");
	sd_assert("Cerința 1 - Test1 min picat", min != NULL);
	sd_assert("Cerința 1 - Test1 max picat", max != NULL);
	bst_print_dot_values(tree, f, 1, min->value, max->value);
	fclose(f);
	system("dot test.dot | neato -n -Tpng -o out_minmax1.png");
	sd_assert("Cerința 1 - Test1 min picat", min != NULL && min->value == -8);
	sd_assert("Cerința 1 - Test1 max picat", max != NULL && max->value == 12);
	destroyTree(&tree);
	
	tree = NULL;
	min = NULL;
	max = NULL;
	for (i = 1; i <= test2[0]; i++) {
		tree = insert(tree, test2[i]);
	}
	min = minimum(tree);
	max = maximum(tree);
	f = fopen("test.dot", "w");
	bst_print_dot_values(tree, f, 1, min->value, max->value);
	fclose(f);
	system("dot test.dot | neato -n -Tpng -o out_minmax2.png");
	sd_assert("Cerința 1- Test2 min picat", min != NULL && min->value == 1);
	sd_assert("Cerința 1 - Test2 max picat", max != NULL && max->value == 35);
	destroyTree(&tree);

	tree = NULL;
	min = NULL;
	max = NULL;
	for (i = 1; i <= test3[0]; i++) {
		tree = insert(tree, test3[i]);
	}
	min = minimum(tree);
	max = maximum(tree);
	f = fopen("test.dot", "w");
	bst_print_dot_values(tree, f, 1, min->value, max->value);
	fclose(f);
	system("dot test.dot | neato -n -Tpng -o out_minmax3.png");
	sd_assert("Cerința 1 - Test3 min picat", min != NULL && min->value == 4);
	sd_assert("Cerința 1 - Test3 max picat", max != NULL && max->value == 200);
	destroyTree(&tree);

	min = minimum(NULL);
	max = maximum(NULL);
	sd_assert("Cerința 1 - Test4 min picat", min == NULL);
	sd_assert("Cerința 1 - Test4 max picat", max == NULL);
	printf("minmax \t\t- Toate testele au trecut!\n");
	return 0;
}

static char *test_contains() {
	Tree tree = NULL;
	int i;

	for (i = 1; i <= test1[0]; i++) {
		tree = insert(tree, test1[i]);
	}
	sd_assert("Cerința 1 - Test1 contains picat", contains(tree, 7) && contains(tree, 10) && contains(tree, 12) &&
												  !contains(tree, 2) && !contains(tree, 20) && contains(tree, 6));
	destroyTree(&tree);
	
	tree = NULL;
	for (i = 1; i <= test2[0]; i++) {
		tree = insert(tree, test2[i]);
	}
	sd_assert("Cerința 1 - Test2 contains picat", contains(tree, 25) && contains(tree, 26) && contains(tree, 1) &&
												  contains(tree, 35) && !contains(tree, 24) && !contains(tree, 28));
	destroyTree(&tree);

	tree = NULL;
	for (i = 1; i <= test3[0]; i++) {
		tree = insert(tree, test3[i]);
	}
	sd_assert("Cerința 1 - Test3 contains picat", contains(tree, 155) && contains(tree, 99) && contains(tree, 43));
	destroyTree(&tree);
	printf("contains \t- Toate testele au trecut!\n");

	return 0;
}

static char *test_delete() {
	Tree tree = NULL;
	int value, i;
	FILE *f;

	for (i = 1; i <= test1[0]; i++) {
		tree = insert(tree, test1[i]);
	}
	value = 12;
	f = fopen("test.dot", "w");
	bst_print_dot_values(tree, f, 1, value, -1);
	fclose(f);
	system("dot test.dot | neato -n -Tpng -o out_delete1_before.png");
	tree = delete(tree, value);
	f = fopen("test.dot", "w");
	bst_print_dot(tree, f, 1);
	fclose(f);
	system("dot test.dot | neato -n -Tpng -o out_delete1_after.png");
	sd_assert("Cerința 1 - Test1 delete picat", height(tree) == 4 && tree != NULL && checkBST(tree) && !contains(tree, value));
	destroyTree(&tree);
	
	tree = NULL;
	for (i = 1; i <= test2[0]; i++) {
		tree = insert(tree, test2[i]);
	}
	value = 29;
	f = fopen("test.dot", "w");
	bst_print_dot_values(tree, f, 1, value, -1);
	fclose(f);
	system("dot test.dot | neato -n -Tpng -o out_delete2_before.png");
	tree = delete(tree, value);
	f = fopen("test.dot", "w");
	bst_print_dot(tree, f, 1);
	fclose(f);
	system("dot test.dot | neato -n -Tpng -o out_delete2_after.png");
	sd_assert("Cerința 1 - Test2 delete picat", height(tree) == 5 && tree != NULL && checkBST(tree) && !contains(tree, value));
	destroyTree(&tree);

	tree = NULL;
	for (i = 1; i <= test3[0]; i++) {
		tree = insert(tree, test3[i]);
	}
	value = 50;
	f = fopen("test.dot", "w");
	bst_print_dot_values(tree, f, 1, value, -1);
	fclose(f);
	system("dot test.dot | neato -n -Tpng -o out_delete3_before.png");
	tree = delete(tree, value);
	f = fopen("test.dot", "w");
	bst_print_dot(tree, f, 1);
	fclose(f);
	system("dot test.dot | neato -n -Tpng -o out_delete3_after.png");
	sd_assert("Cerința 1 - Test3 delete picat", height(tree) == 6 && tree != NULL && checkBST(tree) && !contains(tree, value));
	destroyTree(&tree);

	printf("delete \t\t- Toate testele au trecut!\n");

	return 0;
}

static char *test_lca() {
	Tree tree = NULL, lca = NULL;
	int value1, value2, i;
	FILE *f;

	for (i = 1; i <= test1[0]; i++) {
		tree = insert(tree, test1[i]);
	}
	value1 = 12;
	value2 = -8;
	lca = lowestCommonAncestor(tree, value1, value2);
	sd_assert("Cerința 2 - Test1 lca picat", lca != NULL);
	f = fopen("test.dot", "w");
	bst_print_dot_lca(tree, f, 1, value1, value2, lca->value);
	fclose(f);
	system("dot test.dot | neato -n -Tpng -o out_lca1.png");
	sd_assert("Cerința 2 - Test1 lca picat", lca->value == 7);
	destroyTree(&tree);
	
	tree = NULL;
	for (i = 1; i <= test2[0]; i++) {
		tree = insert(tree, test2[i]);
	}
	value1 = 12;
	value2 = 35;
	lca = lowestCommonAncestor(tree, value1, value2);
	f = fopen("test.dot", "w");
	bst_print_dot_lca(tree, f, 1, value1, value2, lca->value);
	fclose(f);
	system("dot test.dot | neato -n -Tpng -o out_lca2.png");
	sd_assert("Cerința 2 - Test2 lca picat", lca->value == 25);
	destroyTree(&tree);

	tree = NULL;
	for (i = 1; i <= test3[0]; i++) {
		tree = insert(tree, test3[i]);
	}
	value1 = 4;
	value2 = 43;
	lca = lowestCommonAncestor(tree, value1, value2);
	f = fopen("test.dot", "w");
	bst_print_dot_lca(tree, f, 1, value1, value2, lca->value);
	fclose(f);
	system("dot test.dot | neato -n -Tpng -o out_lca3.png");
	sd_assert("Cerința 2 - Test3 lca picat", lca->value == 35);
	destroyTree(&tree);

	printf("lca \t\t- Toate testele au trecut!\n");
	return 0;
}

static char *test_successor() {
	Tree tree = NULL, succ;
	int i;

	for (i = 1; i <= test1[0]; i++) {
		tree = insert(tree, test1[i]);
	}
	succ = successor(tree, -8);
	sd_assert("Cerința 1 - Test1 successor picat", succ != NULL && succ->value == 4);
	succ = successor(tree, 6);
	sd_assert("Cerința 1 - Test2 successor picat", succ != NULL && succ->value == 7);
	succ = successor(tree, 7);
	sd_assert("Cerința 1 - Test3 successor picat", succ != NULL && succ->value == 8);
	succ = successor(tree, 12);
	sd_assert("Cerința 1 - Test4 successor picat", succ == NULL);
	destroyTree(&tree);
	
	tree = NULL;
	for (i = 1; i <= test2[0]; i++) {
		tree = insert(tree, test2[i]);
	}
	succ = successor(tree, 1);
	sd_assert("Cerința 1 - Test5 successor picat", succ != NULL && succ->value == 5);
	succ = successor(tree, 8);
	sd_assert("Cerința 1 - Test6 successor picat", succ != NULL && succ->value == 9);
	succ = successor(tree, 12);
	sd_assert("Cerința 1 - Test7 successor picat", succ != NULL && succ->value == 25);
	succ = successor(tree, 9);
	sd_assert("Cerința 1 - Test8 successor picat", succ != NULL && succ->value == 12);
	succ = successor(tree, 35);
	sd_assert("Cerința 1 - Test9 successor picat", succ == NULL);
	destroyTree(&tree);


	tree = NULL;
	for (i = 1; i <= test3[0]; i++) {
		tree = insert(tree, test3[i]);
	}
	succ = successor(tree, 4);
	sd_assert("Cerința 1 - Test10 successor picat", succ != NULL && succ->value == 9);
	succ = successor(tree, 68);
	sd_assert("Cerința 1 - Test11 successor picat", succ != NULL && succ->value == 90);
	succ = successor(tree, 47);
	sd_assert("Cerința 1 - Test12 successor picat", succ != NULL && succ->value == 50);
	succ = successor(tree, 35);
	sd_assert("Cerința 1 - Test13 successor picat", succ != NULL && succ->value == 37);
	succ = successor(tree, 200);
	sd_assert("Cerința 1 - Test14 successor picat", succ == NULL);
	succ = successor(tree, 99);
	sd_assert("Cerința 1 - Test14 successor picat", succ != NULL && succ->value == 100);
	destroyTree(&tree);
	printf("successor \t- Toate testele au trecut!\n");

	return 0;
}

static char *test_predecessor() {
	Tree tree = NULL, pred;
	int i;

	for (i = 1; i <= test1[0]; i++) {
		tree = insert(tree, test1[i]);
	}
	pred = predecessor(tree, 4);
	sd_assert("Cerința 1 - Test1 predecessor picat", pred != NULL && pred->value == -8);
	pred = predecessor(tree, 7);
	sd_assert("Cerința 1 - Test2 predecessor picat", pred != NULL && pred->value == 6);
	pred = predecessor(tree, 8);
	sd_assert("Cerința 1 - Test3 predecessor picat", pred != NULL && pred->value == 7);
	pred = predecessor(tree, -8);
	sd_assert("Cerința 1 - Test4 predecessor picat", pred == NULL);
	destroyTree(&tree);
	
	tree = NULL;
	for (i = 1; i <= test2[0]; i++) {
		tree = insert(tree, test2[i]);
	}
	pred = predecessor(tree, 5);
	sd_assert("Cerința 1 - Test5 predecessor picat", pred != NULL && pred->value == 1);
	pred = predecessor(tree, 9);
	sd_assert("Cerința 1 - Test6 predecessor picat", pred != NULL && pred->value == 8);
	pred = predecessor(tree, 25);
	sd_assert("Cerința 1 - Test7 predecessor picat", pred != NULL && pred->value == 12);
	pred = predecessor(tree, 12);
	sd_assert("Cerința 1 - Test8 predecessor picat", pred != NULL && pred->value == 9);
	pred = predecessor(tree, 26);
	sd_assert("Cerința 1 - Test9 predecessor picat", pred != NULL && pred->value == 25);
	destroyTree(&tree);


	tree = NULL;
	for (i = 1; i <= test3[0]; i++) {
		tree = insert(tree, test3[i]);
	}
	pred = predecessor(tree, 9);
	sd_assert("Cerința 1 - Test10 predecessor picat", pred != NULL && pred->value == 4);
	pred = predecessor(tree, 90);
	sd_assert("Cerința 1 - Test11 predecessor picat", pred != NULL && pred->value == 68);
	pred = predecessor(tree, 50);
	sd_assert("Cerința 1 - Test12 predecessor picat", pred != NULL && pred->value == 47);
	pred = predecessor(tree, 37);
	sd_assert("Cerința 1 - Test13 predecessor picat", pred != NULL && pred->value == 35);
	pred = predecessor(tree, 4);
	sd_assert("Cerința 1 - Test14 predecessor picat", pred == NULL);
	pred = predecessor(tree, 100);
	sd_assert("Cerința 1 - Test14 predecessor picat", pred != NULL && pred->value == 99);
	pred = predecessor(tree, 68);
	sd_assert("Cerința 1 - Test14 predecessor picat", pred != NULL && pred->value == 50);

	destroyTree(&tree);
	printf("predecessor \t- Toate testele au trecut!\n");

	return 0;
}

static char *all_tests() {
	sd_run_test(test_insert, 1);
	sd_run_test(test_isEmpty, 0.25);
	sd_run_test(test_contains, 0.25);
	sd_run_test(test_minmax, 1);
	sd_run_test(test_successor, 1);
	sd_run_test(test_predecessor, 1);
	sd_run_test(test_delete, 2);
	sd_run_test(test_lca, 2);
	return 0;
}

static char *selective_tests(int argc, char **argv) {
	int i;
	int viz[9] = {0};
	for (i = 1; i < argc; i++) {
		if (viz[atoi(argv[i])]) {
			continue;
		}
		if (!strcmp(argv[i], "1")) {
			viz[1] = 1;
			sd_run_test(test_insert, 1);
		} else if (!strcmp(argv[i], "2")) {
			viz[2] = 1;
			sd_run_test(test_isEmpty, 0.25);
		} else if (!strcmp(argv[i], "3")) {
			viz[3] = 1;
			sd_run_test(test_contains, 0.25);
		} else if (!strcmp(argv[i], "4")) {
			viz[4] = 1;
			sd_run_test(test_minmax, 1);
		} else if (!strcmp(argv[i], "5")) {
			viz[5] = 1;
			sd_run_test(test_successor, 1);
		} else if (!strcmp(argv[i], "6")) {
			viz[6] = 1;
			sd_run_test(test_predecessor, 1);
		} else if (!strcmp(argv[i], "7")) {
			viz[7] = 1;
			sd_run_test(test_delete, 2);
		} else if (!strcmp(argv[i], "8")) {
			viz[8] = 1;
			sd_run_test(test_lca, 2);
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
