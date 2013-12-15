#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#include <SDL/SDL.h>
#include <GL/gl.h>

#define BACKGROUND 4

# define PRESSEDKEY(k) if(pkeys[k]) \
	for(i = 0; i < 4; i++)

float d=2.0;

typedef struct coords {
	float x;
	float y;
	float z;
	float xp;
	float yp;
} coords_t;

typedef struct {
	coords_t coord3d[8];
} box_t;

bool pkeys[512];
bool trick = false;

// http://alienryderflex.com/intersect/
int
lineSegmentIntersection(float Ax, float Ay, float Bx, float By, float Cx, float Cy, float Dx, float Dy, float *X, float *Y)
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
	//glOrtho(0.0, width / 10.0, height / 10.0, 0.0, 1, -1);
	glOrtho(-2, 2, -2, 2, 1.0, -1.0);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_TEXTURE_2D);
}

void
draw_line_points(float x1, float y1, float x2, float y2)
{
	glBegin(GL_LINE_STRIP);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();
}

void
draw_plane_points(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
	glBegin(GL_QUADS);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glVertex2f(x3, y3);
	glVertex2f(x4, y4);
	glEnd();
}

void
draw_line(coords_t c1, coords_t c2)
{
	float x1, y1, d1;
	float x2, y2, d2;
	float z1, z2;
	float cx1, cy1;
	float cx2, cy2;

	z1 = c1.z;
	z2 = c2.z;
	/*cx1 = c1.x;
	  cx2 = c2.x;
	  cy1 = c1.y;
	  cy2 = c2.y;*/

	if (z1 <= 0.01 || z2 <= 0.01)
		return;

	/*x1 = cx1 * d / z1;
	  y1 = cy1 * d / z1;

	  x2 = cx2 * d / z2;
	  y2 = cy2 * d / z2;

	  draw_line_points(x1, y1, x2, y2);*/
	//project_line(&c1, &c2);
	draw_line_points(c1.xp, c1.yp, c2.xp, c2.yp);
}

void
draw_plane(coords_t c1, coords_t c2, coords_t c3, coords_t c4)
{
	draw_plane_points(c1.xp, c1.yp, c2.xp, c2.yp, c3.xp, c3.yp, c4.xp, c4.yp);
}

void
project_line(coords_t *c1, coords_t *c2)
{
	c1->xp = c1->x * d / c1->z;
	c1->yp = c1->y * d / c1->z;

	c2->xp = c2->x * d / c2->z;
	c2->yp = c2->y * d / c2->z;
}

void
project_plane(coords_t *c1, coords_t *c2, coords_t *c3, coords_t *c4)
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

