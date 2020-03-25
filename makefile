OBJ = draw.o Vec3D.o bitmap.o Object.o Plane.o HalfPlane.o Box.o Panel.o Ball.o
fig: fig.o $(OBJ)
	g++ fig.o $(OBJ)