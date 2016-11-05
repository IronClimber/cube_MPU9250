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

//Cube3d box;

/*
       width
         |								Z
     4___v__ 5							|
	 /|    /|						   0|____X
   0/_|__1/ | <-heigth				   /
	|7|___|_|6						 Y/
	| /   | /
	|/____|/ <-depth
	3	  2

*/

void Object3d_InitBox(Object3d__HandleTypeDef* obj,
		int16_t centre_x, int16_t centre_y, int16_t centre_z,
		int16_t width, int16_t depth, int16_t heigth) {

	obj->vertex_quantity = 8;
	obj->edge_quantity = 12;

	Object3d_SetVertex(centre_x, centre_y, centre_z, &obj->centre);

	Object3d_SetVertex(centre_x-width/2, centre_y+depth/2, centre_z+heigth/2, &obj->vertex[0]);
	Object3d_SetVertex(centre_x+width/2, centre_y+depth/2, centre_z+heigth/2, &obj->vertex[1]);
	Object3d_SetVertex(centre_x+width/2, centre_y+depth/2, centre_z-heigth/2, &obj->vertex[2]);
	Object3d_SetVertex(centre_x-width/2, centre_y+depth/2, centre_z-heigth/2, &obj->vertex[3]);
	Object3d_SetVertex(centre_x-width/2, centre_y-depth/2, centre_z+heigth/2, &obj->vertex[4]);
	Object3d_SetVertex(centre_x+width/2, centre_y-depth/2, centre_z+heigth/2, &obj->vertex[5]);
	Object3d_SetVertex(centre_x+width/2, centre_y-depth/2, centre_z-heigth/2, &obj->vertex[6]);
	Object3d_SetVertex(centre_x-width/2, centre_y-depth/2, centre_z-heigth/2, &obj->vertex[7]);

	uint8_t i = 0;
	for (i=0; i<obj->vertex_quantity; i++) {
		obj->vertex_start[i] = obj->vertex[i];
	}

	Object3d_SetEdge(&obj->vertex[0], &obj->vertex[1], &obj->edge[0]);
	Object3d_SetEdge(&obj->vertex[1], &obj->vertex[2], &obj->edge[1]);
	Object3d_SetEdge(&obj->vertex[2], &obj->vertex[3], &obj->edge[2]);
	Object3d_SetEdge(&obj->vertex[3], &obj->vertex[0], &obj->edge[3]);

	Object3d_SetEdge(&obj->vertex[4], &obj->vertex[5], &obj->edge[4]);
	Object3d_SetEdge(&obj->vertex[5], &obj->vertex[6], &obj->edge[5]);
	Object3d_SetEdge(&obj->vertex[6], &obj->vertex[7], &obj->edge[6]);
	Object3d_SetEdge(&obj->vertex[7], &obj->vertex[4], &obj->edge[7]);

	Object3d_SetEdge(&obj->vertex[0], &obj->vertex[4], &obj->edge[8]);
	Object3d_SetEdge(&obj->vertex[1], &obj->vertex[5], &obj->edge[9]);
	Object3d_SetEdge(&obj->vertex[2], &obj->vertex[6], &obj->edge[10]);
	Object3d_SetEdge(&obj->vertex[3], &obj->vertex[7], &obj->edge[11]);

	obj->x_rotate_start = 0;
	obj->y_rotate_start = 0;
	obj->z_rotate_start = 0;

	obj->x_rotate = obj->x_rotate_start;
	obj->y_rotate = obj->y_rotate_start;
	obj->z_rotate = obj->z_rotate_start;

	/*
	obj->x_max = 0;
	obj->x_max = 0;
	obj->x_max = 0;
	obj->x_max = 0;
	*/
}

void Object3d_SetVertex(int32_t x, int32_t y, int32_t z, XYZ_point* point) {

	point->x = x;
	point->y = y;
	point->z = z;

}

void Object3d_SetEdge(XYZ_point* p1, XYZ_point* p2, Edge* e) {

	e->v1 = p1;
	e->v2 = p2;

}

void Object3d_DrawObject(Object3d__HandleTypeDef* obj) {

	/*obj->x_max = 0;
	obj->y_max = 0;
	obj->x_min = X_BORDER;
	obj->y_min = Y_BORDER;*/

	uint8_t i = 0;
	for (i = 0; i < obj->edge_quantity; i++) {
		Object3d_DrawEdge(obj, i);
	}

}

