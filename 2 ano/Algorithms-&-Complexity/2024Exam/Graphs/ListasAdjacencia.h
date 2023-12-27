#define NV 10

typedef struct edge {
    int dest;
    int cost;
    struct edge *next;
} *EList;
typedef EList Graph[NV];

int nArestas(Graph g);
int edgeW(Graph g, int o, int d, int *w);
int outdegree(Graph g, int v);
int indegree(Graph g, int v);