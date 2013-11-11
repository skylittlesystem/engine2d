/*
 *
 *
 *
 *
 * g_polygon.h
 *
 *
 *
 *
 *
 */

#ifndef HAS_G_POLYGON_H
#define HAS_G_POLYGON_H

struct g_polygon
{
#define G_POLYGON_FIELDS \
	unsigned short vertc; /* number of vertices */\
	float (*vertv)[2]; /* vertices */ \
	float bbox[2][2]; /* bounding box */\
	float bradius; /* bounding circle radius */ \

	G_POLYGON_FIELDS
};

#endif /* HAS_G_POLYGON_H */