void Object3d_DrawEdge(Object3d__HandleTypeDef* obj, uint8_t n) {

	//XYZ_point vertex1, vertex2;
	int16_t x1, x2, y1, y2;

	Object3d_GetRealXY(obj->edge[n].v1, &x1, &y1);
	Object3d_GetRealXY(obj->edge[n].v2, &x2, &y2);

	LCD_DrawLine(x1, y1, x2, y2, RED/*e->color*/);

	/*if (x1>obj->x_max) obj->x_max = x1;
	else if (x1<obj->x_min) obj->x_min = x1;
	if (y1>obj->y_max) obj->y_max = y1;
	else if (y1<obj->y_min) obj->y_min = y1;*/


}

void Object3d_CleanObject(Object3d__HandleTypeDef* obj) {
	//LCD_FillRect(obj->x_min, obj->y_min, obj->x_max, obj->y_max, BLACK);
	LCD_FillScreen(BLACK);
}


void Object3d_GetRealXY(XYZ_point* k, int16_t* x, int16_t* y) {
	*x = (k->x) + SCALE_X0 + (k->y)*(k->x)/PERSPECTIVE_COEFICIENT_SCALE;
	*y = -(k->z) + SCALE_Y0 - (k->y)*(k->z)/PERSPECTIVE_COEFICIENT_SCALE;
}

void Object3d_SetRotation(Object3d__HandleTypeDef* obj, float x_angle, float y_angle, float z_angle) {

	obj->x_rotate = x_angle;
	obj->y_rotate = y_angle;
	obj->z_rotate = z_angle;

	Object3d_CalculateObject(obj);

}

void Object3d_CalculateObject(Object3d__HandleTypeDef* obj) {

	uint8_t i = 0;

	for (i = 0; i < obj->vertex_quantity; i++) {
		Object3d_CalculateVertex(obj, i);
	}

}

void Object3d_CalculateVertex(Object3d__HandleTypeDef* obj, uint8_t n) {

	int32_t new_x = obj->vertex_start[n].x;
	int32_t new_y = obj->vertex_start[n].y;
	int32_t new_z = obj->vertex_start[n].z;

	//x axis
	float rx = sqrt(new_z*new_z+new_y*new_y);
	float x_axis_angle = atan2f(new_z, new_y)+obj->x_rotate;
	new_y = (int32_t) (cosf(x_axis_angle)*rx);
	new_z = (int32_t) (sinf(x_axis_angle)*rx);
    //LCD_Printf("r = %6.2f x-a = %6.2", rxy, x_axis_angle);

	//y axis
	float ry = sqrt(new_z*new_z+new_x*new_x);
	float y_axis_angle = atan2f(new_x, new_z)+obj->y_rotate;
	new_z = (int32_t) (cosf(y_axis_angle)*ry);
	new_x = (int32_t) (sinf(y_axis_angle)*ry);
	//LCD_Printf("r = %6.2f x-a = %6.2f\n", rzx, point->start_angle_y);

	//z axis
	//r = sqrt((point->y)*(point->y)+(point->x)*(point->x));
	float rz = sqrt(new_x*new_x+new_y*new_y);
	float z_axis_angle = atan2f(new_y, new_x)-obj->z_rotate;
	new_x = (int32_t) (cosf(z_axis_angle)*rz);
	new_y = (int32_t) (sinf(z_axis_angle)*rz);
	//LCD_Printf("(%d,%d,%d) ang = %d\n",point->x,point->y,point->z, point->start_angle);


    /*
	new_y = new_y*cos(x_angle)+new_z*sin(x_angle);
	new_z = new_y*sin(x_angle)+new_z*cos(x_angle);

	new_x = new_x*cosf(y_angle)+new_z*sinf(y_angle);
	new_z = new_x*sinf(y_angle)+new_z*cosf(y_angle);

	new_x = new_x*cosf(z_angle)+new_y*sinf(z_angle);
	new_y = new_x*sinf(z_angle)+new_y*cosf(z_angle);
	*/

	/*
	point->x = new_x;
	point->y = new_y;
	point->z = new_z;
	*/

	obj->vertex[n].x = new_x;
	obj->vertex[n].y = new_y;
	obj->vertex[n].z = new_z;


}
