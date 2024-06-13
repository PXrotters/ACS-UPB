/*
*	Created by Nan Mihai on 11.04.2023
*	Copyright (c) 2023 Nan Mihai. All rights reserved.
*	Laborator 7 - Structuri de date și algoritmi
*	Facultatea de Automatica si Calculatoare
*	Anul Universitar 2022-2023, Seria CD
*/
#include "avl.h"

Tree createTree(T value) {
	Tree root = malloc(sizeof(struct node));
	root->value = value;
	root->left = NULL;
	root->right = NULL;
	root->height = 0;
	return root;
}

int max(int a, int b) {
	if (a > b) {
		return a;
	} else {
		return b;
	}
}

int height(Tree root) {
    if (root == NULL)
        return -1;
    return root->height;
}

int balancedFactor(Tree root) {
	if (root == NULL) {
		return 0;
	} else {
		return height(root->left) - height(root->right);
	}
}

void updateHeight(Tree root) {
	 if (root == NULL) {
		return;
	 } else {
        updateHeight(root->left);
        updateHeight(root->right);
		root->height = 1 + max(height(root->left), height(root->right));
    }
}

Tree leftRotation(Tree root) {
    if (root == NULL || root->right == NULL) {
        return root;
    } else {
        Tree z = root->right;
        root->right = z->left;
        z->left = root;
        updateHeight(root);
        updateHeight(z);
        return z;
    }
}

Tree rightRotation(Tree root) {
    if (root == NULL || root->left == NULL) {
        return root;
    } else {
        Tree z = root->left;
        root->left = z->right;
        z->right = root;
        updateHeight(root);
        updateHeight(z);
        return z;
    }
}

Tree insert(Tree root, T value) {
    if (root == NULL) {
        root = createTree(value);
        return root;
    }
    if (value < root->value) {
        root->left = insert(root->left, value);
    } else if (value > root->value) {
        root->right = insert(root->right, value);
    } else {
        return root;
    }
    updateHeight(root);
    int bf = balancedFactor(root);
    if (bf > 1 && value < root->left->value) {
        root = rightRotation(root);
    } else if (bf < -1 && value > root->right->value) {
        root = leftRotation(root);
    } else if (bf > 1 && value > root->left->value) {
        root->left = leftRotation(root->left);
        root = rightRotation(root);
    } else if (bf < -1 && value < root->right->value) {
        root->right = rightRotation(root->right);
        root = leftRotation(root);
    }
    return root;
}

Tree minimum(Tree root) {
	if (root == NULL) {
        return NULL;
    }
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

Tree delete(Tree root, T value) {
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
        root->right = delete(root->right, current->value);
		updateHeight(root);
		int bf = balancedFactor(root);
    	if (bf > 1 && balancedFactor(root->right) >= 0) 
		return leftRotation(root);
		if (bf < -1 && balancedFactor(root->left) <= 0)
		return rightRotation(root);
		if (bf > 1 && balancedFactor(root->right) < 0) {
			root->right = rightRotation(root->right);
			return leftRotation(root);
		}
		if (bf < -1 && balancedFactor(root->left) > 0) {
			root->left = leftRotation(root->left);
			return rightRotation(root);
		}
    }
    return root;
}

Tree freeTree(Tree root) {
	if (root == NULL) {
        return NULL;
    }
    root->left = freeTree(root->left);
    root->right = freeTree(root->right);
    free(root);
    return NULL;
}