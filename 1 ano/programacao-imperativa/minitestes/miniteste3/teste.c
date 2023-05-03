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

    return soma % 19;
}

void preenche_notas(Estudante turma[], int N) {
    for(int i = 0; i < N; i++) {
        turma[i].nota = calcula_nota(turma[i].nome);
    }
}

int compara_nomes(const void *a, const void *b) {
    Estudante *est_a = (Estudante *) a;
    Estudante *est_b = (Estudante *) b;

    return strcmp(est_a->nome, est_b->nome);
}

void ordena_turma(Estudante turma[], int N) {
    int i, j;
    Estudante temp;
    for (i = 0; i < N - 1; i++) {
        for (j = 0; j < N - i - 1; j++) {
            if (strcmp(turma[j].nome, turma[j + 1].nome) == 1) {
                temp = turma[j];
                turma[j] = turma[j + 1];
                turma[j + 1] = temp;
            }
        }
    }
}

int main() {

    Estudante turma[TAM_TURMA] = {
        { "Phineas", 0 }, { "Gus Fring", 0 },
        { "Raine Whispers", 0 }, { "Tara Jones", 0 },
        { "America Chavez", 0 }, { "Lito Rodriguez", 0 },
        { "Shirley Bennett", 0 }, { "Nick Nelson", 0 },
        { "Barry Allen", 0 }, { "Natasha Romanoff", 0 },
        { "Waymond Wang", 0 }, { "Anakin Skywalker", 0 },
        { "Amity Blight", 0 }, { "Frodo Baggins", 0 },
        { "Edalyn Clawthorne", 0 }, { "Din Djarin", 0 },
        { "Wanda Maximoff", 0 }, { "Hope Van Dyne", 0 },
        { "Gwen Stacy", 0 }, { "Geralt", 0 },
        { "Michonne", 0 }, { "Todd Chavez", 0 },
        { "BoJack Horseman", 0 }, { "Amos Burton", 0 },
        { "Alex Kamal", 0 }, { "Leia Organa", 0 },
        { "Gamora", 0 }, { "Miles Morales", 0 },
        { "Arthur Curry", 0 }, { "Ashoka Tano", 0 },
        { "Scott Lang", 0 }, { "Nick Fury", 0 },
        { "Thor", 0 }, { "Nomi Marks", 0 },
        { "Sauron", 0 }, { "Daryl Dixon", 0 },
        { "Stanley Pines", 0 }, { "Bobbie Draper", 0 },
        { "Poe Dameron", 0 }, { "Grogu", 0 }
    };
    preenche_notas(turma, TAM_TURMA);

    // Imprimir a nota do estudante de índice 7
    printf("Nota do estudante %d: %d\n", 7, turma[7].nota);

    ordena_turma(turma, TAM_TURMA);

    // Calcular a soma das notas dos últimos 25 alunos
    int soma_ultimos = 0;
    for(int i = 0; i < 15; i++) {
        soma_ultimos += turma[i].nota;
    }
    printf("Soma das notas dos últimos 25 alunos: %d\n", soma_ultimos);

    return 0;
}
