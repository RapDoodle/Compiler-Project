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
#include "stack.h"


char* lexer(char* str)
{
    if (strlen(str) == 0)
        return NULL;

    char* inp_ptr = str, *prev_inp_ptr = NULL;
    int token_idx = -1;

    // Variables for the buffer
    char* buffer = create_buffer(64);
    int buffer_size = 64, buffer_offset = 0;

    int state = 0, actn_shft = -1, actn_rdc = -1, pop_len = 0, rule_id = -1, par_tkid = -1;

    Stack stack;
    create_stack(&stack, 64);
    stack_push(&stack, 0);

    // End of string
    bool eos = false;

    while (!eos) {
        prev_inp_ptr = inp_ptr;
        if (inp_ptr != NULL && *inp_ptr != '\0' && *inp_ptr != '\n') {
            inp_ptr = next_token(inp_ptr, &token_idx);
            if (token_idx < 0) {
                // Override all data in the buffer with the error message
                sprintf(buffer, "Lexecal error.");
                break;
            }

            // Convert to parser token id
            par_tkid = dfa2tkid(accepted_states[token_idx]);
        } else {
            // Get the token id for $
            par_tkid = dfa2tkid(-1);
            eos = true;
        }

        // Check for accept
        // Check for whether to accept the string
        if (actn_acc_tbl[state][par_tkid]) {
            printf("Accept\n");
            break;
        }

        // Check for shift
        actn_shft = actn_shft_tbl[state][par_tkid];
        if (actn_shft >= 0) {
            // Proceed to shift
            state = actn_shft;

            printf("Shift %d\n", actn_shft);

            // Push the current character
            stack_push(&stack, par_tkid);
            stack_push(&stack, state);

            eos = false;
            
        } else {
            // Check for reduce
            actn_rdc = actn_rdc_tbl[state][par_tkid];
            if (actn_rdc >= 0) {
                printf("Reduce %d\n", actn_rdc);

                // Rewind
                inp_ptr = prev_inp_ptr;
                // Proceed to reduce
                // Pop the rhs
                pop_len = rules_tk_count[actn_rdc] * 2;
                int stack_val = 0;
                for (int i = 0; i < pop_len; i++)
                    stack_pop(&stack, &stack_val);

                peek_stack(&stack, &stack_val);
                state = stack_val;

                // Push the lhs to the stack
                stack_push(&stack, -1 * actn_rdc);

                // Push the goto number to the stack
                int rule_id = rules_lhs_idx[actn_rdc];
                state = goto_tbl[state][rule_id];
                stack_push(&stack, state);

                eos = false;
            } else {
                printf("Syntax error\n");
                break;
            }

        }

        char* output_str = show_parser_stack(&stack);
        printf("Stack: |%s|%s|\n", output_str, inp_ptr);
        // write_buffer_string(&buffer, lexemes[token_idx], &buffer_size, &buffer_offset);
        // write_buffer_char(&buffer, ' ', &buffer_size, &buffer_offset);

        
        // printf("%d ", );
    }

    // Check for whether to accept the string
    if (actn_acc_tbl[state][dfa2tkid(-1)])
        printf("Accept!\n");
    else
        printf("Rejected\n");
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

