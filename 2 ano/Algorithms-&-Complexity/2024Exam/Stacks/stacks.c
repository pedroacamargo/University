#include <stdio.h>
#include <stdlib.h>
#include "stacks.h"

int main() {
    Stack s;
    initStack(&s);

    return 0;
}

/**
 * @def Static Arrays
*/
void initStack(Stack *s) {
    s->sp = 0;
    printf("Stack initialized.\n");
}

int push(Stack *s, int value) {
    int r = 0;

    if (s->sp >= MAX) r = 1;
    else s->values[s->sp++] = value;
    return r;
}

int pop(Stack *s) {
    int r = 0;

    if (s->sp <= 0) r = 1;
    else --s->sp;

    return r;
}


/**
 * @def Linked Lists Stacks
*/
void initStackL(StackL *s) {
    *s = NULL;
}

int pushL(StackL *s, int value) {
    int r = 0;

    Celula *new;

    new = malloc(sizeof (Celula));
    if (new == NULL) r = 1;
    else {
        new->value = value;
        new->prox = *s;
        *s = new;
    }

    return r;
}

int popL(StackL *s) {
    int r = 0;
    Celula *tmp;

    if (*s == NULL) r = 1;
    else {
        tmp = s;
        *s = (*s)->prox;
        free(tmp);
    }

    return r;
}


/**
 * @def Dinamic Arrays Stacks
*/
void initStackD(StackD *s, int n) {
    s->size = n;
    s->sp = 0;
    s->values = malloc(n*sizeof(int));
}

int pushD(StackD *s, int value) {
    int r = 0;
    if (s->sp == s->size) {
        r = doubleArray(s);
    } else s->values[s->sp++] = value;

    return r;
}

int popD(StackD *s) {
    int r = 0;
    if (s->sp == 0) r = 1;
    else s->sp--;
    return r;
}

int doubleArray(StackD *s) {
    int r = 0;
    s->size *= 2;
    s->values = realloc(s->values, s->size);
    return r;
}