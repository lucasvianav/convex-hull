#include <stdio.h>
#include "../util.h"
#include "../ATDs/list.h"
#include "../monotone-chain.h"

#define NO_OF_POINTS 8

int main(){
    point p[NO_OF_POINTS] = {{0, 3.32}, {2, 2}, {1, 1}, {2, 1}, {3, 0}, {0.11, 0}, {3, 3.76}, {1.5, 3.76}};

    list *l = list_create();

    for(int i = 0; i < NO_OF_POINTS; i++){
        list_append(l, p[i]);
    }

    list_print(l);
    printf("\n");

    list *hull = convexHull(l);

    list_print(hull);
    printf("\n");

    list_delete(&l);
    list_delete(&hull);

    return 0;
}