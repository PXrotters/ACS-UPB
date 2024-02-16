/*
*	Created by Nan Mihai on 05.05.2021
*	Copyright (c) 2020 Nan Mihai. All rights reserved.
*	Laborator 6 - Structuri de date
*	Grupa 314CD
*	Facultatea de Automatica si Calculatoare
*	Anul Universitar 2020-2021, Seria CD
*/
#include "tree.h"

/*
*	Funcție care creează un arbore cu un singur nod
*/
Tree createTree(Tree parent, Item value) {
	Tree root = malloc(sizeof(TreeNode));
	root->parent = parent;
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
void init(Tree *root, Tree parent, Item value) {
	*root = createTree(parent, value);
}

/*
*	Funcție care inserează o valoare într-un arbore binar, respectând
* proprietățile unui arbore binar de căutare
*/
Tree insert(Tree root, Item value) {
	if (root == NULL) {
		root = createTree(NULL, value);
		return root;
	}
	if (root -> value == value) {
		return root;
	} else if (root -> value > value) {
			root -> left = insert(root -> left, value);
			root -> left -> parent = root;
		} else {
			root -> right = insert(root -> right, value);
			root -> right -> parent = root;
		}
		return root;
	}


/*
*	Funcție care verifică dacă un arbore este vid sau nu
*		- întoarce 1 dacă arborele este vid
*		- întoarce 0 dacă arborele nu este vid
*/
int isEmpty(Tree root) {
	if (root == NULL) {
		return 1;
	}
	return 0;
}

/*
*	Funcție care verifică dacă o valoare există sau nu în arbore
*		- 1 dacă value există în arbore
*		- 0 dacă value nu există în arbore
*/
int contains(Tree tree, Item value) {
	if (tree == NULL) {
		return 0;
	}
	if (tree -> value == value) {
		return 1;
	} else if (tree -> value > value) {
		return contains(tree -> left ,value);
	} else {
		return contains(tree -> right, value);
	}
}

/*
*	Funcție care determină elementul minim dintr-un arbore binar de căutare
*		- NULL pentru arbore vid
*/
Tree minimum(Tree tree) {
	if (tree == NULL || tree -> left == NULL) {
		return tree;
	}
	return minimum(tree -> left);
}

/*
*	Funcție care determină elementul maxim dintr-un arbore binar de căutare
*		- NULL pentru arbore vid
*/
Tree maximum(Tree tree) {
	if (tree == NULL || tree -> right == NULL) {
		return tree;
	}
	return maximum(tree -> right);
}

/*
*	Funcție care determină succesorul în inordine pentru nodul care conține
* valoarea value.
*/
Tree successor(Tree root, Item value) {
    if (root == NULL) {
        return NULL;
    }
    if (root -> value <= value) {
        return successor(root -> right, value);
    } else {
        Tree succ = successor(root -> left, value);
        if (succ == NULL) {
            return root;
        } else {
            return succ;
        }
    }
}


/*
*	Funcție care determină predecesorul în inordine pentru nodul care conține
* valoarea value.
*/
Tree predecessor(Tree root, Item value) {
    if (root == NULL) {
        return NULL;
    }
    if (root -> value >= value) {
        return predecessor(root -> left, value);
    } else {
        Tree pred = predecessor(root -> right, value);
        if (pred == NULL) {
            return root;
        } else {
            return pred;
        }
    }
}


/*
*	Funcție care dealocă întreaga memorie alocată pentru un arbore binar
*		- root va pointa către NULL după ce se va apela funcția
*/
void destroyTree(Tree *root) {
	if (*root == NULL) {
		return;
	}
	destroyTree(&((*root) -> left));
    destroyTree(&((*root) -> right));
    free(*root);
    *root = NULL;
}

/*
*	Funcție care șterge un nod cu o anumită valoare din arbore
*/
Tree delete(Tree root, Item value) {
    if (root == NULL) {
        return NULL;
    }
    if (value < root -> value) {
        root -> left = delete(root -> left, value);
    } else if (value > root -> value) {
        root -> right = delete(root -> right, value);
    } else {
        if (root -> left == NULL) {
            Tree temp = root -> right;
            free(root);
            return temp;
        } else if (root -> right == NULL) {
            Tree temp = root -> left;
            free(root);
            return temp;
        }
        Tree current = root -> right;
        while (current -> left != NULL) {
            current = current -> left;
        }
        root -> value = current -> value;
        root -> right = delete(root -> right, current -> value);
    }
    return root;
}

/*
*	Funcție care determină cel mai apropiat strămoș comun pentru
* două noduri având cheile value1 și value2
*/
Tree lowestCommonAncestor(Tree root, Item value1, Item value2) {
    if (root == NULL) {
        return NULL;
    }
    if (root -> value > value1 && root -> value > value2) {
        return lowestCommonAncestor(root -> left, value1, value2);
    }
    if (root -> value < value1 && root -> value < value2) {
        return lowestCommonAncestor(root -> right, value1, value2);
    }
    return root;
}
