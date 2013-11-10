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

/* FIXME: load this right */
static GLchar fshader_sauce[] =
{
	#include "fshader.glsl.c"
	, '\0'
};

static GLchar vshader_sauce[] =
{
	#include "vshader.glsl.c"
	, '\0'
};

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

int r_fini(struct renderer* R)
{
	glDeleteProgram(R->program_id);
	glDeleteShader(R->fshader_id);
	glDeleteShader(R->vshader_id);
	return 0;
}

int r_init(struct renderer* R)
{
	GLuint shaderv[2];

	R->vshader_id = init_shader(GL_VERTEX_SHADER, vshader_sauce);
	if (R->vshader_id == 0)
		return -1;

	R->fshader_id = init_shader(GL_FRAGMENT_SHADER, fshader_sauce);
	if (R->fshader_id == 0)
		return -1;

	shaderv[0] = R->vshader_id;
	shaderv[1] = R->fshader_id;
	R->program_id = init_program(2, shaderv);
	if (R->program_id == 0)
		return -1;

	return 0;
}

