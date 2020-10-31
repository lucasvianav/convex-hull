/*
    Daniel Carvalho Dantas  10685702
    Lucas Viana Vilela      10748409
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "list.h"
#include "stack.h"

struct list_ {
    int length;
    int maxLength; // maximum number of elements the list can contain
    point *points;
};

list* list_create(int maxLength){
    list *newList = (list *)malloc(sizeof(list));

    if(newList != NULL){
        newList->points = (point *)malloc(maxLength * sizeof(point));
        newList->length = 0;
        newList->maxLength = maxLength;
    }

    return newList;
}

boolean list_isEmpty(list *l){
    if(l == NULL || l->length > 0){ return False; }

    else{ return True; }
}

boolean list_isFull(list *l){
    if(l == NULL || l->length < l->maxLength){ return False; }

    else{ return True; }
}

int list_getLength(list *l){
    if(l == NULL){ return -1; }
    
    else{ return l->length; }
}

void list_append(list *l, point p){
    if(l != NULL && !list_isFull(l)){
        l->points[l->length] = p;
        l->length++;
    }

    return;
}

void list_insert(list *l, point p, int index){
    if(l != NULL && !list_isFull(l) && index <= list_getLength(l)){
        // Moves every point with index >= target index to the next position
        for(int i = list_getLength(l) - 1; i >= index; i--){
            l->points[i+1] = l->points[i];
        }

        // Inserts p as the index element
        l->points[index] = p;
        
        // Increments list length
        l->length++;
    }

    return;
}

void list_remove(list *l, int index){
    if(l != NULL && !list_isEmpty(l) && index < list_getLength(l)){
        // Moves every point with index > target index to the previous position
        // This overrides the element to be removed
        for(int i = index; i < list_getLength(l) - 1; i++){
            l->points[i] = l->points[i+1];
        }

        // Decrements the list's length
        l->length--;
    }

    return;
}

point *list_get(list *l, int index){
    if(l != NULL && !list_isEmpty(l) && index < list_getLength(l)){
        return &(l->points[index]);
    }

    else{ return NULL; }
    
}

int list_search(list *l, point p){
    if(l != NULL && !list_isEmpty(l)){
        // Goes through the whole list
        for(int i = 0; i < list_getLength(l); i++){
            // If the desired point is found
            if(l->points[i].x == p.x && l->points[i].y == p.y){
                return i; // Return it's index
            }
        }
    }

    return -1;
}

void list_delete(list **l){
    if(l != NULL){
        // Deallocates the array's memory
        free((*l)->points);
        (*l)->points = NULL;

        // Deallocates the list's memory
        free(*l);
        *l = NULL;
    }

    return;
}

void list_print(list *l){
    if(l != NULL){
        // Goes through the whole list
        for(int i = 0; i < list_getLength(l); i++){
            // Print's each point with two decimal places
            printf("%.2lf %.2lf\n", l->points[i].x, l->points[i].y);
        }
    }

    return;
}

void list_swap(list *l, int i, int j){
    if(l != NULL && !list_isEmpty(l) && i != j && i < list_getLength(l) && j < list_getLength(l)){
        point tmp = l->points[i];
        l->points[i] = l->points[j];
        l->points[j] = tmp;
    }

    return;
}

void list_shuffle(list *l){
    if(l != NULL && !list_isEmpty(l)){
        // Sets the rand() seed
        srand(time(NULL));

        // Goes through the whole list except for the first element
        for(int i = list_getLength(l) - 1; i > 0; i--){
            // Swaps the current element with a random one (itself or one that comes before it)
            list_swap(l, i, rand() % (i+1));
        }
    }

    return;
}

void quickSort(list *l, char key, int leftIndex, int rightIndex){
    if(0 <= leftIndex && leftIndex < rightIndex && rightIndex < list_getLength(l)){
        int left = leftIndex; // Current index on the left
        int right = rightIndex; // Current index on the right

        // Partition's middle index
        int middleIndex = (int)((rightIndex+leftIndex)/2);
        point pivot = *list_get(l, middleIndex);

        // Separes the vector/subvector into two partitions
        while(True){

            // Selects elements from the left
            while( left <= rightIndex && cmpPoints(l->points[left], pivot, key) ){
                left++;
            }

            // Selects elements from the right
            while( right >= leftIndex && cmpPoints(l->points[right], pivot, toggleChar(key)) ){
                right--;
            }

            // If swapping the above selected elements is worth it, do it
            if(left < right){ list_swap(l, left++, right--); }

            // If the swap is not worth it, the vector was successfully partitionted
            else{ break; }

        }

        // Sorts the partitions
        quickSort(l, key, leftIndex, right);
        quickSort(l, key, right+1, rightIndex);

    }

    return;

}

void list_sort(list *l, char key){
    if(l != NULL && list_getLength(l) > 1){
        if(key != 'x' && key != 'X' && key != 'y' && key != 'Y'){ key = 'x'; }

        list_shuffle(l);
        quickSort(l, key, 0, list_getLength(l)-1);
    }

    return;
}

void list_attachStack(list *l, stack *target){
    // If the list has enough free memory for all of the stack's points
    // Append all of the stack's elements to the list
    if(l != NULL && target != NULL && l->maxLength - l->length >= stack_getLength(target)){
        int length = stack_getLength(target);

        for(int i = 0; i < length; i++){
            point *tmp = stack_pop(target);
            list_append(l, *tmp);
            free(tmp);
        }
        
        // And deletes the stack
        stack_delete(&target);

    }

    return;
}

int list_searchExtreme(list *l, char target){
    if(l != NULL && (target == 'U' || target == 'D' || target == 'L' || target == 'R')){
        int targetIndex = 0;

        // Goes through the whole list, searching for the desired point
        for(int i = 0; i < list_getLength(l); i++){

            if( // Selects the desired point based on the passed key
                (target == 'U' && (l->points[i].y > l->points[targetIndex].y || (l->points[i].y == l->points[targetIndex].y && l->points[i].x < l->points[targetIndex].x))) ||
                (target == 'L' && (l->points[i].x < l->points[targetIndex].x || (l->points[i].x == l->points[targetIndex].x && l->points[i].y < l->points[targetIndex].y))) ||
                (target == 'R' && (l->points[i].x > l->points[targetIndex].x || (l->points[i].x == l->points[targetIndex].x && l->points[i].y < l->points[targetIndex].y))) ||
                (target == 'D' && (l->points[i].y < l->points[targetIndex].y || (l->points[i].y == l->points[targetIndex].y && l->points[i].x < l->points[targetIndex].x)))
            ){ targetIndex = i; }

        }

        return targetIndex;
    }

    return -1;

}

void list_orientate(list *l, int orientation, int startIndex){
    if(l != NULL && (orientation == 0 || orientation == 1) && startIndex >= 0 && startIndex < list_getLength(l)){
        // Auxiliar vector to store the correctly oriented group of points
        point *auxPoints = (point *)malloc(list_getLength(l) * sizeof(point));
        int auxIndex = 0;

        // Considering that l is already anti-clockwise-oriented:
        switch (orientation){
            case 0: // Clockwise

                // Adding the start element and every previous one guarantees 
                // clockwise order starting at that element
                // (inverse of counter-clockwise)
                for (int i = startIndex; i >= 0; i--, auxIndex++){
                    auxPoints[auxIndex] = l->points[i];
                }

                // Same for l's last element and every previous one up to the start element
                for (int i = list_getLength(l) - 1; i > startIndex; i--, auxIndex++){
                    auxPoints[auxIndex] = l->points[i];
                }
                
                break;
            
            case 1: // Counter-Clockwise

                // Adding the start element and every next one guarantees 
                // counter-clockwise order starting at that element
                // (since it's already counter-clockwise)
                for(int i = startIndex; i < list_getLength(l) ; i++, auxIndex++){
                    auxPoints[auxIndex] = l->points[i];
                }

                // Same here
                for (int i = 0; i < startIndex; i++, auxIndex++){
                    auxPoints[auxIndex] = l->points[i];
                }
            
                break;

        }

        // Since auxPoints points to a vector containing the correctly-oriented
        // group of points, there's no need for the vector currently pointed by l->points,
        // so deallocates it (instead of copying each element, which would be a higher cost)
        free(l->points);

        // Then finally makes l->points point to the correctly-oriented vector
        l->points = auxPoints;

    }

    return;
}

boolean list_isCollinear(list *l){
    if(l != NULL && !list_isEmpty(l)){
        int length = list_getLength(l);

        // Only 2 points are alway collinear
        if(length > 2){
            point A = *list_get(l, 0); // first point on the list 
            point B = *list_get(l, length - 1); // last point on the list
            point C; // current point being checked

            // line's equation: y - mx - n = 0
            // line between points A and B
            double m = (A.y - B.y)/(A.x - B.x);
            double n = A.y - m*A.x;

            // Checks if there's at least one element that
            // doesn't belong to that line. If there is,
            // then the points aren't all collinear
            for(int i = 0; i < length; i++){
                C = *list_get(l, i);
                if(dabs(C.y - m*C.x - n) > 0.000000000001){ return False; }
            }
        }

        return True;
    }

    return False;
}