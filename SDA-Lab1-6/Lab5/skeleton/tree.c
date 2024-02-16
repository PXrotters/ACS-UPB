/*
*	Created by Nan Mihai on 28.03.2021
*	Copyright (c) 2021 Nan Mihai. All rights reserved.
*	Laborator 5 - Structuri de date
*	Facultatea de Automatica si Calculatoare
*	Anul Universitar 2020-2021, Seria CD
*/
#include "tree.h"

/*
*	Funcție care creează un arbore cu un singur nod
*/
Tree createTree(Item value) {
	Tree root = malloc(sizeof(TreeNode));
	root->value = value;
	root->left = NULL;
	root->right = NULL;
	return root;
}

/*
*	Funcție care inițializează un nod de arbore
*		- îi alocă memorie
*		- îi setează câmpul valoare
*		- setează left și right să pointeze către NULL
*/
void init(Tree *root, Item value) {
	(*root) -> value = value;
	(*root) -> left = NULL;
	(*root) -> right = NULL;
}

/*
*	Funcție care inserează o valoare într-un arbore binar, respectând
* proprietățile unui arbore binar de căutare
*/
Tree insert(Tree root, Item value) {
	if (root == NULL) {
		root = createTree(value);
	}
	if (root -> value == value) {
		return root;
	} else if (root -> value > value) {
		root -> left = insert(root->left, value);
	} else {
		root -> right = insert(root->right, value);
	}
	return root;
}

/*
*	Funcție care afișează nodurile folosind parcurgerea în postordine
*/
void printPostorder(Tree root) {
	if (root == NULL) {
		return ;
	}
		printPostorder(root -> left);
		printPostorder(root -> right);
		printf("%d ", root -> value);
}

/*
*	Funcție care afișează nodurile folosind parcurgerea în preordine
*/
void printPreorder(Tree root) {
	if (root == NULL) {
		return ;
	}
	printf("%d ", root -> value);
	printPreorder(root -> left);
	printPreorder(root -> right);
}

/*
*	Funcție care afișează nodurile folosind parcurgerea în inordine
*/
void printInorder(Tree root) {
	if (root == NULL) {
		return ;
	}
	printInorder(root -> left);
	printf("%d ", root -> value);
	printInorder(root -> right);
}

/*
*	Funcție care dealocă întreaga memorie alocată pentru un arbore binar
*		- root va pointa către NULL după ce se va apela funcția
*/
void freeTree(Tree *root) {
	if (root == NULL) {
		return ;
	}
	free((*root) -> left);
	free((*root) -> right);
	free(*root);
	*root = NULL;
}


/*
*	Funcție care determină numărul de noduri dintr-un arbore binar
*/
int size(Tree root) {
	if (root == NULL) {
		return 0;
	}
	return 1 + size (root -> left) + size (root -> right);
}

/*
*	Funcție care returnează adâncimea maximă a arborelui
*/
int maxDepth(Tree root) {
	if (root == NULL || (root -> left == NULL && root -> right == NULL))
	return 0;
	int left, right;
	left = (maxDepth(root -> left));
	right = (maxDepth(root -> right));
	if (left < right)
	return right + 1;
	return left + 1;
}

/*
*	Funcție care construiește oglinditul unui arbore binar
*/
void mirror(Tree root) {
	if (root == NULL) {
		return ;
	} else {
		TreeNode *iter;
		iter = root -> left;
		root->left = root -> right;
		root -> right = iter;
		mirror (root -> left);
		mirror (iter);
	}
}

/*
*	Funcție care verifică dacă doi arbori binari sunt identici
*/
int sameTree(Tree root1, Tree root2) {
	if (root1 == NULL && root2 == NULL) {
		return 1;
	} else if (root1 == NULL && root2 != NULL) {
		return 0;
	} else if (root1 != NULL && root2 == NULL) {
		return 0;
	} else if (root1 != NULL && root2 != NULL) {
		if (root1 -> value != root2 -> value) {
			return 0;
		} else {
			int a = sameTree(root1 -> left, root2 -> left);
			int b = sameTree(root1 -> right, root2 -> right);
			return a&&b;
		}
	}
	return 1;
}
