#ifndef __COORD_H__
#define __COORD_H__

#include <math.h>

typedef struct {
	float x;
	float y;
	float z;
	float xp;
	float yp;
} coord_t;

void coord_project(coord_t *c, float d);

void coord_rotate_x(coord_t *c, float alphax);
void coord_rotate_y(coord_t *c, float alphax);
void coord_rotate_z(coord_t *c, float alphax);

void coord_translation(coord_t *c, float x, float y, float z);

void coord_set(coord_t *p, float x, float y, float z);
#endif
