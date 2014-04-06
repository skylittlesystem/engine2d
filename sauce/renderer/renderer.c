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
 * renderer.c
 *
 *
 *
 *
 *
 */

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include "renderer.h"

/* some named colors */
float r_red[4] = {1, 0, 0, 1};
float r_green[4] = {0, 1, 0, 1};
float r_blue[4] = {0, 0, 1, 1};

GLuint r_fshader_id, r_vshader_id, r_program_id;
GLint r_pos_loc, r_color_loc;

/* fragment shader */
static GLchar fshader_sauce[] =
{
	#include "fshader.glsl.c"
	, '\0'
};

/* vertex shader */
static GLchar vshader_sauce[] =
{
	#include "vshader.glsl.c"
	, '\0'
};

/* helper to initialize shader */
static GLuint init_shader(GLenum type, GLchar* sauce)
{
	GLuint shader_id;
	GLint compiled;

	shader_id = glCreateShader(type);

	if (shader_id == 0)
		return 0;

	glShaderSource(shader_id, 1, (const GLchar**) &sauce, NULL); 
	glCompileShader(shader_id);
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compiled);

	if (!compiled)
	{
		GLint len = 0;
		glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &len);
		if (len > 1)
		{
			char log[len];
			glGetShaderInfoLog(shader_id, len, NULL, log);
			fprintf(stderr, "%s:%d: init_shader(): \n%s\n",
					__FILE__, __LINE__, log);
		}

		glDeleteShader(shader_id);
		shader_id = 0;
	}

	return shader_id;
}

/* helper to initialize program*/
static GLuint init_program(unsigned shaderc, GLuint* shaderv)
{
	unsigned i;
	GLuint prg_id;
	GLint linked;

	prg_id = glCreateProgram();

	if (prg_id == 0)
		return 0;

	for (i = 0; i < shaderc; ++i)
		glAttachShader(prg_id, shaderv[i]);

	glLinkProgram(prg_id);
	glGetProgramiv(prg_id, GL_LINK_STATUS, &linked);

	if (!linked)
	{
		GLint len = 0;
		glGetProgramiv(prg_id, GL_INFO_LOG_LENGTH, &len);
		if (len > 1)
		{
			char log[len];
			glGetProgramInfoLog(prg_id, len, NULL, log);
			fprintf(stderr, "%s:%d: init_program(): \n%s\n",
					__FILE__, __LINE__, log);
		}

		glDeleteProgram(prg_id);
		prg_id = 0;
	}

	return prg_id;
}

int r_fini()
{
	glDeleteProgram(r_program_id);
	glDeleteShader(r_fshader_id);
	glDeleteShader(r_vshader_id);
	return 0;
}

int r_init()
{
	GLuint shaderv[2];

	r_vshader_id = init_shader(GL_VERTEX_SHADER, vshader_sauce);
	if (r_vshader_id == 0)
		return -1;

	r_fshader_id = init_shader(GL_FRAGMENT_SHADER, fshader_sauce);
	if (r_fshader_id == 0)
		return -1;

	shaderv[0] = r_vshader_id;
	shaderv[1] = r_fshader_id;
	r_program_id = init_program(2, shaderv);
	if (r_program_id == 0)
		return -1;

	/* make program active */
	glUseProgram(r_program_id);

	/* get uniform locations */
	r_pos_loc = glGetUniformLocation(r_program_id, "pos");
	r_color_loc = glGetUniformLocation(r_program_id, "color");

	return 0;
}

