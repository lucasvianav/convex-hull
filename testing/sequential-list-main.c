#include <stdio.h>
#include "../ADTs/list.h"

#define MAX_LENGTH 20
#define NUMBER_OF_POINTS 6

int main(){
    point p[NUMBER_OF_POINTS] = { {0,0}, {1,-6}, {1,3}, {6,3}, {-16,3}, {0,0} };
    point p2 = {77, 77};
    list *l = list_create(MAX_LENGTH);

    printf("\nlen: %d\n", list_getLength(l));
    printf("\n");

    printf("isempty: %d\n", list_isEmpty(l));
    printf("\n");

    for(int i = 0; i < NUMBER_OF_POINTS; i++){
        list_append(l, p[i]);
        list_print(l);
        printf("%d\n", list_getLength(l));
        printf("\n");
    }
    printf("\n");

    point *current = list_get(l, 0);
    for(int i = 0; i <= NUMBER_OF_POINTS && current != NULL; i++, current = list_get(l, i)){
        printf("(%lf, %lf)\n", current->x, current->y);
    }
    printf("\n");

    list_swap(l, 0, list_getLength(l)-1);
    list_print(l);
    printf("\n");
    list_swap(l, 0, list_getLength(l)-1);
    list_print(l);
    printf("\n");

    printf("search (%.2lf, %.2lf): %d\n", p[0].x, p[0].y, list_search(l, p[0]));
    printf("search (%.2lf, %.2lf): %d\n", p[1].x, p[1].y, list_search(l, p[1]));
    printf("search (%.2lf, %.2lf): %d\n", p[2].x, p[2].y, list_search(l, p[2]));
    printf("search (%.2lf, %.2lf): %d\n", p[3].x, p[3].y, list_search(l, p[3]));
    printf("search (%.2lf, %.2lf): %d\n", p[4].x, p[4].y, list_search(l, p[4]));
    printf("search (%.2lf, %.2lf): %d\n\n", p[5].x, p[5].y, list_search(l, p[5]));

    list_shuffle(l);
    list_print(l);
    printf("\n");

    printf("isempty: %d\n", list_isEmpty(l));
    printf("\n");

    list_insert(l, p2, 2);
    list_print(l);
    printf("\n");

    list_insert(l, p2, 4);
    list_print(l);
    printf("\n");

    list_insert(l, p2, 0);
    list_print(l);
    printf("\n");

    list_append(l, p2);
    list_print(l);
    printf("\n");

    list_insert(l, p2, 7);
    list_print(l);
    printf("\n");

    printf("len: %d\n", list_getLength(l));
    printf("\n");

    list_remove(l, 7);
    list_remove(l, list_getLength(l)-1);
    list_remove(l, 0);
    list_remove(l, 4);
    list_remove(l, 2);

    list_print(l);
    printf("\n");

    printf("len: %d\n", list_getLength(l));
    printf("\n");

    while(list_getLength(l) < MAX_LENGTH){
        list_append(l, p2);
    }

    list_print(l);
    printf("\n");

    printf("len: %d\n", list_getLength(l));
    printf("\n");

    list_append(l, p2);    

    list_print(l);
    printf("\n");

    printf("len: %d\n", list_getLength(l));
    printf("\n");

    printf("full: %d\n", list_isFull(l));
    printf("\n");

    printf("empty: %d\n", list_isEmpty(l));
    printf("\n");

    while(list_getLength(l) > NUMBER_OF_POINTS){
        list_remove(l, list_getLength(l) - 1);
    }

    list_print(l);
    printf("\n");

    printf("len: %d\n", list_getLength(l));
    printf("\n");

    list_swap(l, 0, list_getLength(l)-1);
    list_print(l);
    printf("\n");
    list_swap(l, 0, list_getLength(l)-1);
    list_print(l);
    printf("\n");

    printf("search (%.2lf, %.2lf): %d\n", p[0].x, p[0].y, list_search(l, p[0]));
    printf("search (%.2lf, %.2lf): %d\n", p[1].x, p[1].y, list_search(l, p[1]));
    printf("search (%.2lf, %.2lf): %d\n", p[2].x, p[2].y, list_search(l, p[2]));
    printf("search (%.2lf, %.2lf): %d\n", p[3].x, p[3].y, list_search(l, p[3]));
    printf("search (%.2lf, %.2lf): %d\n", p[4].x, p[4].y, list_search(l, p[4]));
    printf("search (%.2lf, %.2lf): %d\n\n", p[5].x, p[5].y, list_search(l, p[5]));

    list_shuffle(l);
    list_print(l);
    printf("\n");

    printf("isempty: %d\n", list_isEmpty(l));
    printf("\n");

    // SORTING ______________________________

    printf("SORTING::::::::::::::::::::::::\n\n");

    list_sort(l, 'x');
    list_print(l);
    printf("\n");

    list_sort(l, 'X');
    list_print(l);
    printf("\n");

    list_sort(l, 'y');
    list_print(l);
    printf("\n");

    list_sort(l, 'Y');
    list_print(l);
    printf("\n");

    list_delete(&l);

    return 0;
}