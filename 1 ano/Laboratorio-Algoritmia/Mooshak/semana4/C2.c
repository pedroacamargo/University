#include <stdio.h>
#include <string.h>

// checa se há letras repetidas | 1 -> repete | 0 - nao repete
int checar(char array[1001]) {
  for (int i = 0; i < (int) strlen(array); i++) {
    for (int j = i + 1; j < (int) strlen(array); j++) {
      if (array[i] == array[j]) {
        return 1;
      }
    }
  }

  return 0;
}

int main() {
  int N = 0;
  if (scanf("%d",&N) != 1) return 1;
  
  char conjunto[1001];
  int tamanhoConjunto = 0;
  int arrayRes[1001];

  for (int i = 0; i < N; i++) {
    
    if (scanf("%d", &tamanhoConjunto) != 1) return 1;
    getchar();

    char arrayConjunto[1001];
    int index = 0;
    int arrayIndex = 0;
    if (fgets(conjunto,1001,stdin) == 0) return 1;

    // j é cada letra
    for (int j = 0; j < (int) strlen(conjunto); j++) {


      arrayConjunto[index] = conjunto[j];
      index++; 
      
      int size = strlen(arrayConjunto); 

      printf("Tamanho Array -> %d \n", size);
      printf("TamanhoConjunto -> %d\n" , tamanhoConjunto);

      if (tamanhoConjunto == size) {

        printf("ENTREI AQUI");

        int res = checar(arrayConjunto);
        index = 0;
        printf("checar -> %d",res);

        if (res == 1) {
          memset(arrayConjunto,0, strlen(arrayConjunto));
        } else if (res == 0) {
          arrayRes[arrayIndex] = j - 1;
          arrayIndex++;
          memset(arrayConjunto,0, strlen(arrayConjunto));
        }


      }

      // se chegar no fim da string e sempre haver strings repetidas = -1
      if (j == ((int) strlen(conjunto) - 1)) {
        arrayRes[arrayIndex] = -1; 
        arrayIndex++;
      }
      
    } // fim das letras
  }

  for (int z = 0; z < N; z++) {
    printf("Resposta -> %d\n", arrayRes[z]);
  }

}

