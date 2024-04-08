#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char *argv[]) {

    int fifo_fd = open("fifo", O_WRONLY);
    printf("FIFO opened to write...\n");
    if (fifo_fd == -1) {
        perror("open");
        exit(1);
    }


    char BUFFER[256];
    size_t read_bytes;

    while ((read_bytes = read(STDIN_FILENO, BUFFER, sizeof(BUFFER))) > 0) {
        if (write(fifo_fd, BUFFER, read_bytes) == -1) {
            perror("write");
            exit(1);
        }
    }

    close(fifo_fd);

    return 0;
}