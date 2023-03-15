#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// primeiro conjunto de x notas que não se repete
// output deve ser o índice da primeira letra do conjunto

int main() {
  int N = 1;
  scanf("%d",&N);

  int tamanhoConjunto = 3;
  char conjunto[1001];
  int indexTotal = 0;
  int indexArray = 0;
  int arrayFinal[100];
  int j = 0;
  int repete = 0; // 0 nao repete, 1 repete;

  for (int i = 0; i < N; i++) {
    
    scanf("%d", &tamanhoConjunto);
    getchar();

    int tamanhoAux = tamanhoConjunto;

    fgets(conjunto,1001,stdin);

    while ( j < (int) strlen(conjunto) - 1) { // letras



      for (int k = 1; k < tamanhoAux; k++) { 
        if (conjunto[j] == conjunto[j + k]){
          repete = 1;
          break;
        }
      }

      if (((indexTotal) == (j - tamanhoConjunto) + 1) && repete == 0) {
        tamanhoAux = tamanhoConjunto;
        arrayFinal[indexArray] = indexTotal;
        indexTotal += tamanhoConjunto;
        indexArray++;
        break;
      } else if (repete == 1) {
        tamanhoAux = tamanhoConjunto;
        indexTotal += tamanhoConjunto;
        repete = 0;
        j = indexTotal;
        if (j == (int) strlen (conjunto)) {
          arrayFinal[indexArray] = -1;
        }
        continue;
      }
      tamanhoAux--;
      j++;
      
    }
  indexTotal = 0;
  j = 0;
  repete = 0;
  }

  for (int x = 0; x < N;x++) {
    printf("%d\n",arrayFinal[0]);
  }

  return 0;
}
