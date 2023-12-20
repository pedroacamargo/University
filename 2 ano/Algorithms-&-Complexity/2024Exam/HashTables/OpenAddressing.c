#include <stdio.h>
#include <stdlib.h>

#include "OpenAddressing.h"

int main() {


    return 0;
}

int hash(int key, int size) {
    return (key % size);
}

void initTab(HashTable h) {
    int i = 0;
    for (i; i < HSIZE; h[i].status = STATUS_FREE);
}

int find_probe(HashTable h, int k) {   
    int p = hash(k, HSIZE);
    int count = HSIZE;

    while (h[p].status != STATUS_FREE && count > 0 && h[p].key != k) {
        count--;
        p = (p+1) % HSIZE;
    }

    if (count == 0) p = -1;
    return p;
}

int lookup(HashTable h, int k, int *i) {
    int p = find_probe(h, k);
    int found;

    if (p >= 0 && h[p].key == k) {
        *i = h[p].value;
        found = 1;
    } else found = 0;

    return found;
}

int update(HashTable h, int k, int i) {
    int p = find_probe(h, k);
    int new = 0;

    if (h[p].key == k) {
        h[p].value = i;
        new = 1;
    } else if (p < 0) {
        new = 0;
    } else {
        h[p].key = k;
        h[p].status = STATUS_USED;
        h[p].value = i;
        new = 2;
    }

    return new;
}

int find_Quad_probe(HashTable h, int k) {
    int p = hash(k, HSIZE);
    int count = HSIZE, d = 1;

    while (count > 0 && h[p].key != k && h[p].status != STATUS_FREE) {
        count--;
        p = (p + d) % HSIZE;
        d++;
    }

    if (count = 0) p = -1;
    return p;
}