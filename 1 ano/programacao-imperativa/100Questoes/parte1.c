#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

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

void mystrrev(char s[]) {
  int size = strlen(s);
  char array[size];
  int index = 0;
  for (int i = size - 1; i >= 0; i--) {
    array[index] = s[i];
    index++;
  }
  for (int i = 0; i < size; i++) {
    printf("%c",array[i]);

  }
}

// 12)

int vowels(char s[], int size) {
  char vowels[] = "aeiouAEIOU";
  int acc = 0;
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < 10; j++) {
      if (s[i] == vowels[j]) acc++;
    }
  }
  return acc;
}

void mystrnoV(char s[]) {
  char vogais[] = "aeiouAEIOU";
  int size = strlen(s);
  int sizeWV = size - vowels(s, size);
  char s2[sizeWV];
  int index = 0;
  for (int i = 0; i < size; i++) {
    int isVowel = 0;
    for (int j = 0; j < 10; j++) {
      if (s[i] == vogais[j]) isVowel = 1;
    }
    if (isVowel == 0) {
      s2[index] = s[i];
      index++;
    }   
  }
  s2[sizeWV] = '\0';
  printf("%s", s2);
}

// 13
void mytruncW(char t[], int N) {
  int i, j = 0, n=0;

    for(i=0; t[i]; i++){
        if(t[i] == ' '){
            n = 0;
            t[j] = t[i];
            j++;
        } else {
            if (n < N){
                t[j] = t[i];
                j++;
                n++;
            }
        }
    }
    t[j] = '\0';
}

// 14
char mycharMaisfreq (char s[]) {
  char charMaisFreq = 'A';
  int amount = 0, actualAmount = 0;
  
  int size = strlen(s);

  for (int i = 0; s[i]; i++) {
    for (int j = 0; j < size; j++) {
      if (s[i] == s[j]) amount++;
    }
    if (amount > actualAmount) {
      charMaisFreq = s[i];
      actualAmount = amount;
      amount = 0;
    }
  }
  
  return charMaisFreq;
}

// 15
int iguaisConsecutivos (char s[]) {
  int repetidos = 1, res = 0;
  int size = strlen(s);
  for (int i = 0; i < size; i++) {
    if (s[i] == s[i + 1]) repetidos++;
    else if (s[i] != s[i + 1]) {
      if (repetidos > res) {
        res = repetidos;
        repetidos = 1;
      }
    }
  }
  return res;
}

// 16
int difConsecutivos (char s[]) {
  int diferentes = 1, res = 0;
  int size = strlen(s);
  for (int i = 0; i < size; i++) {
    if (s[i] != s[i + 1]) {
      diferentes++;
    } else if (s[i] == s[i + 1]) {
      if (diferentes > res) {
        res = diferentes;
        diferentes = 1;
      }
    }
  }

  return res;
}

// 17
int maiorPrefixo (char s1 [], char s2 []) {
  int comp = 0;
  for (int i = 0; s1[i]; i++) {
    if (s1[i] == s2[i]) {
      comp++;
    } else {
      return comp;
    }
  }
  return comp;
}

// 18
int maiorSufixo(char s1[], char s2[]) {
  // these sizes will give the lasts characters from the given strings
  int size1 = strlen(s1) - 1;
  int size2 = strlen(s2) - 1;
  int count = 0;

  for (int i = 0; s2[i]; i++) {
    if (s1[size1] == s2[size2]) {
      size1--;
      size2--;
      count++;
    } else {
      return count;
    }
  }
  return count;
}

// 19
int sufPref(char s1[], char s2[]) {
  int size = strlen(s1);
  int res = 0;
  int j = 0;
  for (int i = 0; i < size; i++) {
    if (s1[i] == s2[j]) {
      res++;
    } else {
      res = 0;
      j = 0;
    }
  }
  return res;
}

// 20
int contaPal(char s[]) {
  int res = 1;
  int size = strlen(s);
  for (int i = 0; i < size; i++) {
    if (isspace(s[i])) res++;
  }
  return res;
}

int main() {
  int choice = 0;
  char *res;
  char ola;

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
    case 11:
      mystrrev("ola tudo bem querida? Eu sou o Pedro Augusto :)");
      break;
    case 12:
      mystrnoV("pedroaugustOOOO");
      break;
    case 13:
      mytruncW("liberdade, igualdade e fraternidade", 4);
      break;
    case 14:
      ola = mycharMaisfreq("caraaaaaaalho");
      printf("%c",ola);
      break;
    case 15:
      choice = iguaisConsecutivos("bom diiiiiiiioooooooooooooooooaa");
      printf("%d",choice);
      break;
    case 16:
      choice = difConsecutivos("ola tuuuuuuuuudo bem");
      printf("%d",choice);
      break;
    case 17:
      choice = maiorPrefixo("ooooola", "oooola");
      printf("%d",choice);
      break;
    case 18:
      choice = maiorSufixo("oooolaaaaa", "ooolaaaaa");
      printf("%d",choice);
        break;
    case 19:
      choice = sufPref("olaaaaaaa","aaaaaalho");
        printf("%d",choice);
        break;
    case 20:
      choice = contaPal("Pedro Augusto Ennes");
      printf("%d",choice);
      break;
  }

  return 0;
}
