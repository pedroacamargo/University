#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


// /bin - comandos do sistema unix
int main(int argc, char** argv) {
    int res = 0, status;

    char *command[3] = {"ls", "-l", NULL};

    pid_t pid = fork();
    switch (pid) {
        case -1:
            perror("An error occurred while forking the process.");
            res = -1;
            break;
        case 0:

            printf("Child process\n");
            // res = execlp("ls", "ls", "-l", NULL);
            res = execvp(command[0], command);
            if (res == -1) {
                perror("An error occurred while running the command.");
                _exit(-1);
            } _exit(1);

            break;
        case 1:
            int terminated_pid = wait(&status);
            printf("The child process has finished with status %d. %d\n", terminated_pid, WEXITSTATUS(status));
            break;
        default:
            break;
    }

    return res;
}