#define NV 10 // vertex number
#define NEd 10 // numero de arestas
#define NE 0

typedef struct edgeV {
    int dest;
    int cost;
} EdgeV;

typedef struct {
    int vertices [NV + 1];
    EdgeV edges [NEd];
} GraphVect;

void listToVect (Graph go, GraphVect *gd);
void vectToList(GraphVect *go, Graph gd);
int edgeWVect(GraphVect *g, int o, int d, int *w);
int outdegreeVect(GraphVect *g, int v);
int indegreeVect(GraphVect *g, int v);