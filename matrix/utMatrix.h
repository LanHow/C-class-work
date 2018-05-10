#ifndef UTMATRIX_H_INCLUDED
#define UTMATRIX_H_INCLUDED
#include "Matrix.h"
#include "..\Vector.h"
const double epsilon = 0.0001;
TEST(Matrix,constructor){
    double a[]={1,1.25,0,1};
    Matrix m(2,2,a);
    DOUBLES_EQUAL(1,m.component(1,1),epsilon);
    DOUBLES_EQUAL(1.25,m.component(1,2),epsilon);
    DOUBLES_EQUAL(0,m.component(2,1),epsilon);
}
TEST(Matrix,rowvector){
    double a[]={1,1.25,0,1};
    Matrix m(2,2,a);
    double b[]={1,1.25};
    double c[]={0,1};
    Vector v1(2,b);
    Vector v2(2,c);
    CHECK(v1==m.rowVector(1));
    CHECK(v2==m.rowVector(2));
}

TEST(Matrix,apply){
    double a[]={1,1.25,0,1};
    Matrix m(2,2,a);
    double b[]={1,1};
    Vector v(2,b);
    double c[]={2.25,1};
    Vector u(2,c);
    CHECK(u==apply(m,v));
}
#endif // UTMATRIX_H_INCLUDED
