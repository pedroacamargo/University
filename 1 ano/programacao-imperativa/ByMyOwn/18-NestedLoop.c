#include <stdio.h>

int main() {
    // nested loop = a loop inside of another loop

    int rows;
    int column;
    char symbol;

    printf("\nEnter # of columns: ");
    scanf("%d",&column);

    printf("\nEnter # of rows: ");
    scanf("%d",&rows);

    for (int i = 1; i <= rows; i++) {

        for (int j = 1; j <= column; j++) {
            printf("%d", j);
        }
        printf("\n");

    }
}