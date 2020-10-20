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

// Returns the lowest int
int min4(int x, int y, int z, int w);

// key 'x': is p1 to the lower-left of p2 - p1.x < p2.x or (p1.x = p2.x and p1.y < p2.y)
// key 'X': is p2 to to lower-right of p2 - p1.x > p2.x or (p1.x = p2.x and p1.y < p2.y)
// key 'y': is p1 to the leftmost-bottom of p2 - p1.y < p2.y or (p1.y = p2.y and p1.x < p2.x)
// key 'Y': is p1 to the leftmost-top of p2 - p1.y > p2.y or (p1.y = p2.y and p1.x < p2.x)
boolean cmpPoints(point p1, point p2, char key);

#endif