#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 1 = nao repete | 0 = repete
int existe(char arraybrabo[1001],int N) {
  char array[1001];
  
  for (int p = 0; p < N;p++) {
    array[p] = arraybrabo[p];  
  }
    
  int size = strlen(array);
  
  for (int i = 0; i < size; i++) {
    for (int j = 1; j < size - i; j++) {
      if (array[i] == array[j]) return 1;
    }
  }

  return 0;
}

int main() {

  int N = 1;
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
      
      int sizeAux = tamanhoConjunto;
      
      int r = existe(conjuntoAux, sizeAux);

      if (r == 1) {
        arrayFinal[indexArrayFinal] = j;
        indexArrayFinal++;
        break;
      }
      break;
      if (j == ((int) strlen(conjunto)) - tamanhoConjunto + 1) { // se der errado, colocar + 1
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
