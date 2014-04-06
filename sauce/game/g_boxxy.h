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
 * g_boxxy.h
 *
 *
 *
 *
 *
 */

#ifndef HAS_G_BOXXY_H
#define HAS_G_BOXXY_H

/* my name is boxxy */
struct g_boxxy
{
#define G_BOX_FIELDS \
	float p[2]; /* position */ \
	float d[2]; /* dimensions */ \

	G_BOX_FIELDS
};

#endif /* HAS_G_BOXXY_H */