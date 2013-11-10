/*
 *
 *
 *
 *
 * g_player.h
 *
 *
 *
 *
 *
 */

#ifndef HAS_G_PLAYER_H
#define HAS_G_PLAYER_H

#include "g_entity.h"

struct g_player
{
#define G_PLAYER_FIELDS \
	G_ENTITY_FIELDS \

	G_PLAYER_FIELDS
};

void g_player_move(struct g_player* e, float d[2]);
void g_player_look(struct g_player* e, float d[2]);
void g_player_frame(struct g_player* e, unsigned long dt);

#endif /* HAS_G_PLAYER_H */
