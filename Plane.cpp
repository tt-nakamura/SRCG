#include<cmath>
#include "Plane.h"
#include "Vec3D.h"

#define CHECKER_BRIGHTNESS 0.8

Plane::Plane(
    const double p[3][3],
    double v,
    const double d[3],
    double check,
    const double c[3],
    bool rel
) : checkers(check)
// p[0:3] = three points on plane (not colinear)
// v = object's speed (<=1)
// d = direction of motion
// check = number of checker cells in one edge
//   where edge[i] = p[i+1] - p[0] (i=0,1)
// c = color of the plane (default is white)
// rel = use Lorentz contraction or not
{
    int i;
    for(i=0; i<3; i++) vertex[i] = p[0][i];
    for(i=0; i<3; i++) edge[0][i] = p[1][i] - p[0][i];
    for(i=0; i<3; i++) edge[1][i] = p[2][i] - p[0][i];

    set_inv();
    set_velocity(v,d,rel);
    if(c) for(i=0; i<3; i++) color[i] = c[i];
    else  for(i=0; i<3; i++) color[i] = 1;
}

void Plane::set_observer(const double o[3]) {
    Object::set_observer(o);
    mul(X,o,Lorentz);
    for(int i=0; i<3; i++) X[i] -= vertex[i];
}

void Plane::set_inv() {
    int i;
    double a,b;
    cross(inv[2], edge[0], edge[1]);
    cross(inv[0], inv[2], edge[0]);
    cross(inv[1], inv[2], edge[1]);
    a = dot(inv[0], edge[1]);
    b = dot(inv[1], edge[0]);
    for(i=0; i<3; i++) inv[0][i] /= a;
    for(i=0; i<3; i++) inv[1][i] /= b;
}

void Plane::translate(const double d[3])
// translate the plane by vector d
{
    for(int i=0; i<3; i++) vertex[i] += d[i];
}

void Plane::rotate(const double axis[3],
                   double angle,
                   const double center[3])
// rotate the plane wrt axis
//   passing through center by angle (radian)
{
    int i;
    double p[3],R[3][3];
    for(i=0; i<3; i++) p[i] = vertex[i] - center[i];
    RotMat(R, axis, angle);
    mul(p,p,R);
    for(i=0; i<3; i++) vertex[i] = center[i] + p[i];
    mul(edge[0], edge[0], R);
    mul(edge[1], edge[1], R);
    set_inv();
}

int Plane::trace_ray(
    double& t,
    double col[3],
    const double P[3],
    double time)
// input:
//   P = point on yz screen (ray starting)
//   time = time at which the plane is drawn
// output:
//   t = time at which ray hits the plane
//   col = color of hitting point
// return:
//   1 if hit else 0
{
    static const double EPS(1e-6);
    int i;
    double D;
    double e[3],a[3],b[3],x[3];

    for(i=0; i<3; i++) e[i] = P[i] - observer[i];
    normalize(e,e);// unit vector along line of sight
    mul(b, e, Lorentz);
    for(i=0; i<3; i++) a[i] = velocity[i] + b[i];
    D = dot(a, inv[2]);
    if(fabs(D) < EPS) return 0;// ray is parallel to the plane
    time += distance;// time at which ray reach the observer
    for(i=0; i<3; i++) x[i] = X[i] + b[i]*time;
    t = dot(x, inv[2])/D;
    if(t >= time) return 0;// hitting point is at observer's back
    for(i=0; i<3; i++) x[i] -= a[i]*t;
    hit_point[0] = dot(x, inv[0]);// edge[0] coordinate
    hit_point[1] = dot(x, inv[1]);// edge[1] corridnate
    i  = int(floor(hit_point[0] * checkers))&1;
    i ^= int(floor(hit_point[1] * checkers))&1;
    D = (i ? CHECKER_BRIGHTNESS : 1);
    for(i=0; i<3; i++) col[i] = color[i]*D;
    return 1;
}
