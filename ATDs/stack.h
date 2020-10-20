#ifndef STACK_H
#define STACK_H

#include "../util.c"

typedef struct stack_ stack;

// Creates a stack and returns it's pointer
stack* stack_create();

// Inserts a new node 
void stack_push(stack* s,point p);

// Removes the stack_top node from the stack
point* stack_pop(stack* s);

// Returns the stack stack_getLength
int stack_getLength(stack* s);

// Returns the stack_top node from the stack
point *stack_top(stack* s);

// Returns the stack second element from the top
point* stack_second_from_top(stack* s);


#endif