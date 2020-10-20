#include "util.h"

boolean isCCW(point p1, point p2, point p3){
    double crossProduct = p1.x * p2.y + p1.y * p3.x + p2.x * p3.y - p3.x * p2.y - p3.y * p1.x - p2.x * p1.y;

    if(crossProduct < 0){
        return True;
    }

    else{
        return False;
    }
}