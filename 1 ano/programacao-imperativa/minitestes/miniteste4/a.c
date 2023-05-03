#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct aluno {
  char nome[100];
  int nr;
  int nota;
} Aluno; 

typedef struct cel {
  Aluno *aluno;
  struct cel *prox;
} *Turma;

int adicionaAluno(Turma *t, char *nome, int nr, int nota) {
  Aluno *novo_aluno = malloc(sizeof(Aluno));
  if (novo_aluno == NULL)
    return 1;
  strcpy(novo_aluno->nome, nome);
  novo_aluno->nr = nr;
  novo_aluno->nota = nota;

  struct cel *nova_cel = malloc(sizeof(struct cel));
  if (nova_cel == NULL) {
    free(novo_aluno);
    return 1;
  }
  nova_cel->aluno = novo_aluno;

  while (*t != NULL && strcmp((*t)->aluno->nome, nome) < 0) { 
    t = &((*t)->prox);
  }

  nova_cel->prox = *t;
  *t = nova_cel;

  return 0;
}

int main() {
  Turma turma = NULL;

  adicionaAluno(&turma, "João", 123, 7);
  adicionaAluno(&turma, "Ana", 456, 9);
  adicionaAluno(&turma, "Pedro", 789, 5);

  struct cel *p;
  for (p = turma; p != NULL; p = p->prox) {
    printf("Nome: %s, Número: %d, Nota: %d\n", p->aluno->nome, p->aluno->nr, p->aluno->nota);
  }

  return 0;
}