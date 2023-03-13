#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int existe(char c, char array[1001]) {
  int size = strlen(array);
  for (int i = 0; i < size; i++ ) {
    if (c == array[i]) {
      return 1;
    }
  }
  return 0;
}

int main() {
  int N = 0;
  if (scanf("%d",&N) != 1) return 1;
  getchar();
  char letra;
  char array[1001];
  int index = 0;
  char arrayFinal[1001];

  for (int i = 0; i < N; i++) {

    while (scanf("%c", &letra) == 1) {
      
      if (letra == '\n') {
        break;
      }

      if (existe(letra, array) == 1) {
        arrayFinal[i] = letra;
      }

      array[index] = letra;
      index++;
    }
    // reset everything for the next loop
    index = 0; 
		memset(array,0,strlen(array));
  }
  
  for (int j = 0; j < N; j++) {
    printf("%c", arrayFinal[j]);
  }

  printf("\n");
  return 0;
}
