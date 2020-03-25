#include "Mat3D.h"
#include "Vec3D.h"
#include "Object.h"
#include<cmath>

void draw(Mat3D_DP& image,
                 Object *o[], int n,
                 const double obs[3],
                 double H, double W, double T,
                 const double bg_color[3])
// input:
//   image.dim1 = height of image in pixels
//   image.dim2 = width of image in pixels 
//   image.dim3 = 3 (must)
//   o = array of pointers to objects
//   n = number of objects to draw
//   obs = observer's position
//   H,W = height and width of secreen
//   T = time at which objects are drawn
//   bg_color = back gournd color (R,G,B)
// output:
//   image[i][j][k] = intensity of color k at pixel(i,j)
//     i increases from top to bottom
//     j increases from left to right
//     k = 0,1,2 for R,G,B
{
    static const double INFTY(1e300);
    int i,j,k,l,I(image.dim1()),J(image.dim2());
    double dx(H/I),dy(W/J),xmin((dx-H)/2),ymin((dy-W)/2);
    double t,t_max,P[3],Q[3],c[3],R[3][3];
    double b[3] = {1,1,1};// default bg color (white)

    for(i=0; i<n; i++) o[i]->set_observer(obs);

    if(bg_color) for(i=0; i<3; i++) b[i] = bg_color[i];

    normalize(P,obs);
    RotMat(R, atan2(P[1],P[0]), acos(P[2]), 0);
    P[2] = 0;// point on xy screen (x,y,0)

    for(i=0; i<I; i++) {
        P[0] = xmin + i*dx;
        for(j=0; j<J; j++) {
            P[1] = ymin + j*dy;
            mul(Q,P,R);// point on screen normal to line of sight
            t_max = -INFTY;
            for(l=0; l<n; l++) {
                if(o[l]->trace_ray(t,c,Q,T) == 0 ||
                   t < t_max) continue;
                t_max = t;
                for(k=0; k<3; k++) image[i][j][k] = c[k];
            }
            if(t_max == -INFTY)
                for(k=0; k<3; k++) image[i][j][k] = b[k];
        }
    }
}
