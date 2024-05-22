#include "writes.h"

int main(int argc, char *argv[]) {

    if (argc != 3) {
        printf("Usage: %s <origem> <bytes>\n", argv[0]);
        return 1;
    }

    return writes(argv[1], atoi(argv[2]));
}
