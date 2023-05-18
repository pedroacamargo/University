#include <stdio.h>

typedef struct lligada {
int valor;
struct lligada *prox;
} *LInt;

typedef struct nodo {
int valor;
struct nodo *esq, *dir;
} * ABin;

LInt caminho (ABin a, int x) {
    LInt t;
    if (a == NULL) return NULL;
    if (x == a->valor) {
        LInt l = malloc(sizeof(struct nodo));
        l->valor = x;
        l->prox = NULL;
        return l;
    }
    if (x < a->valor) t = caminho (a->esq,x); // f
    else t = caminho(a->dir,x);

    if (t == NULL) return NULL;
    
    LInt l = malloc(sizeof(struct nodo));
    l->valor = x;
    l->prox = NULL;
    return l;
}

int main(){
    

    
    return 0;
}