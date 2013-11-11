/*
 *
 *
 *
 *
 * r_polygon.h
 *
 *
 *
 *
 *
 */

#ifndef HAS_R_POLYGON_H
#define HAS_R_POLYGON_H

#include "renderer.h"
#include "game/g_polygon.h"

struct r_polygon
{
#define R_POLYGON_FIELDS \
	G_POLYGON_FIELDS \
	unsigned tric; \
	unsigned short (*triv)[3]; \

	R_POLYGON_FIELDS
};

void r_polygon(struct renderer* R, struct r_polygon* p);

#endif /* HAS_R_POLYGON_H */
