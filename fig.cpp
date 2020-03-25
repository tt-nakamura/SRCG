#include "Box.h"
#include "Ball.h"
#include "HalfPlane.h"
#include "draw.h"
#include<cmath>

main() {
    Mat3D_DP img1(200, 300, 3);
    Object *obj[4];
    double obs1[3] = {20,0,5};// observer's position
    double obs2[3] = {0,-20,5};// observer's position
    double obs3[3] = {10*sqrt(2),-10*sqrt(2),5};// observer's position
    double C[3] = {0,1,1};// cyan
    double M[3] = {1,0,1};// magenta
    double Y[3] = {1,1,0};// yellow
    double c0[3] = {0.95, 0.95, 0.95};// back gournd color
    double c1[6][3] = {// box colors
        {0,0,1}, {0,1,0}, {1,0,0}, {1,1,0}, {1,0,1}, {0,1,1}
    };

 	double v1[4][3] = {{3,1,1}, {3,1,-1}, {3,3,1}, {1,1,1}};//vertices
 	double v2[4][3] = {{-1,1,1}, {-1,1,-1}, {-1,3,1}, {-3,1,1}};//vertices
 	double v3[4][3] = {{3,-3,1}, {3,-3,-1}, {3,-1,1}, {1,-3,1}};//vertices
 	double v4[4][3] = {{-1,-3,1}, {-1,-3,-1}, {-1,-1,1}, {-3,-3,1}};//vertices
    double v5[3] = {2,2,0};//sphere's center
    double v6[3] = {-2,-2,0};//sphere's center
 	double d1[3] = {1,0,0};//direction of motion
 	double d2[3] = {-1,0,0};//direction of motion

    obj[0] = new Box(v1, 0, 0, 1, c1);
    obj[1] = new Box(v2, 0, 0, 1, c1);
    obj[2] = new Box(v3, 0, 0, 1, c1);
    obj[3] = new Box(v4, 0, 0, 1, c1);
    draw(img1, obj, 4, obs1, 8, 12, 0, c0); WriteBMP("fig1.bmp", img1);
    delete obj[0];
    delete obj[3];
    obj[0] = new Ball(v5, 1.5, 0, 0, 6, C);
    obj[3] = new Ball(v6, 1.5, 0, 0, 6, M);
    draw(img1, obj, 4, obs1, 8, 12, 0, c0); WriteBMP("fig7.bmp", img1);
    delete obj[0];
    delete obj[1];
    delete obj[2];
    delete obj[3];

    obj[0] = new Box(v1, 0.5, d1, 1, c1, false);
    obj[1] = new Box(v2, 0.5, d1, 1, c1, false);
    obj[2] = new Box(v3, 0.5, d2, 1, c1, false);
    obj[3] = new Box(v4, 0.5, d2, 1, c1, false);
    draw(img1, obj, 4, obs1, 8, 12, 0, c0); WriteBMP("fig2.bmp", img1);
    draw(img1, obj, 4, obs2, 8, 12, 0, c0); WriteBMP("fig3.bmp", img1);
    delete obj[0];
    delete obj[3];
    obj[0] = new Ball(v5, 1.5, 0.5, d1, 6, C, 0, false);
    obj[3] = new Ball(v6, 1.5, 0.5, d2, 6, M, 0, false);
    draw(img1, obj, 4, obs1, 8, 12, 0, c0); WriteBMP("fig8.bmp", img1);
    draw(img1, obj, 4, obs2, 8, 12, 0, c0); WriteBMP("fig9.bmp", img1);
    delete obj[0];
    delete obj[1];
    delete obj[2];
    delete obj[3];

    obj[0] = new Box(v1, 0.9, d1, 1, c1, false);
    obj[1] = new Box(v2, 0.9, d1, 1, c1, false);
    obj[2] = new Box(v3, 0.9, d2, 1, c1, false);
    obj[3] = new Box(v4, 0.9, d2, 1, c1, false);
    draw(img1, obj, 4, obs1, 8, 12, 0, c0); WriteBMP("fig4.bmp", img1);
    draw(img1, obj, 4, obs3, 8, 12, 0, c0); WriteBMP("fig5.bmp", img1);
    draw(img1, obj, 4, obs2, 8, 12, 0, c0); WriteBMP("fig6.bmp", img1);
    delete obj[0];
    delete obj[3];
    obj[0] = new Ball(v5, 1.5, 0.9, d1, 6, C, 0, false);
    obj[3] = new Ball(v6, 1.5, 0.9, d2, 6, M, 0, false);
    draw(img1, obj, 4, obs1, 8, 12, 0, c0); WriteBMP("fig10.bmp", img1);
    draw(img1, obj, 4, obs3, 8, 12, 0, c0); WriteBMP("fig11.bmp", img1);
    draw(img1, obj, 4, obs2, 8, 12, 0, c0); WriteBMP("fig12.bmp", img1);
    delete obj[0];
    delete obj[1];
    delete obj[2];
    delete obj[3];

    obj[1] = new Box(v2, 0.5, d1, 1, c1);
    obj[2] = new Box(v3, 0.5, d2, 1, c1);
    obj[0] = new Ball(v5, 1.5, 0.5, d1, 6, C);
    obj[3] = new Ball(v6, 1.5, 0.5, d2, 6, M);
    draw(img1, obj, 4, obs1, 8, 12, 0, c0); WriteBMP("fig14.bmp", img1);
    draw(img1, obj, 4, obs2, 8, 12, 0, c0); WriteBMP("fig15.bmp", img1);
    delete obj[0];
    delete obj[1];
    delete obj[2];
    delete obj[3];

    obj[1] = new Box(v2, 0.9, d1, 1, c1);
    obj[2] = new Box(v3, 0.9, d2, 1, c1);
    obj[0] = new Ball(v5, 1.5, 0.9, d1, 6, C);
    obj[3] = new Ball(v6, 1.5, 0.9, d2, 6, M);
    draw(img1, obj, 4, obs1, 8, 12, 0, c0); WriteBMP("fig16.bmp", img1);
    draw(img1, obj, 4, obs3, 8, 12, 0, c0); WriteBMP("fig17.bmp", img1);
    draw(img1, obj, 4, obs2, 8, 12, 0, c0); WriteBMP("fig18.bmp", img1);
    delete obj[0];
    delete obj[1];
    delete obj[2];
    delete obj[3];


    Mat3D_DP img2(400, 300, 3);
    double v0[3][3] = {{-30,1,-1}, {-30,-1,-1}, {-28,1,-1}};// floor vertices
    double v7[3][3] = {{-30,3,-1}, {-30,3,1}, {-28,3,-1}};// wall vertices
    double v8[3][3] = {{-30,-3,-1}, {-30,-3,1}, {-28,-3,-1}};// wall vertices
    double obs4[3] = {30,0,1};

    obj[0] = new HalfPlane(v0);
    obj[1] = new Box(v2, 0.9, d1, 1, c1);
    draw(img1, obj, 2, obs1, 8, 12, 0); WriteBMP("fig19.bmp", img1);
    draw(img1, obj, 2, obs1, 8, 12, 1); WriteBMP("fig20.bmp", img1);
    draw(img1, obj, 2, obs1, 8, 12, 2); WriteBMP("fig21.bmp", img1);
    delete obj[0];
    delete obj[1];

    obj[0] = new HalfPlane(v0, 0, 0, 1, C);
    obj[1] = new HalfPlane(v7, 0, 0, 1, Y);
    obj[2] = new HalfPlane(v8, 0, 0, 1, Y);
    draw(img2, obj, 3, obs4, 16, 12); WriteBMP("fig22.bmp", img2);
    delete obj[0];
    delete obj[1];
    delete obj[2];

    obj[0] = new HalfPlane(v0, 0.9, d1, 1, C);
    obj[1] = new HalfPlane(v7, 0.9, d1, 1, Y);
    obj[2] = new HalfPlane(v8, 0.9, d1, 1, Y);
    draw(img2, obj, 3, obs4, 16, 12); WriteBMP("fig23.bmp", img2);
    delete obj[0];
    delete obj[1];
    delete obj[2];

    obj[0] = new HalfPlane(v0, 0.98, d1, 1, C);
    obj[1] = new HalfPlane(v7, 0.98, d1, 1, Y);
    obj[2] = new HalfPlane(v8, 0.98, d1, 1, Y);
    draw(img2, obj, 3, obs4, 16, 12); WriteBMP("fig24.bmp", img2);
    delete obj[0];
    delete obj[1];
    delete obj[2];
}