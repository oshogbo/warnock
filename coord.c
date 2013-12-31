#include "coord.h"

void
coord_project(coord_t *c, float d)
{

	c->xp = c->x * d / c->z;
	c->yp = c->y * d / c->z;
}

void
coord_translation(coord_t *c, float x, float y, float z)
{

	c->x += x;
	c->y += y;
	c->z += z;
}

void
coord_set(coord_t *p, float x, float y, float z)
{

	p->x = x;
	p->y = y;
	p->z = z;
}

void
coord_rotate_x(coord_t *c, float alphax)
{
	float radians;

	radians = alphax * M_PI / 180;
	c->y = c->y * cosf(radians) - c->z * sinf(radians);
	c->z = c->y * sinf(radians) + c->z * cosf(radians);
}

void
coord_rotate_y(coord_t *c, float alphax)
{
	float radians;

	radians = alphax * M_PI / 180;
	c->x = c->x * cosf(radians) + c->z * sinf(radians);
	c->z = - c->x * sinf(radians) + c->z * cosf(radians);
}

void
coord_rotate_z(coord_t *c, float alphax)
{
	float radians;

	radians = alphax * M_PI / 180;
	c->x = c->x * cosf(radians) - c->y * sinf(radians);
	c->y = c->x * sinf(radians) + c->y * cosf(radians);
}
