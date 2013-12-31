#include "box.h"

void
init_box(box_t *b)
{
	plane_t *p;

	p = &b->planes[0];
	coord_set(&p->coords[0], 1.0, 1.0, 1.0);
	coord_set(&p->coords[1], 1.0, 2.0, 1.0);
	coord_set(&p->coords[2], 2.0, 2.0, 1.0);
	coord_set(&p->coords[3], 2.0, 1.0, 1.0);

	p = &b->planes[1];
	coord_set(&p->coords[0], 1.0, 2.0, 1.0);
	coord_set(&p->coords[1], 1.0, 2.0, 2.0);
	coord_set(&p->coords[2], 2.0, 2.0, 2.0);
	coord_set(&p->coords[3], 2.0, 2.0, 1.0);

	p = &b->planes[2];
	coord_set(&p->coords[0], 1.0, 2.0, 2.0);
	coord_set(&p->coords[1], 2.0, 2.0, 2.0);
	coord_set(&p->coords[2], 2.0, 1.0, 2.0);
	coord_set(&p->coords[3], 1.0, 1.0, 2.0);

	p = &b->planes[3];
	coord_set(&p->coords[0], 1.0, 1.0, 2.0);
	coord_set(&p->coords[1], 2.0, 1.0, 2.0);
	coord_set(&p->coords[2], 2.0, 1.0, 1.0);
	coord_set(&p->coords[3], 1.0, 1.0, 1.0);

	p = &b->planes[4];
	coord_set(&p->coords[0], 2.0, 2.0, 1.0);
	coord_set(&p->coords[1], 2.0, 2.0, 2.0);
	coord_set(&p->coords[2], 2.0, 1.0, 2.0);
	coord_set(&p->coords[3], 2.0, 1.0, 1.0);

	p = &b->planes[5];
	coord_set(&p->coords[0], 1.0, 1.0, 1.0);
	coord_set(&p->coords[1], 1.0, 2.0, 1.0);
	coord_set(&p->coords[2], 1.0, 2.0, 2.0);
	coord_set(&p->coords[3], 1.0, 1.0, 2.0);
}

void
box_rotate_x(box_t *b, float alphax)
{
	int i;

	for (i = 0; i < 6; i++)
		plane_rotate_x(&b->planes[i], alphax);
}

void
box_rotate_y(box_t *b, float alphax)
{
	int i;

	for (i = 0; i < 6; i++)
		plane_rotate_y(&b->planes[i], alphax);
}

void
box_rotate_z(box_t *b, float alphax)
{
	int i;

	for (i = 0; i < 6; i++)
		plane_rotate_z(&b->planes[i], alphax);
}

void
box_translation(box_t *b, float x, float y, float z)
{
	int i;

	for (i = 0; i < 6; i++)
		plane_translation(&b->planes[i], x, y, z);
}

void
box_project(box_t *b, float d)
{
	int i;

	for (i = 0; i < 6; i++)
		plane_project(&b->planes[i], d);
}

void
draw_boxes(box_t *boxes,
    __attribute__((unused)) float wx1,
    __attribute__((unused)) float wy1,
    __attribute__((unused)) float wx2,
    __attribute__((unused)) float wy2)
{
	int i;

	for (i = 0; i < 6; i++)
		plane_draw(&boxes->planes[i]);
}
