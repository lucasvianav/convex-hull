#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "list.h"
#include "stack.h"

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

    else{ return NULL; }
    
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
            for(int i = 0; i < index - 1; i++){ tmp = tmp->next; }

            // Removes the target-node from the list
            target = tmp->next; 
            tmp->next = target->next;
        }

        // Deallocates the target-node
        free(target);

        // Decrements the length counter
        l->length--;

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

// void list_reverse(list **l){
//     if(*l != NULL && list_getLength(*l) > 1){
//         list *aux = list_create();

//         for(int i = list_getLength(*l) - 1; i >= 0; i--){
//             list_append(aux, *(list_get(l, i)));
//         }

//         list_delete(l);

//         *l = aux;
//     }

//     return;

// }

// void list_reverse(list *l){
//     for(int i = 0, j = list_getLength(l)-1; i < j; i++, j--){
//         list_swap(l, i, j);
//     }

//     return;

// }

void auxReverse(node *previous, node *current){
    if(current != NULL && current->next != NULL){ auxReverse(current, current->next); }

    current->next = previous;

    return;
    
}

void list_reverse(list *l){
    if(l != NULL && list_getLength(l) > 1){
        auxReverse(NULL, l->start);
    }

    node *tmp = l->start;
    l->start = l->end;
    l->end = tmp;

    return;
}

// Local function that quick sorts a given list
void quickSort(list *l, char key, int leftIndex, int rightIndex){
    if(leftIndex < rightIndex){
        int left = leftIndex, right = rightIndex;

        int middleIndex = (int)((rightIndex+leftIndex)/2);
        point pivot = *list_get(l, middleIndex);

        // Sorts from left to right (and bottom to top if there's a draw)
        if(key == 'x'){
            // Separes the vector/subvector into two partitions
            while(True){
                // Selects elements from the left that are > to the pivot
                for(point *current = list_get(l, left); /*current != NULL &&*/ current->x <= pivot.x; current = list_get(l, ++left)){
                    // If there's a draw in x, sort by y
                    if(current->x == pivot.x && current->y >= pivot.y){
                        break;
                    }
                }

                // Selects elements from the right that are < to the pivot
                for(point *current = list_get(l, right); /*current != NULL &&*/ current->x >= pivot.x; current = list_get(l, --right)){
                    if(current->x == pivot.x && current->y <= pivot.y){
                        break;
                    }
                }

                // If the swapping the above selected elements is worth it, do it
                if(left < right){ list_swap(l, left++, right--); } // And pass to the next element

                // If the swap is not worth it, the vector was successfully partitionted
                else{ break; }

            }

            // Sorts the partitions
            quickSort(l, key, leftIndex, right);
            quickSort(l, key, right+1, rightIndex);
        }

        // Sorts from right to left (and bottom to top if there's a draw)
        else if(key == 'X'){
            // Separes the vector/subvector into two partitions
            while(True){
                // Selects elements from the left that are < to the pivot
                for(point *current = list_get(l, left); current != NULL && current->x >= pivot.x; current = list_get(l, ++left)){
                    if(current->x == pivot.x && current->y >= pivot.y){
                        break;
                    }
                }

                // Selects elements from the right that are > to the pivot
                for(point *current = list_get(l, right); current != NULL && current->x <= pivot.x; current = list_get(l, --right)){
                    if(current->x == pivot.x && current->y <= pivot.y){
                        break;
                    }
                }

                // If the swapping the above selected elements is worth it, do it
                if(left < right){ list_swap(l, left++, right--); } // And pass to the next element

                // If the swap is not worth it, the vector was successfully partitionted
                else{ break; }

            }

            // Sorts the partitions
            quickSort(l, key, leftIndex, right);
            quickSort(l, key, right+1, rightIndex);
        }

        // Sorts from bottom to top (and left to right if there's a draw)
        else if(key == 'y'){
            // Separes the vector/subvector into two partitions
            while(True){
                // Selects elements from the left that are > to the pivot
                for(point *current = list_get(l, left); current != NULL && current->y <= pivot.y; current = list_get(l, ++left)){
                    if(current->y == pivot.y && current->x >= pivot.x){
                        break;
                    }
                }

                // Selects elements from the right that are < to the pivot
                for(point *current = list_get(l, right); current != NULL && current->y >= pivot.y; current = list_get(l, --right)){
                    if(current->y == pivot.y && current->x <= pivot.x){
                        break;
                    }
                }

                // If the swapping the above selected elements is worth it, do it
                if(left < right){ list_swap(l, left++, right--); } // And pass to the next element

                // If the swap is not worth it, the vector was successfully partitionted
                else{ break; }

            }

            // Sorts the partitions
            quickSort(l, key, leftIndex, right);
            quickSort(l, key, right+1, rightIndex);
        }

        // Sorts from top to bottom (and left to right if there's a draw)
        else if(key == 'Y'){
            // Separes the vector/subvector into two partitions
            while(True){
                // Selects elements from the left that are < to the pivot
                for(point *current = list_get(l, left); current != NULL && current->y >= pivot.y; current = list_get(l, ++left)){
                    if(current->y == pivot.y && current->x >= pivot.x){
                        break;
                    }
                }

                // Selects elements from the right that are > to the pivot
                for(point *current = list_get(l, right); current != NULL && current->y <= pivot.y; current = list_get(l, --right)){
                    if(current->y == pivot.y && current->x <= pivot.x){
                        break;
                    }
                }

                // If the swapping the above selected elements is worth it, do it
                if(left < right){ list_swap(l, left++, right--); } // And pass to the next element

                // If the swap is not worth it, the vector was successfully partitionted
                else{ break; }

            }

            // Sorts the partitions
            quickSort(l, key, leftIndex, right);
            quickSort(l, key, right+1, rightIndex);
        }
    }

    return;

}

