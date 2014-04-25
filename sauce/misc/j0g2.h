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
#include "j0g.h"

/* NOTE: maybe use j0g_safe? */

#define j0g2_pt(v, j, i) &(j)[i[v]]
#define j0g2_flt(v, j, i) strtof(j0g2_pt(v, j, i), NULL)

#define j0g2k_pt(k, j, i) j0g2_pt(j0g_val(k, j, i), j, i)
#define j0g2k_flt(k, j, i) j0g2_flt(j0g_val(k, j, i), j, i)
#define j0g2k_vec(x, n, k, j, i) j0g2_vec(x, n, j0g_val(k, j, i), j, i)

int j0g2_vec(
		float* v,
		unsigned n,
		int val,
		const char* jason,
		unsigned short* index
		);

#endif /* HAS_J0G2_H */
