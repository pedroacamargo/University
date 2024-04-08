#include <strings.h>
#include "matrix.h"



int main(int argc, char *argv[]) {

    if(argc<2) return -1;

    // generate random matrix
    int **matrix = createMatrix();

    // print matrix
    printMatrix(matrix);

    // allocate memory and initialize vector with zeros
    int *vector = malloc(sizeof(int) * ROWS);
    bzero(vector, sizeof(int) * ROWS);

    lookupNumber(matrix, atoi(argv[1]), vector);

    // print the result vector
    printf("vector = [ ");
    for (int i = 0; i < ROWS; i++) {
        printf("%d ", vector[i]);
    }
    printf("]\n");

    
    //free vector
    free(vector);

    // free matrix
    for (int i = 0; i < ROWS; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}