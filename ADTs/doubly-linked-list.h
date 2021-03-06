/*
    Daniel Carvalho Dantas  10685702
    Lucas Viana Vilela      10748409
*/
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "../util.h"
#include "stack.h"

typedef struct list_ list;

// Creates a list and returns it's pointer
list *list_create();

// Returns the pointer to a deep copy of the given list
list *list_copy(list *l);

// Deallocates the list and all of it's nodes
void list_delete(list **l);

// Insert an element into specified index
void list_insert(list *l, point p, int index);

// Appends an element to the end of list
void list_append(list *l, point p);

// Append all elements from target-list to l
void list_extend(list *l, list *target);

// Append all elements from target-stack to l
// Leaves target-stack unaltered
void list_extendStack(list *l, stack *target);

// Append all elements from target-stack to l
// When completed, deletes the target-stack
void list_attachStack(list *l, stack *target);

// Removes the element at the specified index from the list
void list_remove(list *l, int index);

// Swaps the elements at the specified indexes
void list_swap(list *l, int i, int j);

// Prints all of the list's elements
void list_print(list *l);

// Prints the list's elements in specific order starting at the on in startIndex
// If orientation == 0: Prints the element at startIndex and then the previous ones
// After that, print the last element and then the previous ones until every element was printed
// If orientation == 1: Prints the element at startIndex and then the next ones
// After that, print the first element and then the next ones until every element was printed
// If l is counter-clockwise-oriented, 0 means clockwise and 1 means counter-clockwise
void list_auxPrint(list *l, int orientation, int startIndex);

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
// If the element isn't on the list or an error happens, returns -1
int list_search(list *l, point p);

// Returns the index of the specified extreme point
// U: uppermost point
// L: leftmost point
// R: rightmost point
// D: bottommost point (down)
// If an error happens, returns -1
int list_searchExtreme(list *l, char target);

// Returns the list's length
// If an error happens, returns -1
int list_getLength(list *l);

#endif