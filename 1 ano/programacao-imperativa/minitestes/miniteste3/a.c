#include <stdio.h>
#include <string.h>

#define TAM_TURMA 40

typedef struct estudante {
    char nome[50];
    int nota;
} Estudante;

int calcula_nota(char nome[]) {
    int soma = 0;
    int tam_nome = strlen(nome);
    int i = tam_nome - 1; // começa no último nome

    while(nome[i] != ' ')                                                                       // procura o último nome
    { 
        i--;
    }
    i++; // avança uma posição para deixar de estar em cima do espaço

    while(i < tam_nome) {
        if(nome[i] >= 'a' && nome[i] <= 'z') {
            soma += nome[i] - 'a' + 1; // soma a posição da letra no alfabeto
        }
        i++;
    }

    return soma % 20;
}
// ascii -> 97 - 122 min
// ascii -> 65 - 90 MAI

void preenche_notas(Estudante turma[], int N) {
    for(int i = 0; i < N; i++) {
        turma[i].nota = calcula_nota(turma[i].nome);
    }
}

void ordena_turma(Estudante turma[], int N) {
    // ...
}

// NOMI MARKS

int main() {

    Estudante turma[TAM_TURMA] = {
       { "Evelyn Wang", 0 }, { "Walter White", 0 },
{ "Amity Blight", 0 }, { "Han Solo", 0 },
{ "Anakin Skywalker", 0 }, { "Nick Nelson", 0 },
{ "Willow", 0 }, { "Ciri", 0 },
{ "Shirley Bennett", 0 }, { "Cassian Andor", 0 },
{ "Nick Fury", 0 }, { "Mabel Pines", 0 },
{ "Chrisjen Avasarala", 0 }, { "Hannah Montana", 0 },
{ "Nomi Marks", 0 }, { "America Chavez", 0 },
{ "Barry Allen", 0 }, { "Jeff Winger", 0 },
{ "Rick Grimes", 0 }, { "Riley Blue", 0 },
{ "Groot", 0 }, { "Britta Perry", 0 },
{ "Wolfgang Bogdanow", 0 }, { "Steve Rogers", 0 },
{ "Jaskier", 0 }, { "Doofenshmirtz", 0 },
{ "Loki", 0 }, { "Gus Fring", 0 },
{ "Tony Stark", 0 }, { "Hank Pym", 0 },
{ "Monica Rambeau", 0 }, { "Poe Dameron", 0 },
{ "Lito Rodriguez", 0 }, { "Boba Fett", 0 },
{ "Kylo Ren", 0 }, { "Galadriel", 0 },
{ "Diane Nguyen", 0 }, { "Will Gorski", 0 },
{ "Matt Tholomule", 0 }, { "Tara Jones", 0 } 
    };
    preenche_notas(turma, TAM_TURMA);

    int nota = calcula_nota("Nomi Marks");
    printf("%d\n",nota);

    // ...

    return 0;
}