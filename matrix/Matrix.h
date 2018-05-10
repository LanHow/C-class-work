#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED
#include "..\Vector.h"
#include "..\ProductDot.h"
class Matrix{
public:
    Matrix(int row,int column,double a[]):
        r(row),c(column){
            m=new double [r*c];
            for(int i=0;i<r*c;i++)
                m[i]=a[i];
    }
    double component(int row,int column){
        return m[(row-1)*c+column-1];
    }
    Vector rowVector(int i)const{
        return Vector(c,m+(i-1)*c);
    }
    int row()const{
        return r;
    }

private:
    int r;
    int c;
    double *m;
};
Vector apply(Matrix const &m,Vector const &v){
    int r=m.row();
    double a[r];
    for(int i=0;i<r;i++) {
        /*
        Vector v1(m.rowVector(i+1));
        Vector v2(v);
        a[i]= product_dot(v1,v2);
        */
        a[i] = m.rowVector(i+1)*v;
    }
    return Vector(r,a);
}
#endif // MATRIX_H_INCLUDED
