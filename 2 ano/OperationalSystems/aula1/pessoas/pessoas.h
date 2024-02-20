#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 100

typedef struct pessoas {
    char nome[100];
    int idade;
    char sexo;
} Pessoa;

int pessoas(char *origem, char *destino);