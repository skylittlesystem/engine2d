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

struct game teh_game;
struct ui teh_ui;

/******************************************************************************/

#define M_PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679

static float identity[4][4] =
{
	{1, 0, 0, 0},
	{0, 1, 0, 0},
	{0, 0, 1, 0},
	{0, 0, 0, 1},
};

static void make_polygon(struct r_polygon* s, unsigned n)
{
	unsigned i;
	float dw;

	memset(s, 0, sizeof(struct r_polygon));

	s->tric = n;
	s->vertc = n+1;

	s->triv = malloc(sizeof(unsigned short[n][3]));
	s->vertv = malloc(sizeof(float[n+1][2]));

	dw = (2 * M_PI) / n;
	s->vertv[0][0] = 0;
	s->vertv[0][1] = 0;
//	s->vertv[0][2] = 0;
//	s->vertv[0][3] = 1;
	for (i = 0; i < n; ++i)
	{
		s->vertv[i+1][0] = cos(i*dw);
		s->vertv[i+1][1] = sin(i*dw);
//		s->vertv[i+1][2] = 0;
//		s->vertv[i+1][3] = 1;
		s->triv[i][0] = 0;
		s->triv[i][1] = i + 1;
		s->triv[i][2] = ((i+1) % n) + 1;
	}
}

static void make_terrain_polygon(struct r_polygon* s)
{
	memset(s, 0, sizeof(struct r_polygon));

	s->tric = 4;
	s->vertc = 6;

	s->triv = malloc(sizeof(unsigned short[s->tric][3]));
	s->vertv = malloc(sizeof(float[s->vertc][2]));

	s->vertv[0][0] = -1;
	s->vertv[0][1] = -1;
	s->vertv[1][0] =  1;
	s->vertv[1][1] = -1;
	s->vertv[2][0] =  1;
	s->vertv[2][1] =  1;
	s->vertv[3][0] =   .7;
	s->vertv[3][1] = - .7;
	s->vertv[4][0] = - .7;
	s->vertv[4][1] = - .7;
	s->vertv[5][0] = -1;
	s->vertv[5][1] =  1;

	s->triv[0][0] = 0;
	s->triv[0][1] = 1;
	s->triv[0][2] = 3;
	s->triv[1][0] = 0;
	s->triv[1][1] = 3;
	s->triv[1][2] = 4;
	s->triv[2][0] = 0;
	s->triv[2][1] = 4;
	s->triv[2][2] = 5;
	s->triv[3][0] = 1;
	s->triv[3][1] = 2;
	s->triv[3][2] = 3;
}

static void add_entities(struct game* G)
{
	static struct g_player player;
	static struct g_terrain terrain;
	static struct r_polygon septagon, terrain_polygon;

	memset(&player, 0, sizeof (player));
	memset(&terrain, 0, sizeof (terrain));

	player.type = G_PLAYER;
	terrain.type = G_TERRAIN;

	memcpy(player.T, identity, sizeof(identity));
	memcpy(player.dT, identity, sizeof(identity));
	memcpy(terrain.T, identity, sizeof(identity));
	memcpy(terrain.dT, identity, sizeof(identity));

	/* move player 1 up */
	player.T[3][1] += .5;

	/* make player have 1/4 of it's size */
	player.T[0][0] *= .25;
	player.T[1][1] *= .25;
	player.T[2][2] *= .25;

	make_polygon(&septagon, 7);
	make_terrain_polygon(&terrain_polygon);

	player.poly = (struct g_polygon*) &septagon;
	terrain.poly = (struct g_polygon*) &terrain_polygon;

	g_add(G, (struct g_entity*) &player);
	g_add(G, (struct g_entity*) &terrain);
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
