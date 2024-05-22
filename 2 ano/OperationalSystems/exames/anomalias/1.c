#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#define READ_PIPE 0
#define WRITE_PIPE 1

void defeitos(int N, char* imagens[N], int max) {
    int atual = 0;
    for (int i = 0; i < N; i++) {
        if (fork() == 0) {
            int res = execlp("./detectAnom.sh", "detectAnom", imagens[i]);
            _exit(0);
        }

        atual++;

        int status;
        if (atual == max) {
            wait(&status); 
            atual--;
        }
    }
}

void conta(int N, char* imagens[N]) {
    char buffer[50 * N];
    int p[2];
    pipe(p);

    if (fork() == 0) {
        dup2(p[WRITE_PIPE], STDOUT_FILENO);
        close(p[WRITE_PIPE]); close(p[READ_PIPE]);
        defeitos(N, imagens, 1);
        _exit(0);
    }

    int status;
    wait(&status);

    if (fork() == 0) {
        dup2(p[READ_PIPE], STDIN_FILENO);
        close(p[WRITE_PIPE]); close(p[READ_PIPE]);
        execlp("wc", "wc", "-l", NULL);
        _exit(0);
    }
    close(p[1]);
    close(p[0]);

    wait(&status);
}

int main() {

    char *imagens[20] = {"img1", "img2", "img3", "img4", "img5", "img6", "img7", "img8", "img9", "img10", "img11", "img12", "img13", "img14", "img15", "img16", "img17", "img18", "img19", "img20"};

    char *imagens2[2] = {"img1", "img2"};

    conta(20, imagens);

    return 0; 
}