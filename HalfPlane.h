#ifndef __HalfPlane_h__
#define __HalfPlane_h__

#include "Plane.h"

struct HalfPlane : Plane {
    HalfPlane(const double vertices[3][3],
              double velocity = 0,
              const double direction[3] = 0,
              double checkers = 1,
              const double color[3] = 0,
              bool relativity=true);

    int trace_ray(double& t,
                  double color[3],
                  const double P[3],
                  double time=0);

};

#endif// __HalfPlane_h__
