/*
    Daniel Carvalho Dantas  10685702
    Lucas Viana Vilela      10748409
*/
#ifndef UTIL_H
#define UTIL_H

#define boolean int
#define True 1
#define False 0

// (x, y)
struct point_ {
    double x;
    double y;
};
typedef struct point_ point;

// Checks if 3 points are either collinear or counter-clockwise-oriented
// Returns True if so and False if no
boolean isOriented(point p1, point p2, point p3);

// Returns the lowest in a set of four integers
int min4(int x, int y, int z, int w);

// key 'x': is p1 to the lower-left of p2 - p1.x < p2.x or (p1.x = p2.x and p1.y < p2.y)
// key 'X': is p2 to to upper-right of p2 - p1.x > p2.x or (p1.x = p2.x and p1.y > p2.y)
// key 'y': is p1 to the leftmost-bottom of p2 - p1.y < p2.y or (p1.y = p2.y and p1.x < p2.x)
// key 'Y': is p1 to the rightmost-top of p2 - p1.y > p2.y or (p1.y = p2.y and p1.x > p2.x)
boolean cmpPoints(point p1, point p2, char key);

// Prints point in format (x,y)
void printPoint(point p);

// Lowercase 'x' -> Uppercase 'X' // Uppercase 'X' -> Lowercase 'x'
char toggleChar(char c);

// Returns the absolute value of a double
double dabs(double e);

#endif