#ifndef LIST_H
#define LIST_H

#include "util.c"

typedef struct list_ list;

// Creates a list and returns it's pointer
list *list_create();

// Deallocates the list and all of it's nodes
void list_delete(list **l);

// Insert an element into specified index
void list_insert(list *l, point p, int index);

// Appends an element to the end of list
void list_append(list *l, point p);

// Removes the element at the specified index from the list
void list_remove(list *l, int index);

// Swaps the elements at the specified indexes
void list_swap(list *l, int i, int j);

// Prints all the list's elements
void list_print(list *l);

// Return True if the list is empty or False if it isn't
boolean list_isEmpty(list *l);

// Returns a pointer to the element at the specified index
point *list_get(list *l, int index);

// Returns the index of the specified element
// If the element isn't on the list, returns -1
int list_search(list *l, point p);

// Returns the list's length
int list_getLength(list *l);

#endif