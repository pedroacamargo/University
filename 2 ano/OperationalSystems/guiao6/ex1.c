#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main() {
    // in
    int fd_in = open("/etc/passwd", O_RDONLY);
    if (fd_in == -1) {
        perror("open");
        return 1;
    }

    int res = dup2(fd_in, 0);
    if (res == -1) {
        perror("dup2");
        return 2;
    }

    printf("dup2 in = %d\n", res);

    close(fd_in);

    // out
    int fd_out = open("saida.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd_out == -1) {
        perror("open");
        return 1;
    }

    int fd_out_original = dup(1);
    int resOut = dup2(fd_out, 1);
    if (resOut == -1) {
        perror("dup2");
        return 2;
    }

    printf("dup2 in = %d\n", resOut);

    close(fd_out);


    // out
    int fd_err = open("saida.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd_err == -1) {
        perror("open");
        return 1;
    }

    int resErr = dup2(fd_err, 2);
    if (resErr == -1) {
        perror("dup2");
        return 2;
    }

    printf("dup2 in = %d\n", resErr);

    close(fd_err);

    char buffer[1024];
    int bytes_read;

    while ((bytes_read = read(0, buffer, 1024)) > 0) {
        write(1, buffer, bytes_read);
        write(2, buffer, bytes_read);
    }

    dup2(fd_out_original, 1);

    printf("Fim\n");

    return 0;
}