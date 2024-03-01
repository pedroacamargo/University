#include "mycp.h"

// quando chamamos uma função read, o programa fica bloqueado e so para quando passamos o \n ou 0
// usar o CTRL + D para sair de um processo
// echo $? - last exit code

int mycp(char *origem, char *destino) {
    ssize_t bytesLidos, bytesEscritos;
    char buffer[BUFFER_SIZE];
    
    
    int fd = open(origem, O_RDONLY);
    if (fd == -1) {
        perror("Failed to open file");
        return -1;
    }

    // O_WRONLY - write only
    // O_CREAT - create file if it does not exist
    // O_TRUNC - truncate file to 0 length if it exists
    int fd2 = open(destino, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd2 == -1) {
        perror("Failed to open file");
        return -1;
    }


    while ((bytesLidos = read(fd, buffer, BUFFER_SIZE)) > 0) {

        bytesEscritos = write(fd2, buffer, bytesLidos); // escrever para o stdout

        if (bytesLidos != bytesEscritos) {
            perror("Failed to write to stdout");
            return 1;
        }

    }

    close(fd);
    close(fd2);

    return 0;
}