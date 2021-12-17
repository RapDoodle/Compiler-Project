#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* create_buffer(int size);
void increase_buffer(char** buffer, int* buffer_size);
void write_buffer_string(char** buffer, const char* str, int* buffer_size, int* offset);
void write_buffer_char(char** buffer, const char ch, int* buffer_size, int* offset);
void reset_buffer(char** buffer, int* buffer_size, int* offset);