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
#include "g_zawarudo.h"

#include "misc/mmath.h"
#include "misc/simd.h"

static bool circle_collision(const float* a_b, const float* a_c, float r, float* restrict t)
{
	float A, B, C, delta, sqrt_delta;

	A = v2dprod(a_b, a_b); /* note that A is positive */
	B = v2dprod(a_b, a_c) * 2;
	C = v2dprod(a_c, a_c) - r*r;

	delta = (B*B - 4*A*C);
	if (delta < 0)
		return false;

	sqrt_delta = sqrt(delta);
	t[0] = (B - sqrt_delta)/(2*A);
	t[1] = (B + sqrt_delta)/(2*A);
	return true;
}

static bool line_collision(const float* a, const float* a_b, const float* n, const float d, float* restrict t)
{
	float A, B;

	A = v2dprod(a_b, n);
	if (A == 0)
		return false;

	B = d - v2dprod(a, n);
	(*t) = B/A;
	return true;
}

static bool polygon_collision(const float* a, const float* a_b, const float* polyT, struct g_polygon* poly, float* restrict t)
{
	float tmp;
	bool hit;
	register unsigned i;

	tmp = 0;
	(*t) = 666;
	hit = false;

	for (i = 0; i < poly->vertc; ++i)
	{
		float v[2], n[2], d;
		m4v2prod(v, polyT, poly->vertv[i]);
		m4v2prod_0(n, polyT, poly->normalv[i]);
		d = v2dprod(v, n);

		if (line_collision(a, a_b, n, d, &tmp))
		{
			if (tmp > 0)
			{
				hit = true;
				(*t) = fmin((*t), tmp);
			}
		}
	}

	return hit;
}

void g_zawarudo_frame(struct g_zawarudo* z, unsigned long dt)
{
	struct llist_node* n1, * n2;

	for (n1 = z->entl.root; n1 != NULL; n1 = n1->next)
	{
#define e1 ((struct g_entity*) n1->ptr)
#define e2 ((struct g_entity*) n2->ptr)
#define poly1 (e1->poly)
#define poly2 (e2->poly)
		e1->dT[3][1] = -.4;

		for (n2 = n1->next; n2 != NULL; n2 = n2->next)
		{
			float a[2], b[2], c[2], a_b[2], a_c[2], r, t[2];
			float t_max, t_run;
			float R[4][4];
			bool hit;
			(void) hit;

			m4v2prod(a, e1->T[0], poly1->bcir_p);
			m4v2prod(b, e1->dT[0], a);

			m4v2prod(c, e2->T[0], poly2->bcir_p);

			//r = poly1->bcir_r + poly2->bcir_r;
			r = .51;
			(void) r;

			v2sub(a_b, b, a);
			v2sub(a_c, c, a);

			t_max = ((float) dt) / 1000; /* seconds! */

#if 0
			if (circle_collision(a_b, a_c, r, t))
			{

				if (t[0] >= 0)
					t_run = min(t[0], t_max);

				else if (t[1] >= 0)
					t_run = min(t[1], t_max);

				else
					t_run = t_max;
			}

			else
			{
				t_run = t_max;
			}
#endif

			if (polygon_collision(a, a_b, e2->T[0], e2->poly, t))
				t_run = fmin(t[0], t_max);

			else
				t_run = t_max;

			hit = t_run < t_max;

			if (hit)
				t_run -= 0.0001;

			m4lerp(R[0], e1->T[0], e1->dT[0], t_run);
			m4cpy(e1->T[0], R[0]);
		}

		g_entity_frame(e1, dt);
#undef e2
#undef e1
	}
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

		/* ids are necessarily crescent */
		if (e->id > id)
			return NULL;
#undef e
	}

	return NULL;
}

