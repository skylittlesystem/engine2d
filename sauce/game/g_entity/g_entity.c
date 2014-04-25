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
 * g_entity.c
 *
 *
 *
 *
 *
 */

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "g_entity.h"
#include "g_player.h"
#include "g_terrain.h"

#include "misc/j0g2.h"

void g_entity_frame(struct g_entity* e, unsigned long dt)
{
	switch (e->type)
	{
	case G_PLAYER:
		g_player_frame((struct g_player*) e, dt);
		break;

	case G_TERRAIN:
	case G_DIRT:
	case G_BRICKS:
		g_terrain_frame((struct g_terrain*) e, dt);
		break;

	default:
		assert (false);
	}
}

int g_entity_from_jason(
		struct g_entity* e,
		char* jason,
		unsigned short* index
		)
{
	j0g2k_vec(e->p, 2, "p", jason, index);
	j0g2k_vec(&e->boxxy[0][0], 4, "boxxy", jason, index);

	fprintf(stderr, "p: %G, %G\n", e->p[0], e->p[1]);
	fprintf(stderr, "boxxy: %G, %G, %G, %G\n",
			e->boxxy[0][0],
			e->boxxy[0][1],
			e->boxxy[1][0],
			e->boxxy[1][1]);
	return 0;
}

void g_entity_init(struct g_entity* e)
{
	memset(e, 0, sizeof (struct g_entity));
}
