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

void g_player_move(struct g_player* e, float d[2])
{
	/* TODO */
}

void g_player_look(struct g_player* e, float d[2])
{
	/* TODO */
}

void g_player_frame(struct g_player* e, unsigned long dt)
{
	//fprintf(stderr, "=oplayer %d framing!!1!11ONE!\n", e->id);
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
