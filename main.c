#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "./ATDs/stack.h"
#include "./ATDs/list.h"
#include "monotone-chain.h"

int main(){
    int noPoints; // Total number of points
    char outputStart; // In which element the output must start
    int outputOrientation; // Clockwise x Counter-Clockwise
    float pointsPercentage; // Fraction between points on the hull and the whole

    list* allPoints = list_create();
    point auxPoint; // Auxiliar variable

    // Gets quantity
    scanf("%d",&noPoints);

    // Gets points and appends them to the allPoints list
    for(int i = 0; i < noPoints; i++){
        scanf("%lf", &auxPoint.x);
        scanf("%lf", &auxPoint.y);
        list_append(allPoints,auxPoint);
    }

    // Gets output info
    scanf(" %c", &outputStart);
    scanf("%d", &outputOrientation);

    // Gets this group of points' convex hull
    list* hull = convexHull(allPoints);

    // Calculates the percentage
    pointsPercentage = 100*((float) list_getLength(hull) / (float) list_getLength(allPoints));

    // Prints the hull according to designated output format (starting point and orientation)
    list_auxPrint(hull, outputOrientation, list_searchExtreme(hull, outputStart));
    printf("%.2f\n", pointsPercentage);

    // Frees allocated memory
    list_delete(&allPoints);
    list_delete(&hull);

    return 0;
}
