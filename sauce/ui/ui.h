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
