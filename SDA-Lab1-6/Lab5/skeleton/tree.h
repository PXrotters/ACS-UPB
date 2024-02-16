#ifndef _TREE_H_
#define _TREE_H_
/*
*	Created by Nan Mihai on 28.03.2021
*	Copyright (c) 2021 Nan Mihai. All rights reserved.
*	Laborator 5 - Structuri de date
*	Facultatea de Automatica si Calculatoare
*	Anul Universitar 2020-2021, Seria CD
*/

#include <stdio.h>
#include <stdlib.h>

/*
*	Reprezentarea unui arbore binar prezentată în curs (R1)
*/
typedef int Item;

typedef struct node {
    Item value;
    struct node *left;
    struct node *right;
} TreeNode, *Tree;

void init(Tree *root, Item value);
Tree insert(Tree root, Item value);
void printPostorder(Tree root);
void printPreorder(Tree root);
void printInorder(Tree root);
void freeTree(Tree *root);
int size(Tree root);
int maxDepth(Tree root);
void mirror(Tree root);
int sameTree(Tree root1, Tree root2);
#endif
