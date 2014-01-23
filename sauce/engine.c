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

#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <SDL.h>
#include "game/game.h"
#include "ui/ui.h"

#include "renderer/r_polygon.h"
#include "game/g_entity/g_player.h"
#include "game/g_entity/g_terrain.h"

#include "misc/mmath.h"
#include "misc/simd.h"

struct game teh_game;
struct ui teh_ui;

/******************************************************************************/

#define M_PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679

struct g_player p1, p2;
struct g_box box;

static void add_entities(struct game* G)
{
	v2set(box.p, -.25, -.25);
	v2set(box.d, .5, .5);

	p1.type = G_PLAYER;
	v2set(p1.pos, 0, -1);
	v2set(p1.vel, 0, 1);
	p1.hit_box = &box;

	p2.type = G_PLAYER;
	v2set(p2.pos, 0, 1);
	v2set(p2.vel, 0, -1);
	p2.hit_box = &box;

	g_add(G, (struct g_entity*) &p1);
	g_add(G, (struct g_entity*) &p2);
}

/******************************************************************************/

static void cleanup()
{
	fprintf(stderr, "Cleaning up!\n");
	ui_fini(&teh_ui);
	g_fini(&teh_game);
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

	g_init(&teh_game);
	ui_init(&teh_ui, &teh_game);

	add_entities(&teh_game);

	t1 = SDL_GetTicks();
	do {
		t2 = SDL_GetTicks();
		dt = t2 - t1;

		g_frame(&teh_game, dt);
		ui_frame(&teh_ui, dt);

		t1 = t2;
	} while (!ui_should_quit(&teh_ui));

	ui_fini(&teh_ui);
	g_fini(&teh_game);

	return 0;
}
