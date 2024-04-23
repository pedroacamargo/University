#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>


int main() {
    int bytes_read;
    char buffer[1024];

    int pipe_fd[2];
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        return 1;
    }    


    int fork_res = fork();
    if (fork_res == -1) {
        perror("fork");
        return 2;
    }

    if (fork_res == 0) {
        // child
        close(pipe_fd[1]); // se nao fechar o pipe, o wc nao termina e o programa fica entra em deadlock
        dup2(pipe_fd[0], STDIN_FILENO); // ler do pipe
        close(pipe_fd[0]);
        int exec_res = execlp("wc", "wc", "-l", NULL);
        _exit(0);
    }

    close(pipe_fd[0]);
    

