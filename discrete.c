/*
 * discrete.c
 * This is the main program, right now all the interesting stuff is in the
 * other header files.
 */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dkset.h"
#include "dkmatrix.h"
 
int main()
{
    /*
    printf("BEGIN\n");
    dkset d_a, d_b, d_c, d_head;
    d_a.is_set = false;
    d_a.value = "A";
    
    d_b.is_set = false;
    d_b.value = "B";
    
    d_c.is_set = false;
    d_c.value = "C";
    
    d_head.els = calloc(5, sizeof(dkset));
    d_head.is_set = true;
    *d_head.els = d_a;
    *(d_head.els+1) = d_b;
    *(d_head.els+2) = d_c;
    d_head.size = 3;
    
    char *s = dkset_tostr(&d_head);
    printf("%s\n", s);
    
    scanf(" %[^\n]s", s);
    dkset *d_scanned = parse_dkset(s, 0);
    printf("%s\n", dkset_tostr(d_scanned));
    
    printf("%d\n", powerset_cardinality_dkset(&d_head));
    */
    char* s = malloc(sizeof(char)*100);
    
    printf("A=\n");
    scanf(" %[^\n]s", s);
    dkmatrix* dkma = dkmatrix_parse(s);
    free(s);
    printf("\n%s", dkmatrix_tostr(dkma));  

    s = malloc(sizeof(char)*100);
    printf("B=\n");
    scanf(" %[^\n]s", s);
    dkmatrix* dkmb = dkmatrix_parse(s);
    printf("\n%s", dkmatrix_tostr(dkmb));
    
    dkmatrix *dkmaTIMESdkmb = dkmatrix_mult(dkma, dkmb);
    printf("\n%s", dkmatrixbool_tostr(dkmaTIMESdkmb));
    return EXIT_SUCCESS;
}
 
 