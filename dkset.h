#pragma once
/*
 * dkset.h
 */
#include <stdbool.h>

typedef struct dkset dkset;

typedef struct dkset {
    // if bool is here, then our struct is bigger.
    union {
        dkset *els;
        char *value;
    };
    int size;
    bool is_set;
} dkset;

dkset* parse_dkset(char* s, int index);
char* dkset_tostr(dkset* d);
void free_dkset(dkset* d);
int powerset_cardinality_dkset(dkset* d);