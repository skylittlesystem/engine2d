/*
 *
 *
 *
 *
 * g_zawarudo.h
 *
 *
 *
 *
 *
 */

#ifndef HAS_G_ZAWARUDO_H
#define HAS_G_ZAWARUDO_H

#include "g_entity/g_entity.h"
#include "misc/list.h"

/* WRYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY!!!1!!11ONE! */
struct g_zawarudo
{
#define G_ZAWARUDO_FIELDS \
	struct llist entl; \
	unsigned next_id; \

	G_ZAWARUDO_FIELDS
};

void g_zawarudo_frame(struct g_zawarudo* z, unsigned long dt);
struct llist* g_zawarudo_entl(struct g_zawarudo* z);
void g_zawarudo_add(struct g_zawarudo* z, struct g_entity* e);
void g_zawarudo_remove(struct g_zawarudo* z, struct g_entity* e);
struct g_entity* g_zawarudo_find(struct g_zawarudo* z, unsigned id);

#endif /* HAS_G_ZAWARUDO_H */
