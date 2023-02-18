#include <stdio.h>

int main() {
    int x;
    x = 123;
    int y = 321;

    int age = 21;           // integer
    float gpa = 2.05;       // floating point number
    char grade = 'C';       // shingle character
    char name[] = "Bro";    // array of characters

    printf("You are %d years old \n", age);
    printf("Hello, %s\n", name);
    printf("Your average grade is %c\n", grade);
    printf("Your gpa is %f\n", gpa);


    return 0;
}