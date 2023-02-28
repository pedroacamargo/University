#include <stdio.h>
#include <stdlib.h>

int getSoldier() {
    int soldado;

    if (scanf("%d", &soldado) != 1) {
        abort();
    } else {
        return soldado;
    }
}

int main() {
    int s1,s2,s3;

    s1 = getSoldier();
    s2 = getSoldier();
    s3 = getSoldier();

    if ( (s1 == s2 && s2 == s3) || (s1 >= s2 && s2 >= s3) || (s1 <= s2 && s2 <= s3)) {
        printf("OK\n");
    } else {
        printf("NAO\n");
    }

    return 0;
}