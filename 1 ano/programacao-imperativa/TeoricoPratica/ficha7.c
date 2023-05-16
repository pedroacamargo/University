#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct celula {
char *palavra;
int ocorr;
struct celula * prox;
} * Palavras;

void libertaLista (Palavras p) {
    while (p) {
        Palavras temp = p;
        p = p->prox;
        free(temp);
    }
}

int quantasP(Palavras l) {
    int cont = 0;
    while (l) {
        cont++;
        l = l->prox;
    }
    return cont;
}

void listaPal(Palavras l) {
    while (l) {
        printf("Palavra: %s | Quantidade: %d",l->palavra,l->ocorr);

        l = l->prox;
    }
}

char * ultima(Palavras l) {
    while (l) {
        if (!(l->prox)) {
            printf("%s",l->palavra);
        }
        l = l->prox;
    }
}


Palavras acrescentaInicio(Palavras l, char *p) {
    Palavras new = malloc(sizeof(struct celula));
    new->ocorr = 1;
    new->palavra = strdup(p);
    new->prox = l;
    return new;
}

Palavras acrescentaFim(Palavras l, char *p) {
    Palavras move = l;
    Palavras new = malloc(sizeof(struct celula));
    new->ocorr = 1;
    new->palavra = strdup(p);
    new->prox = NULL;

    if (l == NULL) {
        l = new;
    } else {
        while (move->prox) {
            move = move->prox;
        }
        move->prox = new;
    }
    return l;
}

Palavras acrescenta(Palavras l, char *p){
	Palavras nova = novaCelula(p, 1);
	Palavras move = l;
	Palavras anterior = l;
	
	if(l == NULL)
		l = nova;
	else {
		while(move->prox != NULL && strcmp(p, move->palavra) < 0){
			anterior = move;
			move = move->prox;
		}

		if (strcmp(p, move->palavra) == 0)
			move->ocorr++;
		else if(move->prox == NULL){
			move->prox = nova;
		} else {
			nova->prox = move;
			anterior->prox = nova;
		}

	}

	return l;
}

struct celula * maisFreq (Palavras l) {
    int max = 0;
    Palavras mais_freq = malloc(sizeof(struct celula));
    while (l) {
        if (l->ocorr > max) {
            max = l->ocorr;
            mais_freq = l;
        }
        l = l->prox;
    }
    return mais_freq;
}

int main(){
    
    return 0;
}