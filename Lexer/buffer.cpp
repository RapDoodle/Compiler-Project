#include "buffer.h"

char* create_buffer(int size) 
{
	char* buffer = (char*)malloc(size * sizeof(int));
	if (size > 0)
		buffer[0] = '\0';
	return buffer;
}

void increase_buffer(char** buffer, int* buffer_size)
{
	*buffer = (char*)realloc(*buffer, *buffer_size * 2);
	*buffer_size *= 2;
}

void write_buffer_string(char **buffer, const char *str, int *buffer_size, int *offset)
{
	int str_length = strlen(str);

	// Increase the buffer size on demand
	if (*buffer_size < str_length + *offset)
		increase_buffer(buffer, buffer_size);
	sprintf(*buffer + *offset, "%s", str);
	*offset += str_length;
}

void write_buffer_char(char** buffer, const char ch, int* buffer_size, int* offset)
{
	// Increase the buffer size on demand
	if (*buffer_size < *offset + 1)
		increase_buffer(buffer, buffer_size);
	sprintf(*buffer + *offset, "%c", ch);
	*offset += 1;
}

void reset_buffer(char** buffer, int* buffer_size, int* offset)
{
	free(*buffer);
	*buffer = create_buffer(*buffer_size);
	*offset = 0;
}