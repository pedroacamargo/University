#include <stdio.h>
#include <stdlib.h>
#include <time.h>



int main(){
    
    // pseudo random numbers = A set of values or elements that are statistically random
    //                         (Don't use these for anu sort of cryptographic security)

    srand(time(0)); // use the current time to give us a seed for random numbers

    int number1 = (rand() % 6) + 1; // rand gives a number 0 - 32767
    int number2 = (rand() % 6) + 1;
    int number3 = (rand() % 6) + 1;

    printf("%d\n", number1);
    printf("%d\n", number2);
    printf("%d\n", number3);

    return 0;
}