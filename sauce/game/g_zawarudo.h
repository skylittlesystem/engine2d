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
 * g_zawarudo.h
 *
 *
 *
 *
 *
 */

/* g_entity always should be included before this file! */
#include "g_entity/g_entity.h"

#ifndef HAS_G_ZAWARUDO_H
#define HAS_G_ZAWARUDO_H

#include "misc/list.h"

/* WRYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY!!!1!!11ONE! */
struct g_zawarudo
{
#define G_ZAWARUDO_FIELDS \
	struct llist entl; \
	unsigned next_id; \

	G_ZAWARUDO_FIELDS
};

void g_zawarudo_frame(struct g_zawarudo* z, unsigned long dt);
struct llist* g_zawarudo_entl(struct g_zawarudo* z);
void g_zawarudo_add(struct g_zawarudo* z, struct g_entity* e);
void g_zawarudo_remove(struct g_zawarudo* z, struct g_entity* e);
struct g_entity* g_zawarudo_find(struct g_zawarudo* z, unsigned id);

#endif /* HAS_G_ZAWARUDO_H */
