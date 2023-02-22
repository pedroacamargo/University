#include <stdio.h>
#include <math.h>


// 3.1)
void quadradoBrabo() {
    char x = '#'; // #
    int y; // input do usuário
    int z = 0; // contador no while
    printf("Digite um numero para o comprimento do quadrado brabo: ");
    scanf("%d", &y); // pegar o input para o y
    int altura; // contador para acabar o while (quando altura = input do usuário)


    // z = 0 / y = 5
    while (z <= y) {
        if (z < y) {
            printf("%c", x);
            z += 1;
        };

        if (z == y) {
            printf("\n");
            z = 0;
            altura += 1;
        };

        if (altura == y) {
            break;
        }


    };

}

// 3.2)
void xadrez() {
    int x;
    int contador = 0;
    int altura = 0;
    printf("Digite um numero para as colunas e para as linhas de um tabuleiro de xadrez: ");
    scanf("%d", &x);
    while (contador <= x) {
        if (contador % 2 == 0) {
            if (contador == x) {
                printf("\n");
                contador = 0;
                altura += 1;
            } else {
                printf("#");
                contador += 1;
            }
        } else {
            if (contador == x) {
                printf("\n");
                contador = 0;
                altura += 1;
            } else {
                printf("_");
                contador += 1;
            }
        }

        if (altura == x){
            break;
        }
    }
}

void trianguloBrabo() {
    int x = 0; // contador para as #, quando printa 1 #, x++
    int y = 1; // contador para o maximo de # numa linha, quando x == y, y++/y-- (y++ quando topo = 0 e y-- quando topo = 1) e x = 0, resetando a contagem
    int altura; // a altura do triângulo dada pelo usuário (máximo de # numa linha)
    int topo = 0; // 0 = false || 1 = true

    printf("\nDigite um numero para a altura do triangulo: ");
    scanf("%d", &altura);

    while (x <= altura) {
        x++;
        if (y < x) {
            break;
        }
        printf("#");
        
        
        if (x == altura) {
            printf("\n");
            topo = 1;
            y--;
            x = 0;
        }

        if (x == y) {
            if (topo == 0) {
                printf("\n");
                y++;
                x = 0;
            } else {
                printf("\n");
                y--;
                x = 0;
            }
        }
    }
}

void trianguloBraboVertical(int n) {
    int linha,symbol,espaco,square;
    square = 1;
    // for each line, do something
    for (linha = 1; linha < n + 1; linha++) {
        for (espaco = n - linha;espaco != 0; espaco--) {
            putchar(' ');
        }
        for (symbol = 0; symbol < square; symbol++ ) {
            putchar('#');
        }
        printf("\n");
        square += 2;
    }
}

void matriz(int n) {
    int i = n, j = n; // matrix i x j
    for (i = 1; i <= n; i++) {
        for (j = 1;j <= n; j++) {
            if (i - j == 0) {
                putchar('#');
            } else if (i + j == n + 1) {
                putchar('#');
            } else {
                putchar(' ');
            }
        }
        printf("\n");
    }
}

void circulo(int r) {
    int i,j, contador = 0, diametro = 2*r + 1;
    // matrix lines
    for (i = 0; i < 2*r + 1 ; i++) {
        contador++;
        if (contador == r + 1) {
            for (j = 0; j < 2 * r + 1;j++) {
                putchar('#');
            }
        } else {
            for (j = 0; j<= 2 * r + 1;j++) {
                double distance = sqrt((double)(i-r)*(i-r) + (j-r)*(j-r));
                if (distance>r-0.5 && distance<r+0.5) {
                    printf("#");
                } else { 
                    printf(" ");
                }
            }
        }
        putchar('\n');
        

    }
}


int main() {

    // quadradoBrabo(); -> 3.1
    // xadrez(); -> 3.2 
    // trianguloBrabo(); -> 3.3
    // trianguloBraboVertical(5);
    // matriz(9);
    circulo(4);
    return 0;  
}