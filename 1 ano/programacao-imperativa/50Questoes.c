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

void *n7( char s1[], char s2[]) {
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

// when doing subtraction operations with chars, the ascii number of the given char will be changed and the res will be the ascii value.
// Ex: 'b' - 'a' = 1
void mystrcmp(char s1[], char s2[]) {
  int index = 0;
  for(int i = 0; i < (int) strlen(s1); i++) {
    if (s1[i] != s2[i]) break;
    index++;
  }
  int a = s1[index];
  int b = s2[index];
  printf("%d", a - b);
}

char *mystrstr(char s1[], char s2[]){
  
  if(*s1 == '\0' && *s2 == '\0') return s1;
  
  if(*s1 == '\n' && *s2 == '\0') return s1;
  
	for(; *s1 ; s1++){
		if(*s1 == *s2){
			char *r = s1;
			char *p = s2;
			while(*s1 == *p && *s1){
				p++;
				s1++;
			}

			if(*p == '\0') return r;
		}
	}

	return NULL;
}

int main() {
  int choice = 0;
  char *res;

  printf("Escolha uma questão: ");
  scanf("%d",&choice);
  
  switch (choice) {
    case 1:
      n1();
      break;
    case 2:
      n2();
      break;
    case 3:
      n3();
      break;
    case 4:
      n4(15);
      break;
    case 5:
      n5(16);
      break;
    case 6:
      n6(1990);
      break;
    case 7:
      n7("ola","tudo bem");
      break;
    case 8:
      //char *pArray = &array[0];
      //char *a = strcpyMy("Ola","ola tudo bem");
      //printf("%s",a);
      break;
    case 9:
      mystrcmp("ola", "olb");
      break;
    case 10:
      res = mystrstr("anagrama","ama");
      printf("%s",res);
      break;
  }

  return 0;
}
