#include <stdio.h>
#include <stdlib.h>
#include "BSTrees.h"

int main() {

    return 0;
}

int update(BST *a, int k, int i) {
    int u = 0;

    while (*a != NULL && (*a)->key != k) {
        if ((*a)->key > k) a = &((*a)->left);
        else a = &((*a)->right);
    }

    if (*a == NULL) {
        *a = (BST) malloc(sizeof (struct bst));
        (*a)->key = k;
        (*a)->value = i;
        (*a)->left = (*a)->right = NULL;
        u = 1;
    } else {
        (*a)->value = i;
    }

    return u;
}

int lookup(BST a, int k, int *i) {
    int found = 0;

    while (a != NULL && a->key != k) {
        if (a->key > k) a = a->left;
        else a = a->right;
    }

    if (a != NULL) *i = a->value;
    else found = 0;

    return found;
}