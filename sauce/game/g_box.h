/*
 *
 *
 *
 *
 * g_box.h
 *
 *
 *
 *
 *
 */

#ifndef HAS_G_BOX_H
#define HAS_G_BOX_H

/* a bounding box */
struct g_box
{
#define G_BOX_FIELDS \
	float p[2]; /* position */ \
	float d[2]; /* dimensions */ \

	G_BOX_FIELDS
};

#endif /* HAS_G_BOX_H */
