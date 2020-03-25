#include<cmath>
#include "HalfPlane.h"

HalfPlane::HalfPlane(
    const double p[3][3],
    double v,
    const double d[3],
    double check,
    const double c[3],
    bool rel
) : Plane(p,v,d,check,c,rel)
// p[0],p[2] = two points on half plane's edge
// p[1] = another point on half plane (not on edge)
// v = object's speed (<=1)
// d = direction of motion
// check = number of checker cells in one edge
//   where edge[i] = p[i+1] - p[0] (i=0,1)
// c = color of the plane (default is white)
// rel = use Lorentz contraction or not
{;}

int HalfPlane::trace_ray(
    double& t,
    double c[3],
    const double P[3],
    double T)
// input:
//   P = point on yz screen (ray starting)
//   T = time at which the plane is drawn
// output:
//   t = time at which ray hits the plane
//   c = color of hitting point
// return:
//   1 if hit else 0
{
    if(Plane::trace_ray(t,c,P,T) == 0) return 0;
    if(hit_point[0] < 0) return 0;// other half of plane
    return 1;
}
