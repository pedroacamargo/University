#include <stdio.h>
#include <stdbool.h>

int main() {
    // logical operators = && (AND) checks if two conditions are true
    //                     || (OR) check if one of the conditions is true
    //                     !  (NOT) reverses the state of a condition

    float temp = 25;
    bool sunny = false;

    if(temp >= 0 && temp <= 30 && sunny == true || temp <= 15 && temp > 0) {
        printf("The weather is good!");
    } else {
        printf("The weather is bad!");
    }

    if (!sunny) {
        printf("The weather is bad!");
    }

    return 0;
}