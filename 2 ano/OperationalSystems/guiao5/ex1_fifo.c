#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main() {

    int res = mkfifo("fifo", 0666);
    if (res == -1) {
        perror("mkfifo");
        exit(1);
    }

    return 0;
}