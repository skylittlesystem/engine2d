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
 * engine.c
 *
 *
 *
 *
 *
 */

#include <assert.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <SDL.h>
#include "game/game.h"
#include "ui/ui.h"
#include "renderer/renderer.h"

#include "game/g_entity/g_player.h"
#include "game/g_entity/g_terrain.h"

#include "misc/mmath.h"
#include "misc/simd.h"

static struct game teh_game;
static struct ui teh_ui;


/******************************************************************************/

#define M_PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679

struct g_player p1, p2;
struct g_terrain t1, t2;

static void add_entities(struct game* g)
{
	memset(&p1, 0, sizeof (p1));
	memset(&p2, 0, sizeof (p2));
	memset(&t1, 0, sizeof (t1));
	memset(&t2, 0, sizeof (t2));

	v2set(p2.boxxy[0], -.25, -.25);
	v2set(p2.boxxy[1], .5, .5);
	memcpy(t1.boxxy, p2.boxxy, sizeof (t1.boxxy));
	memcpy(t2.boxxy, p2.boxxy, sizeof (t2.boxxy));

	v2set(p1.boxxy[0], -.24, -.24);
	v2set(p1.boxxy[1], .48, .48);

	p1.type = G_PLAYER;
	v2set(p1.p, 0, -1);
	v2set(p1.v, 0, 1);

	p2.type = G_PLAYER;
	v2set(p2.p, 0, 1);
	v2set(p2.v, 0, -1);

	t1.type = G_TERRAIN;
	v2set(t1.p, 1, 1);

	t2.type = G_TERRAIN;
	v2set(t2.p, 0, 0);

	g_add_player(g, (struct g_player*) &p1);
	g_add(g, (struct g_entity*) &p2);
	g_add(g, (struct g_entity*) &t1);
	g_add(g, (struct g_entity*) &t2);
}

/******************************************************************************/

/*
 * SDL stuff
 *
 */
SDL_Window* window;
SDL_GLContext gl_context;

static int sdl_fini()
{
	SDL_Quit();
	return 0;
}

static int sdl_init()
{
	SDL_Init(SDL_INIT_EVERYTHING);

#define W 1024
#define H 768

	window = SDL_CreateWindow("!!!11!1!!1ONE!!",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			W, H,
			SDL_WINDOW_OPENGL
			);

	if (!window)
		fprintf(stderr, "SDL_GetError(): %s\n", SDL_GetError());

	assert (window); /* TODO: proper handling */

	gl_context = SDL_GL_CreateContext(window);

	if (!gl_context)
		fprintf(stderr, "SDL_GetError(): %s\n", SDL_GetError());

	assert (gl_context); /* TODO: proper handling */

	return 0;
}

/*
 * signal handling
 *
 */
static void cleanup()
{
	fprintf(stderr, "Cleaning up!\n");
	ui_fini(&teh_ui);
	g_fini(&teh_game);
	r_fini();
	sdl_fini();
}

static void sigh(int signo)
{
	fprintf(stderr, "Caught signal %d.\n", signo);
	cleanup();
	fprintf(stderr, "Exitting with status -1...\n");
	_Exit(-1);

	/* raise signal again and let default action take place */
	//signal(signo, SIG_DFL);
	//raise(signo);
}

static void sigh_install(int signo)
{
	if (signal(signo, sigh) == SIG_ERR)
	{
		fputs("Phailed to install signal handler!\n", stderr);
		exit(-1);
	}
}

/*
 * Teh main function!!11!1ONE
 *
 */
int main(int argc, char *argv[])
{
	unsigned long t1, t2, dt;

	sigh_install(SIGABRT);
	sigh_install(SIGSEGV);

	sdl_init();
	r_init();
	g_init(&teh_game);
	ui_init(&teh_ui, &teh_game);

	/* FIXME: remove this */
	add_entities(&teh_game);

	t1 = SDL_GetTicks();
	do {
		t2 = SDL_GetTicks();
		dt = t2 - t1;

		g_frame(&teh_game, dt);
		ui_frame(&teh_ui, dt);

		SDL_GL_SwapWindow(window);

		t1 = t2;
	} while (!ui_should_quit(&teh_ui));

	cleanup();

	return 0;
}
