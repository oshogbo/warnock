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

#ifndef __SURFACE_H__
#define __SURFACE_H__

#define COORDS_PER_SURFACE 4

#include <GL/gl.h>

#include "coord.h"

typedef struct {
	coord_t	coords[COORDS_PER_SURFACE];
	float	r;
	float	g;
	float	b;
} surface_t;

void surface_translation(surface_t *p, float x, float y, float z);

void surface_rotate_x(surface_t *p, float alphax);
void surface_rotate_y(surface_t *p, float alphax);
void surface_rotate_z(surface_t *p, float alphax);

void surface_project(surface_t *p, float d);
void surface_draw(surface_t *p);

void surface_set_color(surface_t *p, float r, float g, float b);
#endif
