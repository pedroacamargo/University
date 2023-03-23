#include <stdio.h>
#include <string.h>

// 1)
int contaVogais(char *s) {
  char vogais[] = "AEIOUaeiou";
  int size = strlen(s);
  int res = 0;
  for (int i = 0; i < size; i++) {
    for(int j = 0; j < 10; j++) {
      if (*s == vogais[j]) res++;
    }
    s = s + 1;
  }
  return res;
}

// Functions
//
// isdigit(c) -> if is a number
// toupper(c) -> will put a char to upperCase
// tolower(c) -> will put a char to lowerCase

// 2)
void retiraVogaisRep(char *s) {
  int size = strlen(s), i = 0, index = 0;
  char res[size];
  while (*s != '\0') {
    while (*s == *s + 1) {
      *s = *s + 1; 
      i++;
    }
    res[index] = s[i];
    *s = *s + 1;
    index++;
  }

  int size2 = strlen(res);
  for (int i = 0; i < size2; i++) {
    s[i] = res[i];
  }
  printf("%s",s); 
}

// resolução prof
int profRetiraVogaisRep(char *s) {
  int repetidasContador = 0;
  int comprimento = strlen(s);
  char aux[comprimento + 1];
  aux[comprimento] = '\0';
  int pos = 1;
  int posAux = 0;

  aux[0] = s[0];

  while (s[pos] != '\0') {
    if (!eVogal(s[pos]) && s[pos] == s[pos - 1]) {
      aux[posAux] = s[pos];
      posAux++;
    } else {
      repetidasContador++;
    }
    pos++;
  }

  int i = 0;
  while (aux[i] != '\0') {
    s[i] = aux[i];
    i++;
  }

  s[i+1] = '\0';

  return repetidasContador;
}

// resolução Vtec
int vtecRetiraVogaisRep(char *s) {
  char *n = s;
  char *p = n + 1;
  while(*p != '\0') {
    if (!(eVogal(*n) && eVogal(*p) && *p == *n)) {
      n++;
      *n = *p;
    }
    p++;
  }
  

  *(n + 1) = '\0';

  return p - n - 1;

}




int main() {
  // int res;
  // char string[] = "aAoOeEiI";
  // res = contaVogais(string);
  // printf("%d",res);
  retiraVogaisRep("olaaa tudo beeem");
  return 0;
}
