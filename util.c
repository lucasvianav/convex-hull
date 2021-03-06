/*
    Daniel Carvalho Dantas  10685702
    Lucas Viana Vilela      10748409
*/
#include <stdio.h>
#include <ctype.h>
#include "util.h"

// Checks the orientation of the points, if they are counterclockwise or not
boolean isOriented(point p1, point p2, point p3){
    // Calculates the triangle formed between the three points' area
    double triangleArea = p1.x * p2.y + p1.y * p3.x + p2.x * p3.y - p3.x * p2.y - p3.y * p1.x - p2.x * p1.y;

    // If the area is <= 0, they're either collinear or counter-clockwise-oriented
    if(triangleArea <= 0){
        return True;
    }

    else{
        return False;
    }
}

// Returns the minimun value between 4 points
int min4(int x, int y, int z, int w){
    if(x <= y && x <= z && x <= w){ return x; }

    else if(y <= x && y <= z && y <=w){ return y; }

    else if(z <= x && z <= y && z <= w){ return z; }

    else{ return w; }
}

boolean cmpPoints(point p1, point p2, char key){
    if(key == 'x' || key == 'X' || key == 'y' || key == 'Y'){
    
        // 'x' checks if p1 is to the lower-left of p2
        if( key == 'x' && p1.x <= p2.x){
            if(p1.x == p2.x && p1.y >= p2.y){
                return False;
            }

            return True;
        }
        
        // 'X' checks if p2 is to to upper-right of p2
        if( key == 'X' && p1.x >= p2.x){
            if(p1.x == p2.x && p1.y <= p2.y){
                return False;
            }

            return True;
        }
        
        // 'y' checks if p1 is to the leftmost-bottom of p2
        if( key == 'y' && p1.y <= p2.y){
            if(p1.y == p2.y && p1.x >= p2.x){
                return False;
            }

            return True;
        }
        
        // 'Y' checks if p1 is to the rightmost-top of p2
        if( key == 'Y' && p1.y >= p2.y){
            if(p1.y == p2.y && p1.x <= p2.x){
                return False;
            }

            return True;
        }

    }

    return False;
}

// Prints the x and y value of the point
void printPoint(point p){
    printf("(%.2lf, %.2lf)\n", p.x, p.y);

    return;
}

// If the character is in Uppercase, returns the Lowercase version and vice versa
char toggleChar(char c){
    if(isupper(c)){ return tolower(c); }

    else{ return toupper(c); }
}

// Returns the absolute value of a double
double dabs(double e){
    if(e < 0){ e *= -1; }

    return e;
}