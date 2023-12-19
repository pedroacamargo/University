#include <stdlib.h>
#include <stdio.h>
#include "queues.h"

int main() {


    return 0;
}

/**
 * Static Array Queues
*/
void initQueue(Queue *q) {
    q->inicio = 0;
    q->tamanho = 0;
}

int enqueue(Queue *q, int value) {
    int r = 0;
    if (q->tamanho == MAX) r = 1;
    else {
        q->values[(q->inicio + q->tamanho++) % MAX] = value;
    }

    return r;
}

int dequeue(Queue *q) {
    int r = 0;

    if (q->tamanho <= 0) r = 1;
    else {
        q->inicio = (q->inicio + 1) % MAX;
        q->tamanho--;
    }

    return r;
}

/**
 * Linked Lists Queues
*/
void initQueueL(QueueL *q) {
    q->fim = q->inicio = NULL;
}

int enqueueL(QueueL *q, int value) {
    int r = 0;
    Celula *new;

    new = malloc(sizeof (Celula));
    if (new == NULL) r = 1;
    else {
        new->value = value;
        new->prox = NULL;
        q->fim->prox = new;
        q->fim = new;
        if (q->inicio == NULL) q->inicio = new;
    }
    return r;
}

int dequeueL(QueueL *q) {
    int r = 0;
    Celula *tmp;

    if (q->inicio == NULL) r = 1;
    else {
        tmp = q->inicio;
        q->inicio = q->inicio->prox;
        if (q->inicio == NULL) q->fim = NULL;
        free(tmp);
    }
    return r;
}