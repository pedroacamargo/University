#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    const int MIN = 1;
    const int MAX = 100;
    int guess;
    int guesses = 0;
    int answer;

    // uses the current time as a seed
    srand(time(0));

    answer = (rand() % MAX) + MIN; // generates a random number between MIN & MAX

    do {
        printf("Enter a guess: ");
        scanf("%d", &guess);

        if (guess > answer) {
            printf("Your guess is too high.\n");
        } else if (guess < answer) {
            printf("Your guess is too low.\n");
        } else {
            printf("You got it!\n");
        }

        guesses++;
    } while (guess != answer);

    printf("************************\n");
    printf("Answer: %d\n", answer);
    printf("Guesses: %d\n", guesses);
    printf("************************");

    return 0;
}