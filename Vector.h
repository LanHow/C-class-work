#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED
#include <string>
#include <vector>
#include <sstream>
#include <math.h>

using namespace std;

class Vector {
public:
    Vector():dim(0),comp(0){}
    Vector (int d, double * com) {
        dim = d;
        comp = new double[d];
        for (int i=0; i< d; ++i)
            comp[i] = com[i];
    }
    Vector (vector<double> const & v) : dim(v.size()){
        comp = new double[dim];
        for (int i=0; i< dim; ++i)
            comp[i] = v[i];
    }
    Vector (const Vector & v) {
        dim = v.dim;
        comp = new double[dim];
        for (int i=0; i< dim; ++i)
            comp[i] = v.comp[i];
    }

    Vector & operator = (const Vector & v) {
        if (comp)
            delete [] comp;
        dim = v.dim;
        comp = new double [dim];
        for (int i=0; i <dim; ++i)
            comp[i] = v.comp[i];
        return *this;
    }
    bool operator == (const Vector & v){
        bool result = true;
        if(dim != v.dimension())
            result = false;
        else
            for(int i=0; i<dim; i++)
                if(comp[i] != v.comp[i]) {
                    result = false;
                    break;
                }
        return result;
    }

    Vector operator - (Vector const & v) const {
        if (dim != v.dim)
            throw string("illegal dimension");
        Vector r(*this);
        for (int i=0; i<dim; ++i)
            r.comp[i] -= v.comp[i];
        return r;
    }
    Vector operator + (Vector const & v) const {
        if (dim != v.dim)
            throw string("illegal dimension");
        Vector r(*this);
        for (int i=0; i<dim; ++i)
            r.comp[i] += v.comp[i];
        return r;
    }
    Vector operator / (double  n) const {
        Vector r(*this);
        for (int i=0; i<dim; ++i)
            r.comp[i] /= n;
        return r;
    }

    double length() const {
        double sumsq = 0.0;
        for (int i=0; i<dim; ++i)
            sumsq += double(comp[i])*double(comp[i]);
        return sqrt(sumsq);
    }

    bool operator > (Vector const & v) {
        return length() > v.length();
    }
    int dimension() const {return dim;}
    double component(int i) const {
        return comp[i-1];
    }
    ~Vector() {
        if (comp) delete [] comp;
    }

    double operator * (Vector const & v) {
        if (v.dim != dim)
            throw string("Unequal dimension");
        double dotProduct =0;
        for (int i = 0; i< dim; ++i) {
            dotProduct += comp[i]*v.comp[i];
        }
        return dotProduct;
    }
    string description() const{
        stringstream ss;
        ss<<"(" << toSVG() <<")";
        return ss.str();
    }
    string toSVG() const {
        stringstream ss;
        for(int i=1;i<dim;i++)
            ss<<component(i)<<",";
        ss<<component(dim);
        return ss.str();
    }
private:
    int dim;
    double * comp;
};



#endif // VECTOR_H_INCLUDED
