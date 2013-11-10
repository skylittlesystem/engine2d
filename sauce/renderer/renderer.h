/*
 *
 *
 *
 *
 * renderer.h
 *
 *
 *
 *
 *
 */

#ifndef HAS_RENDERER_H
#define HAS_RENDERER_H

#if OPENGL_ES
//#include <SDL_opengles.h>
#include <SDL_opengles2.h>
#else
#include <SDL_opengl.h>
#endif

struct renderer
{
	GLuint vshader_id;
	GLuint fshader_id;
	GLuint program_id;
};

int r_fini(struct renderer* R);
int r_init(struct renderer* R);

#endif /* HAS_RENDERER_H */
