#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "./ADTs/stack.h"
#include "./ADTs/list.h"
#include "monotone-chain.h"
#include "./time/tempo.h"

int main(){
    int noPoints; // Total number of points
    char outputStart; // In which element the output must start
    int outputOrientation; // Clockwise x Counter-Clockwise
    float pointsPercentage; // Fraction between points on the hull and the whole

    // Gets quantity
    scanf("%d", &noPoints);

    list* allPoints = list_create(noPoints);
    point auxPoint; // Auxiliar variable

    // Gets points and appends them to the allPoints list
    for(int i = 0; i < noPoints; i++){
        scanf("%lf", &auxPoint.x);
        scanf("%lf", &auxPoint.y);
        list_append(allPoints,auxPoint);
    }

    // Gets output info
    scanf(" %c", &outputStart);
    scanf("%d", &outputOrientation);

    // Start timer
    double interval = seconds();

    // Gets this group of points' convex hull
    list* hull = convexHull(allPoints);

    // Time interval used to calculate the hull
    interval = seconds() - interval;

    // Calculates the percentage
    pointsPercentage = 100*((float) list_getLength(hull) / (float) noPoints);

    // Sorts the list accordingly to input specifications
    list_orientate(hull, outputOrientation, list_searchExtreme(hull, outputStart)); 

    // Prints the hull according to designated output format (starting point and orientation)
    list_print(hull);

    // Prints the percentage
    printf("%.2f\n", pointsPercentage);

    // Frees allocated memory
    list_delete(&allPoints);
    list_delete(&hull);

    // Opens file in which the time interval measured'll be written
    FILE* f = fopen("./results/time-intervals.out", "a");
    if(f == NULL) { return 1; }

    // Writes time interval to file
    fprintf(f,"Input size: %15d | Time interval: %15lfs\n", noPoints, interval);

    // Closes the file
    fclose(f);

    return 0;
}
