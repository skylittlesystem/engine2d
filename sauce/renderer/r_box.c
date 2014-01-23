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
 * r_box.c
 *
 *
 *
 *
 *
 */

#include "r_box.h"
#include "misc/simd.h"

void r_box(struct renderer* R, struct r_box* b)
{
	float v[4][2];
	unsigned short vi[6] = {0, 1, 2, 2, 1, 3};

	v2cpy(v[0], b->p);
	v2add(v[3], b->p, b->d);
	v2set(v[1], v[3][0], v[0][1]);
	v2set(v[2], v[0][0], v[3][1]);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, v);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, vi);
}
