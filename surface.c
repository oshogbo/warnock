/*-
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 Michał Knieć <michalkniec91@gmail.com>
 * Copyright (c) 2014 Mariusz Zaborski <oshogbo@vexillium.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "surface.h"

static void
surface_draw_points(float x1, float y1, float x2, float y2,
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
surface_project(surface_t *p, float d)
{
	int i;

	for (i = 0; i < COORDS_PER_SURFACE; i++)
		coord_project(&p->coords[i], d);
}

void
surface_translation(surface_t *p, float x, float y, float z)
{
	int i;

	for (i = 0; i < COORDS_PER_SURFACE; i++)
		coord_translation(&p->coords[i], x, y, z);
}

void
surface_rotate_x(surface_t *p, float alphax)
{
	int i;

	for (i = 0; i < COORDS_PER_SURFACE; i++)
		coord_rotate_x(&p->coords[i], alphax);
}

void
surface_rotate_y(surface_t *p, float alphax)
{
	int i;

	for (i = 0; i < COORDS_PER_SURFACE; i++)
		coord_rotate_y(&p->coords[i], alphax);
}

void
surface_rotate_z(surface_t *p, float alphax)
{
	int i;

	for (i = 0; i < COORDS_PER_SURFACE; i++)
		coord_rotate_z(&p->coords[i], alphax);
}

void
surface_draw(surface_t *p)
{
	int i;

	for (i = 0; i < COORDS_PER_SURFACE; i++)
		if (p->coords[i].z < 0.001)
			return;

	glColor3f(p->r, p->g, p->b);
	surface_draw_points(p->coords[0].xp, p->coords[0].yp,
	    p->coords[1].xp, p->coords[1].yp,
	    p->coords[2].xp, p->coords[2].yp,
	    p->coords[3].xp, p->coords[3].yp);
}

void
surface_set_color(surface_t *p, float r, float g, float b)
{

	p->r = r;
	p->g = g;
	p->b = b;
}
