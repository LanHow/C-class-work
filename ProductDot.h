#ifndef PRODUCTDOT_H_INCLUDED
#define PRODUCTDOT_H_INCLUDED

#include <string>
#include "Vector.h"

using namespace std;


double product_dot(Vector & a,Vector & b)
{
    double ans = 0;
    int i;
    if(a.dimension() == b.dimension())
        for(i=1;i<=a.dimension();i++)
            ans += a.component(i)*b.component(i);
    else
        throw string("exception");
    return ans;
}

int * const
minus_vector(int a[], int b[] , int da ,int db)
{
    int i;
    int * const ans = new int[da];
    if(da == db)
        for(i=0;i<da;i++)
            ans[i] = a[i] -b[i];
    else
        throw string("subtract_exception");
    return ans ;
}

#endif // PRODUCTDOT_H_INCLUDED
