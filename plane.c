#include "plane.h"

static void
plane_draw_points(float x1, float y1, float x2, float y2,
    float x3, float y3, float x4, float y4)
{
	glBegin(GL_LINE_STRIP);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glVertex2f(x3, y3);
	glVertex2f(x4, y4);
	glEnd();
}

static void
plane_project_calculate(float d, coord_t *c1, coord_t *c2, coord_t *c3,
    coord_t *c4)
{

	c1->xp = c1->x * d / c1->z;
	c1->yp = c1->y * d / c1->z;

	c2->xp = c2->x * d / c2->z;
	c2->yp = c2->y * d / c2->z;

	c3->xp = c3->x * d / c3->z;
	c3->yp = c3->y * d / c3->z;

	c4->xp = c4->x * d / c4->z;
	c4->yp = c4->y * d / c4->z;
}

void
plane_project(plane_t *p, float d)
{

	plane_project_calculate(d, &p->coords[0], &p->coords[1],
	    &p->coords[2], &p->coords[3]);
}

void
plane_translation(plane_t *p, float x, float y, float z)
{
	int i;

	for (i = 0; i < 4; i++)
		coord_translation(&p->coords[i], x, y, z);
}

void
plane_rotate_x(plane_t *p, float alphax)
{
	int i;

	for (i = 0; i < 4; i++)
		coord_rotate_x(&p->coords[i], alphax);
}

void
plane_rotate_y(plane_t *p, float alphax)
{
	int i;

	for (i = 0; i < 4; i++)
		coord_rotate_y(&p->coords[i], alphax);
}

void
plane_rotate_z(plane_t *p, float alphax)
{
	int i;

	for (i = 0; i < 4; i++)
		coord_rotate_z(&p->coords[i], alphax);
}

void
plane_draw(plane_t *p)
{

	plane_draw_points(p->coords[0].x, p->coords[0].y,
	    p->coords[1].x, p->coords[1].y,
	    p->coords[2].x, p->coords[2].y,
	    p->coords[3].x, p->coords[3].y);
}