int
checkIntersection(box_t *b, float wx1, float wy1, float wx2, float wy2)
{
	float x,y;
	bool p[16];
	bool r;

	p[0] = !lineSegmentIntersection(b->coord3d[0].xp, b->coord3d[0].yp, b->coord3d[1].xp, b->coord3d[1].yp, wx1, wy1, wx1, wy2, &x, &y);
	p[1] = !lineSegmentIntersection(b->coord3d[0].xp, b->coord3d[0].yp, b->coord3d[1].xp, b->coord3d[1].yp, wx1, wy2, wx2, wy2, &x, &y);
	p[2] = !lineSegmentIntersection(b->coord3d[0].xp, b->coord3d[0].yp, b->coord3d[1].xp, b->coord3d[1].yp, wx2, wy2, wx2, wy1, &x, &y);
	p[3] = !lineSegmentIntersection(b->coord3d[0].xp, b->coord3d[0].yp, b->coord3d[1].xp, b->coord3d[1].yp, wx2, wy1, wx1, wy1, &x, &y);
	p[4] = !lineSegmentIntersection(b->coord3d[1].xp, b->coord3d[1].yp, b->coord3d[2].xp, b->coord3d[2].yp, wx1, wy1, wx1, wy2, &x, &y);
	p[5] = !lineSegmentIntersection(b->coord3d[1].xp, b->coord3d[1].yp, b->coord3d[2].xp, b->coord3d[2].yp, wx1, wy2, wx2, wy2, &x, &y);
	p[6] = !lineSegmentIntersection(b->coord3d[1].xp, b->coord3d[1].yp, b->coord3d[2].xp, b->coord3d[2].yp, wx2, wy2, wx2, wy1, &x, &y);
	p[7] = !lineSegmentIntersection(b->coord3d[1].xp, b->coord3d[1].yp, b->coord3d[2].xp, b->coord3d[2].yp, wx2, wy1, wx1, wy1, &x, &y);
	p[8] = !lineSegmentIntersection(b->coord3d[2].xp, b->coord3d[2].yp, b->coord3d[3].xp, b->coord3d[3].yp, wx1, wy1, wx1, wy2, &x, &y);
	p[9] = !lineSegmentIntersection(b->coord3d[2].xp, b->coord3d[2].yp, b->coord3d[3].xp, b->coord3d[3].yp, wx1, wy2, wx2, wy2, &x, &y);
	p[10] = !lineSegmentIntersection(b->coord3d[2].xp, b->coord3d[2].yp, b->coord3d[3].xp, b->coord3d[3].yp, wx2, wy2, wx2, wy1, &x, &y);
	p[11] = !lineSegmentIntersection(b->coord3d[2].xp, b->coord3d[2].yp, b->coord3d[3].xp, b->coord3d[3].yp, wx2, wy1, wx1, wy1, &x, &y);
	p[12] = !lineSegmentIntersection(b->coord3d[3].xp, b->coord3d[3].yp, b->coord3d[0].xp, b->coord3d[0].yp, wx1, wy1, wx1, wy2, &x, &y);
	p[13] = !lineSegmentIntersection(b->coord3d[3].xp, b->coord3d[3].yp, b->coord3d[0].xp, b->coord3d[0].yp, wx1, wy2, wx2, wy2, &x, &y);
	p[14] = !lineSegmentIntersection(b->coord3d[3].xp, b->coord3d[3].yp, b->coord3d[0].xp, b->coord3d[0].yp, wx2, wy2, wx2, wy1, &x, &y);
	p[15] = !lineSegmentIntersection(b->coord3d[3].xp, b->coord3d[3].yp, b->coord3d[0].xp, b->coord3d[0].yp, wx2, wy1, wx1, wy1, &x, &y);

	// Czy jakakolwiek linia sie przecina z jakakolwiek inna linia kwadrata - dla jednej plaszczyzny!
	for (i = 0, r = 1; i < 16; i++)
		r &= p[i];

	if (r == 0)
		return 0;
}

void
draw_boxes(box_t *boxes, float wx1, float wy1, float wx2, float wy2)
{
	box_t *b = NULL;
	int i = 0;
	int type;

	for (i = 0; i < 4; i++) {
		b = &boxes[i];
		type = checkIntersection(boxes, wx1, wy1, wx2, wy2);

		switch (type) {
		case 0:
			// Plane outside window
			break;
		case 1:
			// Plane surrounds window
			break;
		case 2:
			// Plane partially meets window
			break;
		case 3:
			// Plane inside window
			break;
		}
	}
	/*draw_plane(b->coord3d[0], b->coord3d[1], b->coord3d[2], b->coord3d[3]);
	  draw_plane(b->coord3d[4], b->coord3d[5], b->coord3d[6], b->coord3d[7]);

	  draw_plane(b->coord3d[1], b->coord3d[2], b->coord3d[6], b->coord3d[5]);
	  draw_plane(b->coord3d[0], b->coord3d[3], b->coord3d[7], b->coord3d[4]);*/
}

void
set_color(int num)
{
	switch(i)
	{
		case 0: glColor3f(1.0, 0.0, 0.0); break;
		case 1: glColor3f(1.0, 1.0, 0.0); break;
		case 2: glColor3f(0.0, 0.0, 1.0); break;
		case 3: glColor3f(0.0, 1.0, 0.0); break;
		case 4: glColor3f(0.0, 0.0, 0.0); break;
	}
}

