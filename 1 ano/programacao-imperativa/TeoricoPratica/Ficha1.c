#include <stdio.h>


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

void trianguloBrabo () {
    int x,y,z;
    int contador, contador2;
    int colunas;
    char primeiro = 's';
    printf("Escolha uma altura para o triangulo: ");
    scanf("%d", &x);
    contador = 0;
    contador2 = x;
    z = x;
    y = 1;
    printf("#\n");
    while (contador2 != 0) {
        while (contador <= y + 1) {
            printf("#");
            contador += 1;
            if (contador == y + 1) {
                printf("\n");
                y += 1;
                contador = 0;
            }
            if (contador2 == y) {
                contador = y + 2;
                break;
            }

        }
        int contador3 = contador2;
        while (contador2 <= y) {
            if (primeiro == 's') {
                contador2 -= 1;
                primeiro = 'a';
            }
            printf("#");
            contador2 -= 1;
            if (contador2 == 0) {
                contador3 -= 1;
                printf("\n");
                contador2 = y-1;
                y -= 1;
                if (contador3 == 0) {
                    break;
                }
            } 
            
        }
        
        break;
    }
}


int main() {

    quadradoBrabo();
    // xadrez(); -> 3.2 
    // trianguloBrabo();
    return 0;  
}