#define LEFT 1 // When the left subtree is bigger than right subtree
#define BAL 0 // Both trees have the same height
#define RIGHT -1 // When the right subtree is bigger than left subtree


typedef struct avl {
    int bal;
    int key, value;
    struct avl *left, *right;
} *AVLTree;

AVLTree updateAVLRec(AVLTree a, int k, int i, int *g, int *u);
AVLTree rotateRight(AVLTree a);
AVLTree rotateLeft(AVLTree a);
AVLTree fixRight(AVLTree a);
AVLTree fixLeft(AVLTree a);
AVLTree build (int a[], int N);
