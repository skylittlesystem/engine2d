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
 * g_entity.h
 *
 *
 *
 *
 *
 */

#ifndef HAS_G_ENTITY_H
#define HAS_G_ENTITY_H

#include "../g_names.h"
#include "../g_box.h"

struct g_entity
{
#define G_ENTITY_FIELDS \
	unsigned type;		/* entity type */ \
	unsigned id;		/* unique identifier assigned by warudo */ \
	float pos[2];		/* position */ \
	float vel[2];		/* linear velocity */ \
	struct g_box* hit_box;	/* bounding box for collision */ \

	G_ENTITY_FIELDS
};

void g_entity_frame(struct g_entity* e, unsigned long dt);

#endif /* HAS_G_ENTITY_H */
