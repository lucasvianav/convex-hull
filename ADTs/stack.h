#ifndef STACK_H
#define STACK_H

#include "../util.h"

typedef struct stack_ stack;

// Creates a stack and returns it's pointer
stack* stack_create();

stack *stack_copy(stack *s);

// Inserts a new node 
void stack_push(stack* s,point p);

// Removes the stack_top node from the stack
// Returns a pointer to that node's point (must be freed in the application)
point *stack_pop(stack* s);

// Returns the stack stack_getLength
int stack_getLength(stack* s);

// Returns if the stack is empty or not
int stack_is_empty(stack *s);

// Returns the stack_top point from the stack
point *stack_top(stack* s);

// Returns the stack second element from the top
point* stack_secondFromTop(stack* s);

// Deletes the whole stack
void stack_delete(stack **s);

#endif