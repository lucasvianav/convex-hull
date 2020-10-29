#include <stdio.h>
#include "../util.h"
#include "../ADTs/list.h"
#include "../monotone-chain.h"

#define NO_OF_POINTS 8

int main(){
    // point p[NO_OF_POINTS] = {{-6, 0}, {-4, 0}, {4, 0}, {6, 0}, {0, 4}, {0, 2}, {0.1, 2}, {-0.1,2}, {6, 1}, {6,3}};
    point p[NO_OF_POINTS] = {{0, 3}, {3, 3}, {1, 2}, {2, 1}, {3, 0}, {6, 3}, {5, 2}, {4, 1}};

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