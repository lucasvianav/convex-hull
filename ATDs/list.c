#include <stdio.h>
#include <stdlib.h>
#include "list.h"

struct node_ {
    point p;
    struct node_ *next;
}; typedef struct node_ node;

struct list_ {
    node *start;
    node *end;
    int length;
};

list* list_create(){
    list *newList = (list *)malloc(sizeof(list));

    if(newList){ 
        newList->start = NULL;
        newList->end = NULL;
        newList->length = 0;
    }

    return newList;
}

boolean list_isEmpty(list *l){
    if(l == NULL || l->length > 0){ return False; }

    else{ return True; }
}

int list_getLength(list *l){
    if(l == NULL){ return -1; }
    
    else{ return l->length; }
}

void list_insert(list *l, point p, int index){
    if(l != NULL && index >= 0 && index <= list_getLength(l)){
        node *newNode = (node *)malloc(sizeof(node));

        newNode->p = p;

        // If the element is added to the first index, insert the new node at the start
        if(index == 0){ 
            newNode->next = l->start;
            l->start = newNode;

            if(list_isEmpty(l)){ l->end = newNode; }
        }

        else if(index == list_getLength(l)){
            newNode->next = NULL;
            l->end->next = newNode;
            l->end = newNode;
        }

        else{
            node *tmp = l->start; // Temporary variable that initially points the the list's beginning

            // Goes as far as the index-1 node
            for(int i = 1; i < index; i++){ tmp = tmp->next; }

            // Inserts the node at the desired index
            newNode->next = tmp->next;
            tmp->next = newNode;
        }

        l->length++;

    }

    return;
}

void list_append(list *l, point p){
    list_insert(l, p, list_getLength(l));

    return;
}

point *list_get(list *l, int index){
    if(l != NULL && index < list_getLength(l)){
        node *tmp = l->start;

        for(int i = 0; i < index; i++){ tmp = tmp->next; }

        return &(tmp->p);
    }

    return NULL;
}

int list_search(list *l, point p){
    int index = 0;

    if(l != NULL && !list_isEmpty(l)){
        node *tmp = l->start; 

        while((tmp->p.x != p.x || tmp->p.y != p.y) && tmp->next != NULL){
            tmp = tmp->next;
            index++;
        }
        
        if(tmp->p.x != p.x || tmp->p.y != p.y){ index = -1; }
    }

    else{ index = -1; }

    return index;
}

void list_remove(list *l, int index){
    if(l != NULL && index < list_getLength(l)){
        node *target = NULL; // Will point to the node at the desired index

        if(index == 0){
            target = l->start;
            l->start = target->next;
        }
        
        else{
            // Temporary variable pointing the the node at index-1
            node *tmp = l->start;
            for(int i = 0; i < index; i++){ tmp = tmp->next; }

            // Removes the target-node from the list
            target = tmp->next; 
            tmp->next = target->next;
        }

        // Deallocates the target-node
        free(target);

    }

    return;
}

// Auxiliar local function to deallocate all the list's nodes as recursion 
void deallocate(node **n){
    // If n ain't the list's last node, calls itself on the next node
    if(*n != NULL && (*n)->next != NULL){ deallocate(&((*n)->next)); }

    free(*n);
    *n = NULL;

    return;
}

void list_delete(list **l){
    if(*l != NULL){
        deallocate(&((*l)->start)); // Deallocates all the list's nodes

        free(*l);
        *l = NULL;

    }
        
    return;
}

void list_print(list *l){
    if(l != NULL){
        node *tmp = l->start;

        while(tmp != NULL){
            printf("%.2lf %.2lf\n", tmp->p.x, tmp->p.y);
            tmp = tmp->next;
        }
    }

    return;
}

void list_swap(list *l, int i, int j){
    if(l != NULL && i < list_getLength(l) && j < list_getLength(l) && i != j){
        node *node_i = l->start; // Node at index i
        node *node_j = l->start; // Node at index j
        point tmp; // Auxiliar variable in order to perform the swap

        // Loops to get the above node variables pointing to it's corresponding nodes
        int k;
        for(k = 0; k < i && k < j; k++){ 
            node_i = node_i->next;
            node_j = node_j->next;
        }

        while(k < i){
            node_i = node_i->next;
            k++;
        }

        while(k < j){
            node_j = node_j->next;
            k++;
        }

        // Swaps the points in each node
        tmp = node_i->p;
        node_i->p = node_j->p;
        node_j->p = tmp;

    }

    return;
}