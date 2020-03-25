#include<iostream>

double dot(const double a[3], const double b[3]);
double abs(const double a[3]);
void normalize(double b[3], const double a[3]);
double angle(const double a[3], const double b[3]);
void cross(double c[3], const double a[3], const double b[3]);
std::ostream& operator<<(std::ostream& s, const double a[3]);

void mul(double C[3][3], const double A[3][3], const double B[3][3]);
void mul(double v[3], const double A[3][3], const double u[3]);
void mul(double v[3], const double u[3], const double A[3][3]);

void RotMat(double R[3][3], const double axis[3], double angle);
void RotMat(double R[3][3], double phi, double theta, double psi);
