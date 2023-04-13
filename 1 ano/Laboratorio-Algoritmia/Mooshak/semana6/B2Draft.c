#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
  char * nome;
  int peso;
  int altura;
  float diffPeso;
} Cozinheiro;


void sort(Cozinheiro *cooks, int N) {
    Cozinheiro aux;
    int diffPeso1 = 0;
    int diffPeso2 = 0;
    int res = 0;

    // this function section will compare the j and j + 1 elements to apply the bubble sort in the given array
    for (int i = 0; i < N-1; i++) {
        for (int j = 0; j < N-i-1; j++) {
          diffPeso1 = abs(cooks[j].peso - 90);
          diffPeso2 = abs(cooks[j+1].peso - 90);
          if (diffPeso1 != diffPeso2) res = diffPeso1 - diffPeso2;
          else if (cooks[j].altura != cooks[j+1].altura) res = cooks[j+1].altura - cooks[j].altura;
          else res = strcmp(cooks[j].nome, cooks[j+1].nome);

          if (res > 0) {
                aux = cooks[j];
                cooks[j] = cooks[j+1];
                cooks[j+1] = aux;
            }
        }
    }
}

int main() {
  int N; // NÚMERO DE COZINHEIROS
  if (scanf("%d",&N) != 1) return 1;
  Cozinheiro cozinheiros[N];
  for (int i = 0; i < N; i++) {
    float pesoIdeal = 90;
    char nome[20];
    int peso = 0, altura = 0;

    if (scanf("%s",nome) != 1) return 1;
    if (scanf("%d",&peso) != 1) return 1;
    if (scanf("%d",&altura) != 1) return 1;
    int diffPeso = fabs(pesoIdeal - peso);
    cozinheiros[i] = (Cozinheiro)  { .nome = strdup(nome), .peso = peso, .altura = altura, .diffPeso = diffPeso}; // this will add the created struct in an array cozinheiros
  } 
  
  sort(cozinheiros,N);
   
  for (int k = 0; k < N; k++) {
    printf("%s %d %d\n",cozinheiros[k].nome,cozinheiros[k].peso,cozinheiros[k].altura);
  }

  return 0;
}
