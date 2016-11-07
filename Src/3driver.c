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

void Object3d_InitBox(Object3d__HandleTypeDef* obj,	int16_t w, int16_t d, int16_t h) {

	obj->width = w;
	obj->depth = d;
	obj->heigth = h;

	obj->vertex_quantity = 8;
	obj->edge_quantity = 12;

	Object3d_SetVertex(0, 0, 0, &obj->centre);

	Object3d_SetBoxVertexes(obj);
	Object3d_SetBoxEdges(obj);



	Object3d_SetEdgesColor(obj, YELLOW);

	obj->x_rotate_start = 0;
	obj->y_rotate_start = 0;
	obj->z_rotate_start = 0;

	obj->x_rotate = obj->x_rotate_start;
	obj->y_rotate = obj->y_rotate_start;
	obj->z_rotate = obj->z_rotate_start;

	obj->position.x = 0;
	obj->position.y = 0;
	obj->position.z = 0;

	Object3d_CalculateObject(obj);

}

void Object3d_SetBoxVertexes(Object3d__HandleTypeDef* obj) {

	Object3d_SetVertex(obj->centre.x-obj->width/2, obj->centre.y+obj->depth/2, obj->centre.z+obj->heigth/2, &obj->vertex_start[0]);
	Object3d_SetVertex(obj->centre.x+obj->width/2, obj->centre.y+obj->depth/2, obj->centre.z+obj->heigth/2, &obj->vertex_start[1]);
	Object3d_SetVertex(obj->centre.x+obj->width/2, obj->centre.y+obj->depth/2, obj->centre.z-obj->heigth/2, &obj->vertex_start[2]);
	Object3d_SetVertex(obj->centre.x-obj->width/2, obj->centre.y+obj->depth/2, obj->centre.z-obj->heigth/2, &obj->vertex_start[3]);
	Object3d_SetVertex(obj->centre.x-obj->width/2, obj->centre.y-obj->depth/2, obj->centre.z+obj->heigth/2, &obj->vertex_start[4]);
	Object3d_SetVertex(obj->centre.x+obj->width/2, obj->centre.y-obj->depth/2, obj->centre.z+obj->heigth/2, &obj->vertex_start[5]);
	Object3d_SetVertex(obj->centre.x+obj->width/2, obj->centre.y-obj->depth/2, obj->centre.z-obj->heigth/2, &obj->vertex_start[6]);
	Object3d_SetVertex(obj->centre.x-obj->width/2, obj->centre.y-obj->depth/2, obj->centre.z-obj->heigth/2, &obj->vertex_start[7]);

}

void Object3d_SetBoxEdges(Object3d__HandleTypeDef* obj) {

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

}

void Object3d_SetCenter(Object3d__HandleTypeDef* obj, int16_t centre_x, int16_t centre_y, int16_t centre_z) {

	Object3d_SetVertex(centre_x, centre_y, centre_z, &obj->centre);

}

void Object3d_SetVertex(int16_t x, int16_t y, int16_t z, XYZ_point* point) {

	point->x = x;
	point->y = y;
	point->z = z;

}

void Object3d_SetEdge(XY_point* p1, XY_point* p2, Edge* e) {

	e->v1 = p1;
	e->v2 = p2;

}

void Object3d_DrawObject(Object3d__HandleTypeDef* obj) {

	Object3d_CalculateObject(obj);

	uint8_t i = 0;
	for (i = 0; i < obj->edge_quantity; i++) {
		Object3d_DrawEdge(obj, i);
	}

}

void Object3d_CleanObject(Object3d__HandleTypeDef* obj) {

	//First way to clean object
	//
	//LCD_FillScreen(BLACK);

	//Second way to clean object

	uint8_t i = 0;
	for (i = 0; i < obj->edge_quantity; i++) {
		Object3d_CleanEdge(obj, i);
	}

}

void Object3d_SetEdgesColor(Object3d__HandleTypeDef* obj, uint16_t c) {

	uint8_t i = 0;

	for (i = 0; i < obj->edge_quantity; i++) {
		Object3d_SetEdgeColor(obj, i, c);
	}

}

