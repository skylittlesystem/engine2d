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

#include <stdbool.h>
#include "../g_names.h"

struct g_entity
{
#define G_ENTITY_FIELDS \
	unsigned type;		/* entity type */ \
	unsigned id;		/* unique identifier assigned by warudo */ \
	float p[2];		/* position */ \
	float v[2];		/* velocity */ \
	float boxxy[2][2];	/* bounding box for collision */ \

	G_ENTITY_FIELDS
};

/* must come after g_entity definition! */
#include "../g_zawarudo.h"

bool g_entity_collide(
		float* restrict t,		/* collision time */
		float* restrict n,		/* collision normal */
		struct g_entity* e1,		/* entity 1 */
		struct g_entity* e2		/* entity 2 */
		);

void g_entity_frame(struct g_entity* e, struct g_zawarudo* z, unsigned long dt);

int g_entity_from_jason(
		struct g_entity* e,
		char* jason,
		unsigned short* index
		);

#endif /* HAS_G_ENTITY_H */
