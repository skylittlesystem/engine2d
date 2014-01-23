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
 * game.h
 *
 *
 *
 *
 *
 */

#ifndef HAS_GAME_H
#define HAS_GAME_H

#include "g_zawarudo.h"

struct game
{
#define GAME_FIELDS \
	struct g_zawarudo zawarudo;

	GAME_FIELDS
};

void g_frame(struct game* g, unsigned long dt);
int g_fini(struct game* g);
int g_init(struct game* g);
#define g_entl(g) g_zawarudo_entl(&(g)->zawarudo)
#define g_add(g, e) g_zawarudo_add(&(g)->zawarudo, (e))
#define g_remove(g, e) g_zawarudo_remove(&(g)->zawarudo, (e))
#define g_find(g, id) g_zawarudo_find(&(g)->zawarudo, (id))

#if GAME_H_INTERNALS

#endif /* if GAME_H_INTERNALS */

#endif /* HAS_GAME_H */
