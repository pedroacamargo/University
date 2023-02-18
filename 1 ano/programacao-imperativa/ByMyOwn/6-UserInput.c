#include <stdio.h>
#include <string.h> // work with strings

int main() {
    char name[25]; // bytes
    int age;
    
    printf("What's your name?");
    // scanf("%s", &name); scanf can't read white spaces
    fgets(name, 25, stdin); // get an input with white space
    name[strlen(name) - 1] = '\0'; // remove the \n specifier

    printf("\nHow old are you?\n");
    scanf("%d", &age);

    printf("Hello %s, how are you?",name);
    printf("You are %d years old", age);

    return 0;
}