#include <stdio.h>
#include <stdlib.h>
#include "monotone-chain.h"
#include "./ATDs/stack.h"
#include "util.h"

list *convexHull(list *allPoints){
    int noPoints = list_getLength(allPoints);

    if(noPoints > 3){

        // Full convex hull
        list *hull = list_create();

        // Convex hull's upper and lower sections
        stack *upperHull = stack_create();
        stack *lowerHull = stack_create();

        // In-focus point
        point currentPoint;

        // Sorts the set of points from left to right (and bottom to top if there's a tie)
        list_sort(allPoints, 'x');

        // Lower Hull construction
        for(int i = 0; i < noPoints; i++){
            currentPoint = *(list_get(allPoints, i));

            // If there's at least 2 points in the stack --> ok
            // If the last 2 points in the stack and the current point are clockwise-oriented --> ok
            // If ok --> push current point to stack
            // If not ok --> pop a point from stack and check again
            while(stack_getLength(lowerHull) >= 2 && !isCCW(*(stack_secondFromTop(lowerHull)), *(stack_top(lowerHull)), currentPoint)){
                stack_pop(lowerHull);
            }

            stack_push(lowerHull, currentPoint);
        }

        // Upper Hull construction
        for(int i = noPoints - 1; i >= 0; i--){
            currentPoint = *(list_get(allPoints, i));

            while(stack_getLength(upperHull) >= 2 && !isCCW(*(stack_secondFromTop(upperHull)), *(stack_top(upperHull)), currentPoint)){
                stack_pop(upperHull);
            }

            stack_push(upperHull, currentPoint);
        }

        // The top point from each stack is the bottom point from the other one
        stack_pop(lowerHull);
        stack_pop(upperHull);

        // Concatenates the stacks into the complete hull (counter-clockwise order)
        list_extendStack(hull, lowerHull);
        list_extendStack(hull, upperHull);

        // Freeing memory
        stack_delete(lowerHull);
        stack_delete(upperHull);

        return hull;

    }

    return allPoints;

}