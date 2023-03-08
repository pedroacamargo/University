#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void n1() {
  int numero = 1;
  int maior = 0;

  while (numero != 0) {

    scanf("%d", &numero);
    
    if (numero > maior) maior = numero;   

    
  }  
  
  printf("%d",maior);

}


int main() {
  n1();   

  return 0;
}
