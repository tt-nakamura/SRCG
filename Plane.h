#ifndef __Plane_h__
#define __Plane_h__

#include "Object.h"

struct Plane : Object {// infinite plane in space
    double vertex[3];// a point on the plane
    double edge[2][3];// two independent vectors lying on the plane
    double inv[3][3];// inverse matrix in cramer formula
    double checkers;// number of checker cells in one edge
    double color[3];// color of the plane (R,G,B)
    double hit_point[2];// ray hitting point in edge coordinates
    double X[3];// = observer * Lorentz - vertex

    Plane(const double vertices[3][3],
          double velocity = 0,
          const double direction[3] = 0,
          double checkers = 1,
          const double color[3] = 0,
          bool relativity=true);

    void set_observer(const double o[3]);

    void set_inv();

    void translate(const double d[3]);

    void rotate(const double axis[3],
                double angle,
                const double center[3]);

    int trace_ray(double& t,
                  double color[3],
                  const double P[3],
                  double time=0);

};

#endif// __Plane_h__
