#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// maximo de pessoas na cozinha -> 40
// linhas < 1000 chars
// cada nome < 20 char

struct Pessoa {
  char *nome;
  int quantidade;
  int index;
};

int main() {
  int N = 0; // linhas
  if (scanf("%d",&N) != 1) return 1;
  getchar();
  char pessoas[1000];
  char palavra[20];
  char listaCompleta[100000][20];
  int pessoaAtual = 0;
  for (int i = 0; i < N; i++) {

    if (fgets(pessoas, 1000, stdin) == 0) return 1;

    // divide each word
    while (sscanf(pessoas, "%s%[^\n]",palavra, pessoas) == 2) {
      
      for (int j = 0; j < (int) strlen(palavra);j++) {
        listaCompleta[pessoaAtual][j] = palavra[j];
      }
      pessoaAtual++;
    }

    for (int j = 0; j < (int) strlen(palavra);j++) {
      listaCompleta[pessoaAtual][j] = palavra[j];
    }
    pessoaAtual++;
  }
  

  // {"pedro", "augusto", "camargo"}
  struct Pessoa pessoa;
  pessoa.quantidade = 1000;
  pessoa.index = 0;
  pessoa.nome = strdup(listaCompleta[0]);

  int quantidadeatual = 0;

  for (int i = 0; i < pessoaAtual; i++) {
    for (int j = 0; j < pessoaAtual; j++) {
      if (strcmp(listaCompleta[i],listaCompleta[j]) == 0) {
        quantidadeatual++;
      }
    }
    if (quantidadeatual < pessoa.quantidade) {
      pessoa.nome = listaCompleta[i];
      pessoa.index = i;
      pessoa.quantidade = quantidadeatual;
    }
    quantidadeatual = 0;
  }

  printf("%s\n", pessoa.nome);


  // for (int i = 0; i < pessoaAtual; i++) {
  //   printf("%s | ", listaCompleta[i]);
  // }  


  return 0;
}
