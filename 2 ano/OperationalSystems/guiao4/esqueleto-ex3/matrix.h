#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

#define MAX_RAND 10
#define ROWS 10
#define COLUMNS 20

typedef struct Minfo{
    int line_nr;
    int ocur_nr;
} Minfo;

int **createMatrix();

void printMatrix(int **matrix);

void lookupNumber(int** matrix, int value, int* vector);
