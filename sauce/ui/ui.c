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

static void ui_poll_events(struct ui* ui, unsigned long dt)
{
	SDL_Event ev;
	while (SDL_PollEvent(&ev))
	{
		switch(ev.type)
		{
		case SDL_KEYDOWN:
			if (ev.key.keysym.sym != SDLK_ESCAPE)
				continue;

		case SDL_QUIT:
			ui->quit = true;

		default:
			//fprintf(stderr, "SDL_Event type = %d\n", ev.type);
			break;
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

