#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"
#include "ListasAdjacencia.h"

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


/**
 * @param peso_de_uma_aresta
 * No caso das matrizes esta função executará em tempo constante pois 
 * temos acesso directo à correspondente posição da matriz
*/
int edgeWMat(GraphMat g, int i, int j, int *w) {
    *w = g[i][j];
    return (*w != NE);
}

/**
 * @param grau_de_entrada
 * O grau de entrada de um vértice define-se como o número de arestas que têm esse vértice como destino
*/
int indegreeMat(GraphMat g, int v) {
    int i, r;
    
    for (i = r = 0; i < NV; i++) {
        if (g[i][v] != NE) r++;
    }

    return r;
}

/**
 * @param grau_de_saída
 * O grau de saída de um vértice define-se como o número de arestas que têm esse vértice como origem
*/
int outdegreeMat(GraphMat g, int v) {
    int i, r;

    for (i = r = 0; i < NV; i++) {
        if (g[v][i] != NE) r++;
    }

    return r;
}