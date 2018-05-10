#ifndef UTCP_H_INCLUDED
#define UTCP_H_INCLUDED
#include "..\Vector.h"
#include "ConvexPolygon.h"
#include <string>
#include "Circle.h"
#include <list>
#include <fstream>
#include "..\matrix\Matrix.h"

using namespace std;
const double epsilon = 0.00001;
TEST(ConvexPolygon, Constructor){
    double u[]={0,0}, v[]={3,0}, w[]={3,4};
    Vector a(2,u), b(2,v), c(2,w);
    Vector vertices[]={a,b,c};
    ConvexPolygon cp(3,vertices);
    LONGS_EQUAL(3,cp.n_vertices());
    /*
    LONGS_EQUAL(0,cp.vertex(1).component(1));
    LONGS_EQUAL(0,cp.vertex(1).component(2));
    */
    CHECK(a == cp.vertex(1));
}

TEST(ConvexPolygon, outofboundlow){
    double u[]={0,0}, v[]={3,0}, w[]={3,4};
    Vector a(2,u), b(2,v), c(2,w);
    Vector vertices[]={a,b,c};
    ConvexPolygon cp(3,vertices);

    try {
        cp.vertex(0);
        FAIL("exception not throw");
    } catch(string s) {
        CHECK (string("illegal vertex index") == s);
    }
}

TEST(ConvexPolygon, outofboundhigh){
    double u[]={0,0}, v[]={3,0}, w[]={3,4};
    Vector a(2,u), b(2,v), c(2,w);
    Vector vertices[]={a,b,c};
    ConvexPolygon cp(3,vertices);

    try {
        cp.vertex(4);
        FAIL("exception not throw");
    } catch(string s) {
        CHECK (string("illegal vertex index") == s);
    }
}

TEST(ConvexPolygon, perimeter){
    double u[]={0,0}, v[]={3,0}, w[]={3,4};
    Vector a(2,u), b(2,v), c(2,w);
    Vector vertices[]={a,b,c};
    ConvexPolygon cp(3,vertices);

    DOUBLES_EQUAL(12.0,cp.perimeter(),0.000);
}

TEST (ConvexPolygon, area) {
    double u[]={0,0}, v[]={3,0}, w[]={3,4};
    Vector a(2,u), b(2,v), c(2,w);
    Vector vertices[]={a,b,c};
    ConvexPolygon cp(3,vertices);

    DOUBLES_EQUAL(6.0,cp.area(),0.0001);
}


TEST(ConvexPolygon, area1){
    double u[]={1,-1}, v[]={1,1}, w[]={-1,1},x[]={-1,-1};
    Vector a(2,u), b(2,v), c(2,w), d(2,x);
    Vector vertices[]={a,c,b,d};
    ConvexPolygon cp=createConvexPolygon(4,vertices,a);
    //ConvexPolygon cp(4,vertices);
    DOUBLES_EQUAL(8.0,cp.perimeter(),0.0001);
    DOUBLES_EQUAL(4.0,cp.area(),0.0001);
}

TEST (ConvexPolygon, description) {
    double u[]={0,0}, v[]={3,0}, w[]={3,4};
    Vector a(2,u), b(2,v), c(2,w);
    Vector vertices[]={a,b,c};
    ConvexPolygon cp(3,vertices);

    string ans("{convex polygon, 3, [(0,0), (3,0), (3,4)]}");
    CHECK(ans==cp.description());

}

TEST(Circle, constructor){
    double c[]={0, 0};
    Vector c1(2, c);
    Circle o(c1, 1);

    DOUBLES_EQUAL(1, o.radius(), 0.0001);
    CHECK(c1 == o.center());
}

TEST(Circle, description){
    double c[]={0, 0};
    Vector c1(2, c);
    Circle o(c1, 1);
    string s("{circle, (0,0), 1}");
    CHECK(s == o.description());
}

