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

struct game teh_game;
struct ui teh_ui;

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
