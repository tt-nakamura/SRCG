#ifndef __Box_h__
#define __Box_h__

#include "Panel.h"

struct Box : Object {// parallelepiped
    Panel *faces[6];// made of 6 parallelograms

    Box(const double vertices[4][3],
        double velocity = 0,
        const double direction[3] = 0,
        int checkers = 1,
        const double color[6][3] = 0,
        bool relativity=true);

    ~Box();

    void set_observer(const double o[3]);

    void translate(const double d[3]);

    void rotate(const double axis[3],
                double angle,
                const double center[3]=0);

    int trace_ray(double& t,
                  double color[3],
                  const double P[3],
                  double time=0);

};

#endif// __Box_h__
