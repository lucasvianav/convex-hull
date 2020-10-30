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
stack* stack_create(){
    
    stack *new_stack = (stack *)malloc(sizeof(stack));

    if(new_stack){ 
        new_stack->top = NULL;
        new_stack->size = 0;
    }

    return new_stack;
}

// Inserts a point at the top of the stack
void stack_push(stack* s,point p){

    if(s == NULL) return;

    node *newNode = (node *)malloc(sizeof(node));

    newNode->p = p;
    newNode->next = s->top;
    s->top = newNode;
    s->size = (s->size) + 1;

    return;
    
}

// Removes the point from the top of the stack and returns it
point *stack_pop(stack* s){

    if(s == NULL || stack_isEmpty(s)){ return NULL; }

    point* return_point = (point*)malloc(sizeof(point));
    return_point->x = s->top->p.x;
    return_point->y = s->top->p.y;
    
    node* aux = s->top; 
    s->top = aux->next;
    free(aux);
    aux = NULL;

    s->size = (s->size) - 1;
    
    return return_point;
}

// Gets the length of the stack at the moment
int stack_getLength(stack* s){

    if(s == NULL) return -1;

    return s->size;

}

// Checks if the size of the stack is 0
int stack_isEmpty(stack *s){

    if(s == NULL) return -1;

    return (s->size == 0);

}

// Returns the point from the top of the stack without removing it 
point *stack_top(stack* s){
    
    if(s == NULL) return NULL;

    return &(s->top->p);
}

// Returns the second element from the top of the stack
point* stack_secondFromTop(stack* s){

    if (s == NULL) return NULL;

    return &(s->top->next->p);

}

// Copies the stack
stack *stack_copy(stack *s){
    if(s != NULL){
        stack *copy = stack_create();
        int length = stack_getLength(s);

        node *tmp = s->top;

        for(int i = 0; i < length; i++){
            stack_push(copy, tmp->p);

            tmp = tmp->next;
        }

        return copy;
    }

    return NULL;

}

// Deletes the stack
void stack_delete(stack **s){

    if ((s == NULL)) return;

    node* current = (*s)->top;
    node* next;

    while(current != NULL){

        next = current->next;
        free(current);
        current = next;

    }

    free(*s);
    *s = NULL;

    return;

}

// Prints the whole stack
void stack_print(stack *s){
    if(s != NULL && !stack_isEmpty(s)){
        node *tmp  = s->top;

        while(tmp != NULL){
            printf("%.2lf %.2lf\n", tmp->p.x, tmp->p.y);
            tmp = tmp->next;
        }
    }

    return;

}