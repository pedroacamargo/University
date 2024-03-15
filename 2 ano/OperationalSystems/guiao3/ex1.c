#include <stdio.h>
#include <unistd.h>


// /bin - comandos do sistema unix
int main(int argc, char** argv) {

    // int res = execl("/bin/ls", "ls", "-l", NULL);
    // if (res == -1) {
    //     perror("Erro");
    // }

    // Will run $PATH
    int res2 = execlp("ls", "ls", "-l", NULL);

    printf("res = %d\n", res2);

    return 0;
}