/*
 *
 *
 *
 *
 * r_box.h
 *
 *
 *
 *
 *
 */

#ifndef HAS_R_BOX_H
#define HAS_R_BOX_H

#include "renderer.h"
#include "game/g_box.h"

struct r_box
{
#define R_BOX_FIELDS \
	G_BOX_FIELDS \

	R_BOX_FIELDS
};

void r_box(struct renderer* R, struct r_box* b);

#endif /* HAS_R_BOX_H */
