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
 * ui.c
 *
 *
 *
 *
 *
 */

#include <signal.h>
#include <assert.h>
#include <SDL.h>
#include "ui.h"
#include "ui_game.h"

#include "renderer/renderer.h"

static void ui_keydown(struct ui* ui, SDL_Keycode k)
{
	switch (k)
	{
	case SDLK_ESCAPE:
		ui->quit = true;
		return;
	}

	/* TODO: dispatch to focused component */
	ui_game_keydown(&ui->ui_g, k);
}

static void ui_keyup(struct ui* ui, SDL_Keycode k)
{
	/* TODO: dispatch to focused component */
	ui_game_keyup(&ui->ui_g, k);
}

static void ui_poll_events(struct ui* ui, unsigned long dt)
{
	SDL_Event ev;
	while (SDL_PollEvent(&ev))
	{
		switch(ev.type)
		{
		case SDL_KEYDOWN:
			ui_keydown(ui, ev.key.keysym.sym);
			break;

		case SDL_KEYUP:
			ui_keyup(ui, ev.key.keysym.sym);
			break;

		case SDL_QUIT:
			ui->quit = true;
			break;

		//default:
			//fprintf(stderr, "SDL_Event type = %d\n", ev.type);
		}
	}
}

void ui_frame(struct ui* ui, unsigned long dt)
{
	r_clear();
	ui_poll_events(ui, dt);
	ui_game_frame(&ui->ui_g, dt);
}

int ui_fini(struct ui* ui)
{
	return 0;
}

int ui_init(struct ui* ui, struct game* g)
{
	ui->g = g;
	ui->ui_g.g = g;
	return 0;
}

