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
 * ui_game.h
 *
 *
 *
 *
 *
 */

#ifndef HAS_UI_GAME_H
#define HAS_UI_GAME_H

#include <SDL.h>
#include "game/game.h"

struct ui_game
{
	struct game* g;

	bool player_walk[4];
};

void ui_game_keydown(struct ui_game* ui_g, SDL_Keycode k);
void ui_game_keyup(struct ui_game* ui_g, SDL_Keycode k);
void ui_game_frame(struct ui_game* ui_g, unsigned long dt);

#endif /* HAS_UI_GAME_H */
