typedef struct bst {
    int key;
    int value;
    struct bst *left, *right;
} *BST;

int update (BST *a, int k, int i);
int lookup(BST a, int k, int *i);