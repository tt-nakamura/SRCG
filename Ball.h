#ifndef __Ball_h__
#define __Ball_h__

#include "Object.h"

struct Ball : Object {
    double center[3];// sphere's center
    double radius, r2;// radius and its square
    double axes[3][3];// directions of painting checkers
    int checkers;// number of checker cells in one round
    double color[3];

    Ball(const double *center,
         double radius,
         double velocity = 0,
         const double direction[3] = 0,
         int checkers = 12,
         const double color[3] = 0,
         const double axis[3] = 0,
         bool relativity=true);

    int trace_ray(double& t,
                  double color[3],
                  const double P[3],
                  double time=0);
};

#endif// __Ball_h__
