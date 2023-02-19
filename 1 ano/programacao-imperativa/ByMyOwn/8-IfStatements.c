#include <stdio.h>

int main() {
    int age;

    printf("\nEnter your age: ");
    scanf("%d", &age);

    if (age >= 18) {
        printf("\nYou are now signed up!");
    } else if (age < 0) {
        printf("\nYou haven't been born yet!");
    } else {
        printf("\nYou are too young to sign up!");
    }
}