#ifndef __Object_h__
#define __Object_h__

struct Object {
    double velocity[3];// rapidity vector gamma*v
    double Lorentz[3][3];// Lorentz transformation matrix
    double observer[3];// observer's position
    double distance;// observer's distance from origin

    void set_velocity(double v,
                      const double d[3],
                      bool relativity=true);

    virtual void set_observer(const double o[3]);

    virtual int trace_ray(double &t,
                          double color[3],
                          const double P[3],
                          double time) {;}
};

#endif// __Object_h__
