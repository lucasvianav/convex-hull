#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "list.h"

struct node_ {
    point p;
    struct node_ *next;
    struct node_ *previous;
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
            newNode->previous = NULL;
            l->start = newNode;

            if(list_isEmpty(l)){ l->end = newNode; }

            else{ l->start->next->previous = l->start; }
        }

        else if(index == list_getLength(l) - 1){
            newNode->previous = l->end;
            newNode->next = NULL;
            l->end->next = newNode;
            l->end = newNode;
        }

        else{
            node *tmp;

            // If the position is in the list's first half
            if(index <= (int) list_getLength(l)/2){
                tmp = l->start; // Temporary variable that initially points the the list's beginning

                // Goes as far as the index node
                for(int i = 1; i < index; i++){ tmp = tmp->next; }

                // Inserts the node at the desired index
                newNode->next = tmp->next;
                newNode->previous = tmp;
                tmp->next->previous = newNode;
                tmp->next = newNode;
            }

            // If the position is in the list's second half
            else{
                tmp = l->end; // Temporary variable that initially points the the list's ending

                // Goes as far as the index node
                for(int i = list_getLength(l) - 1; i > index; i--){ tmp = tmp->previous; }

                // Inserts node at the desired index
                newNode->previous = tmp->previous;
                newNode->next = tmp;
                tmp->previous->next = newNode;
                tmp->previous = newNode;
            }
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
        node *tmp;
        
        // If the target-node is in the list's first half
        if(index <= (int) list_getLength(l)/2){
            tmp = l->start;

            // Goes as far as the index node
            for(int i = 0; i < index; i++){ tmp = tmp->next; }
        }

        // If the target-node is in the list's second half
        else{
            tmp = l->end;

            // Goes as far as the index node
            for(int i = list_getLength(l) - 1; i > index; i--){ tmp = tmp->previous; }
        }

        return &(tmp->p);
    }

    else{ return NULL; }
    
}

int list_search(list *l, point p){

    if(l != NULL && !list_isEmpty(l)){
        node *left = l->start, *right = l->end; 
        int leftIndex = 0, rightIndex = list_getLength(l) - 1;

        while((left->p.x != p.x || left->p.y != p.y) && (right->p.x != p.x || right->p.y != p.y) && left != right){
            left = left->next;
            leftIndex++;

            right = right->previous;
            rightIndex--;
        }
        
        if(left->p.x == p.x && left->p.y == p.y){ 
            return leftIndex;
        }
        
        else if(right->p.x == p.x && right->p.y == p.y){ 
            return rightIndex;
        }
        
        else{ return -1; }
    }

    else{ return -1; }
}

