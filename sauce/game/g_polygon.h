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

/* note on vertices and normals:
 * vertices must be in counter-clockwise order and normals must be exterior!
 */
struct g_polygon
{
#define G_POLYGON_FIELDS \
	unsigned short vertc; /* number of vertices */ \
	float (*vertv)[2]; /* vertices */ \
	float (*normalv)[2]; /* vertices */ \
	float (*pdistv); /* plane distances */ \
	float bbox[2][2]; /* bounding box */ \
	float bcir_p[2]; /* bounding circle position */ \
	float bcir_r; /* bounding circle radius */

	G_POLYGON_FIELDS
};

#endif /* HAS_G_POLYGON_H */
