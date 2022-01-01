#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "buffer.h"
#include "dfa.h"

int get_char_index(char c);
int next_token(char** ptr, int* token_idx);