#include "graphs.h"


int inDegree (GraphL g, int j, int n) {
    return inDegree_sol(g, j, n);
}



int outDegree (GraphL g, int j) {
    return outDegree_sol(g, j);
}


int capacidadeL (GraphL g, int v, int n) {
    return  capacidadeL_sol (g, v, n);
}

int maxCap (GraphL g, int n) {
    return maxCap_sol (g, n);
}


