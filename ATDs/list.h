#ifndef LIST_H
#define LIST_H

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

// Returns a pointer to the array of points
point* point_list(list*l);

// Returns left element index from the array
int indice_esquerda(point* p,int tamanho);

// Returns right element index from the array
int indice_direita(point* p,int tamanho);

// Returns upper element index from the array
int indice_cima(point* p,int tamanho);

// Returns lower element index from the array
int indice_baixo(point* p,int tamanho);

// Prints clockwise
void impressao_horaria(point* pontos, int indice,int tamanho);

// Prints counterclockwise
void impressao_anti_horaria(point* pontos, int indice,int tamanho);

#endif