#include <stdio.h>

/*  Jogador     Inzel       CMD
    Pedra        @           *   
    Papel        |           -
    Tesoura      X           +
*/

int main(){
    int N = 0;
    int InzelWins = 0;
    int CMDWins = 0;
    int draws = 0;
    char inzel,CMD;

    if (scanf("%d\n", &N) != 1) return 1;

    for (int i = 0; i < N; i++) {
        if (scanf("\n%c", &inzel) != 1) return 1;
        if (scanf("%c", &CMD) != 1) return 1;

        switch (inzel) {
            case '@':
                switch (CMD) {
                    case '*':
                        draws++;
                        break;
                    case '-':
                        CMDWins++;
                        break;
                    case '+':
                        InzelWins++;
                        break;
                }   
                break;
            case '|':
                switch (CMD) {
                    case '*':
                        InzelWins++;
                        break;
                    case '-':
                        draws++;
                        break;
                    case '+':
                        CMDWins++;
                        break;
                }
                break;
            case 'X':
                switch(CMD) {
                    case '*':
                        CMDWins++;
                        break;
                    case '-':
                        InzelWins++;
                        break;
                    case '+':
                        draws++;
                        break;
                }
                break;
        }
    }

    printf("%d %d %d\n", InzelWins,CMDWins,draws);

    return 0;
}

