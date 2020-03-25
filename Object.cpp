#include<cstdlib>
#include<cmath>
#include "Object.h"
#include "Vec3D.h"

void Object::set_velocity(double v,
                          const double d[3],
                          bool rel)
// v = object's speed (<=1)
// d = direction of motion
// rel = use Lorentz contraction or not
{
    if(v >= 1) {
        std::cerr << "set velocity slower than light\n";
        exit(1);
    }
    int i,j;
    double gamma, e[3];

    gamma = (rel ? 1/sqrt(1 - v*v) : 1);// Lorentz facror
    if(d) normalize(e,d);// e = unit vector
    for(i=0; i<3; i++) {// build Lorentz matrix
        Lorentz[i][i] = 1 + (gamma-1)*e[i]*e[i];
        for(j=0; j<i; j++) {
            Lorentz[i][j] = (gamma-1)*e[i]*e[j];
            Lorentz[j][i] = Lorentz[i][j];
        }
    }
    v *= gamma; // rapidity = gamma*v
    for(i=0; i<3; i++) velocity[i] = v*e[i];
}

void Object::set_observer(const double o[3]) {
    for(int i=0; i<3; i++) observer[i] = o[i];
    distance = abs(o);
}
