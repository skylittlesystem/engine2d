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
 * g_zawarudo.c
 *
 *
 *
 *
 *
 */

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "g_zawarudo.h"
#include "game/g_entity/g_player.h"

#include "misc/mmath.h"
#include "misc/simd.h"

#define THICK .0000001

/*
 * Move entities on warudo
 *
 */
static void move_entities(struct g_zawarudo* z, float dt)
{
	/* every entity */
	struct llist_node* n1;
	for (n1 = z->entl.root; n1; n1 = n1->next)
	{
		struct g_entity* e1 = n1->ptr;

		/* skip if there is no motion! */
		if (e1->v[0] == 0 && e1->v[1] == 0)
			continue;

		do
		{
			float normal[2];
			bool hit;
			struct g_entity* e_hit;
			float t_hit;

			hit = false;
			t_hit = dt;

			/* FIXME: do something with this */
			(void) e_hit;

			/* and every entity, finding teh first collision */
			struct llist_node* n2;
			for (n2 = z->entl.root; n2; n2 = n2->next)
			{
				struct g_entity* e2 = n2->ptr;
				float t, n[2];

				/* except self */
				if (n2 == n1)
					continue;

				/* try collision */
				if (g_entity_collide(&t, n, e1, e2))
				{
					/* asd */
					if (t < 0)
						continue;

					/* make stuff thick */
					t += THICK / v2dprod(e1->v, n);

					/* this would have collided later */
					if (t >= t_hit)
						continue;

					hit = true;
					e_hit = e2;
					t_hit = t;
					v2cpy(normal, n);
				}
			}

			if (hit)
			{
				float teh_tan[2];
				v2set(teh_tan, -normal[1], normal[0]);
				v2lin(e1->p, e1->p, 1, e1->v, t_hit);
				v2sprod(e1->v, teh_tan, v2dprod(e1->v, teh_tan));
				continue; /* try again! */
			}

			v2lin(e1->p, e1->p, 1, e1->v, dt);
			break;
		} while (true);

	}
}

/*
 * make entities walk
 *
 */
static void walk_entities(struct g_zawarudo* z)
{
	/* every entity */
	struct llist_node* n;
	for (n = z->entl.root; n; n = n->next)
	{
		struct g_player* p = n->ptr;

		switch (p->type)
		{
		case G_PLAYER:
			v2cpy(p->v, p->walk_v);
		}
	}
}

void g_zawarudo_frame(struct g_zawarudo* z, unsigned long dt)
{
	float dt_ = ((float) dt) / 1000;

	walk_entities(z);
	move_entities(z, dt_);
}

struct llist* g_zawarudo_entl(struct g_zawarudo* z)
{
	return &z->entl;
}

void g_zawarudo_add(struct g_zawarudo* z, struct g_entity* e)
{
	e->id = z->next_id;
	++z->next_id;

	llist_push(&z->entl, e);
}

void g_zawarudo_remove(struct g_zawarudo* z, struct g_entity* e)
{
}

struct g_entity* g_zawarudo_find(struct g_zawarudo* z, unsigned id)
{
	struct llist_node* n;

	for (n = z->entl.root; n != NULL; n = n->next)
	{
#define e ((struct g_entity*) n->ptr)
		if (e->id == id)
			return e;

		/* ids are ascending */
		if (e->id > id)
			return NULL;
#undef e
	}

	return NULL;
}

