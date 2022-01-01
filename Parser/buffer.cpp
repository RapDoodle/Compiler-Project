#include "buffer.h"

char* create_buffer(int size)
{
	char* buffer = (char*)malloc(size * sizeof(int));
	if (buffer != NULL && size > 0)
		buffer[0] = '\0';
	return buffer;
}

bool increase_buffer(char** buffer, int* buffer_size)
{
	char* new_buffer = (char*)realloc(*buffer, *(buffer_size) * 2);
	if (new_buffer != NULL) {
		*buffer = new_buffer;
		*buffer_size *= 2;
		return true;
	} else {
		return false;
	}
}

bool write_buffer_string(char** buffer, const char* str, int* buffer_size, int* offset)
{
	int str_length = strlen(str);

	// Increase the buffer size on demand
	if (*buffer_size < str_length + *offset) {
		if (!increase_buffer(buffer, buffer_size))
			return false;
	}
	sprintf(*buffer + *offset, "%s", str);
	*offset += str_length;
	return true;
}

bool write_buffer_char(char** buffer, const char ch, int* buffer_size, int* offset)
{
	// Increase the buffer size on demand
	if (*buffer_size < *offset + 1)
		if (!increase_buffer(buffer, buffer_size))
			return false;
	sprintf(*buffer + *offset, "%c", ch);
	*offset += 1;
	return true;
}

void reset_buffer(char** buffer, int* buffer_size, int* offset)
{
	free(*buffer);
	*buffer = create_buffer(*buffer_size);
	*offset = 0;
}