#ifndef LIST_H
#define LIST_H

#include "../util.c"

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

// Reverses the element's order
void list_reverse(list *l);

// Shuffles the list using the Fisher-Yates algorithm
void list_shuffle(list *l);

// Sorts the list using QuickSort
// key == 'x': sorts from left to right
// key == 'X': sorts from right to left
// key == 'y': sorts from bottom to top
// key == 'Y': sorts from top to bottom
void list_sort(list *l, char key);

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