#include <stdio.h>
#include <stdlib.h>
#include "monotone-chain.h"

// Returns True if the 3 points are in counter-clockwise orientation
// And False if they're not
boolean isCCW(point p1, point p2, point p3){
    double crossProduct = p1.x * p2.y + p1.y * p3.x + p2.x * p3.y - p3.x * p2.y - p3.y * p1.x - p2.x * p1.y;

    if(crossProduct < 0){
        return True;
    }

    else{
        return False;
    }
}

list *convexHull(list *allPoints){
    int noPoints = list_getLength(allPoints);

    if(noPoints >= 3){

        stack *upperHull = stack_create();
        stack *lowerHull = stack_create();

        list_sort(allPoints, 'x');

        for(int i = 0; i < noPoints; i++){
            while(stack_getLength(lowerHull) >= 2 && )


        }

    }

}