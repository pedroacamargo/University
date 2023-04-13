#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int qtdLetras(char l,char p[]) {
  int size = strlen(p);
  int acc = 0;
  for (int i = 0; i < size; i++) {
    if (l == ' ') break;
    if (l == p[i]) acc++;
  }
  return acc;
}

int pertence(char l, char p[]) {
  int size = strlen(p);
  for (int i = 0; i < size; i++) {
    if (l == p[i]) return 1;
  }
  return 0;
}

int main() {
  int N;
  if (scanf("%d",&N) != 1) return 1;

  for (int i = 0; i < N; i++) {
    int candidatos;
    char vilao[101];

    if (scanf("%d",&candidatos) != 1) return 1;
    getchar();
    if (fgets(vilao,101,stdin) == 0) return 1;

    int res[candidatos];
    int tamanho = 0;
    int index = 0;

    for (int j = 0; j < candidatos; j++) {
      char candidato[101];
      if (fgets(candidato,101,stdin) == 0) return 1; // candidato
      int size = strlen(candidato);
      for (int l = 0; l < size; l++) {
        if (pertence(candidato[l],vilao) == 1 && qtdLetras(candidato[l], candidato) <= qtdLetras(candidato[l], vilao)) {
          tamanho++;
        }
      }
      if (size == tamanho) {
        res[index] = j + 1;
        index++;
      } 
      tamanho = 0;
    }
    if (index == 0) {
      res[0] = -1;
      index = 1;
    }

    printf("%d",res[0]);
    for(int k = 1; k < index; k++) {
      printf(" %d",res[k]);
    }
    printf("\n");
  }

  return 0;
}
