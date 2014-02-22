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
		float a1, float a2,
		float b1, float b2)
{
	/* those are necessary */
	assert (b1 <= b2);
	assert (a1 <= a2);

	/* both on left */
	if (a2 < b1)
		return false;

	/* both on right */
	if (b2 < a1)
		return false;

	(*c1) = max(a1, b1);
	(*c2) = min(a2, b2);
	return true;
}

static inline bool intersect2(
		float* restrict c1, float* restrict c2,
		float a1, float a2,
		float b1, float b2)
{
	/* this is a requirement */
	assert (b1 <= b2);

	/* reorder */
	if (a1 > a2)
		return intersect2(c1, c2, a2, a1, b1, b2);

	return intersect2(c1, c2, a1, a2, b1, b2);
}

static inline bool intersect(
		float* restrict c1, float* restrict c2,
		float a1, float a2,
		float b1, float b2)
{
	/* reorder */
	if (a1 > a2)
		return intersect2(c1, c2, a2, a1, b1, b2);

	return intersect2(c1, c2, a1, a2, b1, b2);
}

/*
 *
 *
 * axis aligned bounding box collision
 *
 *
 *
 */

static int cmp_tp(const float** a, const float** b)
{
	if ((**a) < (**b)) return -1;
	if ((**a) > (**b)) return 1;
	return 0; /* unlikely */
}

/*
 * Calculate teh first collision with b on a's path, if any, using axis-aligned
 * bounding boxes
 *
 */
static bool collide_aabb(
		unsigned* restrict dir_hit,	/* left, bottom, right, top */
		float* restrict t_hit,		/* time of collision */
		float* restrict a_pos,		/* a's position */
		struct g_boxxy* restrict a_box,	/* a's hit box */
		float* restrict b_pos,		/* b's position */
		struct g_boxxy* restrict b_box,	/* b's hit box */
		float* restrict a_vel,		/* a's velocity */
		float dt			/* time frame */
		)
{
	/* TODO: simd is easy and straightforward */
	int i;
	float t[4], * tp[4];
	float a[2][2], b[2][2];

	v2add(a[0], a_pos, a_box->p);
	v2add(b[0], b_pos, b_box->p);
	v2add(a[1], a[0], a_box->d);
	v2add(b[1], b[0], b_box->d);

	//fprintf(stderr, "a = {%f, %f}, {%f, %f}\n", a[0][0], a[0][1], a[1][0], a[1][1]);
	//fprintf(stderr, "b = {%f, %f}, {%f, %f}\n", b[0][0], b[0][1], b[1][0], b[1][1]);

	/* calculate collision time for left, bottom, right and top */
	v2sub(&t[0], b[1], a[0]);
	v2sub(&t[2], b[0], a[1]);
	v2div(&t[0], &t[0], a_vel);
	v2div(&t[2], &t[2], a_vel);

	//fprintf(stderr, "t = {%f, %f}, {%f, %f}\n", t[0], t[1], t[2], t[3]);

	/* and order ascending */
	tp[0] = &t[0];
	tp[1] = &t[1];
	tp[2] = &t[2];
	tp[3] = &t[3];

	qsort(tp, 4, sizeof (float*), (int(*)(const void*,const void*)) cmp_tp);

	//fprintf(stderr, "tp = {%f, %f, %f, %f}\n", *tp[0], *tp[1], *tp[2], *tp[3]);

	for (i = 0; i < 4; ++i)
	{
		unsigned j, k;
		float c1, c2, a_[2][2];

		/* convert to array index */
		j = (unsigned) (tp[i] - &t[0]);

		/* and validate result omg */
		switch (j)
		{
		/* left and right, check for y overlap */
		case 0:
		case 2:
			k = 1;
			break;

		/* bottom and top, check for x overlap */
		case 1:
		case 3:
			k = 0;
			break;

		/* wat */
		default:
			assert (false);
		}

		//fprintf(stderr, "it %d: t = %f\n", i, t[j]);

		/* collision rapens negative omg */
		if (t[j] < 0)
			continue;

		/* collision rapens after tiem */
		if (t[j] > dt)
			return false;

		/* check for overlap on line collision */
		v2lin(a_[0], a[0], 1, a_vel, t[j]);
		v2lin(a_[1], a[1], 1, a_vel, t[j]);

		assert (a_[0][k] <= a_[1][k]);
		assert (b[0][k] <= b[1][k]);

		if (intersect3(&c1, &c2, a_[0][k], a_[1][k], b[0][k], b[1][k]))
		{
			//fprintf(stderr, "HIT\n");
			(*t_hit) = t[j];
			return true;
		}
	}

	return false;
}

/*
 * Calculate teh first collision with e2 on e1's path, if any, using
 * axis-aligned bounding boxes
 *
 */
static bool collide_entities(
		float* restrict t_hit,		/* time of collision */
		struct g_entity* restrict e1,	/* entity 1 */
		struct g_entity* restrict e2,	/* entity 2 */
		float dt			/* time frame */
		)
{
#define v1 e1->v

#define p1 e1->p
#define b1 e1->boxxy

#define p2 e2->p
#define b2 e2->boxxy

	unsigned dir_hit;
	if (b1 && b2)
		if (collide_aabb(&dir_hit, t_hit, p1, b1, p2, b2, v1, dt))
			return true;

#undef b2
#undef p2

#undef b1
#undef p1

#undef v1
	return false;
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

		//fprintf(stderr, "ent %d: v = {%f, %f}\n", e1->id, e1->v[0], e1->v[1]);

		/* skip if there is no motion! */
		if (e1->v[0] == 0 && e1->v[1] == 0)
			continue;

		//fprintf(stderr, "ASD\n");

		do
		{
			bool hit = false;
			struct g_entity* e_hit;
			float t_hit = dt;

			/* FIXME: do something with this */
			(void) e_hit;

			/* and every entity */
			struct llist_node* n2;
			for (n2 = z->entl.root; n2; n2 = n2->next)
			{
				struct g_entity* e2 = n2->ptr;
				float t;

				/* except self */
				if (n2 == n1)
					continue;

				e2 = n2->ptr;

				/* try collision */
				if (collide_entities(&t, e1, e2, dt))
				{
					/* this would have collided later */
					if (t > t_hit)
						continue;

					hit = true;
					e_hit = e2;
					t_hit = t;
				}
			}

			if (hit)
			{
				v2lin(e1->p, e1->p, 1, e1->v, t_hit - 0.00001/v2len(e1->v));
				//v2set(e1->v, 0, 0);
				break;
			}

			v2lin(e1->p, e1->p, 1, e1->v, dt);
			break;
		} while (true);

	}
}

void g_zawarudo_frame(struct g_zawarudo* z, unsigned long dt)
{
	float dt_ = ((float) dt) / 1000;

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

