#include "Box.h"

Box::Box(const double p[4][3],
         double v,
         const double d[3],
         int check,
         const double c[6][3],
         bool rel)
// p[0] = a vertex of parallelepiped
// p[1:4] = 3 adjascent vertices of p[0]
// v = object's speed (<=1)
// d = direction of motion
// check = number of checker cells in one edge
// c[0:6] = colors of 6 faces (default: R,G,B,Y,M,C)
//   face order is [012,023,031, opposite of 012,023,031]
// rel = use Lorentz contraction or not
{
    int i,j;
    double q[3][3];
    double color[6][3] = {
        {1,0,0}, {0,1,0}, {0,0,1}, {1,1,0}, {1,0,1}, {0,1,1}
    };
    if(c) for(i=0; i<6; i++)
        for(j=0; j<3; j++) color[i][j] = c[i][j];
    faces[0] = new Panel(p,v,d,check,color[0],rel);
    for(i=0; i<3; i++) q[0][i] = p[0][i];
    for(i=0; i<3; i++) q[1][i] = p[2][i];
    for(i=0; i<3; i++) q[2][i] = p[3][i];
    faces[1] = new Panel(q,v,d,check,color[1],rel);
    for(i=0; i<3; i++) q[1][i] = p[1][i];
    faces[2] = new Panel(q,v,d,check,color[2],rel);
    for(i=0; i<3; i++) q[2][i] = p[2][i] + p[3][i] - p[0][i];
    for(i=0; i<3; i++) q[1][i] = p[3][i] + p[1][i] - p[0][i];
    for(i=0; i<3; i++) q[0][i] = q[2][i] + q[1][i] - p[3][i];
    faces[3] = new Panel(q,v,d,check,color[3],rel);
    for(i=0; i<3; i++) q[2][i] = p[1][i] + p[2][i] - p[0][i];
    faces[4] = new Panel(q,v,d,check,color[4],rel);
    for(i=0; i<3; i++) q[1][i] = p[2][i] + p[3][i] - p[0][i];
    faces[5] = new Panel(q,v,d,check,color[5],rel);
}

Box::~Box() {
    for(int i=0; i<6; i++) delete faces[i];
}

void Box::set_observer(const double o[3]) {
    for(int i=0; i<6; i++) faces[i]->set_observer(o);
}

void Box::translate(const double *d) {
    for(int i=0; i<6; i++) faces[i]->translate(d);
}

void Box::rotate(const double axis[3],
                 double angle,
                 const double center[3])
// center of rotation is box's center by default
{
    int i;
    double o[3];
    if(center) for(i=0; i<3; i++) o[i] = center[i];
    else for(i=0; i<3; i++)
        o[i] = (faces[0]->vertex[i] + faces[3]->vertex[i])/2;
    for(i=0; i<6; i++) faces[i]->rotate(axis, angle, o);
}

int Box::trace_ray(double& t,
                   double color[3],
                   const double P[3],
                   double time)
// input:
//   P = point on yz screen (ray starting)
//   time = time at which the plane is drawn
// output:
//   t = time at which ray hits the plane
//   color = color of hitting point
// return:
//   1 if hit else 0
{
    int i,j,k(0);
    static const double INFTY(1e300);
    double s,c[3];
    t = -INFTY;
    for(i=0; i<6; i++) {
        if(faces[i]->trace_ray(s,c,P,time) == 0 || s<t)
            continue;
        t = s;// find nearest face
        for(j=0; j<3; j++) color[j] = c[j];
        k++;
        if(k==2) return 1;// hit 2 faces at most
    }
    return (t != -INFTY);
}
