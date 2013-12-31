#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#include <SDL/SDL.h>
#include <GL/gl.h>

#include "box.h"

#define BACKGROUND 4

# define PRESSEDKEY(k) if(pkeys[k]) \
	for(i = 0; i < 4; i++)

float d = 2.0;

bool pkeys[512];

void
set_color(int num)
{

	switch(num)
	{
		case 0: glColor3f(1.0, 0.0, 0.0); break;
		case 1: glColor3f(1.0, 1.0, 0.0); break;
		case 2: glColor3f(0.0, 0.0, 1.0); break;
		case 3: glColor3f(0.0, 1.0, 0.0); break;
		case 4: glColor3f(0.0, 0.0, 0.0); break;
	}
}

// http://alienryderflex.com/intersect/
/*int
lineSegmentIntersection(float Ax, float Ay, float Bx, float By, float Cx,
    float Cy, float Dx, float Dy, float *X, float *Y)
{

	float distAB, theCos, theSin, newX, ABpos ;

	//  Fail if either line segment is zero-length.
	if (Ax==Bx && Ay==By || Cx==Dx && Cy==Dy)
		return 0;

	//  Fail if the segments share an end-point.
	if (Ax==Cx && Ay==Cy || Bx==Cx && By==Cy ||
	    Ax==Dx && Ay==Dy || Bx==Dx && By==Dy) {
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
	if (Cy<0. && Dy<0. || Cy>=0. && Dy>=0.)
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
}*/

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
	glOrtho(-2, 2, -2, 2, 1.0, -1.0);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_TEXTURE_2D);
}

void
draw_boxes(box_t *boxes,
    __attribute__((unused)) float wx1,
    __attribute__((unused)) float wy1,
    __attribute__((unused)) float wx2,
    __attribute__((unused)) float wy2)
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

	/* Draw boxes with Warnock Depth Test */
	draw_boxes(boxes, -2, -2, 2, 2);
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

	box_translation(&b[0], 0, -3, 2);
	box_translation(&b[1], -3, -3, 2);
	box_translation(&b[2], 0, -3, 4);
	box_translation(&b[3], -3, -3, 4);

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
			box_translation(b + i, 0, 0, -0.01);
		PRESSEDKEY(SDLK_DOWN)
			box_translation(b + i, 0, 0, 0.01);
		PRESSEDKEY(SDLK_LEFT)
			box_translation(b + i, 0.01, 0, 0);
		PRESSEDKEY(SDLK_RIGHT)
			box_translation(b + i, -0.01, 0, 0);
		PRESSEDKEY(SDLK_PAGEUP)
			box_translation(b + i, 0, 0.01, 0);
		PRESSEDKEY(SDLK_PAGEDOWN)
			box_translation(b + i, 0, -0.01, 0);
		PRESSEDKEY(SDLK_w)
			box_rotate_x(b + i, 0.05);
		PRESSEDKEY(SDLK_s)
			box_rotate_x(b + i, -0.05);
		PRESSEDKEY(SDLK_a)
			box_rotate_y(b + i, 0.05);
		PRESSEDKEY(SDLK_d)
			box_rotate_y(b + i, -0.05);
		PRESSEDKEY(SDLK_e)
			box_rotate_z(b + i, 0.05);
		PRESSEDKEY(SDLK_q)
			box_rotate_z(b + i, -0.05);
		PRESSEDKEY(SDLK_r)
			d += 0.001;
		PRESSEDKEY(SDLK_f)
			d -= 0.001;
		if (d < 0)
			d = 0.001;

		SDL_GL_SwapBuffers();
	}

	return (0);
}
