/*
 *
 *
 *
 *
 * r_polygon.c
 *
 *
 *
 *
 *
 */

#include "r_polygon.h"

void r_polygon(struct renderer* R, struct r_polygon* p)
{
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, p->vertv);
	glDrawElements(GL_TRIANGLES, p->tric * 3, GL_UNSIGNED_SHORT, p->triv);
}