void
draw_scene(box_t *boxes)
{
	int i = 0;
	box_t *b = NULL;

	// Project all scene
	for (i = 0; i < 4; i++)
	{
		b = &boxes[i];
		project_plane(&b->coord3d[0], &b->coord3d[1], &b->coord3d[2], &b->coord3d[3]);
		project_plane(&b->coord3d[4], &b->coord3d[5], &b->coord3d[6], &b->coord3d[7]);
	}

	// Draw boxes with Warnock Depth Test
	draw_boxes(boxes, -2, 2, -2, 2);
}

void
coord_translation(coords_t *c, float x, float y, float z) {
	c->x += x;
	c->y += y;
	c->z += z;
}

void
box_translation(box_t *b, float x, float y, float z)
{
	int i;

	for (i = 0; i < 8; i++)
		coord_translation(&b->coord3d[i], x,y,z);
}

void
coord_rotate_x(coords_t *c, float alphax)
{
	c->y = c->y * cosf(alphax) - c->z * sinf(alphax);
	c->z = c->y * sinf(alphax) + c->z * cosf(alphax);
}

void
box_rotate_x(box_t *b, float alphax)
{
	int i;

	for (i = 0; i < 8; i++)
		coord_rotate_x(&b->coord3d[i], alphax * M_PI / 180);
}

void
coord_rotate_y(coords_t *c, float alphax)
{
	c->x = c->x * cosf(alphax) + c->z * sinf(alphax);
	c->z = - c->x * sinf(alphax) + c->z * cosf(alphax);
}

void
box_rotate_y(box_t *b, float alphax)
{
	int i;

	for (i = 0; i < 8; i++)
		coord_rotate_y(&b->coord3d[i], alphax * M_PI / 180);
}

void
coord_rotate_z(coords_t *c, float alphax)
{
	c->x = c->x * cosf(alphax) - c->y * sinf(alphax);
	c->y = c->x * sinf(alphax) + c->y * cosf(alphax);
}

void
box_rotate_z(box_t *b, float alphax)
{
	int i;

	for (i = 0; i < 8; i++)
		coord_rotate_z(&b->coord3d[i], alphax * M_PI / 180);
}


int
main()
{
	int i;
	float alphax, alphay, alphaz;
	box_t b[4];

	alphax = alphay = alphaz = 0;
	b[0].coord3d[0].x = 1.0;
	b[0].coord3d[0].y = 1.0;
	b[0].coord3d[0].z = 1.0;

	b[0].coord3d[1].x = 1.0;
	b[0].coord3d[1].y = 2.0;
	b[0].coord3d[1].z = 1.0;

	b[0].coord3d[2].x = 2.0;
	b[0].coord3d[2].y = 2.0;
	b[0].coord3d[2].z = 1.0;

	b[0].coord3d[3].x = 2.0;
	b[0].coord3d[3].y = 1.0;
	b[0].coord3d[3].z = 1.0;

	b[0].coord3d[4].x = 1.0;
	b[0].coord3d[4].y = 1.0;
	b[0].coord3d[4].z = 2.0;

	b[0].coord3d[5].x = 1.0;
	b[0].coord3d[5].y = 2.0;
	b[0].coord3d[5].z = 2.0;

	b[0].coord3d[6].x = 2.0;
	b[0].coord3d[6].y = 2.0;
	b[0].coord3d[6].z = 2.0;

	b[0].coord3d[7].x = 2.0;
	b[0].coord3d[7].y = 1.0;
	b[0].coord3d[7].z = 2.0;

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
		PRESSEDKEY(SDLK_1)
			trick = false;
		PRESSEDKEY(SDLK_2)
			trick = true;

		SDL_GL_SwapBuffers();
	}

	return (0);
}
