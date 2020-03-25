#include<cmath>
#include<iostream>

double dot(const double a[3], const double b[3]) {
    double c(0);
    for(int i=0; i<3; i++) c += a[i]*b[i];
    return c;
}

double abs(const double a[3]) {
    double c(0);
    for(int i=0; i<3; i++) c += a[i]*a[i];
    return sqrt(c);
}

void normalize(double b[3], const double a[3])
// b = a/|a|; &b==&a is allowed
{
    double c(abs(a));
    for(int i=0; i<3; i++) b[i] = a[i]/c;
}

double angle(const double a[3], const double b[3]) {
    return acos(dot(a,b)/(abs(a)*abs(b)));
}

void cross(double c[3], const double a[3], const double b[3])
// c = a x b; &c,&a,&b need not be distinct
{
    double u,v;
    u = a[1]*b[2] - a[2]*b[1];
    v = a[2]*b[0] - a[0]*b[2];
    c[2] = a[0]*b[1] - a[1]*b[0];
    c[0] = u;
    c[1] = v;
}

std::ostream& operator<<(std::ostream& s, const double a[3]) {
    s << '[' << a[0];
    for(int i=1; i<3; i++) s << ' ' << a[i];
    s << ']';
    return s;
}

void mul(double C[3][3], const double A[3][3], const double B[3][3])
// C = AB; &C,&A,&B need not be distinct
{
    int i,j,k;
    if(C==A) {
        double D[3][3];
        for(i=0; i<3; i++)
            for(j=0; j<3; j++) D[i][j] = A[i][j];
        mul(C,D,B);
    }
    else if(C==B) {
        double D[3][3];
        for(i=0; i<3; i++)
            for(j=0; j<3; j++) D[i][j] = B[i][j];
        mul(C,A,D);
    }
    else for(i=0; i<3; i++) {
        for(j=0; j<3; j++) {
            C[i][j] = 0;
            for(k=0; k<3; k++)
                C[i][j] += A[i][k]*B[k][j];
        }
    }
}

void mul(double v[3], const double A[3][3], const double u[3])
// v = Au; &v==&u is allowed
{
    int i,j;
    if(v==u) {
        double a[3];
        for(i=0; i<3; i++) a[i] = u[i];
        mul(v,A,a);
    }
    else for(i=0; i<3; i++) {
        v[i] = 0;
        for(j=0; j<3; j++)
            v[i] += A[i][j]*u[j];
    }
}

void mul(double v[3], const double u[3], const double A[3][3])
// v = uA; &v==&u is allowed
{
    int i,j;
    if(v==u) {
        double a[3];
        for(i=0; i<3; i++) a[i] = u[i];
        mul(v,a,A);
    }
    else for(j=0; j<3; j++) {
        v[j] = 0;
        for(i=0; i<3; i++)
            v[j] += u[i]*A[i][j];
    }
}

void RotMat(double R[3][3], const double axis[3], double angle)
// R = matrix of rotation about axis by angle (radian)
// rotated = rotatee * R (multiply from right)
{
    int i,j;
    double n[3], c(cos(angle)), s(sin(angle));
    normalize(n, axis);
    for(i=0; i<3; i++) {
        R[i][i] = c + n[i]*n[i]*(1-c);
        for(j=0; j<i; j++) R[i][j] = R[j][i] = n[i]*n[j]*(1-c);
    }
    for(i=0; i<3; i++) n[i] *= s;
    R[0][1] += n[2]; R[1][0] -= n[2];
    R[1][2] += n[0]; R[2][1] -= n[0];
    R[2][0] += n[1]; R[0][2] -= n[1];
}

void RotMat(double R[3][3], double phi, double theta, double psi)
// phi, theta, psi = Euler angles (radian)
// first rotate about z axis by phi and let new y axis be y'
// then rotate about y' axis by theta and let new z axis be z'
// finally rotate about z' axis by psi
{
    double cph(cos(phi)), sph(sin(phi));
    double cth(cos(theta)), sth(sin(theta));
    double cps(cos(psi)), sps(sin(psi));
    double cc(cph*cth), sc(sph*cth);
    R[0][0] = cc*cps - sph*sps;
    R[1][0] = -cc*sps - sph*cps;
    R[2][0] = cph*sth;
    R[0][1] = sc*cps + cph*sps;
    R[1][1] = -sc*sps + cph*cps;
    R[2][1] = sph*sth;
    R[0][2] = -sth*cps;
    R[1][2] = sth*sps;
    R[2][2] = cth;
}