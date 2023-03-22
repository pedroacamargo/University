#include <stdio.h>

struct Vigilancia {
  int agente;
  int chegada;
  int saida;
};

void sort(int array[]) {
  int temp = 0;
  for(int i = 1; i < array[0]; i++) {
    for(int j = i + 1; j < array[0]; j++) { 
      if(array[i] > array[j]) {
        temp = array[i];
        array[i] = array[j];
        array[j] = temp;
      }
    }
  }
}

int main() {
  
  int N = 0; // linhas
  int A = 0; // agentes
  struct Vigilancia vigia;
  if (scanf("%d",&N) != 1) return 1; // quantidade de horarios

  if (scanf("%d",&A) != 1) return 1; // quantidade de agentes
  
  int horarios[24][A];

  for (int i = 0; i < 24; i++) {
    horarios[i][0] = 1;
  } // o primeiro index do array horarios, será o size de subarray


  for (int i = 0; i < A; i++) {

    if (scanf("%d", &vigia.agente) != 1) return 1;
    if (scanf("%d", &vigia.chegada) != 1) return 1;
    if (scanf("%d", &vigia.saida) != 1) return 1;


    for (int index = vigia.chegada; index <= vigia.saida; index++) {
      int sizeArray = horarios[index][0];
      
      // Checar se o agente já está escalado em determinada hora (Não repetir números)
      for (int j = 1; j <= sizeArray; j++) {

        // se o vigia já existir no subarray, ignorar tudo.
        if (vigia.agente == horarios[index][j]) break;
        
        // aumentar o size do subarray e adicionar o agente
        if (j == sizeArray) {
          horarios[index][sizeArray] = vigia.agente;
          horarios[index][0]++;
        } 
      }
    }
  }

  for (int i = 0; i < 24; i++) sort(horarios[i]);
  
  for (int i = 0; i < 24; i++) {
    int sizeArray = horarios[i][0];
    if (sizeArray > 2) {
      printf("%d",i);
      for (int j = 1; j < sizeArray; j++) printf(" %d",horarios[i][j]);
      printf("\n");
    }
  }
  printf("\n");

  return 0;
}
