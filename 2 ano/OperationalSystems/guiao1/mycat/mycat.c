#include "mycat.h"

// quando chamamos uma função read, o programa fica bloqueado e so para quando passamos o \n ou 0
// usar o CTRL + D para sair de um processo
// echo $? - last exit code

int mycat() {
    ssize_t bytesLidos, bytesEscritos;
    char buffer[BUFFER_SIZE];

    while ((bytesLidos = read(STDIN_FILENO, buffer, BUFFER_SIZE)) > 0) {

        // printf("li %ld bytes \n", bytesLidos);

        bytesEscritos = write(STDOUT_FILENO, buffer, bytesLidos); // escrever para o stdout
        // printf("escrevi %ld bytes \n", bytesEscritos);

        if (bytesLidos != bytesEscritos) {
            perror("Failed to write to stdout");
            return 1;
        }
    }
    return 0;
}