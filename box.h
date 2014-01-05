#ifndef __BOX_H__
#define __BOX_H__

#include "coord.h"
#include "surface.h"

#define SURFACE_PER_BOX 6

typedef struct {
	surface_t surfaces[SURFACE_PER_BOX];
	int color_schame;
} box_t;

void init_box(box_t *b);

void box_rotate_x(box_t *b, float alphax);
void box_rotate_y(box_t *b, float alphax);
void box_rotate_z(box_t *b, float alphax);

void box_translation(box_t *b, float x, float y, float z);

void box_project(box_t *b, float d);

void box_draw(box_t *box);

void box_set_color(box_t *box, float r, float g, float b);

#endif
