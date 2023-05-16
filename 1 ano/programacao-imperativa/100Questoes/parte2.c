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


/* Questão 11 */
int removeDups(LInt *l){
	int count = 0;

	for(; *l ; l = (&(*l)->prox) ){
		LInt anterior = (*l);
		LInt seguinte = (*l)->prox;
		for(; seguinte ; seguinte = anterior->prox){
			if( seguinte->valor == (*l)->valor ){
				count += 1;
				anterior->prox = seguinte->prox;
				free(seguinte);
			} else
				anterior = seguinte;
		}
	}
			
	return count;
}


/* Questão 12 */
int removeMaiorL(LInt *l) {
    int max = (*l)->valor;
    LInt prev = NULL;
    LInt maxPrev = NULL;
    LInt maxL = (*l);
    LInt list = (*l);
    for(;list; list = list->prox) {
        if(list->valor > max) {
            maxPrev = prev;
            maxL = list;
            max = list->valor;
        }
        prev = list;
    }
    if(!maxPrev) (*l) = (*l)->prox;
    else maxPrev->prox = maxL->prox;
    return max;
}


/* Questão 13 */
void init (LInt * l) {
  LInt prev = NULL;
  while ((*l)->prox != NULL) {
    prev = *l;
    l = &( (*l)->prox);
  }
  if (!prev) {
    free(*l);
    *l = NULL;
  } else {
    prev->prox = NULL;
    free(*l);
  }
}


/* Questão 14 */
void appendL (LInt * l, int x) {
    LInt new = malloc(sizeof(struct lligada));
    new->valor = x;
    new->prox = NULL;
    if(!(*l)) *l = new;
    else {
      while((*l)->prox) l = &( (*l)->prox); // While the next element of the list is != NULL, go to the next element 
        (*l)->prox = new;
    }
}


/* Questão 15 */
void concatL (LInt *a, LInt b) {
  while ((*a)->prox) {
    a = &( (*a)->prox);
  }

  (*a)->prox = b;
}


/* Questão 16 */
LInt cloneL (LInt l){
	LInt new_list;
	LInt *sitio;

	sitio = &new_list;

	while( l ){
		*sitio = malloc(sizeof(struct lligada));
		(*sitio)->valor = l->valor;
		l = l->prox;
		sitio = &( (*sitio)->prox );
	}

	*sitio = NULL;

	return new_list;
}


/* Questão 17 */
LInt cloneRev (LInt l) {
    LInt list = NULL;
    while(l) {
        LInt new = malloc(sizeof(struct lligada));
        new->valor = l->valor;
        new->prox = list;
        list = new;
        l = l->prox;
    }
    return list;
} 


/* Questão 18 */
int maximo (LInt l) {
  int maximo = l->valor;
  while (l) {
    if (l->valor > maximo) maximo = l->valor;
    l = l->prox;
  }

  return maximo;
}


/* Questão 19 */
int take (int n, LInt *l) {
  int tamanho = 0;
  while (n != 0 && *l) {
    l = &( (*l)->prox);
    n--;
    tamanho += 1;
  }
  if (!(l)) return tamanho;

  while (*l) {
    LInt temp = (*l)->prox;
    free(*l);
    *l = temp;
  }
  return tamanho;
}


/* Questão 20 */
int drop(int n, LInt *l) {
  if (!(*l)) return 0;
  int rem = 0;
  while (n > 0 && (*l)) {
    LInt temp = (*l);
    *l = (*l)->prox;
    free(temp);
    n--;
    rem++;
  }
  return rem;
}


/* Questão 21 */
LInt Nforward (LInt l, int N){
  LInt laux = l;
  int i = 0;
  while (i != N) {
    laux = laux->prox;
    i++;
  }
  return laux;
}


/* Questão 22 */
int listToArray (LInt l, int v[], int N) {
  int i = 0;
  while (l && i < N) {
    v[i] = l->valor;
    l = l->prox;
    i++;
  }
  return i;
}


/* Questão 23 */
LInt arrayToList (int v[], int N) {
  LInt head;
  LInt *r = &head;
  int i = 0;
  while (i < N) {
    *r = malloc(sizeof(LInt));
    (*r)->valor = v[i];
    r = &(*r)->prox;
  }
  *r = NULL;
  return head;
}


/* Questão 24 */
LInt somasAcL (LInt l) {
  LInt head;
  LInt *r = &head;
  int acc = 0;
  while (l) {
    acc += l->valor;
    l = l->prox;
    *r = malloc(sizeof(LInt));
    (*r)->valor = acc;
    r = &(*r)->prox;
  }
  *r = NULL;
  return head;
}


/* Questão 25 */
void remreps (LInt l) {
  while(l->prox) {
    if(l->prox->valor == l->valor) {
        LInt temp = l->prox;
        l->prox = temp->prox;
        free(temp);
    }
    else l = l->prox;
  }
}


/* Questão 26 */
LInt rotateL(LInt l){
	
	if(!l || !(l->prox))
		return l;
	
	LInt aux = l;
	LInt head = l->prox;

	while(aux->prox)
		aux = aux->prox;

	aux->prox = l;
	l->prox = NULL;

	return head;
}


/* Questão 27 */
LInt parte (LInt l){
  LInt head, *p = &head, *i = &l;
  int j;
  for (j = 1; *i; j++) {
    if (!(j%2)) {
      *p = *i;
      *i = (*i)->prox;
      p = &(*p)->prox;
      
    }
    else i = &(*i)->prox;
  }
  *p = NULL;
  return head;
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
