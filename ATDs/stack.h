#ifndef STACK_H
#define STACK_H

#include "../util.c"

typedef struct stack_ stack;

// Creates a stack and returns it's pointer
stack* stack_create();

// Inserts a new node 
void push(stack* s,point p);

// Removes the top node from the stack
void pop(stack* s);

// Returns the stack size
int size(stack* s);

// Returns the top node from the stack
node* top(stack* s);


#endif