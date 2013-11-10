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
#include "ui.h"
#include "ui_game.h"

#include "renderer/renderer.h"

static void ui_ctrl_frame(struct ui* ui, unsigned long dt)
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
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	ui_ctrl_frame(ui, dt);
	ui_game_frame(&ui->ui_g, dt);

	SDL_GL_SwapWindow(ui->window);
}

int ui_fini(struct ui* ui)
{
	r_fini(&ui->R);
	SDL_Quit();
	return 0;
}

int ui_init(struct ui* ui, struct game* g)
{
	ui->g = g;
	ui->ui_g.g = g;
	ui->ui_g.R = &ui->R;

	SDL_Init(SDL_INIT_EVERYTHING);

#define W 1024
#define H 768

	ui->window = SDL_CreateWindow("!!!11!1!!1ONE!!",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			W, H,
			SDL_WINDOW_OPENGL
			);

	if (!ui->window)
		fprintf(stderr, "SDL_GetError(): %s\n", SDL_GetError());

	assert (ui->window); /* TODO: proper handling */

	ui->gl_context = SDL_GL_CreateContext(ui->window);

	if (!ui->gl_context)
		fprintf(stderr, "SDL_GetError(): %s\n", SDL_GetError());

	assert (ui->gl_context); /* TODO: proper handling */

	glViewport(0, 0, W, H);
	r_init(&ui->R);

	return 0;
}

