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
 * j0g2.h
 *
 *
 *
 *
 *
 */

#ifndef HAS_J0G2_H
#define HAS_J0G2_H

#include <stdlib.h>
#include "js0n.h"
#include "j0g.h"

/* NOTE: maybe use j0g_safe? */

#define js0nc(j, l, i, il) js0n((const unsigned char*) (j), (l), (i), (il))

#define SUBJASON_BEGIN(val, jason, index) \
{ \
	char* sjason; \
	unsigned slen; \
	sjason = jason + index[val];\
	slen = index[val+1]; \
	unsigned short sindex[slen]; \
	int js0n_r = js0nc(sjason, slen, sindex, slen); \
	(void) js0n_r

#define SUBJASON_END() \
}

#define SUBJASON_KEY_BEGIN(key, jason, index) \
{ \
	int val = j0g_val(key, jason, index); \
	SUBJASON_BEGIN(val, jason, index);

#define SUBJASON_KEY_END() \
	SUBJASON_END(); \
}

int j0g2_vec(
		float* v,
		unsigned n,
		const char* jason,
		unsigned short* index
		);
int j0g2_vec_malloc(
		unsigned* c,
		float** v,
		const char* jason,
		unsigned short* index
		);

#endif /* HAS_J0G2_H */
