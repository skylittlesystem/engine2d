/*
 *
 *
 *
 *
 * g_terrain.h
 *
 *
 *
 *
 *
 */

#ifndef HAS_G_TERRAIN_H
#define HAS_G_TERRAIN_H

#include "g_entity.h"

struct g_terrain
{
#define G_TERRAIN_FIELDS \
	G_ENTITY_FIELDS \
	unsigned vertc;		/* vertex count */ \
	float (*vertv)[2];	/* vertices */ \
	
	G_TERRAIN_FIELDS
};

void g_terrain_frame(struct g_terrain* ter, unsigned long dt);

#endif /* HAS_G_TERRAIN_H */
