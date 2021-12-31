#include "lexer.h"

int get_char_index(char c)
{
    for (int i = 0; i < alphabet_len; i++)
        if (c == alphabet[i])
            return i;
    return -1;
}

char* next_token(char *ptr, int *token_idx)
{
    int current_state = 0;
    int col = -1;
    char current_char;
    while (*ptr != '\n' && *ptr != '\0') {
        current_char = *ptr;

        // If the char_index is -1, it indicates the char is not in the alphabet
        col = get_char_index(current_char);
        if (col < 0) {
            *token_idx = -1;
            return NULL;
        }

        // Jump according to the transition table
        current_state = trans_table[current_state][col];

        // Check for whether it is in final states
        for (int i = 0; i < num_accepted_states; i++) {
            if (current_state == accepted_states[i]) {
                *token_idx = i;
                return ptr+1;
            }
        }

        ptr++;
    }
    *token_idx = -1;
    return NULL;
}

