#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// primeiro conjunto de x notas que não se repete
// output deve ser o índice da primeira letra do conjunto

yint main() {
  int N = 0;
  if (scanf("%d",&N) != 1) return 1;

  int tamanhoConjunto = 0;
  char conjunto[1001];
  int indexTotal = 0;
  int indexArray = 0;
  int arrayFinal[100];
  int j = 0;
  int res = 0;

  for (int i = 0; i < N; i++) {
    
    if (scanf("%d", &tamanhoConjunto) != 1) return 1;
    getchar();

    int tamanhoAux = tamanhoConjunto;

    if (fgets(conjunto,1001,stdin) == 0) return 1;
    
    while ( j < (int) strlen(conjunto) - 1) { 
      for (int k = 1; k < tamanhoConjunto; k++) {
        if (conjunto[j] == conjunto[j + k]){
          res = indexTotal;
        }
      }

      if (tamanhoConjunto == 1) {
        tamanhoConjunto = tamanhoAux;
        indexTotal += tamanhoConjunto;
        arrayFinal[indexArray] = res;
        indexArray++;
      }
      tamanhoConjunto--;
      j++;
    }
    indexTotal = 0;
    indexArray = 0;
    res = 0;
    j = 0;
  }

  for (int x = 0; x < N;x++) {
    printf("%d\n",arrayFinal[x]);
  }

  return 0;
}
