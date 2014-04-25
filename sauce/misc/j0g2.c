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
		int val,
		const char* jason,
		unsigned short* index
		)
{
	int i;
	const char* sjason;
	unsigned short sindex[2*n+1];

	sjason = jason + index[val];

	i = js0n((const unsigned char*) sjason, index[val+1], sindex, 2*n+1);

	if (i) return i;

	for (i = 0; i < n && sindex[2*i]; ++i)
		v[i] = j0g2_flt(2*i, sjason, sindex);

	if (i < n) return -1;

	return 0;
}

