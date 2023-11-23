
#include "graphs.h"


int readGraphM_sol(GraphM g) {
    int i, j, n;

    printf("Número de vértices do grafo? (<=%d)\n", MAX);
    scanf("%d", &n);
    if (n > MAX) return 0; 

    printf("\nIntroduza matriz de adjacência do grafo:\n");
   
    for(i=0; i<n; i++)
       for(j=0; j<n; j++)
            scanf("%d", &g[i][j]);

    return n;
}



void printGraphM_sol(GraphM g, int n) {
    int i, j;

    for(i=0; i<n; i++) {
        for(j=0; j<n; j++) 
            printf("%d ", g[i][j]);
        printf("\n");
    }
}



void printGraphL_sol(GraphL g, int n) {
    int i;
    struct edge *p;

    for(i=0; i<n; i++) {
        printf("%d", i);
        for(p=g[i]; p; p=p->next) 
            printf(" --> (%d,%d)", p->dest, p->weight);
        printf("\n");
    }
}



// assume listas de adjacência ordenadas 
// por ordem crescente do vértice destino
void graphLtoM_sol(GraphM gm, GraphL gl, int n) {
    int i, j;
    struct edge *p;

    for (i = 0; i<n; i++) 
        for (j = 0, p = gl[i]; j<n; j++) {
            if (p && p->dest == j) {
                gm[i][j] = p->weight;
                p = p -> next;
            }
            else 
                gm[i][j] = NE;
        }
}









void graphMtoL_sol(GraphL gl, GraphM gm, int n) {
    int i, j;
    struct edge *head, *new;
    
    for (i = 0; i<n; i++) {
        head = NULL;
        for (j = n-1; j>=0; j--) 
            if (gm[i][j] != NE) {
                new = malloc(sizeof(struct edge));
                new -> dest = j;
                new -> weight = gm[i][j];
                new -> next = head;
                head = new;
            }
        gl[i] = head;
    }
}







