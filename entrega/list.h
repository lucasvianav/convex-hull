/*
    Daniel Carvalho Dantas  10685702
    Lucas Viana Vilela      10748409
*/
#ifndef LIST_H
#define LIST_H

#include "util.h"
#include "stack.h"

typedef struct list_ list;

// Creates a list with maxLength positions and returns it's pointer
list *list_create(int maxLength);

// Deallocates the list and all of it's nodes
void list_delete(list **l);

// Appends an element to the end of list
void list_append(list *l, point p);

// Insert an element into specified index
void list_insert(list *l, point p, int index);

// Removes the element at the specified index from the list
void list_remove(list *l, int index);

// Appends all elements from target-stack to l
// When completed, deletes the target-stack
void list_attachStack(list *l, stack *target);

// Swaps the elements at the specified indexes
void list_swap(list *l, int i, int j);

// Prints all of the list's elements
void list_print(list *l);

// Shuffles the list using the Fisher-Yates algorithm
void list_shuffle(list *l);

// Sorts the list using QuickSort
// (after shuffling it to avoid QuickSort's worst case)
// key == 'x': sorts from left to right
// key == 'X': sorts from right to left
// key == 'y': sorts from bottom to top
// key == 'Y': sorts from top to bottom
void list_sort(list *l, char key);

// Sorts a previously counter-clockwise-oriented list in 
// specified orientation, starting at the point in the specified index
// orienteation == 0 --> clockwise
// orientation == 1 -->  counter-clockwise
void list_orientate(list *l, int orientation, int startIndex);

// Return True if the list is empty or False if it isn't
boolean list_isEmpty(list *l);

// Return True if the list is empty or False if it isn't
boolean list_isFull(list *l);

// Checks if all points in a list are collinear
boolean list_isCollinear(list *l);

// Returns a pointer to the element at the specified index
point *list_get(list *l, int index);

// Returns the index of the specified element's first ocurrencev
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