#ifndef CONVEXPOLYGON_H_INCLUDED
#define CONVEXPOLYGON_H_INCLUDED
#include "..\Vector.h"
#include "..\triangle_area.h"
#include "..\cent.h"
#include <string>
#include <algorithm>
#include "Shape.h"
#include "..\matrix\Matrix.h"

class ConvexPolygon: public Shape {
public:
    ConvexPolygon(int a, Vector vs[])
    :n(a),v(new Vector[a]){
        for (int i=0; i<n; ++i)
            v[i] = vs[i];
    }
    int n_vertices() const {return n;}
    Vector & vertex(int i) const {
        if (i<1 || i> n)
            throw std::string("illegal vertex index");
        return v[i-1];
    }

    ConvexPolygon(ConvexPolygon const & cp)
    :n(cp.n),v(new Vector[cp.n]){
        for (int i=0; i<n; ++i)
            v[i] = cp.v[i];
    }

    double perimeter () const {
        double p=0.0;
        for (int i=2; i<=n; ++i)
            p += (vertex(i)-vertex(i-1)).length();
        p += (vertex(1)-vertex(n)).length();
        return p;
    }
    double area() const{
        double a=0.0;
        for(int i=2; i<n; ++i)
            a+= triangle_area(vertex(1),vertex(i),vertex(i+1));
        return a;
    }
    string description() const {
        stringstream ss;
        ss<<"{"<<"convex polygon, "<<n;
        ss<<", [";
        for(int i=0;i<n-1;i++)
            ss<<v[i].description()<<", ";
        ss<<v[n-1].description()<<"]}";
        return ss.str();
    }

    bool operator == (ConvexPolygon const & a){
        if(n!=a.n)
            return false;
        for(int i=0;i<n;i++)
            if(!(v[i]==a.v[i]))
                return false;
        return true;

    }
    string toSVG() const
    {
        stringstream ss;
        ss << "<polygon points=\"";
        for (int i=0; i < n-1; ++i)
            ss << v[i].toSVG()<< " ";
        ss << v[n-1].toSVG() <<"\"\n";
        ss << "         style=\"stroke:orangered; stroke-width: 0.5; fill:navy;\"/>";
        return ss.str();
    }

private:
    int n;
    Vector * v;
};

ConvexPolygon createConvexPolygon(int n,Vector vs[], Vector const & v)
{
    std::sort(vs,vs+n,smallAngleInFront(centroid(n,vs),v));
    return ConvexPolygon(n,vs);
}

bool smallPerimeterInFront(ConvexPolygon const & a,ConvexPolygon const & b){
    return a.perimeter()<b.perimeter();
}

string toSVG(vector<ConvexPolygon> & vs)
{
    stringstream ss;
    ss << "<svg xmlns=\"http://www.w3.org/2000/svg\"\n";
    ss << "     width=\"500\" height=\"500\" viewBox=\"0 0 25 25\">\n";
    for (int i=0;  i<(int)vs.size(); ++i)
        ss << vs[i].toSVG() << "\n";
    ss << "</svg>";
    return ss.str();
}

ConvexPolygon createRegularPolygon(int n)
{
    double pi = 3.14159265359;
    double angle = 2*pi/n;
    Vector vs[n];
    double f[]={1,0};
    Vector fv(2,f);
    vs[0]=fv;
    for(int i=1;i<n;i++){
        double a = 1*cos(angle*i);
        double b = 1*sin(angle*i);
        double j[]={a,b};
        Vector v(2,j);
        vs[i]=v;
    }
    ConvexPolygon result(n,vs);
    return result;
}

ConvexPolygon translate(Vector const & v, ConvexPolygon const & p)
{
    Vector vs[p.n_vertices()];
    for(int i=0;i<p.n_vertices();i++)
        vs[i] = v + p.vertex(i+1);
    ConvexPolygon ct(p.n_vertices(),vs);
    return ct;
}

ConvexPolygon apply(Matrix const & m, ConvexPolygon const & cp) {
    ConvexPolygon c(cp);
    for (int i=1; i<=c.n_vertices(); ++i)
        c.vertex(i) = apply(m, c.vertex(i));
    return c;
}
#endif // CONVEXPOLYGON_H_INCLUDED
