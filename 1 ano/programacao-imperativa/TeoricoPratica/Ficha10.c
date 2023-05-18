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

ABin removeMenor (ABin *a) {
    ABin esquerda = NULL;
    while (a) {
        if ((*a)->esq) {
            a = &( (*a)->esq);
        } else {
            esquerda = *a;
            a = &((*a)->dir);
        }
    }
    return esquerda;
}

void removeRaiz (ABin *a) {
    ABin new = NULL;
    if ((*a)->dir) {
        new = removeMenor((*a)->dir);
        new->dir = (*a)->dir;
        new->esq = (*a)->esq;
    } else {
        new = (*a)->esq;
    }

    free(*a);
    *a = new;
}


/* Questão 2 */
void rodaEsquerda (ABin *a){
    ABin b = (*a)->dir;
    (*a)->dir = b->esq;
    b->esq = (*a);
    *a = b;
}

void rodaDireita (ABin *a){
    ABin b = (*a)->esq;
    (*a)->esq = b->dir;
    b->dir = *a;
    *a = b;
}

void promoveMenor (ABin *a){
    if(*a!=NULL && (*a)->esq!=NULL){
        promoveMenor(&((*a)->esq));
        rodaDireita(a);
    }
}

void promoveMaior (ABin *a){
    if(*a!= NULL && (*a)->dir!=NULL){
        promoveMaior(&((*a)->dir));
        rodaEsquerda(a);
    }   
}

ABin removeMenor2 (ABin *a){
    ABin menor;
    promoveMenor(a);
    menor = *a;
    *a = (*a)->dir;
    return menor;
}

/* Questão 3 */
int constroiEspinhaAux (ABin *a, ABin *ult){
    int r = 0;
    if(*a!=NULL){
        r = constroiEspinhaAux(&((*a)->esq), ult);
        if((*a)->esq!=NULL)
            rodaDireita(a);
        r = r + 1 + constroiEspinhaAux(&((*a)->dir), ult);
    }

    return r;
}

int constroiEspinha (ABin *a){
    return (constroiEspinhaAux(a, NULL));
}

int constroiEspinha2 (ABin *a){
    int r = 0;
    while(*a!=NULL){
        promoveMenor(a);
        a = &((*a)->dir);
        r++;
    }
    return r;
}






int main(){
    


    return 0;
}