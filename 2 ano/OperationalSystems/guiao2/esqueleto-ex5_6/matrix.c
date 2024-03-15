#include "matrix.h"


int **createMatrix() {

    // seed random numbers
    srand(time(NULL));
    // srand(100); // for debugging purposes
    
    // Allocate and populate matrix with random numbers.
    printf("Generating numbers from 0 to %d...", MAX_RAND);
    int **matrix = (int **) malloc(sizeof(int*) * ROWS);
    for (int i = 0; i < ROWS; i++) {
        matrix[i] = (int*) malloc(sizeof(int) * COLUMNS);
        for (int j = 0; j < COLUMNS; j++) {
            matrix[i][j] = rand() % MAX_RAND;
        }
    }
    printf("Done.\n");

    return matrix;
}

void printMatrix(int **matrix) {

    for (int i = 0; i < ROWS; i++) {
        printf("%2d | ", i);
        for (int j = 0; j < COLUMNS; j++) {
            printf("%7d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// ex.5
int valueExists(int **matrix, int value) {
    int fs;
    int pids[ROWS];
    for (int i = 0; i < ROWS; i++) {
        fs = fork();

        if (fs == 0) {
            int res = 0;
            // printf("Child %d searching for value %d in row %d\n", getpid(), value, i);
            for (int j = 0; j < COLUMNS; j++) {
                if (matrix[i][j] == value) {
                    printf("Value %d found at (%d, %d)\n", value, j, i);
                    res += 1;
                }
            }
            _exit(res);
        } else {
            pids[i] = fs;
        }
    }

    int status;
    for (int i = 0; i < 10; i++) {
        // int terminated_pid = wait(&status);
        pid_t terminated_pid = waitpid(pids[i], &status, 0);

        if (WIFEXITED(status)) {
            if (WEXITSTATUS(status) > 0) {
                printf("Child %d found %d occurrences\n", terminated_pid, WEXITSTATUS(status));
            } else {
                printf("Child %d terminated with status %d\n", terminated_pid, WEXITSTATUS(status));
            }
        } else {
            printf("Child %d terminated with status %d\n", terminated_pid, WEXITSTATUS(status));
        }
    }


    return 0;
}


// ex.6
void linesWithValue(int **matrix, int value) {

    // TO DOm
}