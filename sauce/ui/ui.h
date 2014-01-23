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
 * ui.h
 *
 *
 *
 *
 *
 */

#ifndef HAS_UI_H
#define HAS_UI_H

#include <stdbool.h>
#include <SDL.h>

#include "game/game.h"
#include "ui_game.h"
#include "renderer/renderer.h"

struct ui
{
	bool quit;

	SDL_Window* window;
	SDL_GLContext gl_context;

	struct renderer R;
	struct game* g;
	struct ui_game ui_g;
};

#define ui_should_quit(ui) ((ui)->quit)
void ui_frame(struct ui* ui, unsigned long dt);
int ui_fini(struct ui* ui);
int ui_init(struct ui* ui, struct game* g);

#endif /* HAS_UI_H */
