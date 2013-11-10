/*
 *
 *
 *
 *
 * g_entity.h
 *
 *
 *
 *
 *
 */

#ifndef HAS_G_ENTITY_H
#define HAS_G_ENTITY_H

#include "../g_names.h"

struct g_entity
{
#define G_ENTITY_FIELDS \
	unsigned type;		/* entity type */ \
	unsigned id;		/* unique identifier assigned by warudo */ \
	float T[4][4];		/* transform matrix */ \
	float dT[4][4];		/* transform rate of change (with time) */ \

	G_ENTITY_FIELDS
};

void g_entity_frame(struct g_entity* e, unsigned long dt);

#endif /* HAS_G_ENTITY_H */
