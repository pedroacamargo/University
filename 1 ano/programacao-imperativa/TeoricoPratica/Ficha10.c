#include <stdio.h>

typedef struct nodo {
int valor;
struct nodo *esq, *dir;
} * ABin;

/* Questão 1 */
ABin removeMenor (ABin *a) {
    if (a == NULL) return NULL;
    int res;
    ABin ant,cursor = *a;

    while (cursor->esq) {
        a = &cursor;
        cursor = cursor->esq;
    }

    (*a)->esq = cursor->dir;


    //if ((*a)->esq) return removeMenor((*a)->esq);
    //else if (!((*a)->esq)) {
    //    res = (*a)->valor;
    //    while ((*a)->dir) {
    //        (*a)->valor = (*a)->dir->valor;
    //        a = &( (*a)->dir);
    //    }
    //}
    return ant;
}

void removeRaiz(ABin *a) {
    //if ((*a)->esq) return removeRaiz((*a)->esq);
    //else if (!((*a)->esq)) {
    //    while ((*a)->esq || (*a)->dir) {
    //        ABin temp = *a;
    //
    //        free(a);
    //
    //    }
    //}






    
}



int main(){
    


    return 0;
}