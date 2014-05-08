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

/*
 *
 *
 * intersection routines
 *
 *
 *
 */

static inline bool intersect3(
		float* restrict c1, float* restrict c2,
		float* restrict a1, float* restrict a2,
		float* restrict b1, float* restrict b2)
{
	/* don't change to <=, since inf <= inf yields false */
	assert (!(a1 > a2));
	assert (!(b1 > b2));

	/* both on left */
	if ((*a2) < (*b1))
		return false;

	/* both on right */
	if ((*b2) < (*a1))
		return false;

	(*c1) = max((*a1), (*b1));
	(*c2) = min((*a2), (*b2));
	return true;
}

static inline bool intersect2(
		float* restrict c1, float* restrict c2,
		float* restrict a1, float* restrict a2,
		float* restrict b1, float* restrict b2)
{
	/* don't change to <=, since inf <= inf yields false */
	assert (!(a1 > a2));

	/* reorder */
	if ((*b1) > (*b2))
	{
		float tmp;
		tmp = (*b1);
		(*b1) = (*b2);
		(*b2) = tmp;
	}

	return intersect3(c1, c2, a1, a2, b1, b2);
}

static inline bool intersect(
		float* restrict c1, float* restrict c2,
		float* restrict a1, float* restrict a2,
		float* restrict b1, float* restrict b2)
{
	/* reorder */
	if ((*a1) > (*a2))
	{
		float tmp;
		tmp = (*a1);
		(*a1) = (*a2);
		(*a2) = tmp;
	}

	return intersect2(c1, c2, a1, a2, b1, b2);
}

#define THICK .0000001

/*
 *
 *
 * axis aligned bounding boxxy collision
 *
 *
 *
 */

/*
 * Calculate teh first collision with b on a's path, if any, using axis-aligned
 * bounding boxxys
 *
 */
static bool sweep_aabb(
		float* restrict t_,		/* collision time */
		float* restrict n,		/* collision normal */
		float (*restrict a)[2],		/* a's AABB */
		float (*restrict b)[2],		/* b's AABB */
		float* restrict v		/* a's velocity */
		)
{
	float t_in, t_out, t[2][2];

	v2sub(t[0], b[0], a[1]);
	v2sub(t[1], b[1], a[0]);
	/* TODO: can we really expect INFINITY on division by zero? */
	v2div(t[0], t[0], v);
	v2div(t[1], t[1], v);

	if (!intersect(&t_in, &t_out, &t[0][0], &t[1][0], &t[0][1], &t[1][1]))
		return false;

	v2set(n, 1, 1);

	/* horizontal */
	if (t[0][1] < t_in)
		v2set(n, -copysignf(1, v[0]), 0);

	/* vertical */
	else if (t[0][0] < t_in)
		v2set(n, 0, -copysignf(1, v[1]));

#define L 0.70710678118654752440084436210485
	/* teh fucking corner */
	else
		v2set(n, -copysignf(L, v[0]), -copysignf(L, v[1]));
#undef L

	(*t_) = t_in;
	return true;
}

/*
 * Calculate teh first collision with e2 on e1's path, if any, using
 * axis-aligned bounding boxxys
 *
 */
static float sweep_entities(
		float* restrict t,		/* collision time */
		float* restrict n,		/* collision normal */
		struct g_entity* restrict ea,	/* entity a */
		struct g_entity* restrict eb	/* entity b */
		)
{
	float a[2][2], b[2][2];

	v2add(a[0], ea->p, ea->boxxy[0]);
	v2add(a[1], a[0], ea->boxxy[1]);
	v2add(b[0], eb->p, eb->boxxy[0]);
	v2add(b[1], b[0], eb->boxxy[1]);

	return sweep_aabb(t, n, a, b, ea->v);
}

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
				if (sweep_entities(&t, n, e1, e2))
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

