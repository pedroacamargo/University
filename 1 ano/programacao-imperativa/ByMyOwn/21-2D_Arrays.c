#include <stdio.h>

int main() {
    // 2D array = an array, where each element is an entire array
    // useful if you need a matrix, grid, or table of data


    int numbers[2][3] = {
                        {1,2,3},
                        {4,5,6}
                        };

    int rows = sizeof(numbers)/sizeof(numbers[0]);
    int columns = sizeof(numbers[0])/sizeof(numbers[0][0]);
    printf("rows: %d\n", rows);
    printf("columns: %d\n", columns);


    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%d ",numbers[i][j]);
        }
        printf("\n");
    }
}