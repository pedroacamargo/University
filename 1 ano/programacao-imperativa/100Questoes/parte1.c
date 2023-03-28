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

// 21
int contaVogais(char s[]) {
  int acc = 0;
  char vogais[] = "aeiouAEIOU";
  int size = strlen(s);
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < 10; j++) {
      if (s[i] == vogais[j]) acc++;
    }
  }

  return acc;
}

// 22 - 1 for true, 0 for false
int contida(char a[], char b[]) {
  int sizeA = strlen(a);
  int sizeB = strlen(b);
  int indexA = 0;
  for (int i = 0; i < sizeA; i++) {
    for (int j = 0; j < sizeA; j++) {
      if (a[i] == b[j]) indexA++;
    }
    if (indexA == (sizeB - 1)) return 1;
  }
  return 0;
}

// 23
int palindorome(char s[]) {
  int size = strlen(s);
  int palindromo = size/2;
  int res = 1;
  for (int i = 0; i < palindromo - 1; i++) {
    if (!(s[i] == s[size - 1 - i])) {
      res = 0;
    }
  }
  return res;
}

// 24
int remRep(char x[]) {
  int size = strlen(x);
  int index = 0;
  char arrFinal[size];
  for (int i = 0; i < size; i++) {
    if (!(x[i] == x[i+1])) {
      arrFinal[index] = x[i];
      index++;
    }
  }
  return strlen(arrFinal);
}

// 25
int limpaEspacos(char t[]) {
  // int size = strlen(t);
  for(int i = 0; t[i]; i++) {
    if (t[i] == ' ' && t[i+1] == ' ') {
      for(int j=i+1; t[j]; j++) t[j] = t[j+1];
      i--;
    }
  }

  return strlen(t);
}

// 26
void insere(int v[], int N, int x) {
  for (int i = 0; v[i]; i++) {
    if (v[i] > x) {
      for (int j = N; j > i; j--) {
        v[j] = v[j-1];
      }
      v[i] = x;
      break;
    }
    if (i == N -1) {
      v[N] = x;
    }
  }
}

// 27
void merge(int r [], int a[], int b[], int na, int nb) {
  int size = na + nb;
  int aacc = 0, bacc = 0;
  int sizeA = na;
  int sizeB = nb;
  for (int i = 0; i < size; i++) {
    if (a[aacc] > b[bacc]) {
      r[i] = b[bacc];
      bacc++;
      sizeB--;
    } else {
      r[i] = a[aacc];
      aacc++;
      sizeA--;
    }
  }
  for (int k = 0; k < size - 1; k++) {
    printf("%d ",r[k]);
  }
}

// 28
int crescente(int a[], int i, int j) {
  for (int index = i; index <= j; index++) {
    if (!(a[index] < a[index + 1])) return 0;
  }
  return 1;
}

// 29
int retiraNeg(int v[], int N) {
  int acc = -1;
  for (int i = 0; i < N; i++) {
    if (v[i] < 0) {
      for (int j = i; j < N - 1; j++) {
        v[j] = v[j + 1];
      }
    } else {
      acc++;
    }
  }
  return acc;
}

//30

int rep(int num, int arr[], int N) {
  int count = 0;

  for (int i = 0; i < N; i++) {
    if (num == arr[i]) count++;
  }
  return count;
}

int menosFreq(int v[], int N) {
  int menos = rep(v[0],v,N);
  int res = v[0];

  for (int i = 0; i < N; i++) {
    int atual = rep(v[i],v,N);
    if (atual < menos) {
      menos = atual;
      res = v[i];
    }
  }
  return res;
}

// 31
int repete(int num, int v[], int N) {
  int count = 0;
  for (int i = 0; i < N; i++) {
    if (num == v[i]) count++;
  }
  return count;
}

int maisFreq(int v[], int N) {
  int maior = repete(v[0], v, N);
  int res = 0;
  for (int i = 0; i < N; i++) {
    int atual = repete(v[i],v,N);
    if (atual > maior) {
      maior = atual;
      res = v[i];
    }
  }

  return res;
}

// 32
int maxCresc(int v[], int N){
    int i, maior = 1, r = 1;

    for(i=0; i<N; i++){
        if(v[i+1] >= v[i])
            r++;
        else {
            if(r>maior)
                maior = r;
            r=1;
        }
    }
    return maior;
}

// 33
// se repetir mais do q 1 vez, retorna > 0
// se repetir 1 vez retorna 0
int pertence(int elem, int v[], int n) {
  int res = -1;
  for (int i = 0; i < n; i++) {
    if (elem == v[i]) res++;
  }
  return res;
}

int elimRep(int v[], int n) {
  int arr[n];
  int index = 0;
  for (int i = 0; i < n; i++) {
    int elem = pertence(v[i],v,n);
    if (elem == 0) {
      arr[index] = v[i];
      index++;
    }
  }
  for (int j = 0; j < index; j++) {
    v[j] = arr[j];
  }
  return index + 1;
}

// 34
int elimRepOrd (int v[], int n) {
  for (int i = 0; i < n - 1; i++) {
    if (v[i] == v[i + 1]) {
      for (int j = i; j < n; j++) {
        v[j] = v[j + 1];
      }
      n--;
    }
  }
  return n - 1;
}

