/*
    Daniel Carvalho Dantas  10685702
    Lucas Viana Vilela      10748409
*/
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

struct node_ {
    point p;
    struct node_ *next;
};

typedef struct node_ node;

struct stack_ {
    node *top;
    int size; // Size at the moment
};

// Creates an empty stack
stack *stack_create(){
    stack *new_stack = (stack *)malloc(sizeof(stack));

    if(new_stack){ 
        new_stack->top = NULL;
        new_stack->size = 0;
    }

    return new_stack;
}

// Inserts a point at the top of the stack
void stack_push(stack *s, point p){

    if(s == NULL){ return; }

    // Creates a new node
    node *newNode = (node *)malloc(sizeof(node));

    // Sets the new node's point as p
    newNode->p = p;

    // Adds the new node to the stack
    newNode->next = s->top;
    s->top = newNode;

    // Increments the stack's length
    s->size++;

    return;
}

// Removes the point from the top of the stack and returns it
point *stack_pop(stack* s){
    if(s == NULL || stack_isEmpty(s)){ return NULL; }

    // Crestes a variable in the heap and stores the top point
    point* return_point = (point*)malloc(sizeof(point));
    return_point->x = s->top->p.x;
    return_point->y = s->top->p.y;
    
    // Removes the top node from the stack
    node* aux = s->top; 
    s->top = aux->next;

    // Deallocates that node's memory
    free(aux);
    aux = NULL;

    // Decrements the stack's length
    s->size--;
    
    return return_point;
}

// Gets the length of the stack at the moment
int stack_getLength(stack* s){
    if(s == NULL){ return -1; }

    return s->size;
}

// Checks if the size of the stack is 0
boolean stack_isEmpty(stack *s){
    if(s == NULL || s->size > 0){ return False; }

    else{ return True; }
}

// Returns the point from the top of the stack without removing it 
point *stack_top(stack* s){
    if(s == NULL){ return NULL; }

    return &(s->top->p);
}

// Returns the second element from the top stack, but only accessing the top element.
// The top element from the original stack is popped to an auxiliar variable, as well 
// as the new top element (original second from the top). Then those points are pushed
// to the stack, restoring it to it's original version.
point* stack_secondFromTop(stack* s){
    if (stack_getLength(s) < 2){ return NULL; }

    // Gets the original top point
    point *aux = stack_pop(s);

    // Gets the original second from the top point
    point *output = stack_pop(s);

    // Pushes those points back
    stack_push(s, *output);
    stack_push(s, *aux);
    
    // Frees the pointer used for the original top point
    // (won't be used)
    free(aux);

    // Returns the pointer to the original second from the top point
    // (must be freed in the application)
    return output;
}

// Deletes the stack
void stack_delete(stack **s){
    if (s == NULL){ return; }

    // Current node being deallocated
    node *current = (*s)->top;

    // Next node to be deallocated
    node *next;

    // Deallocates all of the stack's nodes
    while(current != NULL){
        next = current->next;
        free(current);
        current = next;
    }

    // Deallocates the stack
    free(*s);
    *s = NULL;

    return;
}