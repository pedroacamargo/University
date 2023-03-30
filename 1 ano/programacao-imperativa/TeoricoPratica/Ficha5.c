
#include <stdio.h>
#include <math.h>
#include "Alunos.h"

void dumpV (int v[], int N){
    int i;
    for (i=0; i<N; i++) printf ("%d ", v[i]);
}
void imprimeAluno (Aluno *a){
    int i;
    printf ("%-5d %s (%d", a->numero, a->nome, a->miniT[0]);
    for(i=1; i<6; i++) printf (", %d", a->miniT[i]);
    printf (") %5.2f %d\n", a->teste, nota(*a));
}

int nota (Aluno a){
    float miniTmedia = 0, notafinal;
    int i;

    for (i = 0; i < N_MINI_TESTES; i++) {
        miniTmedia += a.miniT[i];
    }

    miniTmedia = miniTmedia / N_MINI_TESTES;

    if (miniTmedia < 0.5) return 0;

    notafinal = (miniTmedia * 10) * 0.2 + a.teste * 0.8;

    if (notafinal < 9.5) return 0;

    return round(notafinal);
}

int procuraNum (int num, Aluno t[], int N){
    // int found = -1;
    // int i = 0;
    // while (i < N && found != -1) {
    //     if(num == t[i].numero) {
    //         found = i;
    //     }
    //     i++;
    // }

    // return found;
     int i;
     for ( i = 0; i < N; i++){
        if(num == t[i].numero) return i;
    }
    return -1;
}

void swap_aluno(Aluno *x, Aluno *y) {
    Aluno temp;
    temp = *x;
    *x = *y;
    *y = temp;    
}

void ordenaPorNum (Aluno t [], int N){
    for(int i = 0; i < N; i++) {
        for(int j = 0; j) {
            if(t[j] > t[j+1]) 
        }

    }
    
}
int procuraNumInd (int num, int ind[], Aluno t[], int N){
    return -1;
}

void criaIndPorNum (Aluno t [], int N, int ind[]){
    
}
void criaIndPorNome (Aluno t [], int N, int ind[]){
    
}

// void imprimeTurmaInd (int ind[], Aluno t[], int N){
//     imprimeTurmaInd_sol(ind,t,N);
// }
