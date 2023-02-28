#include <stdio.h>
#include <stdlib.h>

#define isGreater(ordemvalor) {\
    if (scanf("%d",&valor) != 1) abort();\
    if (valor > maior) {\
        maior = valor;\
        ordem = ordemvalor;\
        }\
}

int main() {
    int valor;
    int ordem = 0,maior = 0;

    isGreater(1);
    isGreater(2);
    isGreater(3);
    isGreater(4);
    isGreater(5);

    printf("%d\n",ordem);

    return 0;
}