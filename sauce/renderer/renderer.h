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
#include <SDL_opengles2.h>
#else
#include <SDL_opengl.h>
#endif

extern GLuint r_fshader_id, r_vshader_id, r_program_id;
extern GLint r_pos_loc, r_color_loc;

/* some named colors (they should be constants even if not marked as such) */
extern float r_red[4];
extern float r_green[4];
extern float r_blue[4];

/* teh uniforms */
#define r_pos2fv(v) glUniform2fv(r_pos_loc, 1, (v))
#define r_color4fv(v) glUniform4fv(r_color_loc, 1, (v))
#define r_clear() \
{ \
	glClearColor(1, 1, 1, 1); \
	glClear(GL_COLOR_BUFFER_BIT); \
}

int r_fini();
int r_init();

#endif /* HAS_RENDERER_H */
