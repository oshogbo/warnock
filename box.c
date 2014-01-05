#include <stdbool.h>

#include "box.h"

/*
 * forward back
 */
static void
init_box_fb(surface_t *p, bool b)
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
init_box_tb(surface_t *p, bool b)
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
init_box_lr(surface_t *p, bool r)
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
	init_box_fb(&b->surfaces[i++], false);
	init_box_fb(&b->surfaces[i++], true);

	init_box_tb(&b->surfaces[i++], false);
	init_box_tb(&b->surfaces[i++], true);

	init_box_lr(&b->surfaces[i++], false);
	init_box_lr(&b->surfaces[i++], true);
}

void
box_rotate_x(box_t *b, float alphax)
{
	int i;

	for (i = 0; i < PLANE_PER_BOX; i++)
		surface_rotate_x(&b->surfaces[i], alphax);
}

void
box_rotate_y(box_t *b, float alphax)
{
	int i;

	for (i = 0; i < PLANE_PER_BOX; i++)
		surface_rotate_y(&b->surfaces[i], alphax);
}

void
box_rotate_z(box_t *b, float alphax)
{
	int i;

	for (i = 0; i < PLANE_PER_BOX; i++)
		surface_rotate_z(&b->surfaces[i], alphax);
}

void
box_translation(box_t *b, float x, float y, float z)
{
	int i;

	for (i = 0; i < PLANE_PER_BOX; i++)
		surface_translation(&b->surfaces[i], x, y, z);
}

void
box_project(box_t *b, float d)
{
	int i;

	for (i = 0; i < PLANE_PER_BOX; i++)
		surface_project(&b->surfaces[i], d);
}

void
box_draw(box_t *box)
{
	int i;

	for (i = 0; i < PLANE_PER_BOX; i++)
		surface_draw(&box->surfaces[i]);
}

void
box_set_color(box_t *box, float r, float g, float b)
{
	int i;

	for (i = 0; i < PLANE_PER_BOX; i++)
		surface_set_color(&box->surfaces[i], r, g, b);
}
