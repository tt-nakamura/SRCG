#include<cmath>
#include "Panel.h"

Panel::Panel(
    const double p[3][3],
    double v,
    const double d[3],
    int check,
    const double c[3],
    bool rel
) : Plane(p,v,d,check,c,rel)
// p[0:3] = three vertices of parallelogram
// v = object's speed (<=1)
// d = direction of motion
// check = number of checker cells in one edge
// c = color of the panel (default is white)
// rel = use Lorentz contraction or not
{;}

int Panel::trace_ray(
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
    if(hit_point[0] < 0 ||// out of parallelogram
       hit_point[1] < 0 ||
       hit_point[0] > 1 ||
       hit_point[1] > 1) return 0;
    return 1;
}
