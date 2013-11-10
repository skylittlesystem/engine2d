/*
 *
 *
 *
 *
 * g_zawarudo.c
 *
 *
 *
 *
 *
 */

#include <stdio.h>
#include <string.h>
#include "g_zawarudo.h"

void g_zawarudo_frame(struct g_zawarudo* z, unsigned long dt)
{
	struct llist_node* n;

	for (n = z->entl.root; n != NULL; n = n->next)
	{
#define e ((struct g_entity*) n->ptr)
		g_entity_frame(e, dt);
#undef e
	}
}

struct llist* g_zawarudo_entl(struct g_zawarudo* z)
{
	return &z->entl;
}

void g_zawarudo_add(struct g_zawarudo* z, struct g_entity* e)
{
	e->id = z->next_id;
	++z->next_id;

	llist_push(&z->entl, e);
}

void g_zawarudo_remove(struct g_zawarudo* z, struct g_entity* e)
{
}

struct g_entity* g_zawarudo_find(struct g_zawarudo* z, unsigned id)
{
	struct llist_node* n;

	for (n = z->entl.root; n != NULL; n = n->next)
	{
#define e ((struct g_entity*) n->ptr)
		if (e->id == id)
			return e;

		/* ids are necessarily crescent */
		if (e->id > id)
			return NULL;
#undef e
	}

	return NULL;
}

