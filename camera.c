#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#include <SDL/SDL.h>
#include <GL/gl.h>

#include "box.h"
#include "surface.h"

#define PRESSEDKEY(k) if(pkeys[k]) \
	for(i = 0; i < 4; i++)

float d = 330.0;
bool warnock = true;
bool pkeys[512];

// http://alienryderflex.com/intersect/
int
lineSegmentIntersection(float Ax, float Ay, float Bx, float By, float Cx,
    float Cy, float Dx, float Dy, float *X, float *Y)
{

	float distAB, theCos, theSin, newX, ABpos ;

	//  Fail if either line segment is zero-length.
	if ((Ax==Bx && Ay==By) || (Cx==Dx && Cy==Dy))
		return 0;

	//  Fail if the segments share an end-point.
	if ((Ax==Cx && Ay==Cy) || (Bx==Cx && By==Cy) ||
	    (Ax==Dx && Ay==Dy) || (Bx==Dx && By==Dy)) {
		return 0;
	}

	//  (1) Translate the system so that point A is on the origin.
	Bx-=Ax; By-=Ay;
	Cx-=Ax; Cy-=Ay;
	Dx-=Ax; Dy-=Ay;

	//  Discover the length of segment A-B.
	distAB=sqrt(Bx*Bx+By*By);

	//  (2) Rotate the system so that point B is on the positive X axis.
	theCos=Bx/distAB;
	theSin=By/distAB;
	newX=Cx*theCos+Cy*theSin;
	Cy  =Cy*theCos-Cx*theSin; Cx=newX;
	newX=Dx*theCos+Dy*theSin;
	Dy  =Dy*theCos-Dx*theSin; Dx=newX;

	//  Fail if segment C-D doesn't cross line A-B.
	if ((Cy<0. && Dy<0.) || (Cy>=0. && Dy>=0.))
	    return 0;

	//  (3) Discover the position of the intersection point along line A-B.
	ABpos=Dx+(Cx-Dx)*Dy/(Dy-Cy);

	//  Fail if segment C-D crosses line A-B outside of segment A-B.
	if (ABpos<0. || ABpos>distAB)
	    return 0;

	//  (4) Apply the discovered position to line A-B in the original coordinate system.
	*X=Ax+ABpos*theCos;
	*Y=Ay+ABpos*theSin;

	//  Success.
	return 1;
}

/*
 * 0 - polygon don't have commo part with qube and is not in qube
 * 1 - part of polygon is in qube
 * 2 - polygon is in qube
 * 3 - polygon surrounds qube
 */