TEST (printShapeInfo, convexpolygon) {
    double u[]={0,0}, v[]={3,0}, w[]={3,4};
    Vector a(2,u), b(2,v), c(2,w);
    Vector vertices[]={a,b,c};
    ConvexPolygon cp(3,vertices);

    string ans("{convex polygon, 3, [(0,0), (3,0), (3,4)]}");
    CHECK(ans==printShapeInfo(cp));
}

TEST (printShapeInfo, circle) {
    double c[]={0, 0};
    Vector c1(2, c);
    Circle o(c1, 1);
    string s("{circle, (0,0), 1}");
    CHECK(s == printShapeInfo(o)) ;
    CHECK(string("(0,0)") == printShapeInfo(c1)) ;
}

TEST(ConvexPolygon,SortByPerimeter){
    double u[]={0,0}, v[]={3,0}, w[]={3,4};
    Vector a(2,u), b(2,v), c(2,w);
    Vector vertices[]={a,b,c};
    ConvexPolygon cp1(3,vertices);
    double u2[]={1,-1}, v2[]={1,1}, w2[]={-1,1},x2[]={-1,-1};
    Vector a2(2,u2), b2(2,v2), c2(2,w2), d2(2,x2);
    Vector vertices2[]={a2,c2,b2,d2};
    ConvexPolygon cp2=createConvexPolygon(4,vertices2,a2);
    double u3[]={0,0}, v3[]={1,0}, w3[]={0,1};
    Vector a3(2,u3), b3(2,v3), c3(2,w3);
    Vector vertices3[]={a3,b3,c3};
    ConvexPolygon cp3(3,vertices3);
    ConvexPolygon cps[]={cp1,cp2,cp3};
    vector<ConvexPolygon> vcps (cps,cps+3);
    sort(vcps.begin(),vcps.end(),smallPerimeterInFront);
    //sort(cps,cps+3,smallPerimeterInFront);

    vector<ConvexPolygon>::iterator i = vcps.begin();
    CHECK(cp3==*i); i++;
    CHECK(cp2==*i); i++;
    CHECK(cp1==*i);
}
TEST (stringstream, getline) {
    string s("abc;def");
    stringstream ss(s);
    string half;
    getline(ss,half,';');

    CHECK(string ("abc")== half);

}
TEST (Circle, fromstringnameerror) {
    string s("{ircle; (0,0); 1}");
    try{
        getCircleFromString (s);
        FAIL("exception not throw");
    }catch(string s1){
        CHECK(s1 ==string("format error"));
    }
}

TEST (Circle, fromstring) {
    string s("{circle; (0,0); 1}");
    Circle c = getCircleFromString (s);
    vector<double> v;
    v.push_back(0);
    v.push_back(0);
    CHECK(Vector(v)== c.center() );
    DOUBLES_EQUAL(1, c.radius(), epsilon);
}

TEST (sort, shapeByperimeter) {
    double u[]={0,0}, v[]={3,0}, w[]={3,4};
    Vector a(2,u), b(2,v), c(2,w);
    Vector vertices[]={a,b,c};
    ConvexPolygon cp(3,vertices);
    Circle cir(a,1);
    vector<Shape *> vs;
    vs.push_back(&cp);
    vs.push_back(&cir);
    sort(vs.begin(),vs.end(),ptrToSmallPerimeterInFront);
    CHECK(string("{circle, (0,0), 1}") == vs[0]->description());
    CHECK(string("{convex polygon, 3, [(0,0), (3,0), (3,4)]}")==vs[1]->description());
}

TEST(ConvexPolygon, toSVG) {
    double u[]={0,0}, v[]={3,0}, w[]={3,4};
    Vector a(2,u), b(2,v), c(2,w);
    Vector vertices[]={a,b,c};
    ConvexPolygon cp(3,vertices);
    cout <<cp.toSVG() << endl;
    vector<ConvexPolygon> cps;
    cps.push_back(cp);
    cout << toSVG(cps) << endl;
    ofstream ofs("345.svg");
    ofs <<toSVG(cps);
    ofs.close();
}
#endif // UTCP_H_INCLUDED
