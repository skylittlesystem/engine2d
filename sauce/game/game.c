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
 * game.c
 *
 *
 *
 *
 *
 */

#include <string.h>
#include "game.h"
#include "g_entity/g_player.h"
#include "g_entity/g_terrain.h"

void g_frame(struct game* g, unsigned long dt)
{
	g_zawarudo_frame(&g->zawarudo, dt);
}

int g_fini(struct game* g)
{
	return 0;
}

int g_init(struct game* g)
{
	memset(g, 0, sizeof (struct game));
	return 0;
}
