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
