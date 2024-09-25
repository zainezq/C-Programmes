#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

// Token types
typedef enum {
    TOKEN_KEYWORD,
    TOKEN_IDENTIFIER,
    TOKEN_EOF,
    TOKEN_FUN,
    TOKEN_GLOBAL_VAR,
    TOKEN_LOCAL_VAR,
    TOKEN_CHAR,
    TOKEN_ELSE,
    TOKEN_IF,
    TOKEN_INT,
    TOKEN_RETURN,
    TOKEN_WHILE,
    TOKEN_ASSIGN,
    TOKEN_EQUATE,
    TOKEN_ADD,
    TOKEN_SUB,
    TOKEN_MUL,
    TOKEN_DIV,
    TOKEN_INCREMENT,
    TOKEN_DECREMENT,
    TOKEN_SEMICOLON
    
} TokenType;

// Token structure
typedef struct {
    TokenType type;
    char value[100];  // Assuming a maximum identifier or literal length of 100 characters
} Token;

// Lexer structure
typedef struct {
    char* input;
    int current;
} Lexer;

// Initialize a new lexer
Lexer* createLexer(char* input) {
    Lexer* lexer = (Lexer*)malloc(sizeof(Lexer));
    lexer->input = input;
    lexer->current = 0;
    return lexer;
}

// Free the lexer
void destroyLexer(Lexer* lexer) {
    free(lexer);
}

// Get the next token from the lexer
Token getNextToken(Lexer* lexer) {
    Token token;
    char c = lexer->input[lexer->current];

    // Skip whitespace
    while (isspace(c)){
        ++lexer->current;
        c = lexer->input[lexer->current];
    }
    
    if (c == '#')
    {
        
    }
    
    // Check for end of file
    if (c == '\0') {
        token.type = TOKEN_EOF;
        strcpy(token.value, "");
        return token;
    }

    // Check for keywords or identifiers
    if (isalpha(c)) {
        int i = 0;
        while (isalnum(c) || c == '_') {
            token.value[i++] = c;
            ++lexer->current;
            c = lexer->input[lexer->current];
        }
        token.value[i] = '\0';

        // Check if it's a keyword
        if (strcmp(token.value, "int") == 0) {
            token.type = TOKEN_KEYWORD;
        } else if (strcmp(token.value, "char") == 0)
        {
            token.type = TOKEN_KEYWORD;
        }
         
        
        else {
            token.type = TOKEN_IDENTIFIER;
        }
        return token;
    }

    // Check for integer literals
    if (isdigit(c)) {
        int i = 0;
        while (isdigit(c)) {
            token.value[i++] = c;
            ++lexer->current;
            c = lexer->input[lexer->current];
        }
        token.value[i] = '\0';
        token.type = TOKEN_INT;
        return token;
    }


    // Check for special characters like '='
    if (c == '=') {
        int i = 0;
        while (c == '=') {
            token.value[i++] = c;
            ++lexer->current;
            c = lexer->input[lexer->current];
        }
        // Null-terminate the string after the loop
        token.value[i] = '\0';

        // Check the content of token.value
        if (strcmp(token.value, "=") == 0) {
            token.type = TOKEN_ASSIGN;
        } else if (strcmp(token.value, "==") == 0) {
            token.type = TOKEN_EQUATE;
        }
        return token;
    }

     // Check for character constant
    if (c == '\'') {
        token.type = TOKEN_CHAR;
        token.value[0] = c;  // Include the opening single quote

        // Read the character inside the single quotes
        ++lexer->current;
        c = lexer->input[lexer->current];
        
        if (c != '\'' && c != '\0') {
            token.value[1] = c;
            ++lexer->current;
        } else {
            // Handle error: Empty character constant or missing closing quote
            token.type = TOKEN_EOF;
            return token;
        }

        // Check for the closing single quote
        if (lexer->input[lexer->current] == '\'') {
            token.value[2] = '\'';
            token.value[3] = '\0';  // Null-terminate the string
            ++lexer->current;  // Move past the closing single quote
            return token;
        } else {
            // Handle error: Missing closing quote
            token.type = TOKEN_EOF;
            return token;
        }
    }
    if (c == ';') {
        //printf("making checks %c", c);
        token.type = TOKEN_SEMICOLON;
        token.value[0] = c;
        token.value[1] = '\0';  // Null-terminate the string
        ++lexer->current;
        c = lexer->input[lexer->current];
        return token;
    }

    // If none of the above, treat as an unknown character
    token.type = TOKEN_EOF;
    strcpy(token.value, "");
    ++lexer->current;
    return token;
}

int main(int argc, char *argv[]) {

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

    // Allocate memory to store the file content
    char *input = (char *)malloc(file_size + 1);
    if (input == NULL) {
        perror("Error allocating memory");
        fclose(file);
        return 1;
    }

    // Read the file content into the input buffer
    fread(input, 1, file_size, file);
    input[file_size] = '\0';  // Null-terminate the string

    // Close the file
    fclose(file);

    Lexer* lexer = createLexer(input);

    Token token = getNextToken(lexer);
     while (1) {
        printf("Type: %d, Value: %s\n", token.type, token.value);
        token = getNextToken(lexer);

        // Check for the end of the input
        if (token.type == TOKEN_EOF) {
            break;
        }
    }


    destroyLexer(lexer);
    return 0;
}
