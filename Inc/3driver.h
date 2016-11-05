/*
 * 3driver.h
 *
 *  Created on: 29 זמגע. 2016 נ.
 *      Author: Home
 */

#ifndef DRIVER3D_H_
#define DRIVER3D_H_

/*


#define CUBE_COLOR GREEN*/

#define X_BORDER 240
#define Y_BORDER 320

#define SCALE_X0 X_BORDER/2
#define SCALE_Y0 Y_BORDER/2

#define PERSPECTIVE_COEFICIENT_SCALE 200

//Object3d struct properties
#define OBJECT_VERTEX_QUANTITY_MAX 50
#define OBJECT_EDGE_QUANTITY_MAX 50

typedef struct {
	int32_t x;
	int32_t y;
	int32_t z;
} XYZ_point;

typedef struct {
	XYZ_point* v1;
	XYZ_point* v2;
	uint16_t color;
} Edge;

typedef struct {

	XYZ_point centre;

	uint8_t vertex_quantity;
	uint8_t edge_quantity;

	XYZ_point vertex_start[OBJECT_VERTEX_QUANTITY_MAX];

	XYZ_point vertex[OBJECT_VERTEX_QUANTITY_MAX];
	Edge 	  edge[OBJECT_EDGE_QUANTITY_MAX];

	//Start position
	float x_rotate_start;
	float y_rotate_start;
	float z_rotate_start;

	//Current position
	float x_rotate;
	float y_rotate;
	float z_rotate;

	XYZ_point position;

	//It needs to clean object
	//int32_t x_min, x_max, y_min, y_max;

} Object3d__HandleTypeDef;

//
void Object3d_InitBox(Object3d__HandleTypeDef* obj, int16_t center_x, int16_t center_y, int16_t center_z, int16_t width, int16_t depth, int16_t heigth);

void Object3d_SetVertex(int32_t x, int32_t y, int32_t z, XYZ_point* point);
void Object3d_SetEdge(XYZ_point* p1, XYZ_point* p2, Edge* e);

void Object3d_DrawObject(Object3d__HandleTypeDef* obj);
void Object3d_CleanObject(Object3d__HandleTypeDef* obj);
void Object3d_DrawEdge(Object3d__HandleTypeDef* obj, uint8_t n);

void Object3d_CalculateObject(Object3d__HandleTypeDef* obj);
void Object3d_CalculateVertex(Object3d__HandleTypeDef* obj, uint8_t n);

void Object3d_GetRealXY(XYZ_point* k, int16_t* x, int16_t* y);

void Object3d_SetRotation(Object3d__HandleTypeDef* obj, float x_angle, float y_angle, float z_angle);
void SetNewPointValue(XYZ_point* point, float x_angle, float y_angle, float z_angle);

#endif /* DRIVER3D_H_ */
