#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct LInt_nodo {
int valor;
struct LInt_nodo *prox;
} *LInt;

/* Questão 2 */
LInt removeMaiores(LInt l, int x) {
    LInt current = l;
    LInt prev = NULL;
    LInt temp;

    while (current != NULL) {
        if (current->valor >= x) {
            if (prev == NULL) {
                temp = current;
                current = current->prox;
                l = current;
                free(temp);
            } else {
                temp = current;
                current = current->prox;
                prev->prox = current;
                free(temp);
            }
        } else {
            prev = current;
            current = current->prox;
        }
    }

    return l;
}


int main(){
    


    return 0;
}