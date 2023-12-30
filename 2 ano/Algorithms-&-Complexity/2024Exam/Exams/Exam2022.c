#include <stdio.h>
#include <stdlib.h>


typedef struct avlnode {
    int value, balance;
    struct avlnode *left, *right;
} *AVLTree;

int main() {


    return 0;
}

// 1
AVLTree newNode(int value) {
    AVLTree node = (AVLTree) malloc(sizeof(AVLTree));
    if (node != NULL) {
        node->value = value;
        node->balance = 0;
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}

AVLTree build (int a[], int N) {
    // constroi uma árvore através de busca binária
    //  0  1  2  3  4  5  6
    // [1, 2, 3, 4, 5, 6, 7]
    //           |
    //          mid
    if (N / 2 == 0) return NULL;
    int mid = N / 2;
    AVLTree tree = newNode(a[mid]);
    tree->left = build(a, mid);
    tree->right = build(a + mid, N - mid);

    if (tree->left == NULL && tree->right != NULL) tree->balance = -1;
    if (tree->left != NULL && tree->right == NULL) tree->balance = 1;

    return tree;
}

// 3 Min Heaps
void bubbleDown(int h[], int i, int N) {
    int sucessor = 2*i + 1;
    while (sucessor < N) {
        if (h[sucessor] > h[sucessor + 1] && sucessor + 1 < N) sucessor++; // sucessor da direita é o menor
        if (h[i] < h[sucessor]) break; // se o sucessor é maior q o root, terminar a função
        swap(h, i, sucessor);
        i = sucessor;
        sucessor = 2*i + 1;
    }
}

void bubbleUp(int h[], int i, int N) {
    int antecessor = (i - 1) / 2;

    while (antecessor > 0) {
        if (h[antecessor] < h[i]) break;
        swap(h, i, antecessor);
        i = antecessor;
        antecessor = (i - 1) / 2; 
    }
}

int decrease(int x, int y, int h[], int N) {
    // valor x está na min heap h com tamanho N
    // sucessor esquerdo: 2i + 1
    // sucessor direito: 2i + 2
    // antecessor (i-1)/2
    // [10,15,11,16,22,35,20,21,23,34,37,80,43,22,25,24,28]
    int i, swapped;

    // check if x exists
    for (i = 0; i < N && h[i] != x; i++);

    if (i == N - 1) swapped = 0;
    else {
        h[i] = y;
        if (h[i] < h[(i-1)/2]) bubbleUp(h, i, N);
        else if (h[i] > h[2*i + 1] || h[i] > h[2*i + 2]) bubbleDown(h, i, N);
    }

    return swapped;
}

// 4 Grafos
#define N 10
typedef struct coords {
    int x;
    int y;
} Coords;

typedef struct queue {
    Coords axis[100];
    int start;
    int size;
} QueueCoords;

int maior (int image[N][N]) {
    QueueCoords q; // queue
    int x = 1, y = 1; // start of bitmap
    int maxX = N - 2, maxY = N - 2, minX = 1, minY = 1;
    int maxCount = 0, count = 0;

    for (int i = x; i < maxX; i++) {
        for (int j = y; j < maxY; j++) {
            count = 0;
            if (image[i][j] == 1) {
                count = checkSurroundings(image, &q, i, j);
            }

            if (count > maxCount) maxCount = count;
        }
    }

    return maxCount;
}

int checkSurroundings(int image[N][N], QueueCoords *q, int i, int j) {
    int count = 1;
    if (image[i+1][j] == 1) enqueue(i+1,j,q);
    if (image[i-1][j] == 1) enqueue(i-1,j,q);
    if (image[i][j+1] == 1) enqueue(i,j+1,q);
    if (image[i][j-1] == 1) enqueue(i,j+1,q);
    image[i][j] = 0;

    while (q->size != 0) {
        Coords p = dequeue(*q);
        count += checkSurroundings(image, q, p.x, p.y);
    }

    return count;
}

Coords dequeue(QueueCoords q) {
    Coords r = q.axis[q.start];
    q.size--;
    q.start++;
    return r;
}

void enqueue(int i, int j, QueueCoords *q) {    
    q->axis[q->size].x = i;
    q->axis[q->size].y = j;
    q->size++;
}