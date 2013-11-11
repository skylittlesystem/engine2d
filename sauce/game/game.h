/*
 *
 *
 *
 *
 * game.h
 *
 *
 *
 *
 *
 */

#ifndef HAS_GAME_H
#define HAS_GAME_H

#include "g_zawarudo.h"

struct game
{
#define GAME_FIELDS \
	struct g_zawarudo zawarudo;

	GAME_FIELDS
};

void g_frame(struct game* g, unsigned long dt);
int g_fini(struct game* g);
int g_init(struct game* g);
#define g_entl(g) g_zawarudo_entl(&(g)->zawarudo)
#define g_add(g, e) g_zawarudo_add(&(g)->zawarudo, (e))
#define g_remove(g, e) g_zawarudo_remove(&(g)->zawarudo, (e))
#define g_find(g, id) g_zawarudo_find(&(g)->zawarudo, (id))

#if GAME_H_INTERNALS

#endif /* if GAME_H_INTERNALS */

#endif /* HAS_GAME_H */
