#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main() {

    int res = fork();

    if (res == 0) {
        // child
        printf("CHILD - PID: %d, PPID: %d\n", getpid(), getppid());
        sleep(10);
        printf("CHILD - finished\n");
        _exit(0);
    } else {
        // parent
        printf("PARENT - PID: %d, PPID: %d, Child_PID: %d\n", getpid(), getppid(), res);

        sleep(10);

        printf("PARENT - I will wait\n");
        int status;
        int pid_finished = wait(&status);

        if (WIFEXITED(status))
            printf("PARENT - Child %d finished with status %d\n", pid_finished, WEXITSTATUS(status));
        else printf("PARENT - Child exited abnormally\n");


        sleep(10);
    }

    printf("PARENT - finished\n");

    return 0;
}