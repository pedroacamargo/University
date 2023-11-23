
#include "graphs.h"


// assume listas de adjacência ordenadas 
// por ordem crescente do vértice destino
int inDegree_sol (GraphL g, int j, int n) {
    int i, k = 0;
    struct edge *p;
    
    for (i=0; i<n; i++) {
        for (p = g[i]; p && p->dest < j ; p=p->next) ;
        if (p && p->dest == j) k++;
    }
    
    return k;
}







int outDegree_sol (GraphL g, int i) {
    int n = 0;
    struct edge *p;
    
    for (p = g[i]; p ; p=p->next) n++;
    
    return n;
}












int capacidadeL_sol (GraphL g, int v, int n) {
    int i, k = 0;
    struct edge *p;
    
    for (i=0; i<n; i++) 
        if (i==v)     
            for (p = g[i]; p; p = p->next) 
                { if (p->dest != i) k -= p->weight; } 
        else
            for (p = g[i]; p && p->dest <= v ; p = p->next) 
                { if (p->dest == v) k += p->weight; }

    return k;
}



int maxCap_sol (GraphL g, int n) {
    int i, k = 0;
    int caps[n];
    struct edge *p;
    
    for (i=0; i<n; i++) 
        caps[i] = 0;

    for (i=0; i<n; i++) 
        for (p = g[i]; p; p=p->next) {
            caps[i] -= p-> weight;
            caps[p->dest] += p->weight;
        }   

    k = 0;
    for (i=1; i<n; i++) 
        if (caps[i] > caps[k]) k = i;

    return k;
}


