/* Stack */

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

bool create_stack(Stack* stack, int size)
{
	// Initialize the array of int
	stack->values = (int*)malloc(sizeof(int) * size);

	// Set the top of the stack to -1 indicating the stack is empty
	stack->top = -1;
	stack->max_top = size - 1;
	return true;
}

bool is_stack_empty(Stack* stack)
{
	return stack->top == -1;
}

bool is_stack_full(Stack* stack)
{
	return stack->top == stack->max_top;
}

bool peek_stack(Stack* stack, int* x)
{
	// Set the value of x to the value at the top of the stack
	if (is_stack_empty(stack))
		return false;
	*x = stack->values[stack->top];
	return true;
}

bool stack_push(Stack* stack, int x)
{
	// Check is the stack full before pushing
	if (is_stack_full(stack)) {
		int new_stack_size = (stack->max_top + 1) * 2;
		int* old_stack = stack->values;
		stack->values = (int*)realloc(stack->values, sizeof(int) * new_stack_size);

		// When failed to resize
		if (stack->values == NULL) {
			stack->values = old_stack;
			return false;
		}
		stack->max_top = new_stack_size - 1;
	}
	
	// Push the value to the stack
	stack->values[++stack->top] = x;
	return true;
}

bool stack_pop(Stack* stack, int* x)
{
	// Check is the stack empty before popping
	if (is_stack_empty(stack))
		return false;

	// There's no need to set the value to null in C since its not meaningful
	*x = stack->values[stack->top--];
	return true;
}


void display_stack(Stack* stack)
{
	// Print the indicator
	printf("top --> ");
	if (!is_stack_empty(stack)) {
		// Print from the top to bottom
		for (int i = stack->top; i >= 0; --i) {
			printf("|\t%d\t|\n\t", stack->values[i]);
		}
	}
	printf("|---------------|\n");
}

void destroy_stack(Stack* stack)
{
	// Free the list of values
	free(stack->values);

	// Reset all attributes of the stack
	stack->max_top = -1;
	stack->top = -1;
}