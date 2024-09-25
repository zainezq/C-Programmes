#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef enum {
    TOKEN_INT,
    TOKEN_FLOAT,
    TOKEN_IDENTIFIER,
    TOKEN_OPERATOR,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_SEMICOLON,
    TOKEN_UNKNOWN,
    TOKEN_END
} TokenType;

typedef struct {
    TokenType type;
    char value[100];
} Token;

Token getNextToken(FILE *file) {
    Token token;
    char c = fgetc(file);

    while (isspace(c)) {
        c = fgetc(file); // Skip whitespace
    }

    if (c == EOF) {
        token.type = TOKEN_END;
    } else if (isdigit(c)) {
        ungetc(c, file);
        fscanf(file, "%99[0-9.]", token.value);

        if (strchr(token.value, '.')) {
            token.type = TOKEN_FLOAT;
        } else {
            token.type = TOKEN_INT;
        }
    } else if (isalpha(c) || c == '_') {
        ungetc(c, file);
        fscanf(file, "%99[a-zA-Z0-9_]", token.value);
        token.type = TOKEN_IDENTIFIER;
    } else if (c == '(') {
        token.type = TOKEN_LPAREN;
        token.value[0] = c;
        token.value[1] = '\0';
    } else if (c == ')') {
        token.type = TOKEN_RPAREN;
        token.value[0] = c;
        token.value[1] = '\0';
    } else if (c == ';') {
        token.type = TOKEN_SEMICOLON;
        token.value[0] = c;
        token.value[1] = '\0';
    } else {
        token.type = TOKEN_OPERATOR;
        token.value[0] = c;
        token.value[1] = '\0';
    }

    return token;
}

int main(int argc, char *argv[]) {


     // Check if the correct number of command-line arguments is provided
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    // Open the input file
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Determine the file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    Token token;

    do {
        token = getNextToken(file);

        switch (token.type) {
            case TOKEN_INT:
                printf("Token: INT, Value: %s\n", token.value);
                break;
            case TOKEN_FLOAT:
                printf("Token: FLOAT, Value: %s\n", token.value);
                break;
            case TOKEN_IDENTIFIER:
                printf("Token: IDENTIFIER, Value: %s\n", token.value);
                break;
            case TOKEN_OPERATOR:
                printf("Token: OPERATOR, Value: %s\n", token.value);
                break;
            case TOKEN_LPAREN:
                printf("Token: LPAREN, Value: %s\n", token.value);
                break;
            case TOKEN_RPAREN:
                printf("Token: RPAREN, Value: %s\n", token.value);
                break;
            case TOKEN_SEMICOLON:
                printf("Token: SEMICOLON, Value: %s\n", token.value);
                break;
            case TOKEN_UNKNOWN:
                printf("Token: UNKNOWN\n");
                break;
            case TOKEN_END:
                printf("End of file reached.\n");
                break;
        }

    } while (token.type != TOKEN_END);

    fclose(file);
    return 0;
}
