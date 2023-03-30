#include <stdio.h>
#include <assert.h>
#include "Alunos.h"

// https://estev.ao/lcc-f5


int main() {
    Aluno Turma1 [7] = {{4444, "André", {2,1,0,2,2,2}, 10.5}
                       ,{3333, "Paulo", {0,0,2,2,2,1},  8.7}
                       ,{8888, "Carla", {2,1,2,1,0,1}, 14.5}
                       ,{2222, "Joana", {2,0,2,1,0,2},  3.5}
                       ,{7777, "Maria", {2,2,2,2,2,1},  5.5}
                       ,{6666, "Bruna", {2,2,2,1,0,0}, 12.5}
                       ,{5555, "Diogo", {2,2,1,1,1,0},  8.5}
                       } ;
    int indNome [7], indNum [7];
    int i;

    assert(nota(Turma1[0]) == 11);
    assert(nota(Turma1[3]) == 0);
    
    printf ("\n-------------- Testes --------------\n");
    
    // ordenaPorNum (Turma1, 7);

    printf ("procura 5555: %d\n", procuraNum (5555, Turma1, 7));
    printf ("procura 9999: %d\n", procuraNum (9999, Turma1, 7));

    for (i=0; i<7; imprimeAluno (Turma1 + i++));
    
    // criaIndPorNum (Turma1, 7, indNum);
    
    // criaIndPorNome (Turma1, 7, indNome);

    // imprimeTurmaInd (indNum, Turma1, 7);
    // imprimeTurmaInd (indNome, Turma1, 7);

    // printf ("procura 5555:%d \n",  procuraNumInd (5555, indNum, Turma1, 7));
    // printf ("procura 9999:%d \n",  procuraNumInd (9999, indNum, Turma1, 7));

    printf ("\n---------- Fim dos Testes ----------\n");
    
    return 0;
}


int main() {
    Aluno Turma1 [7] = {{4444, "André", {2,1,0,2,2,2}, 10.5}
                       ,{3333, "Paulo", {0,0,2,2,2,1},  8.7}
                       ,{8888, "Carla", {2,1,2,1,0,1}, 14.5}
                       ,{2222, "Joana", {2,0,2,1,0,2},  3.5}
                       ,{7777, "Maria", {2,2,2,2,2,1},  5.5}
                       ,{6666, "Bruna", {2,2,2,1,0,0}, 12.5}
                       ,{5555, "Diogo", {2,2,1,1,1,0},  8.5}
                       } ;
    int indNome [7], indNum [7];
    int i;

    assert(nota(Turma1[0]) == 11);
    assert(nota(Turma1[3]) == 0);
    
    printf ("\n-------------- Testes --------------\n");
    
    // ordenaPorNum (Turma1, 7);

    printf ("procura 5555: %d\n", procuraNum (5555, Turma1, 7));
    printf ("procura 9999: %d\n", procuraNum (9999, Turma1, 7));

    for (i=0; i<7; imprimeAluno (Turma1 + i++));
    
    // criaIndPorNum (Turma1, 7, indNum);
    
    // criaIndPorNome (Turma1, 7, indNome);

    // imprimeTurmaInd (indNum, Turma1, 7);
    // imprimeTurmaInd (indNome, Turma1, 7);

    // printf ("procura 5555:%d \n",  procuraNumInd (5555, indNum, Turma1, 7));
    // printf ("procura 9999:%d \n",  procuraNumInd (9999, indNum, Turma1, 7));

    printf ("\n---------- Fim dos Testes ----------\n");
    
    return 0;
}
int main() {
    Aluno Turma1 [7] = {{4444, "André", {2,1,0,2,2,2}, 10.5}
                       ,{3333, "Paulo", {0,0,2,2,2,1},  8.7}
                       ,{8888, "Carla", {2,1,2,1,0,1}, 14.5}
                       ,{2222, "Joana", {2,0,2,1,0,2},  3.5}
                       ,{7777, "Maria", {2,2,2,2,2,1},  5.5}
                       ,{6666, "Bruna", {2,2,2,1,0,0}, 12.5}
                       ,{5555, "Diogo", {2,2,1,1,1,0},  8.5}
                       } ;
    int indNome [7], indNum [7];
    int i;

    assert(nota(Turma1[0]) == 11);
    assert(nota(Turma1[3]) == 0);
    
    printf ("\n-------------- Testes --------------\n");
    
    // ordenaPorNum (Turma1, 7);

    printf ("procura 5555: %d\n", procuraNum (5555, Turma1, 7));
    printf ("procura 9999: %d\n", procuraNum (9999, Turma1, 7));

    for (i=0; i<7; imprimeAluno (Turma1 + i++));
    
    // criaIndPorNum (Turma1, 7, indNum);
    
    // criaIndPorNome (Turma1, 7, indNome);

    // imprimeTurmaInd (indNum, Turma1, 7);
    // imprimeTurmaInd (indNome, Turma1, 7);

    // printf ("procura 5555:%d \n",  procuraNumInd (5555, indNum, Turma1, 7));
    // printf ("procura 9999:%d \n",  procuraNumInd (9999, indNum, Turma1, 7));

    printf ("\n---------- Fim dos Testes ----------\n");
    
    return 0;
}
int main() {
    Aluno Turma1 [7] = {{4444, "André", {2,1,0,2,2,2}, 10.5}
                       ,{3333, "Paulo", {0,0,2,2,2,1},  8.7}
                       ,{8888, "Carla", {2,1,2,1,0,1}, 14.5}
                       ,{2222, "Joana", {2,0,2,1,0,2},  3.5}
                       ,{7777, "Maria", {2,2,2,2,2,1},  5.5}
                       ,{6666, "Bruna", {2,2,2,1,0,0}, 12.5}
                       ,{5555, "Diogo", {2,2,1,1,1,0},  8.5}
                       } ;
    int indNome [7], indNum [7];
    int i;

    assert(nota(Turma1[0]) == 11);
    assert(nota(Turma1[3]) == 0);
    
    printf ("\n-------------- Testes --------------\n");
    
    // ordenaPorNum (Turma1, 7);

    printf ("procura 5555: %d\n", procuraNum (5555, Turma1, 7));
    printf ("procura 9999: %d\n", procuraNum (9999, Turma1, 7));

    for (i=0; i<7; imprimeAluno (Turma1 + i++));
    
    // criaIndPorNum (Turma1, 7, indNum);
    
    // criaIndPorNome (Turma1, 7, indNome);

    // imprimeTurmaInd (indNum, Turma1, 7);
    // imprimeTurmaInd (indNome, Turma1, 7);

    // printf ("procura 5555:%d \n",  procuraNumInd (5555, indNum, Turma1, 7));
    // printf ("procura 9999:%d \n",  procuraNumInd (9999, indNum, Turma1, 7));

    printf ("\n---------- Fim dos Testes ----------\n");
    
    return 0;
}
