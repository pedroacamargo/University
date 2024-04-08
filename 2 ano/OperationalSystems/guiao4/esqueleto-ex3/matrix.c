#include "matrix.h"


int **createMatrix() {

    // seed random numbers
    srand(time(NULL));

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

void lookupNumber(int** matrix, int value, int* vector){

    //TODO
    //Hint - use the Minfo struct from matrix.h!
    int fd[2], pid;
    int pids[ROWS];

    if (pipe(fd) == -1) {
        perror("pipe");
        exit(1);
    }
    

    for(int i = 0; i < ROWS; i++){
        pid = fork();
        Minfo minfo;
        
        if (pid == 0){
            minfo.line_nr = i;
            
            for(int j = 0; j < COLUMNS; j++){
                if(matrix[i][j] == value){
                    minfo.ocur_nr++;
                }
            }

            write(fd[1], &minfo, sizeof(Minfo));
            close(fd[0]);
            exit(0);
        } else {
            pids[i] = pid;
        }
    }
    
    int status;
    for (int i = 0; i < 10; i++) {
        close(fd[1]);
        pid_t terminated_pid = waitpid(pids[i], &status, 0);

        if (WIFEXITED(status)) {
            Minfo info;
            size_t res = read(fd[0], &info, sizeof(Minfo));
            vector[info.line_nr] = info.ocur_nr;
        }
    }

}