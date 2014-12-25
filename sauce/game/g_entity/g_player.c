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
 * g_player.c
 *
 *
 *
 *
 *
 */

#include <stdio.h>
#include "g_player.h"

#include "misc/simd.h"

void g_player_walk(struct g_player* e, float v[2])
{
	/* limit walk velocity */
	if (v2len(v) > 1)
		v2sprod(v, v, 1.0/v2len(v));

	v2cpy(e->walk_v, v);
}

void g_player_frame(struct g_player* e, unsigned long dt)
{
	if (v2len(e->walk_v) == 0)
		e->walk_dt = 0;
	else
		e->walk_dt += dt;
}

int g_player_from_jason(
		struct g_player* e,
		char* jason,
		unsigned short* index
		)
{
	int r;
	r = g_entity_from_jason((struct g_entity*) e, jason, index);

	if (r)
		return r;

	e->type = G_PLAYER;
	return 0;
}
