#include "Object.h"
#include "Mat3D.h"

void draw(Mat3D_DP&,
                 Object *o[], int n,
                 const double obs[3],
                 double W,
                 double H,
                 double time = 0,
                 const double bg_color[3] = 0);

void WriteBMP(const char*, const Mat3D_DP&);
