#include <stdio.h>
#include <stdlib.h>
#include "AVLTrees.h"

int main() {

    return 0;
}

/**
 * @def Original Tree
 *              a
 *           3     8
 *         2  4  7  9
 * 
 * 
*/

AVLTree rotateRight(AVLTree a) {
    AVLTree b = a->left;
    /**
     * @def b:
     *          3
     *        2   4
    */

   a->left = b->right;

   /**
    * @def b->right: 4
    * @def a:
    *           a
    *        4     8
    *            7   9
   */

    b->right = a;

    /**
     * @def Final Tree:
     * 
     *          3
     *       2     a
     *           4    8
     *              7   9
     * 
     * 
    */
   return b;

}

AVLTree rotateLeft(AVLTree a) {
    AVLTree b = a->right;
    a->right = b->left;
    b->left = a;
}

AVLTree fixRight(AVLTree a) {
    AVLTree b, c;
    b = a->right;
    if (b->bal == RIGHT) {

    }
}

AVLTree fixRight(AVLTree a) {
    AVLTree b, c;
    b = a->right;
    if (b->bal == RIGHT) {
        a->bal = b->bal = BAL;
        a = rotateLeft(a);
    } else {
        c = b->left;
        switch (c->bal) {
            case LEFT:
                a->bal = BAL;
                b->bal = RIGHT;
                break;
            case RIGHT:
                a->bal = LEFT;
                b->bal = BAL;
                break;
            case BAL:
                a->bal = b->bal = BAL;
        }
        c->bal = BAL;
        a->right = rotateRight(b);
        a = rotateLeft(a);
    }
    return a;
}

AVLTree fixLeft(AVLTree a) {
    AVLTree b, c;
    b = a->left;
    if (b->bal == LEFT) {
        a->bal = b->bal = BAL;
        a = rotateRight(a);
    } else {
        c = b->right;
        switch (c->bal) {
            case LEFT:
                a->bal = RIGHT;
                b->bal = BAL;
                break;
            case RIGHT:
                a->bal = BAL;
                b->bal = LEFT;
                break;
            case BAL:
                a->bal = b->bal = BAL;
        }
        c->bal = BAL;
        a->right = rotateLeft(b);
        a = rotateRight(a);
    }
    return a;
}

AVLTree updateAVLRec(AVLTree a, int k, int i, int *g, int *u) {
    if (a == NULL) {
        a = malloc(sizeof(struct avl));
        a->key = k;
        a->value = i;
        a->bal = BAL;
        a->left = a->right = NULL;
        *g = 1;
        *u = 0;
    } else if (a->key == k) {
        a->value = i;
        *g = 0;
        *u = 1;
    } else if (a->key > k) {
        a->left = updateAVLRec(a->left, k, i, g, u);
        if (*g == 1) {
            switch (a->bal) {
                case LEFT:
                    a = fixLeft(a);
                    *g = 0;
                    break;
                case BAL:
                    a->bal = LEFT;
                    break;
                case RIGHT:
                    a->bal = BAL;
                    *g = 0;
                    break;
            }
        }
    } else {
        a->right = updateAVLRec(a->right, k, i, g, u);
        if (*g == 1) {
            switch (a->bal) {
                case RIGHT:
                    a = fixRight(a);
                    *g = 0;
                    break;
                case BAL:
                    a->bal = RIGHT;
                    break;
                case LEFT:
                    a->bal = BAL;
                    *g = 0;
                    break;
            }
        }
    }
    return a;
}



// Exame 2023
AVLTree createNode(int value) {
    AVLTree b;
    b = (AVLTree) malloc(sizeof(struct avl));
    b->bal = BAL;
    b->value = value;
    b->left = b->right = NULL;

    return b;
}

AVLTree buildAux(int a[], int start, int end) {
    if (start > end)
        return NULL;

    int mid = (start + end) / 2;
    AVLTree root = newNode(a[mid]);

    root->left = buildUtil(a, start, mid - 1);
    root->right = buildUtil(a, mid + 1, end);

    return root;
}

AVLTree build(int a[], int N) {
    return buildAux(a, 0, N - 1);
}