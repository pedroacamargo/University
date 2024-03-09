#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main() {
    printf("PARENT - PID: %d, PPID: %d\n", getpid(), getppid());
    int res;

    for (int i = 0; i < 10; i++) {
        res = fork();

        if (res == 0) {
            printf("CHILD %d - PID: %d, PPID: %d\n", i, getpid(), getppid());

            int status;
            int terminated_pid = wait(&status);
            sleep(1);
            
            _exit(i);
        }
    }



    for (int i = 0; i < 10; i++) {
        int status;
        int terminated_pid = wait(&status);
        printf("PARENT - return %d %d\n", terminated_pid, WEXITSTATUS(status));
    }

    return 0;
}