#ifndef __PLANE_H__
#define __PLANE_H__

#define COORDS_PER_PLANE 4

#include <GL/gl.h>

#include "coord.h"

typedef struct {
	coord_t coords[4];
} plane_t;

void plane_translation(plane_t *p, float x, float y, float z);

void plane_rotate_x(plane_t *p, float alphax);
void plane_rotate_y(plane_t *p, float alphax);
void plane_rotate_z(plane_t *p, float alphax);

void plane_project(plane_t *p, float d);
void plane_draw(plane_t *p);

#endif
