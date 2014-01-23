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
 * g_polygon.h
 *
 *
 *
 *
 *
 */

#ifndef HAS_G_POLYGON_H
#define HAS_G_POLYGON_H

/* note on vertices and normals:
 * vertices must be in counter-clockwise order and normals must be exterior!
 */
struct g_polygon
{
#define G_POLYGON_FIELDS \
	unsigned short vertc; /* number of vertices */ \
	float (*vertv)[2]; /* vertices */ \
	float (*normalv)[2]; /* vertices */ \
	float (*pdistv); /* plane distances */ \
	float bbox[2][2]; /* bounding box */ \
	float bcir_p[2]; /* bounding circle position */ \
	float bcir_r; /* bounding circle radius */

	G_POLYGON_FIELDS
};

#endif /* HAS_G_POLYGON_H */
