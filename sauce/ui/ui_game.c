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

#include "renderer/renderer.h"
#include "renderer/r_game.h"
#include "ui_game.h"
#include "game/g_entity/g_player.h"
#include "misc/simd.h"

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
	r_boxxy(e->boxxy);
}

#if 0
static void draw_zawarudo(struct g_zawarudo* z)
{
	/* TODO */
}
#endif

void ui_game_keydown(struct ui_game* ui_g, SDL_Keycode k)
{
	struct g_player* p = ui_g->g->player;

	switch (k)
	{
	case SDLK_LEFT:
		p->try_walk = true;
		v2set(p->walk_dir, -1, 0);
		return;

	case SDLK_RIGHT:
		p->try_walk = true;
		v2set(p->walk_dir, 1, 0);
		return;
	}
}

void ui_game_keyup(struct ui_game* ui_g, SDL_Keycode k)
{
	struct g_player* p = ui_g->g->player;

	switch (k)
	{
	case SDLK_LEFT:
	case SDLK_RIGHT:
		/* FIXME: this is buggy */
		p->try_walk = false;
		return;
	}
}

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
