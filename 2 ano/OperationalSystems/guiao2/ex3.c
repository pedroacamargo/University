#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main() {
    printf("PARENT - PID: %d, PPID: %d\n", getpid(), getppid());
    int res;

    for (int i = 0; i < 10; i++) {
        res = fork();

        if (res == 0) {
            // FILHO


            // child - print pid,ppid and i
            printf("CHILD %d - PID: %d, PPID: %d\n", i, getpid(), getppid());
            sleep(1);
            
            // _exit(i);
        } else {
            int status;
            int terminated_pid = wait(&status);

            printf("PARENT - return %d\n", WEXITSTATUS(status));
        }
    }


}