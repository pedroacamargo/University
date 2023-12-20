#include <stdio.h>
#include <stdlib.h>
#include "heaps.h"

static int heap[] = { 10, 15, 11, 16, 22, 35, 20, 21, 23, 24, 37, 80, 43, 22, 25, 24, 28, 12 }; 


int main() {
    printHeap(heap);
    bubbleup(heap, 17);
    printHeap(heap);
    return 0;
}

void swap(int v[], int i, int j) {
    int temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

void printHeap(int array[]) {
    size_t size = sizeof(heap) / sizeof(array[0]);
    for (int i = 0; i < size; i++) {
        printf("%d(%d) ",array[i],i);
    }
    printf("\n");
}

void bubbleup(int v[], int i) {
    int p = (i - 1) / 2; // predecessor
    while (i > 0 && v[i] < v[p]) {
        swap(v, i, p);
        i = p;
        p = (i - 1) / 2;
    }
}

void bubbledown(int v[], int i) {
    int size = sizeof(heap) / sizeof(v[0]);
    int c = 2 * i + 1; // left child
    while (c < size) {
        if (c + 1 < size && v[c + 1] < v[c]) {
            c++;
        }
        if (v[i] <= v[c]) {
            break;
        }
        swap(v, i, c);
        i = c;
        c = 2 * i + 1;
    }
}


/**
 * Using Structs
*/
void initPriorityQ(PriorityQ *q) {
    q->size = 0;
}

int add(PriorityQ *q, int x) {
    int r = 0;

    if (q->size == MAX) r = 1;
    else {
        q->values[q->size] = x;
        bubbleup(q, q->size);
        q->size++;
    }

    return r;
}

int remove(PriorityQ *q, int *x) {
    int r = 0;
    if (q->size == 0) r = 1;
    else {
        *x = q->values[0];
        q->values[0] = q->values[--q->size];
        bubbledown(q->values, 0);
    }
}

void heapify(int v[], int N) {
    int i;
    for (i = 1; i < N; i++) bubbleup(v, i);
}