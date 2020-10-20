#ifndef UTIL_H
#define UTIL_H

#define boolean int
#define True 1
#define False 0

// (x, y)
typedef struct {
    double x;
    double y;
} point;

// Checks if 3 points are counter-clockwise-oriented
// Returns True if so and False if no
boolean isCCW(point p1, point p2, point p3);

#endif