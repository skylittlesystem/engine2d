/*
 *
 *
 *
 *
 * r_box.c
 *
 *
 *
 *
 *
 */

#include "r_box.h"
#include "misc/simd.h"

void r_box(struct renderer* R, struct r_box* b)
{
	float v[4][2];
	unsigned short vi[6] = {0, 1, 2, 2, 1, 3};

	v2cpy(v[0], b->p);
	v2add(v[3], b->p, b->d);
	v2set(v[1], v[3][0], v[0][1]);
	v2set(v[2], v[0][0], v[3][1]);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, v);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, vi);
}
