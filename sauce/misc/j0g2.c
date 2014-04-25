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
 * j0g2.c
 *
 *
 *
 *
 *
 */

#include <stdio.h>

#include "js0n.h"
#include "j0g2.h"

/* NOTE: maybe use j0g_safe? */

int j0g2_vec(
		float* v,
		unsigned n,
		const char* jason,
		unsigned short* index
		)
{
	unsigned short* i;

	for (i = index; n > 0 && (*i); --n, i += 2)
		(*(v++)) = strtof(jason + (*i), NULL);

	return n;
}

int j0g2_vec_malloc(
		unsigned* c,
		float** v,
		const char* jason,
		unsigned short* index
		)
{
	unsigned short* i;

	for (i = index; (*i); ++(*c), i += 2);
	(*v) = malloc(sizeof (float) * (*c));
	return j0g2_vec((*v), (*c), jason, index);
}
