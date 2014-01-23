/*
 *
 *
 *
 *
 * simd.h
 *
 *
 *
 *
 *
 */

#ifndef HAS_SIMD_H
#define HAS_SIMD_H

#include <string.h>
#include <math.h>

extern float m4I[4][4];

void v2set(float *a, float x, float y);
#define v2cpy(a, b) memcpy(a, b, sizeof(float[2]))
void v2sprod(float* restrict a, const float* b, float c);
float v2dprod(const float* a, const float* b);
void v2add(float* restrict a, const float* b, const float* c);
void v2sub(float* restrict a, const float* b, const float* c);
void v2div(float* restrict a, const float* b, const float* c);
void v2lin(float* restrict a, const float* b, const float c, const float* d, const float e);
#define v2len(a) sqrt(v2dprod(a, a))

#define m4cpy(a, b) memcpy(a, b, sizeof(float[4][4]))
void m4sprod(float* restrict A, const float* B, float c);
void m4v2prod_0(float* restrict a, const float* B, const float* c);
#define m4v2prod(a, b, c) m4v2prod_1(a, b, c)
void m4v2prod_1(float* restrict a, const float* B, const float* c);
void m4prod(float* restrict A, const float* B, const float* C);
void m4lerp(float* restrict R, const float* T, const float* dT, float t);

#endif /* HAS_SIMD_H */
