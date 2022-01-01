#include "parser.h"

int dfa2tkid(int dfa_state)
{
	// Return the max + 1 index
	if (dfa_state < 0) {
		int max_val = -1;
		for (int i = 0; i < dfa2tkid_tbl_len; i++) {
			if (max_val < dfa2tkid_tbl[i]) {
				max_val = dfa2tkid_tbl[i];
			}
		}
		return max_val + 1;
	}
	
	if (dfa_state >= 0 && dfa_state < dfa2tkid_tbl_len) {
		return dfa2tkid_tbl[dfa_state];
	}
}

char* get_parser_stack(Stack* stack)
{
	// Initialize a string buffer
	char* buffer = create_buffer(64);
	int buffer_size = 64, buffer_offset = 0;

	int val = -1;
	if (!is_stack_empty(stack)) {
		// Print from the top to bottom
		for (int i = 0; i <= stack->top; i++) {
			val = stack->values[i];
			if (i % 2 == 0) {
				char num_str[16];
				sprintf(num_str, "%d ", val);
				write_buffer_string(&buffer, num_str, &buffer_size, &buffer_offset);
			} else {
				if (val < stack_rule_offset) {
					// Ids
					write_buffer_string(&buffer, parser_tks[val], &buffer_size, &buffer_offset);
					
				} else {
					// Tokens
					write_buffer_string(&buffer, rules_lhs_sym[val - stack_rule_offset], &buffer_size, &buffer_offset);
					
				}
			}
		}
	}

	return buffer;
}