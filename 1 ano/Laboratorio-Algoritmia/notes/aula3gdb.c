#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// gcc -Wall -Wextra -pedantic -02 primos.c -ln
// gcc -g primos.c
// help
// start
// lis
// enter -> executa o mesmo comando anteriormente
// C-X + A -> entrar e sair
// ctrl x + 2 -> registros
// step
// next (n) 
// ctrl + l -> refresh
// p limite -> imprime o valor da variável limite
// p *primos@10 -> da os 10 primeiros elementos do array
// b 10 -> breakpoint na linha 10
// watch *primos@10
// n
// where

void encontrar_primos(int limite, bool *primos) {
  for (int i = 1; i < limite; i++) {
    primos[i] = true;
  }

  for (int i = 2; i * i < limite; i++) {
    if (primos[i]) {
      for (int j = 2 * i; j < limite; j+= 1) {
        primos[j] = false;
      }
    }
  }
}

int contar_primos(int limite,bool *primos) {
  int cnt = 0;
  for (int i = 2; i< limite;i++) {
    if (primos[i]) cnt++;
  }
  return cnt;
}

int main() {
  int limite;
  if (scanf("%d", &limite) != 1) {
    fprintf(stderr, "Não consegui ler o limite\n");
    return 0;
  }
 
  bool * primos = (bool *) malloc(limite * sizeof(bool));  

  encontrar_primos(limite, primos);
  printf("%d\n", contar_primos(limite, primos));

  return 0;
}
