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
#include "game/g_entity/g_terrain.h"
#include "misc/simd.h"

/*
 * keypress handling
 *
 */
static int dir_map(SDL_Keycode k)
{
	switch (k)
	{
	case SDLK_RIGHT:
		return 0;

	case SDLK_UP:
		return 1;

	case SDLK_LEFT:
		return 2;

	case SDLK_DOWN:
		return 3;
	}

	assert (false); /* oops */
	return -1;
}

void ui_game_keydown(struct ui_game* ui_g, SDL_Keycode k)
{
	switch (k)
	{
	case SDLK_RIGHT:
	case SDLK_LEFT:
	case SDLK_UP:
	case SDLK_DOWN:
		ui_g->player_walk[dir_map(k)] = true;
		break;
	}
}

void ui_game_keyup(struct ui_game* ui_g, SDL_Keycode k)
{
	switch (k)
	{
	case SDLK_RIGHT:
	case SDLK_LEFT:
	case SDLK_UP:
	case SDLK_DOWN:
		ui_g->player_walk[dir_map(k)] = false;
		break;
	}
}

/*
 * draw
 *
 */
#if 0
static void draw_inventory()
{
	/* TODO */
}
#endif

static void draw_entity(struct g_entity* e)
{
	struct g_terrain* terr;
	terr = (struct g_terrain*) e;

	r_pos2fv(e->p);
	switch (e->type)
	{
	case G_PLAYER:
		r_color4fv(r_red);
		r_boxxy(e->boxxy);
		break;

	case G_TERRAIN:
		r_color4fv(r_blue);
		r_boxxy(e->boxxy);
		r_color4fv(r_green);
		r_poly(terr->vertc, terr->vertv);
		break;

	case G_DIRT:
	case G_BRICKS:
	default:
		r_color4fv(r_green);
		r_boxxy(e->boxxy);
	}
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

/*
 * frame
 *
 */
void ui_game_frame(struct ui_game* ui_g, unsigned long dt)
{
	/* make player walk */
	float* v;

	if (ui_g->g->player)
	{
		float v[2];
		v2set(v, 0, 0);

		if (ui_g->player_walk[0])
			v[0] += 1;

		if (ui_g->player_walk[1])
			v[1] += 1;

		if (ui_g->player_walk[2])
			v[0] -= 1;

		if (ui_g->player_walk[3])
			v[1] -= 1;

		g_player_walk(ui_g->g->player, v);
	}

	ui_game_draw(ui_g);
}
