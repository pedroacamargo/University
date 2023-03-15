#include <stdio.h>
#include <string.h>


// 1 = repete | 0 = n/ repete
int existe(char letra, char array[1001]) {
  int size = strlen(array);
  for (int i = 0; i < size - 1; i++) {
    if (letra == array[i + 1]) {
      return 0;
    }
  } 
  return 0;
}




int main() {
  int N = 0;
  if (scanf("%d", &N) != 1) return 1;
  getchar();

  int tamanhoConjunto = 0;
  char conjunto[1001];
  int exist = 0;
  int indexArrayFinal = 0;
  int arrayFinal[N];
  
  for (int i = 0; i < N; i++) {
    if (scanf("%d", &tamanhoConjunto) != 1) return 1;

    if (fgets(conjunto, 1001, stdin) == 0) return 1;

    // int tamanhoAux = tamanhoConjunto;
    char conjuntoAux[1001];

    for (int j = 0; j < (int) strlen(conjunto); j += tamanhoConjunto - 1) {
      
      // criar os grupos
      for (int k = 0; k < tamanhoConjunto; k++) {
        conjuntoAux[k] = conjunto[j + k];
      }


      // ver se repete no grupo
      for (int x = 0; x < (int) strlen(conjuntoAux); x++) {
        exist = existe(conjuntoAux[x], conjuntoAux);
        if (exist == 1) break; 
      } 
      

      if (exist == 1) {
        arrayFinal[indexArrayFinal] = j;
        indexArrayFinal++;
      }

      //resets
      memset(conjuntoAux,0,strlen(conjuntoAux));
      exist = 0;
    }
  }

  printf("%d",arrayFinal[0]);



  return 0;
}