void list_shuffle(list *l){
    srand(time(NULL));

    for(int i = list_getLength(l)-1; i > 0; i--){
        int j = rand() % (i+1);
        list_swap(l, i, j);
    }

    return;
}

void list_sort(list *l, char key){
    if(l != NULL && list_getLength(l) > 1 && (key == 'x' || key == 'X' || key == 'y' || key == 'Y')){
        list_shuffle(l);
        quickSort(l, key, 0, list_getLength(l) - 1);
    }

    return;
}

list *list_copy(list *l){
    if(l != NULL){
        list *copy = list_create();
        int length = list_getLength(l);

        for(int i = 0; i < length; i++){
            list_append(copy, *list_get(l, i));
        }

        return copy;
    }

    else{ return NULL; }

}

void list_extend(list *l, list *target){
    if(l != NULL && target != NULL){
        int length = list_getLength(target);
        node *tmp = target->start;

        for(int i = 0; i < length; i++){
            list_append(l, tmp->p);

            tmp = tmp->next;
        }
    }

    return;
}

/*
void list_extendStack(list *l, stack *target){
    if(l != NULL && target != NULL){
        stack *s = stack_copy(target);
        int length = stack_getLength(s);

        for(int i = 0; i < length; i++){
            list_append(l, *stack_pop(s));
        }
    }

    stack_delete(&s);

    return;
}
*/
void list_extendStack(list *l, stack *target){
    if(l != NULL && target != NULL){
        int length = stack_getLength(target);

        for(int i = 0; i < length; i++){
            list_append(l, *stack_pop(target));
        }
    }

    stack_delete(&target);

    return;
}

point* point_list(list*l){

    int size = list_getLength(l);

    point* point_list = malloc(size * sizeof(point));

    node* aux = l->start;

    for(int i  = 0; i < size; i++){
        
        point_list[i] = aux->p;
        aux = aux->next;
    }

    return point_list;

}


int indice_esquerda(point* p,int tamanho){
    
    int mais_esquerda = 0;

    for(int i = 0; i < tamanho; i++){
        if(p[i].x < p[mais_esquerda].x){
            mais_esquerda = i;
        }
        else if(p[i].x == p[mais_esquerda].x){
            if(p[i].y < p[mais_esquerda].y){
                mais_esquerda = i;
            }
        }
    }
    return mais_esquerda;
}

int indice_direita(point* p, int tamanho){

    int mais_direita = 0;

    for(int i = 0; i < tamanho; i++){
        if(p[i].x > p[mais_direita].x){
            mais_direita = i;
        }
        else if(p[i].x == p[mais_direita].x){
            if(p[i].y < p[mais_direita].y){
                mais_direita = i;
            }
        }
    }
    return mais_direita;
    
}

int indice_cima(point* p,int tamanho){
    int mais_acima = 0;

    for(int i = 0; i < tamanho; i++){
        if(p[i].y > p[mais_acima].y){
            mais_acima = i;
        }
        else if(p[i].y == p[mais_acima].y){
            if(p[i].x < p[mais_acima].x){
                mais_acima = i;
            }
        }
    }
    return mais_acima;
}

int indice_baixo(point* p,int tamanho){
    int mais_abaixo = 0;

    for(int i = 0; i < tamanho; i++){
        if(p[i].y < p[mais_abaixo].y){
            mais_abaixo = i;
        }
        else if(p[i].y == p[mais_abaixo].y){
            if(p[i].x < p[mais_abaixo].x){
                mais_abaixo = i;
            }
        }
    }
    return mais_abaixo;
    
}

void impressao_horaria(point* pontos, int indice,int tamanho){
    

    for (int i = indice; i >= 0 ; i--){
                printf("%.2f %.2f\n",pontos[i].x,pontos[i].y);
            }

            for (int i = tamanho - 1; i > indice; i--){
                printf("%.2f %.2f\n",pontos[i].x,pontos[i].y);
            } 

    return;
}

void impressao_anti_horaria(point* pontos, int indice,int tamanho){

    for (int i = indice; i < tamanho ; i++){
                printf("%.2f %.2f\n",pontos[i].x,pontos[i].y);
            }

            for (int i = 0; i < indice; i++){
                printf("%.2f %.2f\n",pontos[i].x,pontos[i].y);
            }
    
    return;
}