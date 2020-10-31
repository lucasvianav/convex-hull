/*
    Daniel Carvalho Dantas  10685702
    Lucas Viana Vilela      10748409
*/
#include <stdio.h>
#include <stdlib.h>
#include "monotone-chain.h"
#include "stack.h"
#include "util.h"

list *convexHull(list *allPoints){
    int noPoints = list_getLength(allPoints);

    if(noPoints > 3){

        // Convex hull's upper and lower sections
        stack *upperHull = stack_create();
        stack *lowerHull = stack_create();

        // In-focus point
        point currentPoint, *auxPoint = NULL;

        // Sorts the set of points from left to right (and bottom to top if there's a tie)
        list_sort(allPoints, 'x');

        // Lower Hull construction
        for(int i = 0; i < noPoints; i++){
            currentPoint = *(list_get(allPoints, i));
            if(stack_getLength(lowerHull) >= 2){ auxPoint = stack_secondFromTop(lowerHull); }

            // If there's at least 2 points in the stack --> ok
            // If the last 2 points in the stack and the current point are not clockwise-oriented --> ok
            // If ok --> push current point to stack
            // If not ok --> pop a point from stack and check again
            while(stack_getLength(lowerHull) >= 2){
                if(!isOriented(*auxPoint, *(stack_top(lowerHull)), currentPoint)){
                    free(stack_pop(lowerHull));
                    free(auxPoint);
                    if(stack_getLength(lowerHull) >= 2){ auxPoint = stack_secondFromTop(lowerHull); }
                }
                else{
                    free(auxPoint);
                    break;
                }
            }

            stack_push(lowerHull, currentPoint);
        }

        // Upper Hull construction
        for(int i = noPoints - 1; i >= 0; i--){
            currentPoint = *(list_get(allPoints, i));
            if(stack_getLength(upperHull) >= 2){ auxPoint = stack_secondFromTop(upperHull); }

            while(stack_getLength(upperHull) >= 2){
                if(!isOriented(*auxPoint, *(stack_top(upperHull)), currentPoint)){
                    free(stack_pop(upperHull));
                    free(auxPoint);
                    if(stack_getLength(lowerHull) >= 2){ auxPoint = stack_secondFromTop(upperHull); }
                }
                else{
                    free(auxPoint);
                    break;
                }
            }

            stack_push(upperHull, currentPoint);
        }

        // The top point from each stack is the bottom point from the other one
        free(stack_pop(lowerHull));
        free(stack_pop(upperHull));

        // Full convex hull
        list *hull = list_create(stack_getLength(lowerHull) + stack_getLength(upperHull));

        // Concatenates the stacks into the complete hull (counter-clockwise order)
        list_attachStack(hull, lowerHull);
        list_attachStack(hull, upperHull);

        return hull;

    }

    return allPoints;

}
