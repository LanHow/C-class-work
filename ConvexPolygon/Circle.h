#ifndef CIRCLE_H_INCLUDED
#define CIRCLE_H_INCLUDED

#include <string>
#include <sstream>
#include "Shape.h"
#include "../getVector.h"
const double PI = 3.14159265;
class Circle : public Shape {
public:
    Circle(){}
    Circle(Vector center, double radius):c(center), r(radius){}
    double perimeter()const {
        return (2 * PI * r);
    }
    double area() const{return PI * r * r;}
    Vector center() const{return c;}
    double radius() const{return r;}

    std::string description() const{
        std::stringstream ss;
        ss << "{circle, " << c.description() << ", " << r << "}";
        return ss.str();
        }
private:
    Vector c;
    double r;
};

Circle getCircleFromString(string s){
    string FormatError("format error");
    stringstream ss(s);
    char c;
    ss >> c;
    if(c!='{') throw FormatError;
    string shape, center;
    double r;
    getline(ss,shape,';');
    if(shape != string ("circle"))
        throw FormatError;
    getline(ss,center,';');
    Vector O = getVectorFromString(center);
    ss >> r >> c;
    if(c!='}') throw FormatError;
    if(!ss.good())
        throw FormatError;
    return Circle(O, r);
}

#endif // CIRCLE_H_INCLUDED
