#include <stdio.h>

// A -> pessoas a vigiar
// N -> numero de linhas

void elem(int array[]) {
  for(int i = 1 ;i < array[0];i++){
   for(int j = i + 1; j <= array[0]; j++){
      if(array[i] == array[j]){
         for(int k = j; k <= array[0]; k++){
            array[k] = array[k+1];
         }
         j--;
         array[0]--;
      }
    }
  }
}

void sort(int array[]) {
  int temp = 0;
  for(int i = 1; i < array[0]; i++) {
    for(int j = i + 1; j <= array[0]; j++) { 
      if(array[i] > array[j]) {
        temp = array[i];
        array[i] = array[j];
        array[j] = temp;
      }
    }
  }
}

int main() {
  
  int A = 0, N = 0;

  if (scanf("%d",&A) != 1) return 1; // numero de vigias

  if (scanf("%d",&N) != 1) return 1; // linhas

  int lista[24][A];
 

  // criar um elemento no começo de todos arrays dentro de lista, para ajudar no futuro (size)
  for (int i = 0; i < 24; i++) {
    lista[i][0] = 0;
  }

  // codigo do agente | hora de chegada | hora de partida
  
  for (int i = 0; i < N; i++) {
    int agente = 0;
    int horaChegada = 0;
    int horaPartida = 0;
    
    if (scanf("%d",&agente) != 1) return 1;

    if (scanf("%d",&horaChegada) != 1) return 1;

    if (scanf("%d",&horaPartida) != 1) return 1;
    
    for (int hora = horaChegada; hora <= horaPartida; hora++) {
      int index = lista[hora][0];
      lista[hora][index + 1] = agente;
      lista[hora][0]++;
    }
  }
  
  for (int h = 0; h < 24; h++) {
    sort(lista[h]);
    elem(lista[h]);
  }

  for (int i = 0; i < 24; i++) {
    printf("%d ",i);
    for (int j = 1; j <= lista[i][0]; j++) {
      if ( j == lista[i][0]) {
        printf("%d",lista[i][j]); // para na obugar no mooshak (espaço no fim)
      } else {
        printf("%d ",lista[i][j]);
      }
    }
    printf("\n");
  }

  return 0;
}
