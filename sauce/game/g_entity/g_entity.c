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

#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "g_entity.h"
#include "g_player.h"
#include "g_terrain.h"

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

void g_entity_init(struct g_entity* e)
{
	memset(e, 0, sizeof (struct g_entity));
}
