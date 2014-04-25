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
 * r_game.c
 *
 *
 *
 *
 *
 */

#include <assert.h>
#include <stdbool.h>
#include "renderer.h"
#include "game/game.h"
#include "game/g_entity/g_player.h"

#include "misc/simd.h"

void r_boxxy(float (*boxxy)[2])
{
	float v[4][2];
	v2cpy(v[0], boxxy[0]);
	v2add(v[2], boxxy[0], boxxy[1]);
	v2set(v[1], v[2][0], v[0][1]);
	v2set(v[3], v[0][0], v[2][1]);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, v);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void r_poly(unsigned c, float* (v)[2])
{
	glEnable(GL_STENCIL_TEST);
	assert (glIsEnabled(GL_STENCIL_TEST));

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, v);

	glStencilMask(127);
	glClearStencil(0);
	glClear(GL_STENCIL_BUFFER_BIT);

	/**/

	glStencilFunc(GL_NEVER, 0, 127);
	glStencilOp(GL_INVERT, GL_KEEP, GL_KEEP);

	glDrawArrays(GL_TRIANGLE_FAN, 0, c);

	/**/

	glStencilMask(0);
	glStencilFunc(GL_NOTEQUAL, 0, 127);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

	glDrawArrays(GL_TRIANGLE_FAN, 0, c);

	/**/

	glDisable(GL_STENCIL_TEST);
	assert (!glIsEnabled(GL_STENCIL_TEST));
}
