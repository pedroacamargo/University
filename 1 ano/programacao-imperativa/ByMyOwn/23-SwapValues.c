#include <stdio.h>
#include <string.h>

int main() {
    char x[15] = 'water';
    char y[15] = 'lemonade';
    char temp[15];

    strcopy(temp, x);
    strcopy(x, y);
    strcopy(y, temp);

    printf("x = %c\n",x);
    printf("x = %c\n",y);

    return 0;
}