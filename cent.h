#ifndef CENT_H_INCLUDED
#define CENT_H_INCLUDED

#include <math.h>

const double pi = 3.14159265;

Vector centroid(int n, Vector vs[]) {
  Vector a(vs[0]);

  for(int i=1;i<n;++i)
        a=a+vs[i];

  return a/n;
}

bool zout(Vector &v1, Vector & v2) {
    return v1.component(1)*v2.component(2) >= v1.component(2)*v2.component(1);
}
class smallAngleInFront {
public:
    smallAngleInFront(Vector const & cent, Vector const & refV)
        :o(cent),v(refV) {}
    bool operator () (Vector const & a, Vector const & b) {
        Vector r = v-o;
        Vector va = a-o;
        Vector vb = b-o;
        double theta_a = acos(r*va/(r.length()*va.length()));
        double theta_b = acos(r*vb/(r.length()*vb.length()));
        if (!zout(r,va)) theta_a = 2*pi - theta_a;
        if (!zout(r,vb)) theta_b = 2*pi - theta_b;

        return theta_a <= theta_b;
    }
private:
    Vector o, v;
};

#endif // CENT_H_INCLUDED
