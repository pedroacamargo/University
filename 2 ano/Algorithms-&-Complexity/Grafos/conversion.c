#include "graphs.h"



int readGraphM(GraphM g) {

    
    return readGraphM_sol(g);
}



void printGraphM(GraphM g, int n) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%d ", g[i][j]);
        }
        printf("\n");
    }
}



void printGraphL(GraphL g, int n) {

    
    
    printGraphL_sol(g, n);
}



void graphLtoM(GraphM gm, GraphL gl, int n) {
    graphLtoM_sol(gm, gl, n);
}



void graphMtoL(GraphL gl, GraphM gm, int n) {

    
    
    graphMtoL_sol(gl, gm, n);
}


