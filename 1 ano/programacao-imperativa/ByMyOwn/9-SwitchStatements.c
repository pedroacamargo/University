#include <stdio.h>

// switch = A more efficient alternative to using many "else if" statemets allows a value to be tested for equality against many cases
int main() {
    char grade; 

    printf("\n Enter a letter grade: ");
    scanf("%c", &grade);

    switch (grade) {
    case 'A':
        printf("Perfect! \n");
        break;
    case 'B':
        printf("Very Good! \n");
        break;
    case 'C':
        printf("Good! \n");
        break;
    case 'D':
        printf("At least it's not an F!\n");
        break;
    case 'F':
        printf("YOU FAILED! \n");
        break;
    default:
        printf("Please enter only valid grades.");
        break;
    }

}



