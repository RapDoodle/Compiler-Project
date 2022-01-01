#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* create_buffer(int size);
/*
 function:
	Create an empty buffer whose capacity is size
 argunment:
	size: The size of the initial buffer
 return:
	the address of the buffer
*/

bool increase_buffer(char** buffer, int* buffer_size);
/*
 function:
	Increase the size of the buffer
 argunment:
	buffer: the address of the variable that stores the address
			of the buffer
	buffer_size: the address of buffer size
 return:
	bool: true if the operation is success
*/

bool write_buffer_string(char** buffer, const char* str, int* buffer_size, int* offset);
/*
 function:
	Write string into the buffer. Will increase the buffer 
	size on demand
 argunment:
	buffer: the address of the variable that stores the address
			of the buffer
	str: the string to be written to the buffer
	buffer_size: the address of buffer size (in case of a realloc)
	offset: the address of offset variable (in case of a realloc)
 return:
	bool: true if the operation is success
*/

bool write_buffer_char(char** buffer, const char ch, int* buffer_size, int* offset);
/*
 function:
	Write a character into the buffer. Will increase the buffer
	size on demand
 argunment:
	buffer: the address of the variable that stores the address
			of the buffer
	ch: the character to be written to the buffer
	buffer_size: the address of buffer size (in case of a realloc)
	offset: the address of offset variable (in case of a realloc)
 return:
	bool: true if the operation is success
*/

void reset_buffer(char** buffer, int* buffer_size, int* offset);
/*
 function:
	Empty the buffer
 argunment:
	buffer: the address of the variable that stores the address
			of the buffer
	buffer_size: the address of buffer size
	offset: the address of offset variable
 return:
	void
*/
