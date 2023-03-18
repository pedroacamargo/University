#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void n1() {
  int numero = 1;
  int maior = 0;

  while (numero % 10 != 0) {

    scanf("%d", &numero);
    
    if (numero > maior) maior = numero;   
    
  }  
  
  printf("%d",maior);


}

void n2() {
  int num = 0;
  int acc = 0;
  int soma = 0;
  int media = 0;
  while (scanf("%d", &num) == 1) {
    if (num % 10 != 0) {
      break;
    }
    acc++;
    
    soma += num;
  }

  media = soma / acc;
  printf("%d", media);
}

void n3() {
  int maior = 0;
  int maior2 = 0;
  int num = 0;
  while (scanf("%d",&num) == 1) {
    if (num % 10 != 0) {
      break;
    }

    if (num > maior) {
      maior2 = maior;
      maior = num;
    } else if (num > maior2 && num < maior) {
      maior2 = num;
    }
  }
  
  printf("Maior2: %d",maior2);

}

void n4(unsigned int n) {
  int acc = 0;

  while (n != 0) {
    if (n % 2 == 1) {
      acc++;
    } 
    n /= 2;
  }

  printf("%d",acc);
}

void n5(unsigned int n) {
  int acc = 0;

  while (n != 0) {
    if (n % 2 == 0) {
      acc++;
    }
    n /= 2;
  }

  printf("%d", acc);
}

void n6(unsigned int n) {
  int acc = 0;

  while (n != 0) {
    acc++;
    n /= 10;
  }

  printf("%d", acc);
}

char *n7( char s1[], char s2[]) {
  char newString[strlen(s1) + strlen(s2)];
  int i, j; 
  for (i = 0; i < (int) strlen(s1); i++) {
    newString[i] = s1[i];
  }

  for (j = 0; j < (int) strlen(s2); j++) {
    newString[i + j] = s2[j];
  }

  newString[strlen(s1) + strlen(s2)] = '\0';

  printf("%s\n",newString);
  return s1; 

}

char *strcpyMy (char *dest, char source[]) {
  for (int i = 0; i < (int) strlen(source); i++) {
    dest[i] = source[i];
  }

  return dest;
}


int main() {
  // n1();   
  // n2();
  // n3();
  // n4(15);
  // n5(16);
  // n6(1990);
  //*n7("ola", "tudo bem");
  char array[] = "Olá";
  char *pArray = &array[0];
  char *a = strcpyMy(array, "ola tudo bem");
  printf("%s",a);
  return 0;
}
