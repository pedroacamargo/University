#include <stdio.h>
#include <stdlib.h>
#include "ListasAdjacencia.h"

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

/**
 * @param peso_de_uma_aresta
 * No caso das listas de adjacência, a aresta deve ser procurada
 * na lista dos vértices adjacentes ao primeiro.
*/
int edgeW(Graph g, int o, int d, int *w) {
    EList it;
    int found = 0;

    for (it = g[0]; (it != NULL) && !found; it = it->next) {
        found = (it->dest = d);
    }

    if (found) *w = it->cost;

    return found;
}

/**
 * @param grau_de_saída
 * O grau de saída de um vértice define-se como o número de arestas que têm esse vértice como origem
*/
int outdegree(Graph g, int v) {
    int r = 0; EList it;

    for (it = g[v]; it != NULL; it = it->next) r++;

    return r;
}

/**
 * @param grau_de_entrada
 * O grau de entrada de um vértice define-se como o número de arestas que têm esse vértice como destino
*/
int indegree(Graph g, int v) {
    int r, i; EList it;

    for (i = r = 0; i < NV; i++)
        for (it = g[i]; it != NULL; it = it->next)
            if (it->dest == v) r++;

    return r;
}