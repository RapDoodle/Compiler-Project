// Compiler Construction Group Project (Phase 1)
//
// Authors: Group 1
// Date: 11/08/2021
// Compiler: Visual C++ 2019
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>

#include "lexer.h"
#include "buffer.h"
#include "utils.h"
#include "stack.h"
#include "parser.h"


char* lexer(char* str)
{
    if (strlen(str) == 0)
        return NULL;

    // prev_ptr is used to keep track of the beginning of a token
    char* prev_ptr = NULL;
    char* ptr = str;
    int token_idx = -1;

    // Variables for the buffer
    char* buffer = create_buffer(64);
    int buffer_size = 64;
    int buffer_offset = 0;
    while (ptr != NULL && *ptr != '\0' && *ptr != '\n') {
        prev_ptr = ptr;
        ptr = next_token(ptr, &token_idx);
        printf("%d ", dfa2tkid(accepted_states[token_idx]));

        if (token_idx < 0) {
            // Override all data in the buffer with the error message
            sprintf(buffer, "Lexecal error.");
        } else {
            write_buffer_string(&buffer, lexemes[token_idx], &buffer_size, &buffer_offset);
            write_buffer_char(&buffer, ' ', &buffer_size, &buffer_offset);
        }
    }
    return buffer;
}


int main()
{
    printf("Relational Algebra Analyzer (Version: 1.1)\nBuilt by Group 1\n\n");

    Stack stack;
    create_stack(&stack, 64);
    
    // Read from the file
    int buffer_size = 64;
    char* buffer = create_buffer(buffer_size);
    int buffer_offset = 0;

    // Open the file
    FILE* fin_ptr = fopen("in.txt", "r");
    FILE* fout_ptr = fopen("out.txt", "w");

    if (fin_ptr == NULL)
        printf("Unable to open in.txt for read.\n");
    if (fout_ptr == NULL)
        printf("Unable to open out.txt for write.\n");

    // Read from in.txt
    char ch = NULL, pk_ch = NULL;
    if (fin_ptr != NULL && (pk_ch = fpeek(fin_ptr)) != EOF) {
        printf(">>> ");
        while (true) {
            ch = fgetc(fin_ptr);
            if (ch == '\n' || ch == EOF) {
                char* out = lexer(buffer);
                printf("\n%s\n", out);

                // Write the out.txt if available
                if (fout_ptr != NULL)
                    fprintf(fout_ptr, "%s\n", out);

                // Print the '>>>' symbol if not the end of file
                if ((pk_ch = fpeek(fin_ptr)) != EOF)
                    printf(">>> ");
                else
                    break;

                buffer_size = 64;
                reset_buffer(&buffer, &buffer_size, &buffer_offset);
            } else {
                printf("%c", ch);
                write_buffer_char(&buffer, ch, &buffer_size, &buffer_offset);
            }
        }
    }

    // Close all file pointers
    if (fin_ptr != NULL)
        fclose(fin_ptr);
    if (fout_ptr != NULL)
        fclose(fout_ptr);

    // Interactive mode
    while (true) {
        printf(">>> ");

        // Reset the buffer to empty
        buffer_size = 64;
        reset_buffer(&buffer, &buffer_size, &buffer_offset);
        char current_char;

        // Read input iteratively
        while (true) {
            scanf("%c", &current_char);

            if (current_char == '\n') {
                break;
            } else {
                write_buffer_char(&buffer, current_char, &buffer_size, &buffer_offset);
            }
        }

        // Send to the lexer for lexical analysis
        char* out_str = lexer(buffer);
        if (out_str != NULL) {
            printf("%s\n", out_str);
            free(out_str);
        }

        // Reset the buffer for the next input
        buffer_size = 64;
        reset_buffer(&buffer, &buffer_size, &buffer_offset);
    }
    return 0;
}

