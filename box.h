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

#ifndef __BOX_H__
#define __BOX_H__

#include "coord.h"
#include "surface.h"

#define SURFACE_PER_BOX 6

typedef struct {
	surface_t surfaces[SURFACE_PER_BOX];
	int color_schame;
} box_t;

void init_box(box_t *b);

void box_rotate_x(box_t *b, float alphax);
void box_rotate_y(box_t *b, float alphax);
void box_rotate_z(box_t *b, float alphax);

void box_translation(box_t *b, float x, float y, float z);

void box_project(box_t *b, float d);

void box_draw(box_t *box);

void box_set_color(box_t *box, float r, float g, float b);

#endif
