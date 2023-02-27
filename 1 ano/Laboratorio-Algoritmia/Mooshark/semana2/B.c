#include <stdio.h>

int main(){
    int C,A,N;
    int comando;

    if (scanf("%d", &C)!= 1) return 1; // Onde começou
    if (scanf("%d", &A)!= 1) return 1; // Quantidade de andares
    if (scanf("%d", &N)!= 1) return 1; // número de comandos

    for (int i = 0; i < N; i++) {
        if (scanf("%d", &comando) != 1) return 1;
        switch (comando) {
            case 1:
                if (C < A) {
                    C++;
                }
                break;
            case -1:
                if (C > 0) {
                    C--;
                }
                break;
        }
    }

    printf("%d\n", C);

    return 0;
}