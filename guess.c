#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Seed the random number generator with the current time, to get different number each time its run
    srand(time(NULL));
    int num1;

    // Generate a random number between 0 and 19
    int r = rand() % 20;
    
    printf("Guess the number between 0 and 19: ");
    scanf("%d", &num1);  

    while (1) {
        if (num1 == r) {
            printf("Well Done! \n");
            break;
        } else if (num1 < r) {
            printf("The number you guessed is smaller than the actual number, try again \n");
        } else if (num1 > r) {
            printf("The number you guessed is larger than the actual number, try again \n");
        }

        // Get a new guess inside the loop
        printf("Guess the number between 0 and 19: ");
        scanf("%d", &num1);
    }

    printf("Random number between 0 and 19: %d\n", r);

    return 0;
}
