#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>

// wc < /etc/passwd > saida.txt 

int main() {
    // in
    int fd_in = open("/etc/passwd", O_RDONLY);
    if (fd_in == -1) {
        perror("open");
        return 1;
    }

    int res = dup2(fd_in, STDIN_FILENO);
    if (res == -1) {
        perror("dup2");
        return 2;
    }

    // printf("dup2 in = %d\n", res);

    close(fd_in);
    printf("redirecionei STDIN para /etc/passwd\n");

    // out
    int fd_out = open("saida.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666); // O_TRUNC -> Start writing at the beginning of the file
    if (fd_out == -1) {
        perror("open");
        return 1;
    }

    int fd_out_original = dup(STDOUT_FILENO); 
    int resOut = dup2(fd_out, 1);
    if (resOut == -1) {
        perror("dup2");
        return 2;
    }
    close(fd_out);
    printf("redirecionei STDOUT para saida.txt\n");


    // error
    int fd_err = open("erros.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd_err == -1) {
        perror("open");
        return 1;
    }

    int resErr = dup2(fd_err, 2);
    if (resErr == -1) {
        perror("dup2");
        return 2;
    }
    close(fd_err);
    printf("redirecionei STDERR para erros.txt\n");
    

    int exec_res = execlp("wc", "wc", NULL);
    if (exec_res == -1) {
        perror("exec");
        return 3;
    }



    dup2(fd_out_original, 1);
    printf("Fim\n");

    return 0;
}