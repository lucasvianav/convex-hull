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

int min4(int x, int y, int z, int w){
    if(x <= y && x <= z && x <= w){ return x; }

    else if(y <= x && y <= z && y <=w){ return y; }

    else if(z <= x && z <= y && z <= w){ return z; }

    else if(w <= x && w <= y && w <= z){ return w; }
}

boolean cmpPoints(point p1, point p2, char key){
    if(key == 'x' || key == 'X' || key == 'y' || key == 'Y'){
        
        if( key == 'x' && ( p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y) ) ){
            return True;
        }
        
        if( key == 'X' && ( p1.x > p2.x || (p1.x == p2.x && p1.y < p2.y) ) ){
            return True;
        }
        
        if( key == 'y' && ( p1.y < p2.y || (p1.y == p2.y && p1.x < p2.x) ) ){
            return True;
        }
        
        if( key == 'Y' && ( p1.y < p2.y || (p1.y == p2.y && p1.x < p2.x) ) ){
            return True;
        }
    }

    return False;
}