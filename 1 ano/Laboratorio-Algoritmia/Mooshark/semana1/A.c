#include <stdio.h>

#define isGreater(ordemvalor) {\
    if (scanf("%d",&valor) != 1) ABORTAR("Não consegui ler um valor");\
    if (valor > ordemvalor) {\
        }\
}

int main() {
    int a1,a2,a3,a4,a5;
    int ordem,maior;

    scanf("%d\n",&a1);
    ordem = 1;
    maior = a1;

    scanf("%d\n",&a2);
    if (a2 > maior) {
        ordem = 2;
        maior = a2;
    }


    scanf("%d\n",&a3);
    if (a3 > maior) {
        ordem = 3;
        maior = a3;
    }

    scanf("%d\n",&a4);
    if (a4 > maior) {
        ordem = 4;
        maior = a4;
    }

    scanf("%d",&a5);
    if (a5 > maior) {
        ordem = 5;
        maior = a5;
    }

    printf("%d\n",ordem);

    return 0;
}