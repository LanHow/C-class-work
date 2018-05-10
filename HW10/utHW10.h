#ifndef UTHW10_H_INCLUDED
#define UTHW10_H_INCLUDED
#include "..\Vector.h"
#include "..\ConvexPolygon\ConvexPolygon.h"
#include <string>
#include "..\ConvexPolygon\Circle.h"
#include <list>
#include <fstream>
#include "..\matrix\Matrix.h"
#include <math.h>

using namespace std;
const double epsilon = 0.00001;

TEST(createRegularPolygon, T1){
    ConvexPolygon t = createRegularPolygon(3);
    double a[]={1,0},b[]={-sqrt(3),0.5},c[]={-sqrt(3),-0.5};
    Vector va(2,a);
    Vector vb(2,b);
    Vector vc(2,c);
    Vector vs[]={va,vb,vc};
    ConvexPolygon ans(3,vs);
    LONGS_EQUAL(3,t.n_vertices());
    DOUBLES_EQUAL(sqrt(3),t.perimeter()/3,epsilon);
    DOUBLES_EQUAL(sqrt(3)*3,t.perimeter(),epsilon);
    DOUBLES_EQUAL(sqrt(3)*3/4,t.area(),epsilon);
}

TEST(translate, T2){
    double a[]={2,2};
    Vector va(2,a);
    ConvexPolygon t = createRegularPolygon(4);
    ConvexPolygon s = translate(va,t);
    for(int i=1;i<5;i++)
        CHECK((t.vertex(i)+va) == s.vertex(i));
}

TEST(appy, T3){
    double am[]={2,0,0,2};
    Matrix m(2,2,am);
    ConvexPolygon t1 = createRegularPolygon(4);
    ConvexPolygon ans1 = createRegularPolygon(4);
    //cout << t1.description() << "\n" <<endl;
    ConvexPolygon t2 = apply(m,t1);
    //cout << t1.description() << "\n" <<endl;
    double tr[]={2,2};
    Vector vt(2,tr);
    ConvexPolygon t3 = translate(vt,t2);
    for(int i=1;i<5;i++)
    {
        Vector ans2 = apply(m,ans1.vertex(i));
        CHECK((ans2+vt) == t3.vertex(i));
    }
}

TEST(svg, T4){
    vector<ConvexPolygon> cps;
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
        {
            ConvexPolygon cp = createRegularPolygon((i*5)+j+3);
            double a[]={3*(j+1),3*(i+1)};
            Vector va(2,a);
            cp = translate(va,cp);
            cps.push_back(cp);
        }
    }
    ofstream ofs("RegularPolygons.svg");
    ofs <<toSVG(cps);
    ofs.close();
}
#endif // UTHW10_H_INCLUDED
