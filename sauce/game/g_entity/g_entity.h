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
#include "../g_box.h"

struct g_entity
{
#define G_ENTITY_FIELDS \
	unsigned type;		/* entity type */ \
	unsigned id;		/* unique identifier assigned by warudo */ \
	float pos[2];		/* position */ \
	float vel[2];		/* linear velocity */ \
	struct g_box* hit_box;	/* bounding box for collision */ \

	G_ENTITY_FIELDS
};

void g_entity_frame(struct g_entity* e, unsigned long dt);

#endif /* HAS_G_ENTITY_H */
