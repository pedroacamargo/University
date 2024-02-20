#include "pessoas.h"

// quando chamamos uma função read, o programa fica bloqueado e so para quando passamos o \n ou 0
// usar o CTRL + D para sair de um processo
// echo $? - last exit code

int pessoas(char *origem, char *destino) {
    ssize_t bytesLidos, bytesEscritos;
    char buffer[BUFFER_SIZE];
    
    int fd = open(origem, O_RDONLY);
    int fd2 = open(destino, O_WRONLY);

    // printf("fd: %d\n", fd);
    // printf("fd2: %d\n", fd2);

    if ((bytesLidos = read(fd, buffer, BUFFER_SIZE)) > 0) {

        bytesEscritos = write(fd2, buffer, bytesLidos); // escrever para o stdout

        if (bytesLidos != bytesEscritos) {
            perror("Failed to write to stdout");
            return 1;
        }

    } else {
        perror("Failed to read from file");
        return 1;
    }

    close(fd);
    close(fd2);

    return 0;
}