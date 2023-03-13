#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// retorna 1 se é vogal e 0 se é consoante
int eVogal(char letter) {
  if (letter == '\n') {
    return 2;
  }
  char vogais[] = "AEIOUYaeiouy";
  for (int j = 0; j < (int) strlen(vogais); j++) {
    if (letter == vogais[j]) {
      return 1;
    }
  }
  return 0;
}

int main() {
   
  int N;
  if (scanf("%d", &N) != 1) return 1;
  getchar();

  char row[1001];
  int atual = 0, posterior = 0;
  char *word;

  int correct = 1; // 1 se é alternada, 0 se não é alternada
  int palavras_certas = 0;
  int arrayOutput[100];

  // linhas
  for (int i = 0; i < N; i++) {
    if (fgets(row, 1001, stdin) == 0) return 1;

    word = strtok(row, " ");

    while (word != NULL) {
      // int size = strlen(word);
      for (int j = 0; j < ((int) strlen(word)) - 1; j++) {
        atual = eVogal(word[j]);
        posterior = eVogal(word[j + 1]);
        if (posterior == 2) {
          break;
        }
        if ((atual == 1 && posterior == 0) || (atual == 0 && posterior == 1)) {
          correct = 1;
        } else if ((atual == 0 && posterior == 0) || (atual == 1 && posterior == 1)){
          correct = 0;
          break;
        }
      }
      if (correct == 1) {
        palavras_certas++;
      } 
      word = strtok(NULL, " ");
    }
     
    arrayOutput[i] = palavras_certas;
    palavras_certas = 0;
  }


  for (int p = 0; p < N;p++) {
    printf("%d\n",arrayOutput[p]);
  }
  
  return 0;

}
