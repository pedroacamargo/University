#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main() {

    int fifo_fd = open("fifo", O_RDONLY);
    printf("FIFO opened to read...\n");
    char buffer[256];
    size_t read_bytes;

    while ((read_bytes = read(fifo_fd, buffer, sizeof(buffer))) > 0) {
        if (write(STDOUT_FILENO, buffer, read_bytes) == -1) {
            perror("write");
            exit(1);
        }
    }

    return 0;
}