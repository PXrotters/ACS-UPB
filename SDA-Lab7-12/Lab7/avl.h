/*
*	Created by Nan Mihai on 11.04.2023
*	Copyright (c) 2023 Nan Mihai. All rights reserved.
*	Laborator 7 - Structuri de date și algoritmi
*	Facultatea de Automatica si Calculatoare
*	Anul Universitar 2022-2023, Seria CD
*/
#include <stdio.h>
#include <stdlib.h>

typedef int T;

typedef struct node {
	T value;
	int height;
	struct node *left, *right;
} *Tree;

Tree createTree(T);
int max(int, int);
int height(Tree);
int balancedFactor(Tree);
void updateHeight(Tree);
Tree leftRotation(Tree);
Tree rightRotation(Tree);
Tree insert(Tree, T);
Tree minimum(Tree);
Tree delete(Tree, T);
Tree freeTree(Tree);
