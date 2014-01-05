#ifndef __SURFACE_H__
#define __SURFACE_H__

#define COORDS_PER_SURFACE 4

#include <GL/gl.h>

#include "coord.h"

typedef struct {
	coord_t	coords[COORDS_PER_SURFACE];
	float	r;
	float	g;
	float	b;
} surface_t;

void surface_translation(surface_t *p, float x, float y, float z);

void surface_rotate_x(surface_t *p, float alphax);
void surface_rotate_y(surface_t *p, float alphax);
void surface_rotate_z(surface_t *p, float alphax);

void surface_project(surface_t *p, float d);
void surface_draw(surface_t *p);

void surface_set_color(surface_t *p, float r, float g, float b);
#endif