int
test_surface(const surface_t *p, float wx1, float wy1, float wx2, float wy2)
{
	float x,y;
	float bx, by, sx, sy;
	bool r;
	int i;
	const coord_t *c[COORDS_PER_SURFACE];

	for (i = 0; i < COORDS_PER_SURFACE; i++)
		c[i] = &p->coords[i];
	/*
	 * 0 - some of line are interaction with qube line
	 * 1 - none of line are interaction with qube line
	 */
	r = lineSegmentIntersection(c[0]->xp, c[0]->yp, c[1]->xp, c[1]->yp, wx1, wy1, wx1,
	    wy2, &x, &y) == 0;
	r &= lineSegmentIntersection(c[0]->xp, c[0]->yp, c[1]->xp, c[1]->yp, wx1, wy2, wx2,
	    wy2, &x, &y) == 0;
	r &= lineSegmentIntersection(c[0]->xp, c[0]->yp, c[1]->xp, c[1]->yp, wx2, wy2, wx2,
	    wy1, &x, &y) == 0;
	r &= lineSegmentIntersection(c[0]->xp, c[0]->yp, c[1]->xp, c[1]->yp, wx2, wy1, wx1,
	    wy1, &x, &y) == 0;
	r &= lineSegmentIntersection(c[1]->xp, c[1]->yp, c[2]->xp, c[2]->yp, wx1, wy1, wx1,
	    wy2, &x, &y) == 0;
	r &= lineSegmentIntersection(c[1]->xp, c[1]->yp, c[2]->xp, c[2]->yp, wx1, wy2, wx2,
	    wy2, &x, &y) == 0;
	r &= lineSegmentIntersection(c[1]->xp, c[1]->yp, c[2]->xp, c[2]->yp, wx2, wy2, wx2,
	    wy1, &x, &y) == 0;
	r &= lineSegmentIntersection(c[1]->xp, c[1]->yp, c[2]->xp, c[2]->yp, wx2, wy1, wx1,
	    wy1, &x, &y) == 0;
	r &= lineSegmentIntersection(c[2]->xp, c[2]->yp, c[3]->xp, c[3]->yp, wx1, wy1, wx1,
	    wy2, &x, &y) == 0;
	r &= lineSegmentIntersection(c[2]->xp, c[2]->yp, c[3]->xp, c[3]->yp, wx1, wy2, wx2,
	    wy2, &x, &y) == 0;
	r &= lineSegmentIntersection(c[2]->xp, c[2]->yp, c[3]->xp, c[3]->yp, wx2, wy2, wx2,
	    wy1, &x, &y) == 0;
	r &= lineSegmentIntersection(c[2]->xp, c[2]->yp, c[3]->xp, c[3]->yp, wx2, wy1, wx1,
	    wy1, &x, &y) == 0;
	r &= lineSegmentIntersection(c[3]->xp, c[3]->yp, c[0]->xp, c[0]->yp, wx1, wy1, wx1,
	    wy2, &x, &y) == 0;
	r &= lineSegmentIntersection(c[3]->xp, c[3]->yp, c[0]->xp, c[0]->yp, wx1, wy2, wx2,
	    wy2, &x, &y) == 0;
	r &= lineSegmentIntersection(c[3]->xp, c[3]->yp, c[0]->xp, c[0]->yp, wx2, wy2, wx2,
	    wy1, &x, &y) == 0;
	r &= lineSegmentIntersection(c[3]->xp, c[3]->yp, c[0]->xp, c[0]->yp, wx2, wy1, wx1,
	    wy1, &x, &y) == 0;

	/* part of polygon is in qube */
	if (r == 0)
		return 1;

	/*
	 * we know that no line is cut qube, so if one of polygon point is in the qube
	 * all other points are in qube, and that means that polygon is in qube
	 */
	if (c[0]->xp < wx2 && c[0]->xp > wx1 && c[0]->yp < wy2 && c[0]->yp > wy1)
		return 2;

	/*
	 * we know that no line is cut qube, so if two points of polygon are one
	 * two diffrent sites of one point of qube that mean that
	 * polygon is around qube
	 */
	 bx = fmax(c[0]->xp, fmax(c[1]->xp, fmax(c[2]->xp, c[3]->xp)));
	 sx = fmin(c[0]->xp, fmin(c[1]->xp, fmin(c[2]->xp, c[3]->xp)));

	 by = fmax(c[0]->yp, fmax(c[1]->yp, fmax(c[2]->yp, c[3]->yp)));
	 sy = fmin(c[0]->yp, fmin(c[1]->yp, fmin(c[2]->yp, c[3]->yp)));

	 if (bx > wx1 && sx < wx1 && by > wy1 && sy < wy1)
		return 3;

	/* ok, we don't have other choose this must be polygon from one side */
	return 0;
}


void
init_window(int width, int height, const char *name, bool fs)
{
	Uint32 flags;

	flags = SDL_OPENGL;
	if (fs)
		flags |= SDL_FULLSCREEN;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_SetVideoMode(width, height, 0, flags);
	SDL_WM_SetCaption(name, NULL);

	glMatrixMode(GL_PROJECTION);
	glViewport(0, 0, width, height);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0);

	glLoadIdentity();
	glOrtho(-width / 2, width / 2.0, - height / 2.0, height / 2.0, 1, -1);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_TEXTURE_2D);
}

void
draw_boxes_warnock(box_t *boxes, float wx1, float wy1, float wx2, float wy2)
{
	int i, j, type, pos;
	int sow_count, spmw_count, siw_count, ssw_count;
	surface_t *surfaces[SURFACE_PER_BOX * 4], *sow[SURFACE_PER_BOX * 4];
	surface_t *spmw[SURFACE_PER_BOX * 4], *siw[SURFACE_PER_BOX * 4];
	surface_t *ssw[SURFACE_PER_BOX * 4];

	sow_count = spmw_count = siw_count = ssw_count = 0;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < COORDS_PER_SURFACE; j++) {
			pos = i * COORDS_PER_SURFACE + j;
			surfaces[pos] = &boxes[i].surfaces[j];
			type = test_surface(surfaces[i], wx1, wy1, wx2, wy2);
			switch (type) {
				case 0:
					/* Surface outside window */
					sow[sow_count] = surfaces[pos];
					sow_count ++;
					break;
				case 1:
					/* Surface partially meets window */
					spmw[spmw_count] = surfaces[pos];
					spmw_count ++;
					break;
				case 2:
					/* Surface inside window */
					siw[siw_count] = surfaces[pos];
					siw_count ++;
					break;
				case 3:
					/* Surface surrounds window */
					ssw[ssw_count] = surfaces[pos];
					ssw_count ++;
					break;
			}
		}
	}

	for (i = 0; i < 4; i++)
		box_draw(boxes + i);
}