void list_remove(list *l, int index){
    if(l != NULL && index < list_getLength(l)){
        node *target = NULL; // Will point to the node at the desired index

        if(index == 0){
            target = l->start;

            l->start->previous = NULL;
            l->start = target->next;
        }

        else if(index == list_getLength(l) - 1){
            target = l->end;

            l->end = target->previous;
            l->end->next = NULL;
        }
        
        else{
            target = list_get(l, index);

            target->next->previous = target->previous;
            target->previous->next = target->next;
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

void list_reverse(list *l){
    if(l != NULL){
        node *tmp;

        if(list_getLength(l) > 1){
            node *currentNode = l->end;

            for(int i = list_getLength(l) - 1; i >= 0; i--){
                tmp = currentNode->next;
                currentNode->next = currentNode->previous;
                currentNode->previous = tmp;

                currentNode = currentNode->next;
            }

        }

        tmp = l->start;
        l->start = l->end;
        l->end = tmp;

    }

    return;
}

// Local method that swaps the points in the nodes n1 and n2
void pointSwap(node *n1, node *n2){
    point tmp = n1->p;
    n1->p = n2->p;
    n2->p = tmp;

    return;
}

void list_swap(list *l, int i, int j){
    if(l != NULL && i < list_getLength(l) && j < list_getLength(l) && i != j){
        node *node_i; // Node at index i
        node *node_j; // Node at index j
        int middleIndex = (int)list_getLength(l)/2, k;

        // Assures that i < j
        if(i > j){
            k = i;
            i = j;
            j = k;
        }

        // Gets the above node variables pointing to it's corresponding nodes
        if(i > middleIndex && j > middleIndex){
            int k = list_getLength(2);
            node_j = l->end;
            while(k > j){
                node_j = node_j->previous;
                k--;
            }

            node_i = node_j;
            while(k > i){
                node_i = node_i->previous;
                k--;
            }
        }

        else if((i <= middleIndex/2 && j > middleIndex) || (i >= middleIndex/2 && j >= 3/2*middleIndex)){
            k = 0;
            node_i = l->start;
            while(k < i){
                node_i = node_i->next;
                k++;
            }

            k = list_getLength(l) - 1;
            node_j = l->end;
            while(k > j){
                node_j = node_j->previous;
                k--;
            }
        }

        else{
            int k = 0;
            node_i = l->start;
            while(k < i){
                node_i = node_i->next;
                k++;
            }

            node_j = node_i;
            while(k < j){
                node_j = node_j->next;
                k++;
            }
        }

        // Swaps the points in each node
        pointSwap(node_i, node_j);

    }

    return;
}

void list_shuffle(list *l){
    if(l != NULL){
        srand(time(NULL));

        // Current node to be swapped
        node *currentNode = l->end;
        int currentIndex = list_getLength(l)-1;
        
        // Auxiliar node variable in order to get the target node
        node *aux;
        int auxIndex = 0;

        // Target node's index (node to be swapped with the current one)
        int targetIndex;

        int distanceCurrent, distanceEnd, minDist;

        while(currentIndex > 0){
            // Randomly selects a target to the left of the current one
            targetIndex = rand() % (currentIndex+1);

            // Calculates which indexed node is the closest to targetIndex-node
            distanceCurrent = abs(targetIndex - currentIndex);
            distanceEnd = abs(targetIndex - list_getLength(l) - 1);
            minDist = min4(distanceCurrent, abs(targetIndex - auxIndex), targetIndex, distanceEnd);

            // targetIndex-node is closest from the current-node
            if(minDist == distanceCurrent){
                aux = currentNode;
                auxIndex = currentIndex;
            }

            // targetIndex-node is closest from the first node
            else if(minDist == targetIndex){
                aux = l->start;
                auxIndex = 0;
            }

            // targetIndex-node is closest from the last node
            else if(minDist == distanceEnd){
                aux = l->end;
                auxIndex = list_getLength(l) - 1;
            }

            // Now, aux is the indexed node closest to targetIndex-node

            // Gets targetIndex-node to aux
            while(auxIndex < targetIndex){ aux = aux->next; } // If it's on the right
            while(auxIndex > targetIndex){ aux = aux->previous; } // If it's on the left

            pointSwap(aux, currentNode);

            currentNode = currentNode->previous;
            currentIndex--;
        }

    }

    return;
}

// Local function that quick sorts a given list
void quickSort(list *l, char key, int leftIndex, int rightIndex){
    if(leftIndex < rightIndex){
        int left = leftIndex; // Current index on the left
        int right = rightIndex; // Current index on the right

        node *leftNode = l->start; // Current node on the left
        node *rightNode = l->end; // Current node on the right

        int middleIndex = (int)((rightIndex+leftIndex)/2);
        point pivot = *list_get(l, middleIndex);

        // Sorts from left to right (and bottom to top if there's a draw)
        if(key == 'x'){
            // Separes the vector/subvector into two partitions
            while(True){
                // Selects elements from the left that are > to the pivot
                // for(point *current = list_get(l, left); current->x <= pivot.x; current = list_get(l, ++left)){
                while(leftNode->p.x <= pivot.x){
                    // If there's a draw in x, sort by y
                    if(leftNode->p.x == pivot.x && leftNode->p.y >= pivot.y){
                        break;
                    }

                    leftNode = leftNode->next;
                    left++;
                }

                // Selects elements from the right that are < to the pivot
                for(point *current = list_get(l, right); current->x >= pivot.x; current = list_get(l, --right)){
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

        node *tmp = l->start;

        for(int i = 0; i < length; i++){
            list_append(copy, tmp->p);

            tmp = tmp->next;
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

void list_extendStack(list *l, stack *target){
    if(l != NULL && target != NULL){
        stack *s = stack_copy(target);
        int length = stack_getLength(s);

        for(int i = 0; i < length; i++){
            list_append(l, *stack_pop(s));
        }

        stack_delete(&s);

    }

    return;
}

void list_attachStack(list *l, stack *target){
    if(l != NULL && target != NULL){
        int length = stack_getLength(target);

        for(int i = 0; i < length; i++){
            list_append(l, *stack_pop(target));
        }
        
        stack_delete(&target);

    }

    return;
}