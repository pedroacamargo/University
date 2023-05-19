#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/* Questão 1 */
int pesquisa (int a[], int N, int x) {
    for (int i = 0; i < N; i++) if (x == a[i]) return i;
    return -1;
}

typedef struct LInt_nodo {
int valor;
struct LInt_nodo *prox;
} *LInt;

/* Questão 2 */
void roda(LInt *l) {
    if (*l == NULL || (*l)->prox == NULL)
        return; // Empty list or only one element, no need to rotate

    LInt head = *l;
    LInt tail = *l;

    while (tail->prox != NULL) {
        tail = tail->prox;
    }

    tail->prox = head->prox;
    head->prox = NULL;
    *l = tail;
}

typedef struct ABin_nodo {
    int valor;
    struct ABin_nodo *esq, *dir;
} *ABin;

/* Questão 3 */
ABin encontrarPai(ABin raiz, ABin filho) {
    if (raiz == NULL || raiz == filho) {
        return NULL; // Não há pai para a raiz ou se o nó é a própria raiz
    }

    if (raiz->esq == filho || raiz->dir == filho) {
        return raiz; // Encontrou o pai
    }

    ABin pai = encontrarPai(raiz->esq, filho); // Procura pelo pai na subárvore esquerda
    if (pai == NULL) {
        pai = encontrarPai(raiz->dir, filho); // Se não encontrou na subárvore esquerda, procura na subárvore direita
    }

    return pai;
}

int apaga(ABin a, int n) {
    if (!a) return 0;
    
    ABin del = a;
    int tdel = 0;
    
    while (tdel != n) {
        if (!del->esq && !del->dir) {
            if (a == del) {
                free(del);
                return 1;
            }
            
            ABin pai = encontrarPai(a, del);  // Função auxiliar para encontrar o pai do nó del
            if (pai->esq == del)
                pai->esq = NULL;
            else
                pai->dir = NULL;
            
            free(del);
            tdel++;
        }
        
        if (del->esq) {
            del = del->esq;
        } else if (del->dir) {
            del = del->dir;
        }
    }

    return tdel;
}


/* Questão 4 */
// "248" -> 4 + 4 + 1 + 6
void checksum (char s[]) {
    int soma = 0;
    int size = strlen(s); // 3
    int i;
    int number;
    char indexType = ' ';
    // if size == odd i = 1
    // if size == even i = 0
    if (size % 2 == 0) {
        indexType = 'o';
    }
    else indexType = 'e';

    for (i = 0; i < size; i++) {
        if (indexType == 'o') {
            // first, we'll get the number in index i
            number = (s[i] - '0') * 2;
            if (number > 9) number = 1 + (number - 10); 
            soma += number;
            indexType = 'e';
            number = 0;
        } else {
            number = s[i] - '0';
            soma += number;
            indexType = 'o';
            number = 0;
        }
    }
    // calculate the left to reach 10 multiple
    int controlDigit = soma % 10;
    // put the controlDigit in the last ch of the string
    s[size] = controlDigit + '0';
    s[size + 1] = '\0';
}

int escolhe (int N, int valor[], int peso[], int C, int quant[]) {
    int indexMaior = 0;
    int maiorNum = 0;

    for (int i = 0; i < N; i++) {
        if (maiorNum < peso[i]) {
            maiorNum = peso[i];
            indexMaior = i;
        }
    }
    // ...
}



int main(){
    


    return 0;
}