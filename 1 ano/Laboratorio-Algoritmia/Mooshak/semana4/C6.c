#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// ver em cada grupo se existe algum char repetido
int ver(char conjunto[],int conjuntoTamanho) {
  for (int i = 0; i < conjuntoTamanho;i++) {
    for (int j = i + 1; j < conjuntoTamanho; j++) {
      if (conjunto[i] == conjunto[j]) return 1;
    }
  }

  return 0;
}

int elem(char conjunto[], int conjuntoTamanho) {
  
  for (int i = 0; i < (int) strlen(conjunto) - conjuntoTamanho + 1; i++) {

    if (!ver(conjunto + i, conjuntoTamanho)) return i;
  }


  return -1;
}

int main() {
  int N = 0;
  int conjuntoTamanho = 0;
  char conjunto[1001];

  // N = NUMERO DE LINHAS
  if (scanf("%d",&N) != 1) return 1;

  char arrayFinal[N];

  // LOOP PARA CADA NUMERO DE LINHAS
  for (int i = 0; i < N; i++) {
    if (scanf("%d", &conjuntoTamanho) != 1) return 1;
    
    if (scanf("%s",conjunto) != 1) return 1;

    // ARRAY FINAL -> PRINTAR AS RESPOSTAS
    arrayFinal[i] = elem(conjunto, conjuntoTamanho);

  }
  for (int i = 0; i < N; i++) printf("%d\n",arrayFinal[i]);

  return 0;
}
