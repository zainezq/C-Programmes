### README.md:

# Simple Lexers for Learning Purposes

This repository contains two example lexers written in C that are intended for learning purposes. The lexers are not complete and do not handle all possible cases. They serve as a starting point for understanding the basics of lexer implementation in the context of compiler construction.

## Usage

1. **Compile the Lexers:**

   ```bash
   gcc lexer.c -o lexer
   gcc lexer2.c -o lexer2
   ```

2. **Run the Lexers:**

   ```bash
   ./lexer hello.c
   ./lexer2 hello.c
   ```

   The lexers will read an input file and print the identified tokens to the console.

## Important Note

These lexers are incomplete and may not handle all possible input cases. They are meant for educational purposes, providing a foundation for those who want to learn about lexer design and implementation (and possibly compiler designing).

## Learning Objectives

- Understand the basic structure and logic of a lexer.
- Explore tokenization of simple constructs such as integers, floats, and identifiers.
- Recognize the challenges and considerations in lexer development.

## Compiler Diagram 
   **A simple diagram to help understand how compilers work:**
   
![Compilation Diagram](https://raw.githubusercontent.com/zainezq/C-Programmes/main/lexer-skeleton/CompilerDiagram.png)


## Disclaimer

These lexers are not intended for production use. If you require a production-ready lexer, consider using established tools and libraries such as Flex.
