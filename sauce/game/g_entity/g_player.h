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
 * g_player.h
 *
 *
 *
 *
 *
 */

#ifndef HAS_G_PLAYER_H
#define HAS_G_PLAYER_H

#include <stdbool.h>

#include "g_entity.h"
#include "misc/list.h"

struct g_player
{
#define G_PLAYER_FIELDS \
	G_ENTITY_FIELDS \
	unsigned long walk_dt;		/* for how long have we walked */ \
	float walk_v[2];		/* walk velocity */ \
	struct llist inventory;		/* list of player's items */ \

	G_PLAYER_FIELDS
};

void g_player_walk(struct g_player* e, float v[2]);
void g_player_frame(struct g_player* e, unsigned long dt);
int g_player_from_jason(
		struct g_player* e,
		char* jason,
		unsigned short* index
		);

#endif /* HAS_G_PLAYER_H */