void
draw_boxes(box_t *boxes)
{
	int i;

	for (i = 0; i < 4; i++)
		box_draw(boxes + i);
}

void
draw_scene(box_t *boxes)
{
	int i;

	/* Project all scene */
	for (i = 0; i < 4; i++)
		box_project(&boxes[i], d);

	if (warnock)	/* Draw boxes with Warnock Depth Test */
		draw_boxes_warnock(boxes, -2, -2, 2, 2);
	else		/* or not */
		draw_boxes(boxes);
}

int
main()
{
	int i;
	box_t b[4];

	init_box(&b[0]);
	memcpy(&b[1], &b[0], sizeof(b[0]));
	memcpy(&b[2], &b[0], sizeof(b[0]));
	memcpy(&b[3], &b[0], sizeof(b[0]));
	box_set_color(&b[0], 1.0, 0.0, 0.0);
	box_set_color(&b[1], 0.0, 1.0, 0.0);
	box_set_color(&b[2], 0.0, 0.0, 1.0);
	box_set_color(&b[3], 1.0, 0.0, 1.0);

	box_translation(&b[0],    0.0, -720.0,  600.0);
	box_translation(&b[1], -900.0, -720.0,  600.0);
	box_translation(&b[2],    0.0, -720.0, 1200.0);
	box_translation(&b[3], -900.0, -720.0, 1200.0);

	init_window(600, 480, "gk", false);

	while (true)
	{
		SDL_Event ev;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();

		draw_scene(b);

		memset(&ev, 0, sizeof(ev));
		while(SDL_PollEvent(&ev))
		{
			switch(ev.type)
			{
				case SDL_KEYDOWN:
					pkeys[ev.key.keysym.sym] = true;
					break;
				case SDL_KEYUP:
					pkeys[ev.key.keysym.sym] = false;
					break;
				case SDL_QUIT:
					SDL_Quit();
					exit(1);
			}
		}

		/* EVENTS */
		PRESSEDKEY(SDLK_UP)
			box_translation(b + i, 0, 0, -10.0);
		PRESSEDKEY(SDLK_DOWN)
			box_translation(b + i, 0, 0, 10.0);
		PRESSEDKEY(SDLK_LEFT)
			box_translation(b + i, 10.0, 0, 0);
		PRESSEDKEY(SDLK_RIGHT)
			box_translation(b + i, -10.0, 0, 0);
		PRESSEDKEY(SDLK_PAGEUP)
			box_translation(b + i, 0, 10.0, 0);
		PRESSEDKEY(SDLK_PAGEDOWN)
			box_translation(b + i, 0, -10.0, 0);
		PRESSEDKEY(SDLK_w)
			box_rotate_x(b + i, 0.5);
		PRESSEDKEY(SDLK_s)
			box_rotate_x(b + i, -0.5);
		PRESSEDKEY(SDLK_a)
			box_rotate_y(b + i, 0.5);
		PRESSEDKEY(SDLK_d)
			box_rotate_y(b + i, -0.5);
		PRESSEDKEY(SDLK_e)
			box_rotate_z(b + i, 0.5);
		PRESSEDKEY(SDLK_q)
			box_rotate_z(b + i, -0.5);
		PRESSEDKEY(SDLK_r)
			d += 1.0;
		PRESSEDKEY(SDLK_f)
			d -= 1.0;
		if (d < 0)
			d = 0.001;
		PRESSEDKEY(SDLK_1)
			warnock = true;
		PRESSEDKEY(SDLK_2)
			warnock = false;

		SDL_GL_SwapBuffers();
	}

	return (0);
}
