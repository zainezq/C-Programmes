#include <stdio.h>

int main() {
    // Declare a character array to store the user's name
    char name[50];

    // Prompt the user to enter their name
    printf("Enter your name: ");

    // Read the user's name from the console
    scanf("%s", name);

    // Greet the user
    printf("Hello, %s! Welcome to the meet and greet C program.\n", name);

    return 0; // Indicates successful execution
}
