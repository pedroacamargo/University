#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct LInt_nodo {
int valor;
struct LInt_nodo *prox;
} *LInt;

/* Questão 2 */
void roda(LInt *l) {
    if (*l == NULL || (*l)->prox == NULL)
        return; // Empty list or only one element, no need to rotate

    LInt head = *l;
    LInt tail = *l;

    while (tail->prox != NULL) {
        tail = tail->prox;
    }

    tail->prox = head->prox;
    head->prox = NULL;
    *l = tail;
}


int main(){
    


    return 0;
}