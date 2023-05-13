#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct lligada {
int valor;
struct lligada *prox;
} *LInt;


/* Questão 1 */
int length(LInt lista) {
  int count = 0;

  while (lista != NULL) {
    count++;
    lista = lista->prox;
  }

  printf("Linked list size: ");
  return count;
}

/* Questão 2 */
void freeL(LInt l) {
  LInt list;

	while(l != NULL){
		list = l->prox;
		free(l);
		l = list;
	}
}

/* Questão 3 */
void imprimeL (LInt lista) {
  printf("%d ",lista->valor);
  do {
    lista = lista->prox;
    printf("%d ", lista->valor);
  } while (lista->prox != NULL);

  printf("\n");
}

/* Questão 4 */
/*
  lista = 1 2 3 4 5 NULL
  
  prox = 2 3 4 5 NULL
  lista = 1 NULL
  {
    LInt temp = 3 4 5 NULL
    prox = 2 1 NULL
    lista = 2 1 NULL
    prox = 3 4 5 NULL
  } 
  ....
  lista = 5 4 3 2 1 NULL
*/
LInt reverseL (LInt lista) {
  LInt prox = lista->prox;
  lista->prox = NULL;
  while (prox) {
    LInt aux = prox->prox;
    prox->prox = lista;
    lista = prox;
    prox = aux;
  }

  return lista;
}


/* Questão 5 */
void insertOrd (LInt * lista, int n) {
  LInt nova = malloc(sizeof(LInt)); 
  nova->prox = NULL;
  nova->valor = n;
  while (lista != NULL && (*lista)->valor < n) {
    lista = &((*lista)->valor);
  }

  nova->prox = *lista;
  lista = &nova;
}


/* Questão 6 */
int removeOneOrd (LInt * lista, int n) {
  int res = 1;
  LInt ant;
  for (;*lista && (*lista)->valor != n; ant = *lista, lista = &((*lista)->prox));
  if (!(*lista)) return 1;
  if (ant) ant->prox = (*lista)->prox;
  return 0;
}


/* Questão 7 */
void merge (LInt *r, LInt a, LInt b) {
  
  while (a != NULL || b != NULL) {
    if ((a != NULL && b != NULL && a->valor < b->valor) || b == NULL) {
      *r = a;
      a = a->prox;
    } else {
      *r = b;
      b = b->prox;
    }

    r = &( (*r)->prox);
  }

  *r = NULL;
}


/* Questão 8 */
void splitQS (LInt l, int x, LInt *mx, LInt *Mx) {
  while (l !=  NULL) {
    if (l->valor < x) {
      *mx = l;
      mx = &( (*mx)->prox);  
    } else {
      *Mx = l;
      Mx = &( (*Mx)->prox);
    }
    l = l->prox;
  }

  *mx = NULL;
  *Mx = NULL;
}


/* Questão 9 */
LInt parteAmeio (LInt *l) {
  int meio = length(l)/2;

  if (meio == 0) return NULL;

  LInt y = (*l);
  LInt prev = NULL;
  for (int i = 0; i < meio; i++) {
      prev = (*l);
      (*l) = (*l)->prox;
  }
  prev->prox = NULL;
  return y;
}


/* Questão 10 */
int removeAll(LInt *l, int x) {
  int rem = 0;
  LInt prev = NULL;
  while (*l) {
    if ((*l)->valor == x) {
      if (!prev) (*l) = (*l)->prox;
      else prev->prox = (*l)->prox;
      rem++;
    } else {
      prev = *l;
      *l = &((*l)->prox);
    }
  }
  return rem;
}



/* Auxiliary functions */
LInt getLInt(int len, int lnum) {
    lnum++;
    if(len == 0) return NULL;
    LInt new = malloc(sizeof(struct lligada));
    printf("Insert a value for element %d: ",lnum);
    int num;
    scanf("%d",&num);
    new->valor = num;
    new->prox = getLInt(len - 1, lnum);
    return new;
}

void printLInt(LInt l) {
    if(l == NULL) putchar('\n');
    else {
        printf("%d ",l->valor);
        printLInt(l->prox);
    }
}


int main() {
  int option;
  printf("Question number: ");
  scanf("%d",&option);
  LInt lista, lista2, lista3;

  while (getchar() != '\n');
  switch (option) {
    case 1:
      lista = getLInt(5, 0);
      printLInt(lista);
      int a = length(lista);
      printf("%d\n",a);
      break; 
    case 2:
      lista = getLInt(5, 0);
      printLInt(lista);
      printf("%d\n",length(lista));
      freeL(lista);
      printLInt(lista);
      printf("%d\n",length(lista));
      break;
    case 3:
      lista = getLInt(5, 0);
      imprimeL(lista);
      break;
  }

  return 0;
}
