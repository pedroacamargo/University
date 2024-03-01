#include <unistd.h>
#include <stdio.h>

int main() {

    printf("PID: %d, PPID: %d\n", getpid(), getppid());

    return 0;
}