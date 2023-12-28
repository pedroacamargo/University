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

/**
 * @param depth_first
 *  A pesquisa em profundidade (depth-first search) é um algoritmo de pesquisa não informada utilizado para
 *  percorrer todos os nós de uma árvore ou estrutura de dados do tipo grafo.
*/
int procura(Graph g, int o, int d) {
    int visitados[NV], i;
    for (i = 0; i < NV; i++) visitados[i] = 0;
    return procuraRec(g, o, d, visitados);
}

int procuraRec(Graph g, int o, int d, int visitados[]) {
    int found = 0;
    EList it;

    visitados[o] = 1;
    if (o == d) return 1;
    else {
        for (it = g[o]; (it != NULL) && !found; it = it->next) {
            if (!visitados[it->dest]) found = procuraRec(g, it->dest, d, visitados);
        }
    }
    return found;
}

int travessiaDF(Graph g, int o) {
    int visitados[NV], i;

    for (i = 0; i < NV; i++) visitados[i] = 0;

    return DFRec(g, o, visitados);
}

int DFRec(Graph g, int o, int visitados[]) {
    int count = 1;
    EList it;
    visitados[o] = 1;
    for (it = g[o]; it != NULL; it = it->next) {
        if (!visitados[it->dest]) count += DFRec(g, it->dest, visitados);
    }

    return count;
}