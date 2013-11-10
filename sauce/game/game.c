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

/*
 *
 *
 *
 *
 * teh temp
 *
 *
 *
 *
 *
 */
static float identity[4][4] =
{
	{1, 0, 0, 0},
	{0, 1, 0, 0},
	{0, 0, 1, 0},
	{0, 0, 0, 1},
};

static struct g_player player[16];
static struct g_terrain terrain;

static void player_init(struct g_zawarudo* z)
{
	unsigned i;
	memset(player, 0, sizeof (player));

	for (i = 0; i < 16; ++i)
	{
		player[i].type = G_PLAYER;
		memcpy(player[i].T, identity, sizeof (identity));

		player[i].T[0][0] = .25;
		player[i].T[1][1] = .25;
		player[i].T[2][2] = .25;

		player[i].T[3][0] = -1.0 + .25 + .5 * (i%4);
		player[i].T[3][1] = -1.0 + .25 + .5 * (i/4);
		player[i].T[3][2] = 0;

		g_zawarudo_add(z, (struct g_entity*) &player[i]);
	}
}

static void terrain_init(struct g_zawarudo* z)
{
	memset(&terrain, 0, sizeof (terrain));

	terrain.type = G_DIRT;
	memcpy(terrain.T, identity, sizeof (identity));

	g_zawarudo_add(z, (struct g_entity*) &terrain);
}
/*
 *
 *
 *
 *
 * end of teh temp
 *
 *
 *
 *
 *
 */

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

	player_init(&g->zawarudo);
	terrain_init(&g->zawarudo);
	return 0;
}

