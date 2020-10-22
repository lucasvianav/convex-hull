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

void stack_push(stack* s,point p){

    if(s == NULL) return;

    node *newNode = (node *)malloc(sizeof(node));

    newNode->p = p;
    newNode->next = s->top;
    s->top = newNode;
    s->size = (s->size) + 1;

    return;
    
}

point *stack_pop(stack* s){

    if(s == NULL || stack_is_empty(s)){ return NULL; }

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

int stack_getLength(stack* s){

    if(s == NULL) return -1;

    return s->size;

}

int stack_is_empty(stack *s){

    if(s == NULL) return -1;

    return (s->size == 0);

}

point *stack_top(stack* s){
    
    if(s == NULL) return NULL;

    return &(s->top->p);
}

point* stack_secondFromTop(stack* s){

    if (s == NULL) return NULL;

    return &(s->top->next->p);

}

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