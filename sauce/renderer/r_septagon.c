/*
 *
 *
 *
 *
 * r_septagon.c
 *
 *
 *
 *
 *
 */

#include <stdbool.h>
#include <math.h>
#include "r_septagon.h"

#define M_PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679

void r_septagon(struct renderer* R)
{
	static float vertv[8][4];
	static unsigned short idxv[7][3];
	static bool init = true;

	if (init)
	{
		unsigned i;
		float dw;

		dw = (2 * M_PI) / 7;
		vertv[0][0] = 0;
		vertv[0][1] = 0;
		vertv[0][2] = 0;
		vertv[0][3] = 1;
		for (i = 0; i < 7; ++i)
		{
			vertv[i+1][0] = cos(i*dw);
			vertv[i+1][1] = sin(i*dw);
			vertv[i+1][2] = 0;
			vertv[i+1][3] = 1;
			idxv[i][0] = 0;
			idxv[i][1] = (i % 7) + 1;
			idxv[i][2] = ((i+1) % 7) + 1;
		}

		init = false;
	}

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, vertv);
	glDrawElements(GL_TRIANGLES, 7*3, GL_UNSIGNED_SHORT, idxv);
}
