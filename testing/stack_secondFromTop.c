#include <stdio.h>
#include <stdlib.h>
#include "../ADTs/stack.h"
#include "../util.h"

int main(){
    point p[] = { {0,0}, {1,-6}, {1,3}, {6,3}, {-16,3}, {0,0} };
    point *pp;

    stack *s = stack_create();

    for(int i = 0; i < 5; i++){
        stack_push(s, p[i]);
    }
    stack_print(s);

    printf("\n");
    pp = stack_secondFromTop(s);
    printPoint(*pp);

    printf("\n");
    stack_print(s);

    free(pp);
    stack_delete(&s);

    return 0;

}