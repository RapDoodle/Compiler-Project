#pragma once

typedef struct stack
{
	int* values;
	int top;
	int max_top;
} Stack;

bool create_stack(Stack* stack, int size);
/*
 function:
	Create an empty stack whose capacity is size
 argunment:
	The address of the stack to be initialized
 return:
	true if the stack is initialized correctly
*/

bool is_stack_empty(Stack* stack);
/*
 function:
	Check if the stack is empty
 argunment:
	The address of the stack
 return:
	true if the stack is stack is empty
	false if the stack is not empty
*/

bool is_stack_full(Stack* stack);
/*
 function:
	Check if the stack is full
 argunment:
	The address of the stack
 return:
	true if the stack is stack is full
	false if the stack is not full
*/

bool peek_stack(Stack* stack, int* x);
/*
 function:
	Peek at the top of the stack
 argunment:
	The address of the stack and the value variable to be altered
	with the value at the top of the stack
 return:
	true if the opration is successful
	false if the operation is not successful
*/

bool stack_push(Stack* stack, int x);
/*
 function:
	Push (add) a new element with value x to the top of the stack
 argunment:
	The address of the stack and the value to be pushed
 return:
	true if the opration is successful
	false if the operation is not successful
*/

bool stack_pop(Stack* stack, int* x);
/*
 function:
	Pop (delete) the element at the top of the stack
 argunment:
	The address of the stack and the value to be popped
 return:
	true if the opration is successful
	false if the operation is not successful
*/

void display_stack(Stack* stack);
/*
 function:
	Print the entire stack
 argunment:
	The address of the stack
 return:
	void
*/

void destroy_stack(Stack* stack);
/*
 function:
	Destroy the stack
 argunment:
	The address of the stack
 return:
	void
*/