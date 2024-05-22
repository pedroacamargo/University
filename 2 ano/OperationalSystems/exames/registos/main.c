#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

#define READ_PIPE 0
#define WRITE_PIPE 1

struct RegistoF {
    char nome[20];
    char cargo[20];
    int salário;
};

void aumentaSalario(char *ficheiro, char *cargo, int valor, long N, int P) {
    int fd = open(ficheiro, O_RDWR);
    size_t read_bytes;
    struct RegistoF registo;
    while (read_bytes = read(fd, &registo, sizeof(registo)) > 0) {
        if (strcmp(cargo, registo.cargo)) {
            registo.salário += valor;
            lseek(fd, -sizeof(struct RegistoF), SEEK_CUR);
            write(fd, &registo, sizeof(struct RegistoF));
        }
    }
}

int main() {

    struct RegistoF registo;

    return 0; 
}