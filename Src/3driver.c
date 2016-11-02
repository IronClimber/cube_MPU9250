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
float rxy, rzy, rzx;
float s_angle_x, s_angle_y, s_angle_z;

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

	//SetXYZ(60, 0, 60, &box.A);
	SetXYZ(-width/2, depth/2, heigth/2, &box.A);
	SetXYZ(width/2, depth/2, heigth/2, &box.B);
	SetXYZ(width/2, depth/2, -heigth/2, &box.C);
	SetXYZ(-width/2, depth/2, -heigth/2, &box.D);
	SetXYZ(-width/2, -depth/2, heigth/2, &box.E);
	SetXYZ(width/2, -depth/2, heigth/2, &box.F);
	SetXYZ(width/2, -depth/2, -heigth/2, &box.G);
	SetXYZ(-width/2, -depth/2, -heigth/2, &box.H);

	rxy = sqrt(width*width/4 + depth*depth/4);
	rzy = sqrt(heigth*heigth/4 + depth*depth/4);
	rzx = sqrt(width*width/4 + heigth*heigth/4);

	//float ang = atan2f(point->y,point->x);
}

void SetXYZ(int32_t x, int32_t y, int32_t z, XYZ_point* point) {

	point->x = x;
	point->y = y;
	point->z = z;
	point->start_x = x;
	point->start_y = y;
	point->start_z = z;
	//LCD_Printf("(%d,%d,%d)\n",x,y,z);
}

void Draw3dCube(uint16_t color) {
	//DrawTarget(&box.A, color);
	DrawEdge(&box.A, &box.B, color);
	DrawEdge(&box.B, &box.C, color);
	DrawEdge(&box.C, &box.D, color);
	DrawEdge(&box.D, &box.A, color);

	DrawEdge(&box.E, &box.F, RED);
	DrawEdge(&box.F, &box.G, RED);
	DrawEdge(&box.G, &box.H, RED);
	DrawEdge(&box.H, &box.E, RED);

	DrawEdge(&box.A, &box.E, BLUE);
	DrawEdge(&box.B, &box.F, BLUE);
	DrawEdge(&box.C, &box.G, BLUE);
	DrawEdge(&box.D, &box.H, BLUE);

}

void Clean3dCube(uint16_t color) {
	//DrawTarget(&box.A, color);
	DrawEdge(&box.A, &box.B, color);
	DrawEdge(&box.B, &box.C, color);
	DrawEdge(&box.C, &box.D, color);
	DrawEdge(&box.D, &box.A, color);

	DrawEdge(&box.E, &box.F, color);
	DrawEdge(&box.F, &box.G, color);
	DrawEdge(&box.G, &box.H, color);
	DrawEdge(&box.H, &box.E, color);

	DrawEdge(&box.A, &box.E, color);
	DrawEdge(&box.B, &box.F, color);
	DrawEdge(&box.C, &box.G, color);
	DrawEdge(&box.D, &box.H, color);

}

void MoveY(int32_t y_move) {
	box.A.y += y_move;
}


void MoveY_Abs(int32_t y_move) {
	box.A.y = y_move;
}
void DrawTarget(XYZ_point* k1, uint16_t color) {
	int16_t x1,y1,d_x,d_y;
	d_x = k1->y+SCALE_X0;
	d_y = -k1->z+SCALE_Y0;
	LCD_DrawPixel(d_x,d_y,BLUE);
	GetRealXY(k1, &x1, &y1);

	LCD_DrawLine(x1-4,y1,x1+4,y1,color);
	LCD_DrawLine(x1,y1-4,x1,y1+4,color);
}

void DrawEdge(XYZ_point* k1, XYZ_point* k2, uint16_t color) {
	int16_t x1,x2,y1,y2;
	GetRealXY(k1, &x1, &y1);
	GetRealXY(k2, &x2, &y2);
	LCD_DrawLine(x1,y1,x2,y2,color);
}

void GetRealXY(XYZ_point* k, int16_t* x, int16_t* y) {
	*x = (k->x) + SCALE_X0 + (k->y)*(k->x)/PERSPECTIVE_COEFICIENT_SCALE;
	*y = -(k->z) + SCALE_Y0 - (k->y)*(k->z)/PERSPECTIVE_COEFICIENT_SCALE;
}

void SetCubePosition(float x_angle, float y_angle, float z_angle) {
	LCD_SetCursor(0,0);
	SetNewPointValue(&box.A, x_angle, y_angle, z_angle);
	SetNewPointValue(&box.B, x_angle, y_angle, z_angle);
	SetNewPointValue(&box.C, x_angle, y_angle, z_angle);
	SetNewPointValue(&box.D, x_angle, y_angle, z_angle);
	SetNewPointValue(&box.E, x_angle, y_angle, z_angle);
	SetNewPointValue(&box.F, x_angle, y_angle, z_angle);
	SetNewPointValue(&box.G, x_angle, y_angle, z_angle);
	SetNewPointValue(&box.H, x_angle, y_angle, z_angle);
}

void SetNewPointValue(XYZ_point* point, float x_angle, float y_angle, float z_angle) {

	int32_t new_x = point->start_x;
	int32_t new_y = point->start_y;
	int32_t new_z = point->start_z;

	//x axis
	float rx = sqrt(new_z*new_z+new_y*new_y);
	float x_axis_angle = atan2f(new_z, new_y)+x_angle;
	new_y = (int32_t) (cosf(x_axis_angle)*rx);
	new_z = (int32_t) (sinf(x_axis_angle)*rx);
    //LCD_Printf("r = %6.2f x-a = %6.2", rxy, x_axis_angle);

	//y axis
	float ry = sqrt(new_z*new_z+new_x*new_x);
	float y_axis_angle = atan2f(new_x, new_z)+y_angle;
	new_z = (int32_t) (cosf(y_axis_angle)*ry);
	new_x = (int32_t) (sinf(y_axis_angle)*ry);
	//LCD_Printf("r = %6.2f x-a = %6.2f\n", rzx, point->start_angle_y);

	//z axis
	//r = sqrt((point->y)*(point->y)+(point->x)*(point->x));
	float rz = sqrt(new_x*new_x+new_y*new_y);
	float z_axis_angle = atan2f(new_y, new_x)+z_angle;
	new_x = (int32_t) (cosf(z_axis_angle)*rz);
	new_y = (int32_t) (sinf(z_axis_angle)*rz);
	//LCD_Printf("(%d,%d,%d) ang = %d\n",point->x,point->y,point->z, point->start_angle);


/*
	new_y = new_y*cos(x_angle)+new_z*sin(x_angle);
	new_z = new_y*sin(x_angle)+new_z*cos(x_angle);
*/
	/*new_x = new_x*cosf(y_angle)+new_z*sinf(y_angle);
	new_z = new_x*sinf(y_angle)+new_z*cosf(y_angle);

	new_x = new_x*cosf(z_angle)+new_y*sinf(z_angle);
	new_y = new_x*sinf(z_angle)+new_y*cosf(z_angle);*/

	point->x = new_x;
	point->y = new_y;
	point->z = new_z;




}
/*
void SetOneAxisNewPosition(XYZ_point* point, float angle) {

}*/
