#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "buffer.h"
#include "dfa.h"

int get_char_index(char c);
/*
 function:
	Get the index of a character
 argunment:
	c: The character to be indexed
 return:
	The index of the character in the DFA transition table.
	A -1 will be returned if the character is not found.
*/

int next_token(char** ptr);
/*
 function:
	Get the next token
 argunment:
	ptr: The address of the variable that stores the input string
	to
 return:
	true if the stack is initialized correctly
*/