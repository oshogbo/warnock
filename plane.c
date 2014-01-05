#include "plane.h"

static void
plane_draw_points(float x1, float y1, float x2, float y2,
    float x3, float y3, float x4, float y4)
{
	
	glBegin(GL_QUADS);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glVertex2f(x3, y3);
	glVertex2f(x4, y4);
	glEnd();
}

void
plane_project(plane_t *p, float d)
{
	int i;

	for (i = 0; i < COORDS_PER_PLANE; i++)
		coord_project(&p->coords[i], d);
}

void
plane_translation(plane_t *p, float x, float y, float z)
{
	int i;

	for (i = 0; i < COORDS_PER_PLANE; i++)
		coord_translation(&p->coords[i], x, y, z);
}

void
plane_rotate_x(plane_t *p, float alphax)
{
	int i;

	for (i = 0; i < COORDS_PER_PLANE; i++)
		coord_rotate_x(&p->coords[i], alphax);
}

void
plane_rotate_y(plane_t *p, float alphax)
{
	int i;

	for (i = 0; i < COORDS_PER_PLANE; i++)
		coord_rotate_y(&p->coords[i], alphax);
}

void
plane_rotate_z(plane_t *p, float alphax)
{
	int i;

	for (i = 0; i < COORDS_PER_PLANE; i++)
		coord_rotate_z(&p->coords[i], alphax);
}

void
plane_draw(plane_t *p)
{

	glColor3f(p->r, p->g, p->b);
	plane_draw_points(p->coords[0].xp, p->coords[0].yp,
	    p->coords[1].xp, p->coords[1].yp,
	    p->coords[2].xp, p->coords[2].yp,
	    p->coords[3].xp, p->coords[3].yp);
}

void
plane_set_color(plane_t *p, float r, float g, float b)
{

	p->r = r;
	p->g = g;
	p->b = b;
}
