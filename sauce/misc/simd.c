/*
 * Copyright (C) 2014 Igor de Sant'Ana Fontana.
 * <rogi@skylittlesystem.org>
 *
 * This file is part of engine2d.
 *
 * engine2d is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Affero General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * engine2d is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public
 * License along with engine2d.  If not, see
 * <http://www.gnu.org/licenses/>.
 *
 */

/*
 *
 *
 *
 *
 * simd.c
 *
 *
 *
 *
 *
 */

#include <math.h>
#include <stdarg.h>

#define MAT(T, m, i, j) (T)[(i) + (j)*(m)]

#define A(i, j) MAT(A, 4, i, j)
#define B(i, j) MAT(B, 4, i, j)
#define C(i, j) MAT(C, 4, i, j)
#define tmp(i, j) MAT(tmp, 4, i, j)

float m4I[4][4] =
{
	{1, 0, 0, 0},
	{0, 1, 0, 0},
	{0, 0, 1, 0},
	{0, 0, 0, 1},
};

void v2set(float *a, float x, float y)
{
	a[0] = x;
	a[1] = y;
}

void v2sprod(float* restrict a, const float* b, float c)
{
	a[0] = b[0] * c;
	a[1] = b[1] * c;
}

float v2dprod(const float* a, const float* b)
{
	return a[0] * b[0] + a[1] * b[1];
}

void v2add(float* restrict a, const float* b, const float* c)
{
	a[0] = b[0] + c[0];
	a[1] = b[1] + c[1];
}

void v2sub(float* restrict a, const float* b, const float* c)
{
	a[0] = b[0] - c[0];
	a[1] = b[1] - c[1];
}

void v2div(float* restrict a, const float* b, const float* c)
{
	a[0] = b[0] / c[0];
	a[1] = b[1] / c[1];
}

void v2lin(float* restrict a, const float* b, const float c, const float* d, const float e)
{
	a[0] = b[0] * c + d[0] * e;
	a[1] = b[1] * c + d[1] * e;
}

void m4sprod(float* restrict A, const float* B, float c)
{
	register unsigned j;
	for (j = 0; j < 4; ++j)
	{
		A(0, j) = B(0, j) * c;
		A(1, j) = B(1, j) * c;
		A(2, j) = B(2, j) * c;
		A(3, j) = B(3, j) * c;
	}
}

void m4v2prod_0(float* restrict a, const float* B, const float* c)
{
	a[0] = B(0, 0) * c[0] + B(0, 1) * c[1];
	a[1] = B(0, 1) * c[0] + B(1, 1) * c[1];
}

void m4v2prod_1(float* restrict a, const float* B, const float* c)
{
	a[0] = B(0, 0) * c[0] + B(0, 1) * c[1] + B(0, 3);
	a[1] = B(0, 1) * c[0] + B(1, 1) * c[1] + B(1, 3);
}

void m4prod(float* restrict A, const float* B, const float* C)
{
#define line_times_col(i, j) \
	( \
		B(i, 0) * C(0, j) + \
		B(i, 1) * C(1, j) + \
		B(i, 2) * C(2, j) + \
		B(i, 3) * C(3, j) \
	)

	register unsigned j;
	for (j = 0; j < 4; ++j)
	{
		A(0, j) = line_times_col(0, j);
		A(1, j) = line_times_col(1, j);
		A(2, j) = line_times_col(2, j);
		A(3, j) = line_times_col(3, j);
	}

#undef line_times_col
}

void m4lerp(float* restrict R, const float* T, const float* dT, float t)
{
	float tmp[16], one_minus_t;

	m4sprod(tmp, dT, t);

	one_minus_t = 1 - t;
	tmp(0, 0) += one_minus_t;
	tmp(1, 1) += one_minus_t;
	tmp(2, 2) += one_minus_t;
	tmp(3, 3) += one_minus_t;

	m4prod(R, tmp, T);
}
