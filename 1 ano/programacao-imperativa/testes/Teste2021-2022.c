#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "tipos.h"


/* Questão 1 */
int nesimo(int a[], int N, int i) {
    for (int b = 0; b < N; b++) {
        for (int j = b + 1; j < N; j++) {
            if (a[b] > a[j]) {
                int temp = a[j];
                a[j] = a[b];
                a[b] = temp;
            }
        }
    }
    return a[i - 1];
}




/* Questão 2 */
LInt removeMaiores(LInt l, int x) {
    LInt current = l;
    LInt prev = NULL;
    LInt temp;

    while (current != NULL) {
        if (current->valor > x) {
            if (prev == NULL) {
                temp = current;
                current = current->prox;
                l = current;
                free(temp);
            } else {
                temp = current;
                current = current->prox;
                prev->prox = current;
                free(temp);
            }
        } else {
            prev = current;
            current = current->prox;
        }
    }

    return l;
}

/* Questão 3 */
LInt caminho(ABin a, int x){
    LInt l = NULL;
    if(a == NULL){
        return NULL;
    }
    if(a->valor == x){
        l = malloc(sizeof(struct LInt_nodo));
        l->valor = x;
        l->prox = NULL;
        return l;
    }
    if(a->valor > x){
        l = caminho(a->esq, x);
    }
    else{
        l = caminho(a->dir, x);
    }
    if(l != NULL){
        LInt aux = malloc(sizeof(struct LInt_nodo));
        aux->valor = a->valor;
        aux->prox = l;
        l = aux;
    }
    return l;
}


/* Questão 4 */
void inc(char s[]) {
    int i = 0;
    int carry = 1; // carry é inicializado como 1 para incrementar o último dígito

    // Percorre a string da direita para a esquerda
    for (i = strlen(s) - 1; i >= 0; i--) {
        int digit = s[i] - '0'; // Converte o caractere para um dígito inteiro
        int sum = digit + carry;

        // Verifica se há carry
        if (sum >= 10) {
            carry = 1;
            sum -= 10;
        } else {
            carry = 0;
        }

        // Atualiza o dígito na string
        s[i] = sum + '0';
    }

    // Se ainda houver carry após o loop, adiciona um dígito '1' no início da string
    if (carry == 1) {
        memmove(s + 1, s, strlen(s) + 1); // Move os caracteres para a direita
        s[0] = '1';
    }
}


/* Questão 5 */
int sacos(int p[], int N, int C) {
    int soma = 0;
    int sacos = 0;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (p[i] > p[j]) {
                int temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    for(int i = 0; i < N; i++) {
        soma += p[i] + p[i + 1];
        if(soma <= C) {
            p[i] = 0;
            p[i + 1] = 0;
        }
        else{
            soma = 0;
            i--;
            sacos++;
        }
    }

    return sacos;

}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------
                                                                            /*   TESTES    */


LInt newLInt (int x, LInt xs){
	LInt r = malloc (sizeof (struct LInt_nodo));
	r->valor = x; r->prox = xs;
	return r;
}


LInt LfromArray(int v[], int N){
	int i;
	LInt r = NULL;
	for (i=N-1; i>=0; i--)
		r = newLInt (v[i],r);
	return r;
}



void dumpL (LInt l){
	while (l!= NULL) {
		printf ("%d ", l->valor);
		l = l->prox;
	}
	putchar ('\n');
}

void freeLInt (LInt l) {
	LInt aux;
	while (l!=NULL) {
		aux = l; l=l->prox;free (aux);
	}
}

void freeABin (ABin a){
	if (a!= NULL) {
		freeABin (a->esq);freeABin (a->dir); free (a);
	}
}


ABin newABin (int r, ABin e, ABin d){
	ABin x = malloc (sizeof(struct ABin_nodo));
	x->valor = r;
	x->esq = e; x->dir = d; 
	return x;
}


ABin AfromArray(int v[], int N){
	ABin r;
	int m;
	if (N<=0) r = NULL;
	else {
		m = N/2;
		r = newABin (v[m],AfromArray (v,m),
			              AfromArray (v+m+1,N-m-1));
	}
	return r;
}


int main (){

	//testes para a questão 1
	printf ("\nQuestao 1\n----------\n");

	int q1 [20] = {11,12,3,17,19,15,18,2,7,1,20,8,14,13,16,6,5,9,10,4};

	printf ("i=1: %d\n", nesimo(q1,20,1));
	printf ("i=10: %d\n", nesimo(q1,20,10));
	printf ("i=20: %d\n", nesimo(q1,20,20));

    // testes para a questão 2: nesta altura q1 está ordenado!
	printf ("\nQuestao 2\n----------\n");

	LInt q2 = LfromArray (q1,20);

	dumpL (q2);
	q2 = removeMaiores(q2,15);
	printf ("removeMaiores 15: "); dumpL (q2);
	q2 = removeMaiores(q2,5);
	printf ("removeMaiores 5: "); dumpL (q2);
	q2 = removeMaiores(q2,-5);
	printf ("removeMaiores -5: "); dumpL (q2);


    // testes para a questão 3: q1 ainda está ordenado, q2 está a NULL
	printf ("\nQuestao 3\n----------\n");

    ABin q3 = AfromArray (q1,20);

    q2 = caminho(q3,10); 
    printf ("caminho até 10: "); dumpL (q2);
    freeLInt (q2);
    q2 = caminho(q3,5); 
    printf ("caminho até 5: "); dumpL (q2);
    freeLInt (q2);

    // testes para a questão 4
	printf ("\nQuestao 4\n----------\n");

	char s1[10] = "12345678",
	     s2[10] = "12345999",
	     s3[10] = "99999999";

	printf ("%s %s %s\n", s1, s2, s3);
	inc(s1); inc(s2); inc(s3);
	printf ("%s %s %s\n", s1, s2, s3);


    // testes para a questão 5
	printf ("\nQuestao 5\n----------\n");

	int ex1 [ 9] = {3,6,2,1,5,7,2,4,1},   N1 =  9, C1 = 10,
	    ex2 [ 7] = {3,3,3,3,5,5,11},      N2 =  7, C2 = 11,
	    ex3 [10] = {6,6,6,6,6,6,6,6,6,6}, N3 = 10, C3 = 10;

	printf ("ex1 = %d\n", sacos(ex1,N1,C1));
	printf ("ex2 = %d\n", sacos(ex2,N2,C2));
	printf ("ex3 = %d\n", sacos(ex3,N3,C3));




	return 0;
}