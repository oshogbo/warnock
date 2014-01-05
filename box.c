#include <stdbool.h>

#include "box.h"

/*
 * forward back
 */
static void
init_box_fb(plane_t *p, bool b)
{
	float f;

	f = (b ? 1.0 : 2.0) * 300;
	coord_set(&p->coords[0], 300.0, 240.0, f);
	coord_set(&p->coords[1], 300.0, 480.0, f);
	coord_set(&p->coords[2], 600.0, 480.0, f);
	coord_set(&p->coords[3], 600.0, 240.0, f);
}

/*
 * top bottom
 */
static void
init_box_tb(plane_t *p, bool b)
{
	float f;

	f = (b ? 1.0 : 2.0) * 240.0;
	coord_set(&p->coords[0], 300.0, f, 300.0);
	coord_set(&p->coords[1], 300.0, f, 600.0);
	coord_set(&p->coords[2], 600.0, f, 600.0);
	coord_set(&p->coords[3], 600.0, f, 300.0);
}

/*
 * left right
 */
static void
init_box_lr(plane_t *p, bool r)
{
	float f;

	f = (r ? 1.0 : 2.0) * 300.0;
	coord_set(&p->coords[0], f, 240.0, 300.0);
	coord_set(&p->coords[1], f, 240.0, 600.0);
	coord_set(&p->coords[2], f, 480.0, 600.0);
	coord_set(&p->coords[3], f, 480.0, 300.0);
}

void
init_box(box_t *b)
{
	int i;

	i = 0;
	init_box_fb(&b->planes[i++], false);
	init_box_fb(&b->planes[i++], true);

	init_box_tb(&b->planes[i++], false);
	init_box_tb(&b->planes[i++], true);

	init_box_lr(&b->planes[i++], false);
	init_box_lr(&b->planes[i++], true);
}

void
box_rotate_x(box_t *b, float alphax)
{
	int i;

	for (i = 0; i < PLANE_PER_BOX; i++)
		plane_rotate_x(&b->planes[i], alphax);
}

void
box_rotate_y(box_t *b, float alphax)
{
	int i;

	for (i = 0; i < PLANE_PER_BOX; i++)
		plane_rotate_y(&b->planes[i], alphax);
}

void
box_rotate_z(box_t *b, float alphax)
{
	int i;

	for (i = 0; i < PLANE_PER_BOX; i++)
		plane_rotate_z(&b->planes[i], alphax);
}

void
box_translation(box_t *b, float x, float y, float z)
{
	int i;

	for (i = 0; i < PLANE_PER_BOX; i++)
		plane_translation(&b->planes[i], x, y, z);
}

void
box_project(box_t *b, float d)
{
	int i;

	for (i = 0; i < PLANE_PER_BOX; i++)
		plane_project(&b->planes[i], d);
}

void
box_draw(box_t *box)
{
	int i;

	for (i = 0; i < PLANE_PER_BOX; i++)
		plane_draw(&box->planes[i]);
}
