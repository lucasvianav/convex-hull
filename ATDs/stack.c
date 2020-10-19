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
    int size;
};

stack* stack_create(){
    
    stack *new_stack = (stack *)malloc(sizeof(stack));

    if(new_stack){ 
        new_stack->top = NULL;
        new_stack->size = 0;
    }

    return new_stack;
}

void push(stack* s,point p){

    if(s == NULL) return;

    node *newNode = (node *)malloc(sizeof(node));

    newNode->p = p;
    newNode->next = s->top;
    s->top = newNode;
    s->size = (s->size) + 1;

    return;
    
}

void pop(stack* s){
    
    if(s == NULL) return;

    node* aux = s->top;
    s->top = s->top->next;
    free(aux);

    s->size = (s->size) - 1;
    
    return;
}

int size(stack* s){

    if(s == NULL) return -1;

    return s->size;

}

node* top(stack* s){
    
    if(s == NULL) return NULL;

    return s->top;
}




