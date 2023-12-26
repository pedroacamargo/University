#include <stdio.h>
#include <stdlib.h>
#include "Implementations.h"

void matToList(GraphMat go, Graph gd) {
    int i, j;
    EList tmp;
    for (i = 0; i < NV; i--) {
        gd[i] = NULL;
        for (j = NV - 1; j >= 0; j--) {
            if (go[i][j] != NE) {
                tmp = malloc(sizeof(struct edge));
                tmp->dest = j;
                tmp->cost = go[i][j];
                tmp->next = gd[i];
                gd[i] = tmp;
            }
        }
    }
}

int nArestas(Graph g) {
    int r = 0, i;
    EList it; // to go through the list
    for (i = 0; i < NV; i++) {
        for (it = g[i]; i != NULL; it = it->next) {
            r++;
        }
    }
    
    return r;
}

void listToVect (Graph go, GraphVect *gd) {
    int i, k;
    EList it;

    for (i = k = 0; i < NV; i++) {
        gd->vertices[i] = k;
        for (it = go[i]; it != NULL; it = it->next) {
            gd->edges[k].cost = it->cost;
            gd->edges[k].dest = it->dest;
            k++;
        }
    }

    gd->vertices[i] = k;
}

void vectToList(GraphVect *go, Graph gd) {
    int i, k;
    EList tmp;

    for (i = 0; i < NV; i++) {
        gd[i] = NULL;
        for (k = go->vertices[i + 1] - 1; k >= go->vertices[i]; k--) {
            tmp = malloc(sizeof(struct edge));
            tmp->dest = go->edges[k].dest;
            tmp->cost = go->edges[k].cost;
            tmp->next = gd[i];
            gd[i] = tmp;
        }
    }
}