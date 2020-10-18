#include <stdio.h>
#include "../ATDs/list.h"

int main(){
    point p[] = { {0,0}, {1,-6}, {1,3}, {6,3}, {-16,3} };
    point p2 = {77, 77};
    list *l = list_create();

    printf("%d\n", list_getLength(l));
    printf("\n");

    for(int i = 0; i < 5; i++){
        list_append(l, p[i]);
        list_print(l);
        printf("%d\n", list_getLength(l));
        printf("\n");
    }
    printf("\n");

    point *current = list_get(l, 0);
    for(int i = 0; i <= 6 && current != NULL; i++, current = list_get(l, i)){
        printf("(%lf, %lf)\n", current->x, current->y);
    }
    printf("\n");

    list_swap(l, 0, list_getLength(l)-1);
    list_print(l);
    printf("\n");
    list_swap(l, 0, list_getLength(l)-1);
    list_print(l);
    printf("\n");

    printf("search (%.2lf, %.2lf): %d\n", p[2].x, p[2].y, list_search(l, p[2]));
    printf("\n");    

    list_reverse(l);
    list_print(l);
    printf("\n");

    list_shuffle(l);
    list_print(l);
    printf("\n");

    printf("%d\n", list_isEmpty(l));
    printf("\n");

    list_insert(l, p2, 2);
    list_print(l);
    printf("\n");

    list_insert(l, p2, 4);
    list_print(l);
    printf("\n");

    list_remove(l, 4);
    list_remove(l, 2);
    list_print(l);
    printf("\n");

    printf("%d\n", list_getLength(l));
    printf("\n");

    // SORTING ______________________________

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