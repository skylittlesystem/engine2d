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

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "g_entity.h"
#include "g_player.h"
#include "g_terrain.h"

#include "misc/j0g2.h"

#include "misc/mmath.h"
#include "misc/simd.h"

/*
 * collision
 *
 */

/* 1d intersection, a and b sorted */
static inline bool intersect3(
		float* restrict c1, float* restrict c2,
		float* restrict a1, float* restrict a2,
		float* restrict b1, float* restrict b2)
{
	/* don't change to <=, since inf <= inf yields false */
	assert (!(a1 > a2));
	assert (!(b1 > b2));

	/* both on left */
	if ((*a2) <= (*b1))
		return false;

	/* both on right */
	if ((*b2) <= (*a1))
		return false;

	(*c1) = max((*a1), (*b1));
	(*c2) = min((*a2), (*b2));
	return true;
}

/* 1d intersection, a sorted */
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

/* 1d intersection */
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

/* collide aabb with raytracing */
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
 * collision solver
 *
 */
bool g_entity_collide(
		float* restrict t,		/* collision time */
		float* restrict n,		/* collision normal */
		struct g_entity* e1,		/* entity 1 */
		struct g_entity* e2		/* entity 2 */
		)
{
	float a[2][2], b[2][2], v[2];

	v2add(a[0], e1->p, e1->boxxy[0]);
	v2add(a[1], a[0], e1->boxxy[1]);
	v2add(b[0], e2->p, e2->boxxy[0]);
	v2add(b[1], b[0], e2->boxxy[1]);

	v2cpy(v, e1->v);
	v2sub(v, v, e2->v);

	return sweep_aabb(t, n, a, b, v);
}

/*
 * frame
 *
 */
void g_entity_frame(struct g_entity* e, struct g_zawarudo* z, unsigned long dt)
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

int g_entity_from_jason(
		struct g_entity* e,
		char* jason,
		unsigned short* index
		)
{
	SUBJASON_KEY_BEGIN("p", jason, index);
	j0g2_vec(e->p, 2, sjason, sindex);
	SUBJASON_KEY_END();
	fprintf(stderr, "p: %G, %G\n", e->p[0], e->p[1]);

	SUBJASON_KEY_BEGIN("boxxy", jason, index);
	j0g2_vec(e->boxxy[0], 4, sjason, sindex);
	SUBJASON_KEY_END();
	fprintf(stderr, "boxxy: %G, %G, %G, %G\n",
			e->boxxy[0][0],
			e->boxxy[0][1],
			e->boxxy[1][0],
			e->boxxy[1][1]);

	return 0;
}

void g_entity_init(struct g_entity* e)
{
	memset(e, 0, sizeof (struct g_entity));
}
