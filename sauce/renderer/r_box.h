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
 * r_box.h
 *
 *
 *
 *
 *
 */

#ifndef HAS_R_BOX_H
#define HAS_R_BOX_H

#include "renderer.h"
#include "game/g_boxxy.h"

struct r_box
{
#define R_BOX_FIELDS \
	G_BOX_FIELDS \

	R_BOX_FIELDS
};

void r_box(struct renderer* R, struct r_box* b);

#endif /* HAS_R_BOX_H */
