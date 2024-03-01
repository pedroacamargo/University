#include "mycp.h"

int main(int argc, char *argv[]) {

    // printf("argc: %d\n", argc);

    if (argc != 3) {
        printf("Usage: %s <origem> <destino>\n", argv[0]);
        return 1;
    }

    return mycp(argv[1], argv[2]);
}
