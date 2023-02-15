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

int main() {
    quadradoBrabo();

    return 0;  
}