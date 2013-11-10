/*
 *
 *
 *
 *
 * g_entity.c
 *
 *
 *
 *
 *
 */

#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "g_entity.h"
#include "g_player.h"
#include "g_terrain.h"

void g_entity_frame(struct g_entity* e, unsigned long dt)
{
	switch (e->type)
	{
	case G_PLAYER:
		g_player_frame((struct g_player*) e, dt);
		break;

	case G_DIRT:
	case G_BRICKS:
		g_terrain_frame((struct g_terrain*) e, dt);
		break;

	default:
		assert (false);
	}
}

void g_entity_init(struct g_entity* e)
{
	memset(e, 0, sizeof (struct g_entity));
}
