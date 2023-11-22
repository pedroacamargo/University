 #include <stdio.h>
#include <stdlib.h>

#define NE 0

#define MAX 100

typedef int WEIGHT;

struct edge {
  int dest;
  WEIGHT weight;
  struct edge *next;
};

typedef struct edge *GraphL[MAX];

typedef WEIGHT GraphM[MAX][MAX];


int readGraphM(GraphM);
void printGraphM(GraphM, int);
void printGraphL(GraphL, int);
void graphLtoM(GraphM, GraphL, int);
void graphMtoL(GraphL, GraphM, int);

int inDegree (GraphL, int, int);
int outDegree (GraphL, int);
int capacidadeL (GraphL g, int v, int n);
int maxCap (GraphL g, int n);


int readGraphM_sol(GraphM);
void printGraphM_sol(GraphM, int);
void printGraphL_sol(GraphL, int);
void graphLtoM_sol(GraphM, GraphL, int);
void graphMtoL_sol(GraphL, GraphM, int);

int inDegree_sol (GraphL, int, int);
int outDegree_sol (GraphL, int);
int capacidadeL_sol (GraphL g, int v, int n);
int maxCap_sol (GraphL g, int n);

