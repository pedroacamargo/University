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

// 3)
int verMaiorDivisor(int a) {
    

    for (int i = a - 1; i != 0; i--) {
        if (i == 1) {
            return 0;
        }
        if (a % i == 0 && i != 1) {
            return i;
        }
    }
}

int mdc1(int a, int b) {
    int maiorDivisorA = verMaiorDivisor(a); // 7
    int maiorDivisorB = verMaiorDivisor(b); // 0
    int temp = a * b;
    // mdc 8,4 = 2 x 2 x 2 = 8
    // mdc 16, 14 = 2 x 2 x 2 x 2 x 7
    // mdc 15 = 5
    if (a % b == 0) {
        if (a < b) {
            printf("Passei aqui");
            return b;
        } else {
            printf("Passei aqui");
            return a;
        }
    } else if (maiorDivisorA > maiorDivisorB) {
        maiorDivisorA = verMaiorDivisor(maiorDivisorA);
    } else if (maiorDivisorA < maiorDivisorB) {
        maiorDivisorB = verMaiorDivisor(maiorDivisorB);
    } else if (maiorDivisorA == 0 || maiorDivisorB == 0) {
        printf("Passei aqui");
        return temp;
    }
}



int main(){
    float res1 = multInt1(10,2.0);
    float res2 = multInt2(81,423);
    int res3 = mdc1(15,5);
    printf("%d", res3);
    // printf("%.0f",res3);
    return 0;
}