#include <stdio.h>

typedef struct nodo {
    int valor;
    struct nodo *esq, *dir;
} * ABin;

ABin newABin (int r, ABin e, ABin d) {
    ABin a = malloc (sizeof(struct nodo));
    if (a!=NULL) {
        a->valor = r; a->esq = e; a->dir = d;
    }   
    return a;
}

/* Questão 1 */
int max(int x, int y) {
    return (x>y) ? x : y;
}
int altura (ABin a) {
    int r = 0;
    if (a) {
        r = 1 + max(altura(a->esq), altura(a->dir));
    }
    return r;
}


int nFolhas (ABin a) {
    int r = 0;
    if (!(a)) return 0;
    if (a->dir || a->esq) {
        if (!(a->dir) ) r += nFolhas(a->esq);
        else if (!(a->esq)) r += nFolhas(a->dir);
    }
    if (!(a->dir) && !(a->esq)) return 1;;

    return r;
}

int nFolhas2 (ABin a){
    int r = 0;
    if(a != NULL){
        if(a->dir == NULL && a->esq == NULL)
            r = 1;
        else 
            r = nFolhas(a->dir) + nFolhas(a->esq);
        }
    return r;
}


ABin maisEsquerda (ABin a) {
    ABin r = a;
    while (a) {
        r = a;
        a = a->esq;
    }
    return r;
}

void imprimeNivel(ABin a, int l){
    if(a && l >= 0){
        if(l==0)
            printf("%d ", a->valor);
        else{
            imprimeNivel(a->esq, l-1);
            imprimeNivel(a->dir, l-1);
        }
    }
}

int procuraE (ABin a, int x) {
    if (a == NULL) return 0;
    else {
        if (x == a->valor) return 1;
        else return procuraE(a->esq,x) || procuraE(a->dir,x);
    }
}

/* Questão 2 */
struct nodo *procura (ABin a, int x) {
    ABin r = NULL;
    while (a) {
        if (x < a->valor) a = a->esq;
        else if (x > a->valor) a = a->dir;
        else r = a;
    }
    return r;
}

struct nodo *procuraRecursivo (ABin a, int x){
    ABin n = NULL;
    if(a!=NULL){
        if(a->valor == x)
            n = a;
        else if(a->valor > x)
            n = procura(a->esq, x);
        else
            n = procura(a->dir, x);
    }

    return n;
}

int nivel (ABin a, int x) {
    int nivel = 0;
    while (a) {
        if (a->valor == x) return nivel;
        else if (x < a->valor) a = a->esq;
        else if (x > a->valor) a = a->dir;
        nivel++;
    }
    return -1;
}

void imprimeAte (ABin a, int x){
    if(a!=NULL){
        imprimeAte(a->esq, x);
        if(a->valor<x){
            printf("%d ", a->valor);
            imprimeAte(a->dir, x);
            }
    }
}

int main(){
    
    return 0;
}