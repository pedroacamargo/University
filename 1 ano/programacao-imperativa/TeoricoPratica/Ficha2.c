#include <stdio.h>

// 1) produto de um número m por um inteiro n -> somátorio de n parcelas constantes
float multInt1(int n, float m) {
    int r = 0;


    for (n; n != 0;n--) {
        r += m;
    }

    return r;
}

// 2) dado dois números n e m, construir uma tabela de divisão inteira n por 2
float multInt2(int n, float m) {
    int imparN = 0;

    while (n != 1) {

        // caso n seja impar, adicionar na variável o valor de m 
        if (n % 2 == 1) {
            imparN += m;
        }
        
        n /= 2;
        m *= 2;
    }

    return m + imparN;
}



int main(){
    float res1 = multInt1(10,2.0);
    float res2 = multInt2(81,423);
    printf("%.0f",res2);
    return 0;
}