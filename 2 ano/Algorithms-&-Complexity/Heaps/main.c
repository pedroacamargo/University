/* Main function of the C program. */

#include <stdio.h>
#include <stdlib.h>

#include "minheap.h"

int main()
{

    Heap h;
    int i, x;

    initHeap(&h, 1);
    
    insertHeap(&h, 30);
    insertHeap(&h, 60);
    insertHeap(&h, 40);
    insertHeap(&h, 10);
    insertHeap(&h, 100);
    insertHeap(&h, 20);
    insertHeap(&h, 90);
    insertHeap(&h, 50);
    insertHeap(&h, 80);
    insertHeap(&h, 70);
  
    printf("Heap construída (capacidade %d):\n", h.size);
    for (i = 0; i < h.used; i++)
        printf("%d\n", h.values[i]);

    printf("Extracção de elementos:\n");
    while (extractMin(&h, &x)) 
        printf("%d\n", x);
    
}
