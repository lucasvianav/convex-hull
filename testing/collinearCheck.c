#include <stdio.h>
#include "../util.h"
#include "../ADTs/list.h"

int main(){
    point p[] = {{2,1}, {2.3,1.9}, {2.7,3.1}, {3.4,5.2}, {5, 10}};
    list *l= list_create(5);

    for(int i = 0; i < 5; i++){
        list_append(l, p[i]);
    }

    list_print(l);

    printf("is collinear: %d\n", list_isCollinear(l));

    list_delete(&l);

    return 0;
}