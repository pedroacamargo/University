#include <stdio.h>

typedef struct slist {
    int valor;
    struct slist * prox;
} * LInt;

typedef LInt Stack;

typedef struct {
LInt inicio,fim;
} Queue;

LInt newLInt (int x, LInt xs) {
    LInt r = malloc (sizeof(struct slist));
    if (r!=NULL) {
        r->valor = x; r->prox = xs;
    }
    return r;
}

/* Questão 1 */
void initStack (Stack *s) {
    (*s)->valor = 0;
    (*s)->prox = NULL;
}

int SisEmpty (Stack s) {
    return !(s);
}

int push (Stack *s, int x) {
    int r = 0;
    int add = newLInt(x, *s);
    if (add) *s = add;
    else r = 1;

    return r;
}

int pop (Stack *s, int *x) {
    int r = 0;
    if (!SisEmpty(s)) {
        LInt ant = *s;
        *x = ant->valor;
        *s = (*s)->prox;
        free(ant);
    } else {
        r = 1;
    }

    return r;
}

int top (Stack s, int *x) {
    int r = 0;
    if (!SisEmpty(s)) {
        while (s->prox) {
            s = s->prox;
        }
        *x = s->valor;
    } else {
        r = 1;
    }

    return r;
}

/* Questão 2 */
void initQueue (Queue *q) {
    q->inicio = NULL;
    q->fim = NULL;
}

int QisEmpty (Queue q) {
    int r = 0;
    if (!(q.inicio && q.fim)) r = 1;
    return r;
}

int enqueue (Queue *q, int x){
    LInt new = newLInt(x, NULL);
    int r = 1;
    if(new){
        r = 0;
        if(QisEmpty(*q))
            q->inicio = q->fim = new;
        else
            q->fim = q->fim->prox = new;
    }

    return r;
}

int dequeue (Queue *q, int *x){
    int r = 1;
    if(q->inicio){
        LInt temp = q->inicio;
        r = 0;
        *x = q->inicio->valor;
        if(q->inicio == q->fim)
            q->inicio = q->fim = NULL;
        else
            q->inicio = q->inicio->prox;
        free(temp);
    }

    return r;
}

/* Questão 3 */
typedef LInt QueueC;


void initQueueC (QueueC *q){
    *q = NULL;
}


int QisEmptyC (QueueC q){
    return (q==NULL);
}


int enqueueC (QueueC *q, int x){
    int r = 1;
    LInt new = newLInt(x, NULL);
    if(new){
        r = 0;
        if(QisEmptyC(*q))
            (*q)->prox = new->prox = new;
        else{
            new->prox = (*q)->prox;
            (*q)->prox = new;
            *q = new;
        }
    }

    return r;
}

int dequeue (QueueC *q, int *x){
    int r = 1;
    if(*q){
        r = 0;
        LInt temp = (*q)->prox;
        *x = (*q)->valor;
        if((*q)->prox == *q)
            *q = NULL;
        else
            (*q)->prox = (*q)->prox->prox;
        free(temp);
    }

    return r;
}

int frontC (QueueC *q, int *x){
    int r = 1;
    if(*q){
        r = 0;
        *x = (*q)->valor;
    }
    
    return r;
}




/* Questão 4 */
typedef struct dlist {
    int valor;
    struct dlist *ant, *prox;
} *DList;

typedef struct {
    DList back, front;
} Deque;

DList newDList (int x, DList ant, DList prox){
    DList new = malloc(sizeof(struct dlist));
    if(new!=NULL){
        new->valor = x;
        new->ant = ant;
        new->prox = prox;
    }

    return new;
}

// NULL <- [1] -> <- [2] -> <- [3] -> NULL
int pushBack (Deque *q, int x){
    DList new = newDlist(x, NULL, q->back);
    int r = 1;
    if(new!=NULL){
        r = 0;
        if(q->back==NULL)
            q->back = q->front = new;
        else
           q->back = q->back->ant = new;
    }

    return r;
}

int pushFront (Deque *q, int x){
    DList new = newDlist(x, q->front, NULL);
    int r = 1;
    if(new!=NULL){
        r = 0;
        if(q->back==NULL) // tanto faz, porque se uma é NULL a outra também é
            q->back = q->front = new;
        else
           q->front = q->front->prox = new;
    }

    return r;
}


int main(){
    
    return 0;
}