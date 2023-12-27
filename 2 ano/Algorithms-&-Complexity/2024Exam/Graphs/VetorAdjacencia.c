#include <stdio.h>
#include <stdlib.h>
#include "VetorAdjacencias.h"
#include "ListasAdjacencia.h"

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

/**
 * @param peso_de_uma_aresta
*/
int edgeWVect(GraphVect *g, int o, int d, int *w) {
    int k;
    int found = 0;

    for (k = g->vertices[o]; (k < g->vertices[o + 1]) && !found; k++) {
        found = (g->edges[k].dest == d);
    }

    if (found) *w = g->edges[k].cost;

    return found;
}

/**
 * @param grau_de_entrada
 * O grau de entrada de um vértice define-se como o número de arestas que têm esse vértice como destino
*/
int indegreeVect(GraphVect *g, int v) {
    int r, i; EList it;

    for (i = r = 0; i < NV; i++) {
        if (g->edges[i].dest == v) r++;
    }

    return r;
}

/**
 * @param grau_de_saída
 * O grau de saída de um vértice define-se como o número de arestas que têm esse vértice como origem
*/
int outdegreeVect(GraphVect *g, int v) {
    return (g->vertices[v + 1] - g->vertices[v]);
}