// 35
int comunsOrd(int a[], int na, int b[], int nb) {
  int count = 0;
  for (int i = 0; i < na; i++) {
    for (int j = 0; j < nb; j++) {
      if (a[i] == b[j]) {
        count++;
        i++;
      } else if (a[i] < b[j]) {
        i++;
      }
    }  
  }
  return count;
}

// 36
int pertence2(int b[], int num, int nb) {
  for (int i = 0; i < nb; i++) {
    if (b[i] == num) {
      return 1;
    }
  }
  return 0;
}
int comuns(int a[], int na, int b[], int nb) {
  int count = 0;
  for (int i = 0; i < na; i++) {
    if (pertence2(b, a[i], nb) == 1) count++;
  }
  return count;
}

// 37
int minInd(int v[], int n) {
  int menor = v[0];

  for (int i = 0; i < n; i++) {
    if (v[i] <= menor) menor = v[i];
  }
  
  return menor;
}

// 38
void somasAc (int v[], int Ac [], int N) {
  Ac[0] = v[0];
  for (int i = 1; i < N; i++) {
    Ac[i] = 0;
    for (int j = 0; j <= i; j++) {
      Ac[i] += v[j];
    }
  }
}

// 39
// [
//  1 2 3
//  0 2 3
//  0 0 3
// ]
int triSup (int N, float m[N][N]) {
  for (int i = 1; i < N; i++) {
    for (int j = 0; j < i;j++) {
      if (m[i][j] != 0) return 0;
    }
  }
  return 1;
}

// 40
void transposta(int N, float m [N][N]) {
  float temp;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      temp = m[i][j];
      m[i][j] = m[j][i];
      m[j][i] = temp;
    }
  }
}

// 41
void addTo (int N, int M, int a [N][M], int b[N][M]) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      a[i][j] += b[i][j];
    }
  }
}

// 42
int unionSet (int N, int v1[N], int v2[N], int r[N]){
  int count = 0;
  for (int i = 0; i < N; i++) {
    r[i] = v1[i] || v2[i];
    count++;
  }
  return count;
}

// 43
int intersectSet(int N, int v1[N], int v2[N], int r[N]) {
  int count = 0;
  for (int i = 0; i < N; i++) {
    r[i] = v1[i] && v2[i];
    count++;
  }
  return count;
}

// 44
int intersectMSet (int N, int v1[N], int v2[N],int r[N]) {
    int len = 0;
    for(int i = 0; i < N; i++) {
        r[i] = v1[i] < v2[i] ? v1[i] : v2[i];
        len += r[i]; 
    }
    return len;
}

// 45
int unionMSet (int N, int v1[N], int v2[N], int r[N]) {
    int len = 0;
    for(int i = 0; i < N; i++) {
        r[i] = v1[i] + v2[i];
        len += r[i]; 
    }
    return len;
}

// 46
int cardinalMSet (int N, int v[N]) {
    int len = 0;
    for(int i = 0; i < N; i++) len += v[i];
    return len;
}


int main() {
  int choice = 0;
  char *res;
  char ola;
  char str[] = "Ola   tudo bem";
  int vetor[100];
  int vetorA[] = {1,3,4,11,11,11,11};
  int vetorB[] = {2,5,10,12};
  int vetor38[] = {1,2,3,4};
  int vetor38_2[5];

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
    case 21:
      choice = contaVogais("Pedro Camargo");
      printf("%d",choice);
      break;
    case 22:
      choice = contida("abe","abcd");
      printf("%d",choice);
      break;
    case 23:
      choice = palindorome("rotatorrrrr");
      printf("%d",choice);
      break;
    case 24:
      choice = remRep("aaabaaabbbaaa");
      printf("%d",choice);
      break;
    case 25:
      choice = limpaEspacos(str);
      printf("%d",choice);
      break;
    // case 26:
      // insere({1,2,3,4,5},3,10);
      // break;
    case 27:
      merge(vetor, vetorA, vetorB,6,5);
      break;
    case 28:
      choice = crescente(vetorA,1,3);
      printf("%d",choice);
      break;
    case 29:
      choice = retiraNeg(vetorA, 6);
      printf("%d",choice);
      break;
    case 30:
      choice = menosFreq(vetorA,6);
      printf("%d",choice);
      break;
    case 31:
      choice = maisFreq(vetorA, 6);
      printf("%d",choice);
      break;
    case 32:
      choice = maxCresc(vetorA, 6);
      printf("%d",choice);
      break;
    case 33:
      choice = elimRep(vetorA, 6);
      printf("%d",choice);
      break;
    case 34:
      choice = elimRepOrd(vetorA, 6);
      printf("%d",choice);
      break;
    case 35:
      // choice = comunsOrd(int *a, int na, int *b, int nb)
      break;
    case 36:
      // choice = comuns(int *a, int na, int *b, int nb)
      break; 
    case 37:
      choice = minInd(vetorA, 6);
      printf("%d",choice);
      break;
    case 38:
      somasAc(vetor38, vetor38_2, 4);
      break;
    case 39:
      // triSup(int N, float (*m)[N])
      break;
    case 40:
      // transposta(int N, float (*m)[N]) 
      break;
    case 41:
      // unionSet(int N, int *v1, int *v2, int *r)
      break;
    case 42:
      // intersectSet(int N, int *v1, int *v2, int *r)
      break;
    
  }

  return 0;
}
