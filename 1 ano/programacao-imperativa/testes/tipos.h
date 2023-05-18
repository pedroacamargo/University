typedef struct LInt_nodo {
	int valor;
	struct LInt_nodo *prox;
} *LInt;

typedef struct ABin_nodo {
	int valor;
	struct ABin_nodo *esq, *dir;
} *ABin;

int nesimo(int a[], int N, int i);

LInt removeMaiores (LInt l, int x);

LInt caminho (ABin a, int x);

void inc(char s[]) ;

int sacos (int p[], int N, int C);

LInt newLInt (int x, LInt xs);

LInt LfromArray(int v[], int N);

void dumpL (LInt l);

void freeLInt (LInt l);

ABin AfromArray(int v[], int N);

void freeABin (ABin a);