void Object3d_SetEdgeColor(Object3d__HandleTypeDef* obj, uint8_t n, uint16_t c) {

	obj->edge[n].color = c;

}

void Object3d_DrawEdge(Object3d__HandleTypeDef* obj, uint8_t n) {

	int16_t x1 = obj->edge[n].v1->x;
	int16_t x2 = obj->edge[n].v2->x;
	int16_t y1 = obj->edge[n].v1->y;
	int16_t y2 = obj->edge[n].v2->y;
	uint16_t color = obj->edge[n].color;

	LCD_DrawLine(x1, y1, x2, y2, color);

}

void Object3d_CleanEdge(Object3d__HandleTypeDef* obj, uint8_t n) {

	int16_t x1 = obj->edge[n].v1->x;
	int16_t x2 = obj->edge[n].v2->x;
	int16_t y1 = obj->edge[n].v1->y;
	int16_t y2 = obj->edge[n].v2->y;

	LCD_DrawLine(x1, y1, x2, y2, BLACK);

}

XY_point Object3d_GetRealXY(XYZ_point* k) {

	XY_point k_real;

	k_real.x = (k->x) + SCALE_X0 + (k->y)*(k->x)/PERSPECTIVE_COEFICIENT_SCALE;
	k_real.y = -(k->z) + SCALE_Y0 - (k->y)*(k->z)/PERSPECTIVE_COEFICIENT_SCALE;

	return k_real;
}

void Object3d_SetRotation(Object3d__HandleTypeDef* obj, float x_angle, float y_angle, float z_angle) {

	obj->x_rotate = x_angle;
	obj->y_rotate = y_angle;
	obj->z_rotate = z_angle;

}

void Object3d_SetPosition(Object3d__HandleTypeDef* obj, int16_t x_pos, int16_t y_pos, int16_t z_pos) {

	obj->position.x = x_pos;
	obj->position.y = y_pos;
	obj->position.z = z_pos;

}

void Object3d_SetStartRotation(Object3d__HandleTypeDef* obj, float x_angle, float y_angle, float z_angle) {

	obj->x_rotate_start = x_angle;
	obj->y_rotate_start = y_angle;
	obj->z_rotate_start = z_angle;

}

void Object3d_CalculateObject(Object3d__HandleTypeDef* obj) {

	uint8_t i = 0;
	XYZ_point new_vertex;

	for (i = 0; i < obj->vertex_quantity; i++) {
		new_vertex = Object3d_CalculateVertex(obj, i);
		obj->vertex[i] = Object3d_GetRealXY(&new_vertex);
	}

}

XYZ_point Object3d_CalculateVertex(Object3d__HandleTypeDef* obj, uint8_t n) {

	XYZ_point nv;

	int16_t new_x = obj->vertex_start[n].x;
	int16_t new_y = obj->vertex_start[n].y;
	int16_t new_z = obj->vertex_start[n].z;

	//x axis
	float rx = sqrt(new_z*new_z+new_y*new_y);
	float x_axis_angle = atan2f(new_z, new_y)+obj->x_rotate+obj->x_rotate_start;
	new_y = (int16_t) (cosf(x_axis_angle)*rx);
	new_z = (int16_t) (sinf(x_axis_angle)*rx);

	//y axis
	float ry = sqrt(new_z*new_z+new_x*new_x);
	float y_axis_angle = atan2f(new_x, new_z)+obj->y_rotate+obj->y_rotate_start;
	new_z = (int16_t) (cosf(y_axis_angle)*ry);
	new_x = (int16_t) (sinf(y_axis_angle)*ry);

	//z axis
	float rz = sqrt(new_x*new_x+new_y*new_y);
	float z_axis_angle = atan2f(new_y, new_x)-obj->z_rotate+obj->z_rotate_start;
	new_x = (int16_t) (cosf(z_axis_angle)*rz);
	new_y = (int16_t) (sinf(z_axis_angle)*rz);

	nv.x = new_x + obj->position.x;
	nv.y = new_y + obj->position.y;
	nv.z = new_z + obj->position.z;

	return nv;

}
