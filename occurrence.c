#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 50
#define MAX_WORDS 1000

void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

int isDelimiter(char c) {
    return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == ',' || c == '.' || c == '!' || c == '?');
}

int main() {
    char filename[100];
    char word[MAX_WORD_LENGTH];
    char words[MAX_WORDS][MAX_WORD_LENGTH];
    int count[MAX_WORDS];
    int wordCount = 0;

    // Prompt the user to enter the filename
    printf("Enter the filename: ");
    scanf("%s", filename);

    // Attempt to open the file for reading
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("File not found or could not be opened.\n");
        return 1;
    }

    // Read words from the file
    while (fscanf(file, "%s", word) != EOF) {
        // Convert the word to lowercase for consistency
        toLowerCase(word);

        int found = 0;
        for (int i = 0; i < wordCount; i++) {
            if (strcmp(words[i], word) == 0) {
                // If the word is found, increment its count
                count[i]++;
                found = 1;
                break;
            }
        }

        if (!found) {
            if (wordCount < MAX_WORDS) {
                // If the word is not found and there's space, add it to the arrays
                strcpy(words[wordCount], word);
                count[wordCount] = 1;
                wordCount++;
            } else {
                printf("Maximum word count exceeded. Some words may not be counted.\n");
            }
        }
    }

    // Close the file
    fclose(file);

    // Display word frequency
    printf("\nWord Frequency:\n");
    for (int i = 0; i < wordCount; i++) {
        printf("%s: %d\n", words[i], count[i]);
    }

    return 0;
}
