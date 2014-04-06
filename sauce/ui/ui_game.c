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
 * ui_game.c
 *
 *
 *
 *
 *
 */

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#include "ui_game.h"
#include "game/g_entity/g_player.h"
#include "misc/simd.h"

static void draw_boxxy(struct g_boxxy* b)
{
	float v[4][2];
	unsigned short vi[6] = {0, 1, 2, 2, 1, 3};

	v2cpy(v[0], b->p);
	v2add(v[3], b->p, b->d);
	v2set(v[1], v[3][0], v[0][1]);
	v2set(v[2], v[0][0], v[3][1]);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, v);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, vi);
}

#if 0
static void draw_inventory()
{
	/* TODO */
}
#endif

static void draw_entity(struct g_entity* e)
{
	r_pos2fv(e->p);
	switch (e->type)
	{
	case G_PLAYER:
		r_color4fv(r_red);
		break;
	case G_TERRAIN:
	case G_DIRT:
	case G_BRICKS:
	default:
		r_color4fv(r_green);
	}
	draw_boxxy(e->boxxy);
}

#if 0
static void draw_zawarudo(struct g_zawarudo* z)
{
	/* TODO */
}
#endif

void ui_game_draw(struct ui_game* ui_g)
{

	struct game* g;
	struct llist* entl;
	struct llist_node* n;
	g = ui_g->g;

	entl = g_entl(g);

	for (n = entl->root; n != NULL; n = n->next)
		draw_entity((struct g_entity*) n->ptr);
}

void ui_game_frame(struct ui_game* ui_g, unsigned long dt)
{
	ui_game_draw(ui_g);
}
