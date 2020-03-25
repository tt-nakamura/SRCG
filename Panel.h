#ifndef __Panel_h__
#define __Panel_h__

#include "Plane.h"

struct Panel : Plane {// parallelogram
    Panel(const double vertices[3][3],
          double velocity = 0,
          const double direction[3] = 0,
          int checkers = 1,
          const double color[3] = 0,
          bool relativity=true);
        
    int trace_ray(double& t,
                  double color[3],
                  const double P[3],
                  double time=0);

};

#endif// __Panel_h__
