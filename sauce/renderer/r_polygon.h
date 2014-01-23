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
 * r_polygon.h
 *
 *
 *
 *
 *
 */

#ifndef HAS_R_POLYGON_H
#define HAS_R_POLYGON_H

#include "renderer.h"
#include "game/g_polygon.h"

struct r_polygon
{
#define R_POLYGON_FIELDS \
	G_POLYGON_FIELDS \
	unsigned tric; \
	unsigned short (*triv)[3]; \

	R_POLYGON_FIELDS
};

void r_polygon(struct renderer* R, struct r_polygon* p);

#endif /* HAS_R_POLYGON_H */
