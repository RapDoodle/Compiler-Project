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