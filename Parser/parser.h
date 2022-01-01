#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#include "stack.h"
#include "buffer.h"
#include "slr1.h"

int dfa2tkid(int dfa_state);
char* get_parser_stack(Stack* stack);