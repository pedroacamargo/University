#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 1 = nao repete | 0 = repete
int existe(char array[1001]) {
  int size = strlen(array);
  
  for (int i = 0; i < size; i++) {
    
  }

  return 1;
}

int main() {

  int N = 0;
  if (scanf("%d", &N) != 1) return 1;

  char conjunto[1001];
  char conjuntoAux[1001];
  int tamanhoConjunto = 0;
  int j = 0;
  char arrayFinal[N];
  int indexArrayFinal = 0;

  for (int i = 0; i < N; i++) {
    if (scanf("%d",&tamanhoConjunto) != 1) return 1;

    if (fgets(conjunto,1001,stdin) == 0) return 1;

    while (j < (int) strlen(conjunto)) {
      // grupos
      for (int k = 0; k < tamanhoConjunto; k++) {
        conjuntoAux[k] = conjunto[j + k];
      }

      if (existe(conjuntoAux) == 0) {
        arrayFinal[indexArrayFinal] = j;
        indexArrayFinal++;
        break;
      }

      if (j == ((int) strlen(conjunto)) - tamanhoConjunto) { // se der errado, colocar + 1
        arrayFinal[indexArrayFinal] = -1;
        indexArrayFinal++;
        break;
      }
      j++;
    }
    j = 0;
  }

  for (int z = 0; z < N; z++) printf("%d",arrayFinal[z]);

  return 0;
}
