#include <stdio.h>
#include "../util.h"
#include "../ADTs/list.h"

// #define NUMBER_OF_POINTS 5
#define NUMBER_OF_POINTS 3

int main(){
    // point p[NUMBER_OF_POINTS] = {{2,1}, {2.3,1.9}, {2.7,3.1}, {3.4,5.2}, {5, 10}}; // collinear
    // point p[NUMBER_OF_POINTS] = {{0,0.2}, {1,1.33}, {2,2}}; // barely non-collinear
    point p[NUMBER_OF_POINTS] = {{0,0.2}, {1,1.4}, {2,2}}; // non-collinear

    list *l= list_create(NUMBER_OF_POINTS);

    for(int i = 0; i < NUMBER_OF_POINTS; i++){
        list_append(l, p[i]);
    }

    list_print(l);

    printf("is collinear: %d\n", list_isCollinear(l));

    list_delete(&l);

    return 0;
}