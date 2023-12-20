#include <stdio.h>
#include <stdlib.h>

#include "Chaining.h"

int main() {


    return 0;
}

int hash(int key, int size) {
    return (key % size);
}

void initTab(HashTableChain h) {
    int i;
    for (i = 0; i < HSIZE; h[i++]=NULL);
}

int lookup(HashTableChain h, int k, int *i) {
    int p = hash(k, HSIZE);
    int found;
    Bucket item = h[p];

    // Get the last element in the linked list of the given key
    while (item != NULL && item->key!=k) {
        item = item->next;
    }

    if (item != NULL) {
        *i = item->value;
        found = 1;
    } else found = 0;

    return found;
}

int update(HashTableChain h, int k, int i) {
    int p = hash(k, HSIZE);
    int new;
    Bucket item = h[p];

    while (item != NULL && item->key != k) {
        item = item->next;
    }
    
    if (item != NULL) {
        item->value = i;
        new = 0;
    } else {
        item = (Bucket) malloc(sizeof(struct bucket));
        item->key = k;
        item->value = i;
        item->next = h[p];
        h[p] = item;
        new = 1;
    }

    return new;
}

int removeKey(HashTableChain h, int k) {
    int p = hash(k, HSIZE);
    int removed;
    Bucket item = h[p], tmp;

    while(item != NULL && item->value != k) {
        item = item->next;
    }

    if (item != NULL) {
        tmp = item;
        item = item->next;
        free(tmp);
        removed = 1;
    } else removed = 0;

    return removed;
}