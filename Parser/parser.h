#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#include "stack.h"
#include "buffer.h"
#include "slr1.h"

int dfa2tkid(int dfa_state);
/*
 function:
	Convert the state id in the DFA to the token id for the SLR(1)
	parsing table
 argunment:
	dfa_state: The state in the DFA. When -1 is specified, the index
		for $ (EOF) is returned
 return:
	int: The token id in the SLR(1) parsing table. or -1 if the token
		is not found.
*/

char* get_parser_stack(Stack* stack);
/*
 function:
	Get the stack's string representation for the SLR(1) parser
 argunment:
	stack: The address of the stack
 return:
	char*: A string containing the stack's string representation
*/
