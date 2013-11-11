/*
 *
 *
 *
 *
 * game.c
 *
 *
 *
 *
 *
 */

#include <string.h>
#include "game.h"
#include "g_entity/g_player.h"
#include "g_entity/g_terrain.h"

void g_frame(struct game* g, unsigned long dt)
{
	g_zawarudo_frame(&g->zawarudo, dt);
}

int g_fini(struct game* g)
{
	return 0;
}

int g_init(struct game* g)
{
	memset(g, 0, sizeof (struct game));
	return 0;
}
