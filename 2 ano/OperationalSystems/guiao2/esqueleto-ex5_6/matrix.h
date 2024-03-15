#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

#define MAX_RAND 100
#define ROWS 200
#define COLUMNS 200



int **createMatrix();

void printMatrix(int **matrix);

// ex.5
int valueExists(int **matrix, int value);

// ex.6
void linesWithValue(int **matrix, int value);