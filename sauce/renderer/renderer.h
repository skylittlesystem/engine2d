/*
 * Copyright (C) 2014 Igor de Sant'Ana Fontana.
 * <rogi@skylittlesystem.org>
 *
 * This file is part of engine2d.
 *
 * engine2d is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Affero General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * engine2d is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public
 * License along with engine2d.  If not, see
 * <http://www.gnu.org/licenses/>.
 *
 */

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
