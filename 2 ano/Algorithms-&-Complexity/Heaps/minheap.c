
#include <stdlib.h>

#include "minheap.h"

void swap(Elem a[], int i, int j) {
    Elem tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}


void initHeap (Heap *h, int size) {
    h->values = malloc(size * sizeof(int));
    h->size = size;
    h->used = 0;
}

void bubbleUp (Elem h[], int i) {
    // [1, 10, 20, 40, 50, 60, 70]
    //  0   1  2    3   4   5   6    INDICE
    //  1   2  2    3   3   3   3    NIVEL
    int p = PARENT(i);
    while (i != 0 && h[i] < h[PARENT(i)]) {
        swap(h, i, PARENT(i));
        i = p;
        p = PARENT(i);
    }
    
}

/***
 * Recursive
 * void bubbleUp (Elem h[], int i) {
    if (i != 0) {
        if (a[i] < a[PARENT(i)]) {
            swap(a, i, PARENT(i));
            bubbleUp(a, PARENT(i));
        }
    }
}

 * 
*/

int  insertHeap (Heap *h, Elem x) {
    
    if (h->used == h->size) {
        h->values = realloc(h->values, sizeof(int) * h->size * 2);
        h->size = h->size * 2;
    }
    
    h->values[h->used] = x;
    (h->used)++;
    
    bubbleUp_sol(h->values, h->used-1);
    return 1;
}



void bubbleDown (Elem a[], int N) {
    int i = 0, min;
    while (LEFT(i) < N) {
        min = a[i] < a[LEFT(i)] ? i : LEFT(i);
        if (RIGHT(i) < N) {
            min = a[min] < a[RIGHT(i)] ? min : RIGHT(i);
        }
        if (min != i) {
            swap(a, i, min);
            i = min;
        } else break;
    }

}


void bubbleDown3 (Elem a[], int N) {
    int i = 0, min;

    while (RIGHT(i) < N && a[min = a[LEFT(i)] < a[RIGHT(i)] ? LEFT(i) : RIGHT(i)] < a[i]) {
        swap(a, i, min);
        i = min;
    }

    if (LEFT(i) < N && a[LEFT(i)] < a[i]) {
        swap(a, i, LEFT(i));
    }

}



int  extractMin (Heap *h, Elem *x) {
    if (h->used > 0) {
        *x = h->values[0];
        h->values[0] = h->values[h->used - 1];
        (h->used)--;
        bubbleDown(h->values, h->used);
    }
    return 0;
}



int minHeapOK (Heap h) {
    
 // ...
}