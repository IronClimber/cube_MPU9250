/*
 * 3driver.c
 *
 *  Created on: 29 זמגע. 2016 נ.
 *      Author: Home
 */
#include "stm32f4xx_hal.h"
#include "display\lcd.h"
#include "3driver.h"
#include "math.h"

Cube3d box;
XYZ_point At, Bt, Ct, Dt, Et, Ft, Gt, Ht;

/*
       width
         |
     E___v__ F
	 /|    /|
   A/_|__B/ | <-heigth
	|H|___|_| G
	| /   | /
	|/____|/ <-depth
	D	  C

*/

void Cube3d_Init(int16_t width, int16_t depth, int16_t heigth) {

	SetXYZ(0, 0, 0, &box.O);
	SetXYZ(-width/2, depth/2, heigth/2, &box.A);
	SetXYZ(width/2, depth/2, heigth/2, &box.B);
	SetXYZ(width/2, depth/2, -heigth/2, &box.C);
	SetXYZ(-width/2, depth/2, -heigth/2, &box.D);
	SetXYZ(-width/2, -depth/2, heigth/2, &box.E);
	SetXYZ(width/2, -depth/2, heigth/2, &box.F);
	SetXYZ(width/2, -depth/2, -heigth/2, &box.G);
	SetXYZ(-width/2, -depth/2, -heigth/2, &box.H);
    At = box.A;
    Bt = box.B;
    Ct = box.C;
    Dt = box.D;
    Et = box.E;
    Ft = box.F;
    Gt = box.G;
    Ht = box.H;

}

void SetXYZ(int32_t x, int32_t y, int32_t z, XYZ_point* point) {
	point->x = x;
	point->y = y;
	point->z = z;
	LCD_Printf("(%d,%d,%d)\n",x,y,z);
}

void Draw3dCube(uint16_t color) {

	DrawEdge(&At, &Bt, color);
	DrawEdge(&Bt, &Ct, color);
	DrawEdge(&Ct, &Dt, color);
	DrawEdge(&Dt, &At, color);

	DrawEdge(&Et, &Ft, color);
	DrawEdge(&Ft, &Gt, color);
	DrawEdge(&Gt, &Ht, color);
	DrawEdge(&Ht, &Et, color);

	DrawEdge(&At, &Et, color);
	DrawEdge(&Bt, &Ft, color);
	DrawEdge(&Ct, &Gt, color);
	DrawEdge(&Dt, &Ht, color);

}

void DrawEdge(XYZ_point* k1, XYZ_point* k2, uint16_t color) {
	int16_t x1,x2,y1,y2;
	GetRealXY(k1, &x1, &y1);
	GetRealXY(k2, &x2, &y2);
	LCD_DrawLine(x1,y1,x2,y2,color);
}

void GetRealXY(XYZ_point* k, int16_t* x, int16_t* y) {
	*x = (k->x) + SCALE_X0 - (k->y)*(k->x)/PERSPECTIVE_COEFICIENT_SCALE;
	*y = -(k->z) + SCALE_Y0 + (k->y)*(k->z)/PERSPECTIVE_COEFICIENT_SCALE;
}

void SetCubePosition(float x_angle, float y_angle, float z_angle) {
	LCD_SetCursor(0,0);
	SetNewPointValue(&box.A, &At, x_angle, y_angle, z_angle);
	SetNewPointValue(&box.B, &Bt, x_angle, y_angle, z_angle);
	SetNewPointValue(&box.C, &Ct, x_angle, y_angle, z_angle);
	SetNewPointValue(&box.D, &Dt, x_angle, y_angle, z_angle);
	SetNewPointValue(&box.E, &Et, x_angle, y_angle, z_angle);
	SetNewPointValue(&box.F, &Ft, x_angle, y_angle, z_angle);
	SetNewPointValue(&box.G, &Gt, x_angle, y_angle, z_angle);
	SetNewPointValue(&box.H, &Ht, x_angle, y_angle, z_angle);
}

void SetNewPointValue(XYZ_point* real_point, XYZ_point* point, float x_angle, float y_angle, float z_angle) {
	//SetOneAxisNewPosition(point, x_angle);

	//x axis
	float r = sqrt((real_point->z)*(real_point->z)+(real_point->y)*(real_point->y));
	float x_axis_angle = atan2f(real_point->z,real_point->y)+x_angle;
	point->y = (int32_t) (cos(x_axis_angle)*r);
	point->z = (int32_t) (sin(x_axis_angle)*r);
    LCD_Printf("r = %6.2f x-a = %6.2", r, x_axis_angle);

	//y axis
	r = sqrt((real_point->z)*(real_point->z)+(real_point->x)*(real_point->x));
	float y_axis_angle = atan2f(real_point->z,real_point->x)+y_angle;
	point->x = (int32_t) (cos(y_axis_angle)*r);
	point->z = (int32_t) (sin(y_axis_angle)*r);

	//z axis
	r = sqrt((real_point->y)*(real_point->y)+(real_point->x)*(real_point->x));
	float z_axis_angle = atan2f(real_point->y,real_point->x)+z_angle;
	point->x = (int32_t) (cos(z_axis_angle)*r);
	point->y = (int32_t) (sin(z_axis_angle)*r);
	LCD_Printf("(%d,%d,%d)\n",point->x,point->y,point->z);
}
/*
void SetOneAxisNewPosition(XYZ_point* point, float angle) {

}*/
