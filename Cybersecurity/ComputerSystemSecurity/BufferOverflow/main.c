#include <stdio.h>
#include <string.h>

void f(char *input) {
    char buffer[100];
    // Potential buffer overflow if input exceeds 100 characters
    strcpy(buffer, input);
    printf("%s\n", buffer);
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        f(argv[1]);
    } else {
        printf("Please provide an input string.\n");
    }
    return 0;
}

// gdb ./program
// gdb$ b f
// gdb$ r A
// gdb$ p $eip