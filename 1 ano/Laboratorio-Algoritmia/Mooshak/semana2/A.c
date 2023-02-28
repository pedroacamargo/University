#include <stdio.h>

enum Coord{x = 0, y = 0};

int main(){
    int cartas;
    int carta;

    enum Coord posicaoFinalX = x;
    enum Coord posicaoFinalY = y;


    if (scanf("%d\n", &cartas) != 1) {
        return 1;
    }

    for (int i = 0;i < cartas; i++) {
        if (scanf("%d", &carta) != 1 && carta <= 78 && carta > 0) {
            return 1;
        }

        switch ((carta % 4)) {
            case 0:
                posicaoFinalX++;
                break;
            case 1:
                posicaoFinalY--;
                break;
            case 2:
                posicaoFinalY++;
                break;
            case 3:
                posicaoFinalX--;
                break;
        }
    }

    printf("%d %d\n",posicaoFinalX,posicaoFinalY);
    return 0;
}