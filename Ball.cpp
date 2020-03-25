#include<cmath>
#include "Ball.h"
#include "Vec3D.h"

#define CHECKER_BRIGHTNESS 0.8

Ball::Ball(const double o[3],
           double r,
           double v,
           const double d[3],
           int check,
           const double c[3],
           const double z[3],
           bool rel
) : radius(r),
    r2(r*r),
    checkers(check)
// o,r = sphere's center and radius
// v = object's speed (<=1)
// d = direction of motion
// check = number of checker cells in one round
// c = color (default is white)
// z = north direction of checkers (default: (0,0,1))
// rel = use Lorentz contraction or not
{
    static double EPS(1e-6);
    int i;

    for(i=0; i<3; i++) center[i] = o[i];

    if(z) for(i=0; i<3; i++) axes[2][i] = z[i];
    else {
        axes[2][0] = 0;
        axes[2][1] = 0;
        axes[2][2] = 1;
    }
    if(fabs(axes[2][1]) < EPS && fabs(axes[2][2]) < EPS) {
        axes[0][0] = 0;
        axes[0][1] = 1;
        axes[0][2] = 0;
    }
    else {
        axes[0][0] = 0;
        axes[0][1] = axes[2][2];
        axes[0][2] =-axes[2][1];
    }
    normalize(axes[2], axes[2]);
    normalize(axes[0], axes[0]);
    cross(axes[1], axes[2], axes[0]);

    set_velocity(v,d,rel);
    if(c) for(i=0; i<3; i++) color[i] = c[i];
    else  for(i=0; i<3; i++) color[i] = 1;
}

int Ball::trace_ray(double& t,
                    double col[3],
                    const double P[3],
                    double time)
// input:
//   P = point on yz screen (ray starting)
//   time = time at which the sphere is drawn
// output:
//   t = time at which ray hits the sphere
//   col = color of hitting point
// return:
//   1 if hit else 0
{
    int i;
    static const double PI(atan(1)*4);
    double c,a2,D,x,y,z;
    double e[3],a[3],b[3],p[3],r[3];

    for(i=0; i<3; i++) e[i] = P[i] - observer[i];
    normalize(e,e);// unit vector along line of sight
    mul(a, e, Lorentz);
    for(i=0; i<3; i++) a[i] += velocity[i];
    time += distance;// time at which ray reach the observer
    for(i=0; i<3; i++) p[i] = e[i]*time + observer[i];
    mul(b, p, Lorentz);
    for(i=0; i<3; i++) b[i] -= center[i];
    c = dot(a,b);
    a2 = dot(a,a);
    D = c*c - a2*(dot(b,b) - r2);
    if(D<0) return 0;// ray doesn't hit the sphere
    t = (c + sqrt(D))/a2;
    if(t >= time) return 0;// hitting point is at observer's back
    for(i=0; i<3; i++) r[i] = (b[i] - t*a[i])/radius;
    z = dot(axes[2], r);// z coordinate of hitting point
    for(i=0; i<3; i++) r[i] -= z * axes[2][i];
    x = dot(axes[0], r);// x coordinate of hitting point
    y = dot(axes[1], r);// y coordinate of hitting point
    i  = int(acos(z)/PI*checkers)&1;
    i ^= int((atan2(y,x)/PI + 1)*checkers)&1;
    c = (i ? CHECKER_BRIGHTNESS : 1);
    for(i=0; i<3; i++) col[i] = color[i]*c;
    return 1;
}
