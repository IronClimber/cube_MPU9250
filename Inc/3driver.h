/*
 * 3driver.h
 *
 *  Created on: 29 זמגע. 2016 נ.
 *      Author: Home
 */

#ifndef DRIVER3D_H_
#define DRIVER3D_H_

#define CUBE_WIDTH  100
#define CUBE_DEPTH  60
#define CUBE_HEIGTH 120

#define CUBE_COLOR GREEN

#define X_BORDER 240
#define Y_BORDER 320

#define SCALE_X0 X_BORDER/2
#define SCALE_Y0 Y_BORDER/2

#define PERSPECTIVE_COEFICIENT_SCALE 200

typedef struct {
	int32_t x;
	int32_t y;
	int32_t z;
	int32_t start_x;
	int32_t start_y;
	int32_t start_z;
} XYZ_point;

typedef struct {
	XYZ_point A;
	XYZ_point B;
	XYZ_point C;
	XYZ_point D;
	XYZ_point E;
	XYZ_point F;
	XYZ_point G;
	XYZ_point H;
	XYZ_point O;
	float r;
} Cube3d;

void Cube3d_Init(int16_t width, int16_t depth, int16_t heigth);
void SetXYZ(int32_t x, int32_t y, int32_t z, XYZ_point* point);
void Draw3dCube(uint16_t color);
void DrawEdge(XYZ_point* k1, XYZ_point* k2, uint16_t color);
void GetRealXY(XYZ_point* k, int16_t* x, int16_t* y);

void SetCubePosition(float x_angle, float y_angle, float z_angle);
void SetNewPointValue(XYZ_point* point, float x_angle, float y_angle, float z_angle);

#endif /* DRIVER3D_H_ */
