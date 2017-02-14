/*
 * dkmatrix.h
 * A column-major matrix
 * The matrix:
 * 1 2 
 * 3 4
 * 5 6
 * is stored as:
 * .rowsc = 3
 * .colsc = 2
 * *els = 1 3 5 2 4 6
 */
#pragma once
#include <stdbool.h>
/*
https://en.wikipedia.org/wiki/Matrix_representation
https://en.wikipedia.org/wiki/Multiply%E2%80%93accumulate_operation
https://en.wikipedia.org/wiki/Matrix_multiplication
 */
typedef struct dkmatrix dkmatrix;

typedef struct dkmatrix {
    signed char rowsc;
    signed char colsc;
    int *els;
} dkmatrix;

dkmatrix* dkmatrix_parse(char* s);
int dkmatrix_index(dkmatrix* dkm, short row, short col);
char* dkmatrix_tostr(dkmatrix* dkm);
char* dkmatrixbool_tostr(dkmatrix* dkm);
bool dkmatrix_add_isdef(dkmatrix* a, dkmatrix* b);
dkmatrix* dkmatrix_add(dkmatrix* ap, dkmatrix* bp);
bool dkmatrix_mult_isdef(dkmatrix* a, dkmatrix* b);
dkmatrix* dkmatrix_mult(dkmatrix* ap, dkmatrix* bp);