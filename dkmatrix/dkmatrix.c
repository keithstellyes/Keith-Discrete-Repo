/*
 * dkmatrix.c
 */

#include "dkmatrix.h"
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

/* 
 * String must be formatted as follows:
 * <columns count>x<rows count> <value> <value> <value>
 * semicolons, commas, | may be used as separators, but have no affect on parsing.
 */
dkmatrix* dkmatrix_parse(char* s)
{
    /* A useful macro here that is pointless outside the function. */
    #define READ_TOKEN() tokenread = strtok(NULL, seps)
    char *seps = " x,|;";
    int rowc, colc;
    dkmatrix *result = malloc(sizeof(dkmatrix));
    char *tokenread;
    
    tokenread = strtok(s, " x");
    sscanf(tokenread, "%d", &rowc);
    result->rowsc = rowc;
    
    /* Read number of rows */
    READ_TOKEN();
    sscanf(tokenread, "%d", &colc);
    result->colsc = colc;
    
    int *values = malloc(sizeof(int)*rowc*colc);
    result->els = values;
    
    READ_TOKEN();
    while (tokenread != NULL) {
        sscanf(tokenread, "%d", values);
        values++;
        READ_TOKEN();
    }
    return result;
    
    #undef READ_TOKEN
}

int dkmatrix_index(dkmatrix* dkm, short row, short col)
{
    int offset = row + col*(dkm->rowsc);
    
    return *((dkm->els) + offset);
}

char* dkmatrix_tostr(dkmatrix* dkm)
{
    dkmatrix _dkm = *dkm;
    /* -127 is longest sequence, +1 for a space. */
    int maxchars_perval = 5;
    /* +1 for each newline. */
    int maxchars_perrow = maxchars_perval * _dkm.colsc + 1;
    /* +1 for null char */
    int maxchars_forresult = maxchars_perrow * _dkm.rowsc + 1;
    char *result = (char*) calloc(maxchars_forresult, sizeof(char));
    
    int rowi, coli;

    for (rowi = 0; rowi < _dkm.rowsc; ++rowi){
        for (coli = 0; coli < _dkm.colsc; ++coli){
            char* buffer = calloc(sizeof(char)*maxchars_perval, sizeof(char));
            int elsidx = coli*(_dkm.rowsc);
            sprintf(buffer, "%hd", *(_dkm.els+elsidx));
            
            strcat(result, buffer);
            free(buffer);
            
            // add a space
            strcat(result, " ");
        }
        _dkm.els++;
        strcat(result, "\n");
    }
    return result;
}

bool dkmatrix_add_isdef(dkmatrix* a, dkmatrix* b)
{
    return a->rowsc == b->rowsc && a->colsc == b->colsc;
}

/* We can add matrices row-major or column-major agnostically :) */
dkmatrix* dkmatrix_add(dkmatrix* ap, dkmatrix* bp)
{
    if(!dkmatrix_add_isdef(ap, bp)) {
        return NULL;
    }
    dkmatrix a = *ap;
    dkmatrix b = *bp;
    
    dkmatrix *result = malloc(sizeof(dkmatrix));
    result->rowsc = a.rowsc;
    result->colsc = a.colsc;
    
    int valscount = a.rowsc*a.colsc;
    int *resultvalues = malloc(valscount*sizeof(dkmatrix));
    result->els = resultvalues;
    int i;
    for(i = 0; i < valscount; i++) {
        *resultvalues = (*a.els) + (*b.els);
        a.els++;
        b.els++;
        resultvalues++;
    }
    
    return result;
}

/*
 * Returns if the multiplication is defined.
 */
bool dkmatrix_mult_isdef(dkmatrix* a, dkmatrix* b)
{
    return a->colsc == b->rowsc;
}

/*
 * Matrix multplication is a very classic, well-studied problem
 * in CS for which there are many clever algorithms. I've opted for a simpler
 * one, but note that this is by no means optimized or anything.
 */
dkmatrix* dkmatrix_mult(dkmatrix* ap, dkmatrix* bp)
{
    if(!dkmatrix_mult_isdef(ap, bp)) {
        return NULL;
    }
    
    dkmatrix a = *ap;
    dkmatrix b = *bp;
    dkmatrix *result = malloc(sizeof(dkmatrix));
    
    result->rowsc = a.rowsc;
    result->colsc = b.colsc;
    int totalvaluescount = a.rowsc*b.colsc;
    
    int *resultvalues = calloc(totalvaluescount, sizeof(short));
    result->els = resultvalues;
    
    int rowi, coli;
    
    for(coli = 0; coli < result->colsc; coli++){
        for (rowi = 0; rowi < result->rowsc; rowi++){
            int j;
            for(j = 0; j < a.colsc; j++) {
                int resultvalue = *(resultvalues);
                int aval = dkmatrix_index(ap, rowi, j);
                int bval = dkmatrix_index(bp, j, coli);
                // fma?
                *(resultvalues) = resultvalue + aval * bval;
            }
            resultvalues++;
        }
    }
    return result;
}