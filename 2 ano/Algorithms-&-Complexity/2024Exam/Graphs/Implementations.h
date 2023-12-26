#define NV 10 // vertex number
#define NEd 10 // numero de arestas
#define NE 0

// with matrices
typedef int GraphMat[NV][NV];
GraphMat g1 = {{NE, 2 , 7 , NE, NE, NE},
               {NE, NE, NE, 1 , NE, NE},
               {NE, NE, NE, NE, NE, 1},
               { 5 , NE, NE, NE, 8 , NE},
               { 3 , NE, NE, NE, NE, NE},
               { 4 , NE, NE, 3 , 2 , NE}};


typedef struct edge {
    int dest;
    int cost;
    struct edge *next;
} *EList;
typedef EList Graph[NV];



// Vetor de Adjacências
typedef struct edgeV {
    int dest;
    int cost;
} EdgeV;

typedef struct {
    int vertices [NV + 1];
    EdgeV edges [NEd];
} GraphVect;