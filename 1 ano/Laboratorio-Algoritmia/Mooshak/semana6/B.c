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

// Deve-se desconfiar dos cozinheiros demasiado magros! 
// Deve-se desconfiar dos cozinheiros demasiado gordos! 
// Não se devem contratar cozinheiros demasiado baixos!

// O peso ideal é 90kgs.
// Se dois cozinheiros tiverem o mesmo peso, ele prefere o mais alto.
// Se tiverem o mesmo peso e altura ele quer que sejam mostrados por ordem alfabética.

// #define PESO_IDEAL 90;
// printf("%.0lf",diff);

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
  } // end of input loop  
  Cozinheiro temp;
  int i = N;
    for (int p = 0; p < i; p++) {
        for (int j = 0; j < p - i - 1; j++) {
        // if weight is different between the cooks
          if (cozinheiros[j].diffPeso > cozinheiros[j+1].diffPeso) {
            temp = cozinheiros[j];
            cozinheiros[j] = cozinheiros[j + 1];
            cozinheiros[j+1] = temp;
            continue;
          }
          // if height is different between the cooks 
          if (!(cozinheiros[j].diffPeso == cozinheiros[j+1].diffPeso)) {
            if (cozinheiros[j].altura > cozinheiros[j + 1].altura) {
              temp = cozinheiros[j];
              cozinheiros[j] = cozinheiros[j + 1];
              cozinheiros[j + 1] = temp;
              continue;
            }
          }
        }
          // if (strcmp(cozinheiros[j].nome,cozinheiros[j + 1].nome) > 0) {
          //   temp = cozinheiros[j];
          //   cozinheiros[j] = cozinheiros[j + 1];
          //   cozinheiros[j + 1] = temp;
          //   continue;
          // }
    } // end of height comparison

  for (int i = 0; i < N; i++) {
    printf("%d° -> %s %d %d\n",i + 1,cozinheiros[i].nome,cozinheiros[i].peso,cozinheiros[i].altura);
  }

  return 0;
}
