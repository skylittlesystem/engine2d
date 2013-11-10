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

#include "renderer/renderer.h"
#include "game/game.h"

struct ui_game
{
	struct renderer* R;
	struct game* g;
};

void ui_game_frame();

#endif /* HAS_UI_GAME_H */
