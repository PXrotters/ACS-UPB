#ifndef _TREE_H_
#define _TREE_H_
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

/*
*	Reprezentarea unui arbore binar
*/
typedef int Item;

typedef struct node {
    Item value;
    struct node *left;
    struct node *right;
    struct node *parent;
} TreeNode, *Tree;

Tree createTree(Tree parent, Item value);
void init(Tree *root, Tree parent, Item value);
int isEmpty(Tree root);
Tree insert(Tree root, Item value);
int contains(Tree root, Item value);
Tree minimum(Tree root);
Tree maximum(Tree root);
Tree delete(Tree root, Item value);
Tree successor(Tree root, Item value);
Tree predecessor(Tree root, Item value);
void destroyTree(Tree *root);

Tree lowestCommonAncestor(Tree root, Item value1, Item value2);
#endif
