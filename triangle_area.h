#ifndef TRIANGLE_AREA_H_INCLUDED
#define TRIANGLE_AREA_H_INCLUDED
#include "Vector.h"
#include <math.h>

double triangle_area(Vector const & v1,Vector const & v2,Vector const & v3){
    double a=(v2-v1).length();
    double b=(v3-v2).length();
    double c=(v1-v3).length();
    double s=(a+b+c)/2;
    return sqrt(s*(s-a)*(s-b)*(s-c));
}

#endif // TRIANGLE_AREA_H_INCLUDED
