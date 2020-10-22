#include <stdio.h>
#include <ctype.h>
#include "util.h"

boolean isOriented(point p1, point p2, point p3){
    double triangleArea = p1.x * p2.y + p1.y * p3.x + p2.x * p3.y - p3.x * p2.y - p3.y * p1.x - p2.x * p1.y;

    if(triangleArea <= 0){
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

    else{ return w; }
}

boolean cmpPoints(point p1, point p2, char key){
    if(key == 'x' || key == 'X' || key == 'y' || key == 'Y'){
    
        if( key == 'x' && p1.x <= p2.x){
            if(p1.x == p2.x && p1.y >= p2.y){
                return False;
            }

            return True;
        }
        
        if( key == 'X' && p1.x >= p2.x){
            if(p1.x == p2.x && p1.y <= p2.y){
                return False;
            }

            return True;
        }
        
        if( key == 'y' && p1.y <= p2.y){
            if(p1.y == p2.y && p1.x >= p2.x){
                return False;
            }

            return True;
        }
        
        if( key == 'Y' && p1.y >= p2.y){
            if(p1.y == p2.y && p1.x <= p2.x){
                return False;
            }

            return True;
        }

    }

    return False;
}

void printPoint(point p){
    printf("(%.2lf, %.2lf)\n", p.x, p.y);

    return;
}

char toggleChar(char c){
    if(isupper(c)){ return tolower(c); }

    else{ return toupper(c); }
}