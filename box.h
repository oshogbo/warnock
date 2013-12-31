#ifndef __BOX_H__
#define __BOX_H__

#include "coord.h"
#include "plane.h"

typedef struct {
	plane_t planes[6];
} box_t;

void init_box(box_t *b);

void box_rotate_x(box_t *b, float alphax);
void box_rotate_y(box_t *b, float alphax);
void box_rotate_z(box_t *b, float alphax);

void box_translation(box_t *b, float x, float y, float z);

void box_project(box_t *b, float d);

void draw_boxes(box_t *boxes, float wx1, float wy1, float wx2, float wy2);
#endif