/*
    Daniel Carvalho Dantas  10685702
    Lucas Viana Vilela      10748409
*/
#include <stdio.h>
#include <stdlib.h>
#include "monotone-chain.h"
#include "./ADTs/stack.h"
#include "util.h"

list *convexHull(list *allPoints){
    // If the list contains only 2 or fewer points they're always collinear
    // If the list contains only collinear points, then a hull can't be determined
    if(!list_isCollinear(allPoints)){
        int noPoints = list_getLength(allPoints);

        // Convex hull's upper and lower sections
        stack *upperHull = stack_create();
        stack *lowerHull = stack_create();

        // In-focus point
        point currentPoint;

        // Auxiliar variable that'll store
        // the second point from the top of the stack
        point *auxPoint = NULL;

        // Sorts the set of points from left to right (and bottom to top if there's a tie)
        list_sort(allPoints, 'x');

        // Lower Hull construction
        for(int i = 0; i < noPoints; i++){
            currentPoint = *(list_get(allPoints, i)); // Current point on the list
            if(stack_getLength(lowerHull) >= 2){ auxPoint = stack_secondFromTop(lowerHull); } // Second point from the top of the stack

            // If there's lees than 2 points in the stack --> the current point is ok
            // If the last 2 points in the stack and the current point are not clockwise-oriented --> the current point is ok
            // If the current point is ok --> push it to the stack
            // If the current point is not ok --> pop a point from the stack and check again (and get new second point from the top)
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

    return NULL;

}
