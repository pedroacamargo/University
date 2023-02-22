#include <stdio.h>

void hello(char[], int); // function prototype

int main() {
    // function prototype

    // What is it?
    // Functions declaration, w/o a body, before main()
    // Ensures that calls to a function are made with the correct arguments

    // IMPORTANT NOTES:
    // Many C compilers do not check for parameter matching
    // Missing arguments will result in unexpected behavior
    // A function prototype causes the compiler to flag an error if arguments are missing

    // ADVANTAGES: 
    // 1- Easier to navigate a program w/ main() at the top
    // 2- Helps with debugging
    // 3- Commonly used in header files

    
    char name[] = "Bro";

    hello(name,21);
}

void hello(char name[], int age) {
    printf("\nHello %s", name);
    printf("\nYou are %d years old", age);
}