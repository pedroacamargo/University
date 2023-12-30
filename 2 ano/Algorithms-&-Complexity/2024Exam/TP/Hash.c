#include <stdio.h>
#include <stdlib.h>
#define SIZE 30

//  Hash
unsigned hash(char *str) {
    unsigned hashV = 5381;
    int c;

    while (c = *str++) {
        hashV = ((hashV << 5) + hashV) + c; /* hashV * 33 + c */
    }

    return hashV;
} 

int main() {
    char string[] = "ola";
    unsigned hashValue = hash(string);
    printf("%d \n", hashValue);
    printf("%d \n", (hashValue % SIZE));
    return 0;
}

// Chaining
typedef struct nodo {
    char *chave;
    int ocorr;
    struct nodo *prox;
} Nodo, *THash[SIZE];

void initEmpty(THash t) {
    for (int i = 0; i < SIZE; i++) {
        t[i] = NULL;
    }
}

void add(char *s, THash t) {
    int pos = (hash(s) % SIZE);
    
    while (t[pos] && t[pos]->chave != *s) {
        t[pos] = t[pos]->prox;
    }

    if (t[pos]->chave == *s) t[pos]->ocorr++;
    else {
        t[pos] = malloc(sizeof(Nodo));
        t[pos]->chave = *s;
        t[pos]->ocorr = 1;
        t[pos]->prox = NULL;
    }
}

#define Free 0
#define Used 1
#define Deleted 2

typedef struct bucket {
    int status;
    int ocorr;
    char *chave;
} THashOA[SIZE];

int where(char *s, THashOA t) {
    int pos = (hash(s) % SIZE);
    int found = 0, count = 0;

    while (t[pos].chave != *s && count < SIZE) {
        if (pos == SIZE - 1) pos = 0;
        else pos++;
        count++;
    }

    if (count == SIZE) found = 0;
    else found = 1;

    return found;
}

int garb_collection (THashOA t) {
    int count = 0;
    while (count < SIZE) {
        if (t[count].status == Deleted) {
            t[count].status = Free;
            t[count].ocorr = 0;
        }
        count++;
    }
}