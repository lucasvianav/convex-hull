/*
    Daniel Carvalho Dantas  10685702
    Lucas Viana Vilela      10748409
*/
#ifndef STACK_H
#define STACK_H

#include "../util.h"

typedef struct stack_ stack;

// Creates a stack and returns it's pointer
stack *stack_create();

// Appends a new point to the top of the stack
void stack_push(stack *s, point p);

// Removes the point from the top of the stack
// Returns a pointer to that point's value (must be freed in the application)
point *stack_pop(stack *s);

// Returns the stack's length
// If an error occurs, return -1
int stack_getLength(stack *s);

// Returns True if the stack is empty
// or False if it isn't
boolean stack_isEmpty(stack *s);

// Returns a pointer to the point on top of the stack
point *stack_top(stack *s);

// Returns a pointer to the second point from the stack's top
// (must be freed in the application)
point *stack_secondFromTop(stack *s);

// Deletes the whole stack
void stack_delete(stack **s);

#endif