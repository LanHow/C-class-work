#ifndef UTVECTOR_H_INCLUDED
#define UTVECTOR_H_INCLUDED

#include "..\cppunitlite\TestHarness.h"
#include "..\Vector.h"
#include "..\ProductDot.h"
#include "..\cent.h"

const double epsilon = 0.0001;
TEST(Vector, first) {
  double a[] = {1,2};
  Vector v(2,a);
//  Vector v;
//  v.dimension = 2;
//  v.component = a;
  LONGS_EQUAL(2,v.dimension());
  DOUBLES_EQUAL(1,v.component(1),epsilon);
  DOUBLES_EQUAL(2,v.component(2),epsilon);
}

TEST(product_dot, OK_vector) {
    double a[]={2,3};
    double b[]={3,4.1};
    Vector va(2,a);
    Vector vb(2,b);
    DOUBLES_EQUAL(18.3, product_dot(va,vb),epsilon);
}

TEST(extractVector,ok){
    string s("2 1 2.1");

    Vector v(extractVector(s));

    LONGS_EQUAL(2, v.dimension());
    DOUBLES_EQUAL(1, v.component(1),epsilon);
    DOUBLES_EQUAL(2.1, v.component(2),epsilon);
}

TEST(Vector, copyAssignment) {
  double a[] = {1,2.1};
  Vector v(2,a);
  Vector u;
  LONGS_EQUAL(0,u.dimension());
  u = v;
  LONGS_EQUAL(2,u.dimension());
  DOUBLES_EQUAL(1,u.component(1),epsilon);
  DOUBLES_EQUAL(2.1,u.component(2),epsilon);
}

TEST(Vector, subtract) {
    double a[]={2,3};
    double b[]={3,4.1};
    Vector va(2,a);
    Vector vb(2,b);
    Vector vc = vb-va;
    DOUBLES_EQUAL(1, vc.component(1),epsilon);
    DOUBLES_EQUAL(1.1, vc.component(2),epsilon);
}

TEST (Vector, length) {
    double a[]={3,4};
    Vector va(2,a);
    DOUBLES_EQUAL(5.0, va.length(), 0.0001);
}

TEST (Vector, equality)
{
    double a[]={2, 1, 2}, b[] = {2, 1, 2};
    Vector v1(3, a), v2(3, b);
    CHECK(v1 == v2);
}

TEST(Vector, dot) {
    double a[]={2, 1, 2}, b[] = {2, 1, 2};
    Vector v1(3, a), v2(3, b);
    DOUBLES_EQUAL(9,v1*v2,epsilon);
}

TEST(Vector, centroid){
    double a[]={1,2}, b[] = {2,3}, c[] = {3,4};

    Vector va(2, a),vb(2, b),vc(2, c);
    Vector varray[]={va,vb,vc};
    Vector cent(centroid(3,varray));
    DOUBLES_EQUAL(2,cent.component(1),epsilon);
    DOUBLES_EQUAL(3,cent.component(2),epsilon);
}
TEST(Vector, centroid2){
    double a[]={0,0}, b[] = {3,0}, c[] = {3,4};

    Vector va(2, a),vb(2, b),vc(2, c);
    Vector varray[]={va,vb,vc};
    Vector cent(centroid(3,varray));
    LONGS_EQUAL(2,cent.component(1));
    DOUBLES_EQUAL(1.333333333,cent.component(2),0.0001);

}
TEST(Vector, add){

    double a[]={0,0}, b[] = {3,0};

    Vector va(2, a),vb(2, b);

    Vector r(va+vb);
    DOUBLES_EQUAL(3,r.component(1),epsilon);
    DOUBLES_EQUAL(0,r.component(2),epsilon);


}

TEST(Vector, div){
    double a[]={4,2};
    double n =2.0;
    Vector va(2, a);

    Vector r(va/n);
    DOUBLES_EQUAL(2,r.component(1),epsilon);
    DOUBLES_EQUAL(1,r.component(2),epsilon);
}

TEST (Vector, fromstring) {
    string s("(0,0)");
    Vector v = getVectorFromString(s);

    LONGS_EQUAL(2,v.dimension());
    DOUBLES_EQUAL(0,v.component(1),epsilon);
    DOUBLES_EQUAL(0,v.component(2),epsilon);
}

TEST (Vector, fromstring_exceptional) {
    string s("(0 0)");
    Vector v;
    try{
        v = getVectorFromString(s);
        FAIL("exception not thrown");
    } catch (string s){
        CHECK(s==string("format error"));
    }

}
#endif // UTVECTOR_H_INCLUDED
