#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>

int main() {
    int fds[2];

    if (pipe(fds) == -1) {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    }

    switch (pid) {
        case -1: {
            perror("Fork failed");
            break;
        }
        case 0: {
            close(fds[0]);
            
            close(fds[1]);
            break;
        }
        default: {
            // pai
            close(fds[1]);
            int value_read;
            int bytes_read = 1;
            while (bytes_read > 0) {
                printf("Pai: | i'll read\n");
                bytes_read = read(fds[0], &value_read, sizeof(int));
                printf("Pai: | read %d bytes with value %d\n", bytes_read, value_read);
            }
            close(fds[0]);
            printf("Pai: | finished\n");

            int status;
            int wait_res = wait(&status);
            if (WIFEXITED(status)) {
                printf("Pai: | child exited with status %d\n", wait_res, WEXITSTATUS(status));
            } else {
                printf("Pai: | child exited abnormally\n");
            }
            break;
        }
    }     // PRIMEIRO LEMOS DO PIPE E DEPOIS ESPERAMOS

    return 0;
}