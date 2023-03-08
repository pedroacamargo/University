#include <stdio.h>
#include <assert.h>

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
            return 1;
        }
        if (a % i == 0 && i != 1) {
            return i;
        }
    }
  return 0;
}

int mdc1(int a, int b) {
    int temp = a * b;
    int maiorDivisorA = verMaiorDivisor(a); // 7
    int maiorDivisorB = verMaiorDivisor(b); // 0
    // mdc 8,4 = 2 x 2 x 2 = 8
    // mdc 16, 14 = 2 x 2 x 2 x 2 x 7
    // mdc 15 = 5
    if (a % b == 0) {
        if (a < b) {
            return b;
        } else {
            return a;
        }
    } else if (maiorDivisorA > maiorDivisorB) {
        maiorDivisorA = verMaiorDivisor(maiorDivisorA);
    } else if (maiorDivisorA < maiorDivisorB) {
        maiorDivisorB = verMaiorDivisor(maiorDivisorB);
    } else if (maiorDivisorA == 0 || maiorDivisorB == 0) {
        return temp;
    }
  return 0;
}

// substituir o maior dos argumentos pela diferença entre eles até que seja 0 || 
int mdc2(int a, int b) {
    int c = 0; 
    if (a > b) {
        mdc2(a - b,b);
    } else if (b > a) {
        mdc2(a,b - a);
    } else if (a == 0 || b == 0){
        switch (a) {
            case 0:
                return b;
                break;
            default:
                return a;
                break;
        }
    }
  return 0;
}

int mdc2Resto(int a, int b) {
    if (a == 0 || b == 0) {
        switch (a) {
            case 0:
                return b;
                break;
            default:
                return a;
                break;
        }
    } else if (a > b) {
        mdc2(a % b,b);
    } else if (b > a) {
        mdc2(a,b % a);
    } 
  return 0;
}

// 6)
int fib1(int n) {
    int res;
    if (n >= 2) {
        return (fib1(n-1) + fib1(n-2));
    } else if (n == 1){
        return 1;
    } else {
        return 0;
    }
}

int fib2(int n) {
    int a = 1;
    int b = 1;
    int i, resultado;

    if (n == 1 || n == 0) {
        return 1;
    }
    
   for (i = 1;i < n;i++) {
        resultado = a + b;
        a = b;
        b = resultado;
    }
    return resultado;
}

// 6.1)
int fibonacci1(int n) {
  int res;
  if (n >= 2) {
    return (fibonacci1(n - 1) + fibonacci1(n - 2));
  } else if (n == 1) {
    return 1;
  } else {
    return 0;
  }
}

// resolução stor 6.2
int fibonacci2(int n) {
  if (n == 0) return 0;

  int acc1, acc2;
  acc1 = acc2 = 1;
  int tmp;

  int i;

  for(i = 3;i < n; i++) {
    tmp = acc2;
    acc2 = acc2 + acc1;
    acc1 = tmp;
  } 

  return acc2;
}

// resolução 2 stor 6.2
int fibonacci2_1(int n) {
  if (n == 0) return 0;

  int acc1, acc2;
  acc1 = acc2 = 1;
  int tmp;

  int i;

  for(i = 3;i < n; i++) {
    acc2 += acc1;
    acc1 = acc2 - acc1;
  } 

  return acc2;
}



int main(){
    float res2 = multInt2(81,423);
    int res3 = mdc1(21,2);
    int res4 = mdc2(100,5);
    int res5 = fibonacci2(7);
    

    // fazer o assert para dizer se algo deu mal na função
    // assert(i != 2) -> se i == 2, crashar e nos avisar
    assert(8 == fibonacci2(6));

    printf("%d\n", res5);
    return 0;
}
